module;


#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxdisp.h>        // MFC Automation classes


#include <debugapi.h>
#include <cassert>
#include <chrono>
#include <array>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <filesystem>
#include <locale>



#include <GridCellBase.h>
#include <sstream>
#include <format>



#include <sqlite_orm/sqlite_orm.h>
#include <JDGridCtrl.h>
#include <optional>



export module grids_contents;


export import util;

export {
	template<int ID_COLUMN = 1>
	class GridId
	{
		CJDGridCtrl& m_grid;
	public:
		GridId(CJDGridCtrl& grid) : m_grid{ grid } {}
		int GetId(const int row) const
		{
			auto id_cs = m_grid.GetItemText(row, ID_COLUMN);
			auto id_s = util::to_string(id_cs.GetBuffer());

			if (id_s.empty())	return -1;

			int id = std::stoi(id_s);
			return id;
		}
		int GetRowForId(const int id) const
		{
			const int count = m_grid.GetRowCount();

			for (int row = 1; row < count; ++row)
			{
				int row_id = this->GetId(row);
				if (row_id == id) return row;
			}

			return -1;
		}
	};

}

export {

	struct IDisplayer
	{
		virtual void display() = 0;
		virtual ~IDisplayer() = default;
	};

	template<int N>
	struct Integral
	{
		static constexpr int Int = N;
	};


	template<int Value, typename List, int Index>
	struct Find
	{
		constexpr static bool same = std::get<Index>(List::Values).Int == Value;
		constexpr static bool Check()
		{
			// if same, found it - end recursion
			return same || Find<Value, List, Index - 1>::Check();	// not found at Index, try at Index - 1
		}
	};

	template<int Value, typename List>
	struct Find<Value, List, 0>
	{
		constexpr static bool same = std::get<0>(List::Values).Int == Value;
		constexpr static bool Check()
		{
			return same;
		}
	};


	/// <summary>
	/// is Value in values list?
	/// </summary>
	template<int...N>
	struct IntegerList
	{
		constexpr inline static std::tuple<Integral<N>...> Values;
		constexpr static unsigned Count = std::tuple_size_v<decltype(Values)>;

		template<int Value>
		constexpr static bool found()
		{
			using lista = IntegerList;

			bool found = Find<Value, lista, lista::Count - 1>::Check();
			return found;
		}
	};

	template<>
	struct IntegerList<>
	{
		template<int Value>
		constexpr static bool found()
		{
			return false;
		}
	};

#if 0
	template<int...N>
	using ColonesCols = IntegerList;

	template<int...N>
	using DollarsCols = IntegerList;
#endif


}

export {

	template<typename T>
	class GridDisplayer
	{
		CJDGridCtrl& grid;
		using Container = std::vector<std::remove_reference_t<T>>;
		Container lines;
		using ValueType = typename Container::value_type;

		// std::tuple<DataTypes...> tuple;
		std::vector<std::string>	headers;
	public:
		// template<typename ...DataTypes>
		GridDisplayer(CJDGridCtrl& grid,
			Container&& lines_,
			std::vector<std::string>&& headers_)
			: lines{ std::move(lines_) }, grid{ grid }, headers{ std::move(headers_) }
		{
			grid.SetColumnCount(headers.size() + 1);
			grid.SetRowCount(lines.size() + 1);
			grid.SetFixedRowCount();
			grid.SetFixedColumnCount();
			grid.SetHeaderSort(true);
			grid.SetSingleRowSelection(true);

			int col = 1;
			for (auto& str : headers)
			{
				auto head = util::to_cstring(str);
				grid.SetItemText(0, col, head);
				++col;
			}
		}

		template<typename ...DataTypes>
		void display(DataTypes... dts)
		{
			RECT rect;
			grid.GetWindowRect(&rect);

			for (int i = 0; i < lines.size(); ++i)
			{
				printDataInGrid(i, 1, lines[i], dts...);
			}
			grid.SetColumnWidth(0, 100);
			int width = grid.GetColumnWidth(0);
			for (int i = 0; i < headers.size(); ++i)
			{
				grid.AutoSizeColumn(i + 1);	// skip vertical headers
				width += grid.GetColumnWidth(i + 1);
			}
			auto frame = grid.GetParentFrame();
			width += GetSystemMetrics(SM_CXVSCROLL);
			grid.SetWindowPos(frame, 10, 10, width, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);
		}

	private:
		template<typename DataType>
		void printDataInGrid(int row, int col, T& z, DataType p)
		{
			auto value = z.*p;
			auto cs = format(value);
			grid.SetItemText(row + 1, col, cs);
		}


		template<typename DataType, typename ... RestDataTypes>
		void printDataInGrid(int row, int col, T& z, DataType p, RestDataTypes...qs)
		{
			printDataInGrid(row, col, z, p);
			printDataInGrid(row, ++col, z, qs...);
		}
		template<typename T>
		CString format(const T& t)
		{
			return util::to_cstring(t);
		}
		template<typename T>
		static CString format(const std::shared_ptr<T>& t)
		{
			if (t)
			{
				return util::to_cstring(*t);
			}
			return L"";
		}
	};


	inline double& extractValue(const std::unique_ptr<double>& val)
	{
		static double null_value = 0.0;
		if (val)
		{
			return *val;
		}
		return null_value;
	}
#if 0
	template<typename T> requires (!std::is_same_v<T, std::unique_ptr<double>&>)
		inline static T& extractValue(T& t)
	{
		static double null_value = 0.0;
		if (t)
			return *t;
		return null_value;
	}
#endif
	template<typename T>
	inline T& extractValue(std::optional<T>& opt)
	{
		if (opt)
			return *opt;
		return T{};
	}

	template<typename T>
	inline T& extractValue(T& val)
	{
		return val;
	}


	template<typename T, typename ColonesCols, typename DollarsCols>
	class JoinedGridDisplayer : public IDisplayer
	{
		using Container = std::vector<std::remove_reference_t<T>>;
		using RowType = typename Container::value_type;
		inline static constexpr size_t NumCols = std::tuple_size<RowType>::value;
		CJDGridCtrl& grid;
		Container					lines;
		std::vector<std::string>	headers;
	public:
		JoinedGridDisplayer(CJDGridCtrl& grid,
			Container&& lines_,
			std::vector<std::string> headers_)
			: lines{ std::move(lines_) }, grid{ grid }, headers{ std::move(headers_) }
		{
			// reset grid
			grid.SetRowCount(0);
			grid.SetColumnCount(0);
			// new grid
			grid.SetColumnCount(NumCols + 1); // headers.size() + 1);
			grid.SetRowCount(lines.size() + 1);
			grid.SetFixedRowCount();
			grid.SetFixedColumnCount();
			grid.SetHeaderSort(true);
			grid.SetSingleRowSelection(true);

			grid.m_sortingFunctions.resize(NumCols + 1);
			grid.m_sortingFunctions[0] = util::Comparison::Text;

			int col = 1;
			for (auto& str : headers)
			{
				auto head = util::to_cstring(str);
				grid.SetItemText(0, col, head);
				++col;
			}
			//static_assert(NumCols == MaxCol, "");
		}

		void display() override
		{
			RECT rect;
			grid.GetWindowRect(&rect);

			for (int i = 0; i < lines.size(); ++i)
			{
				PrintDataInGrid<0, Container, NumCols>::Apply(i, lines, grid);
			}
			grid.SetColumnWidth(0, 100);
			// int width = grid.GetColumnWidth(0);
			int width{};
			for (int i = 0; i <= headers.size(); ++i)
			{
				// grid.AutoSizeColumn(i + 1);	// skip vertical headers
				// width += grid.GetColumnWidth(i + 1);
				grid.AutoSizeColumn(i);	// skip vertical headers
				width += grid.GetColumnWidth(i);
			}
			auto frame = grid.GetParentFrame();
			width += GetSystemMetrics(SM_CXVSCROLL);
			grid.SetWindowPos(frame, 10, 10, width, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);
		}

	private:
		template<int Col, typename FieldType, typename T>
		static CString FormatCol(T& value, CJDGridCtrl& grid)
		{
			CString cs;
			if constexpr ((std::is_integral_v<FieldType> || std::is_floating_point_v<FieldType>) && !std::is_same_v<std::remove_const_t<FieldType>, bool>)
			{
				grid.m_sortingFunctions[Col + 1] = util::Comparison::Money;

				if (ColonesCols::template found<Col + 1>())
				{
					Colones c(value);
					cs = format(c);
				}
				else if (DollarsCols::template found<Col + 1>())
				{
					Dolares d(value);
					cs = format(d);
				}
				else
				{
					cs = format(value);
				}
			}
			else
			{
				grid.m_sortingFunctions[Col + 1] = util::Comparison::Text;
				cs = format(value);
			}
			return cs;
		}
		template<int Col, typename Container, unsigned NumCols>
		struct PrintDataInGrid
		{
			static void Apply(int row, const Container& z, CJDGridCtrl& grid)
			{
				CString cs;

				using FieldType = std::remove_reference_t<decltype(std::get<Col>(z[row]))>;
				FieldType* pT = nullptr;
				if constexpr (std::is_same_v<FieldType, const std::unique_ptr<double>>)
				{
					auto&& value = extractValue(std::move(std::get<Col>(z[row])));
					cs = FormatCol<Col, double>(value, grid);
				}
				else
				{
					auto&& value = std::get<Col>(z[row]);
					// auto val = extractValue(value);	// JDH

					cs = FormatCol<Col, FieldType>(value, grid);
				}
				grid.SetItemText(row + 1, Col + 1, cs);
				PrintDataInGrid<Col + 1, Container, NumCols>::Apply(row, z, grid);
			}
		};

		template<typename Container>
		struct PrintDataInGrid<NumCols, Container, NumCols>
		{
			static void Apply(int row, const Container& z, CJDGridCtrl& grid)
			{
			}
		};


		template<typename T>
		static CString format(T&& t)
		{
			// static_assert(std::is_same_v<decltype(t), T>);
			return util::to_cstring(std::forward<T>(t));
		}

		template<typename T>
		static CString format(const std::shared_ptr<T>& t)
		{
			if (t)
			{
				return util::to_cstring(*t);
			}
			return L"";
		}

		template<typename T>
		static CString format(const std::optional<T>& t)
		{
			if (t)
			{
				return util::to_cstring(*t);
			}
			return L"";
		}

	};
}
