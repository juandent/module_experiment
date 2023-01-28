module;

#include <sqlite_orm/sqlite_orm.h>
#include <unordered_set>
#include <afx.h>
#include <afxwin.h>
#include <cassert>



export module control_contents;

using namespace sqlite_orm;



namespace control_contents
{

	export struct Posting
	{
	private:
		Posting() = default;	// singleton
		std::unordered_set<HWND> m_postingWindows;
		void AddWindow(HWND hwnd)
		{
			m_postingWindows.insert(hwnd);
		}
		bool exists(LPARAM lParam)
		{
			HWND hwnd = reinterpret_cast<HWND>(lParam);
			auto f = m_postingWindows.find(hwnd);
			if (f != m_postingWindows.end())
			{
				m_postingWindows.erase(hwnd);
				return true;
			}
			return false;
		}
	public:

		static constexpr int WindowProcNotHandled = 1;

		static Posting& get()	// access Posting only instance
		{
			static Posting posting;
			return posting;
		}

		template<typename Box>
		void PostSelChangeNotification(Box& box)
		{
			AddWindow(box.m_hWnd);
			box.GetParent()->PostMessageW(WM_COMMAND, (WPARAM)MAKELONG(box.GetDlgCtrlID(), LBN_SELCHANGE), (LPARAM)(HWND)box.m_hWnd);
		}

		LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
		{
			if (message == WM_COMMAND)
			{
				auto loword = LOWORD(wParam);
				auto hiword = HIWORD(wParam);

				if (hiword == LBN_SELCHANGE)
				{
					if (Posting::get().exists(lParam))		// this window already responded to initial LBN_SELCHANGE
					{
						return 0;
					}
				}
			}
			return WindowProcNotHandled;
		}

	};

	export template<typename Table>
	using TableStringizer = CString(*)(const Table&);

	export template<typename Database, typename Table, int Table::* keyCol, typename BoxType = CListBox>
	class BoxContents
	{
	private:
		Database& m_db;
		BoxType& m_box;
		TableStringizer<Table> line_definition;

	public:

		BoxContents(Database& db, BoxType& listbox, TableStringizer<Table>  f) : m_db{ db }, m_box(listbox), line_definition(f) {}

		void ResetContent()
		{
			m_box.ResetContent();
			m_box.SetCurSel(-1);
		}

		template<typename WhereClause>
		std::optional<Table> exists(WhereClause& clause)
		{
			using namespace sqlite_orm;

			std::optional<Table> record;
			auto e = m_db.select(columns(keyCol), where(clause));
			if (e.size() > 0)
			{
				auto id = std::get<0>(e[0]);
				record = m_db.get<Table>(id);
			}

			return record;
		}

		std::optional<Table> current()
		{
			std::optional<Table> record;
			int cur_sel = m_box.GetCurSel();
			if (cur_sel != npos)
			{
				auto id = static_cast<long long>(m_box.GetItemData(cur_sel));
				record = m_db.get<Table>(id);
			}
			return record;
		}
		int GetCurSel() const
		{
			return m_box.GetCurSel();
		}
		void SetCurSel(int index) const
		{
			m_box.SetCurSel(index);
		}

		std::optional<Table> select_by_pk(int pk)
		{
			std::optional<Table> record;
			if (pk < 0)
			{
				m_box.SetCurSel(npos);
				return record;
			}
			int index = find_index_of_pk(pk);
			if (index != npos)
			{
				m_box.SetCurSel(index);
				record = m_db.get<Table>(pk);

				Posting::get().PostSelChangeNotification(m_box);
			}
			else
			{
				m_box.SetCurSel(npos);
			}
			return record;
		}

		int get_pk(Table& record)
		{
			return record.*keyCol;
		}

		int get_pk(std::optional<Table>& record)
		{
			return record ? record.*keyCol : -1;
		}

		// will check if record exists in listbox and do nothing if so
		int insert_into_listbox(Table& record)
		{
			int index = find_in_listbox(record);
			if (index != npos)	return index;	// exists already, do nothing

			auto displayStr = line_definition(record);
			index = m_box.AddString(displayStr);
			m_box.SetItemData(index, get_pk(record));
			m_box.SetCurSel(index);
			return index;
		}

		bool delete_from_box(Table& record)
		{
			int index = find_index_of_pk(record);
			if (index != npos)
			{
				m_box.DeleteString(index);
				return true;
			}
			return false;
		}

		int find_index_of_pk(Table& record) const
		{
			const int pk = record.*keyCol;
			return find_index_of_pk(pk);
		}
		int find_index_of_pk(const int pk) const
		{
			int index = m_box.GetCount();
			while (index >= 0)
			{
				auto id = m_box.GetItemData(index);
				if (pk == id)
				{
					return index;
				}
				--index;
			}
			return npos;
		}

		void loadLB(const std::vector<Table>& records)
		{
			m_box.ResetContent();
			moveVectorIntoBox(records);
		}
		constexpr static const int npos = -1;
	private:
		template<typename T>
		void moveVectorIntoBox(T& vec)
		{
			m_box.ResetContent();
			for (auto& record : vec)
			{
				auto displayStr = line_definition(record);
				int index = m_box.AddString(displayStr);
				m_box.SetItemData(index, record.*keyCol);
				// SetCurSel(index);
			}
			// ???
			SetCurSel(npos);
		}
	};

	export class RadioButtonGroup
	{
		const std::vector<CButton*> m_radios;
		const std::vector<int> m_values;
	public:
		RadioButtonGroup(std::initializer_list<CButton*> list, std::initializer_list<int> values)
			: m_radios{ list }, m_values{ values }
		{
		}
		void Initialize()
		{
			m_radios[0]->SetCheck(BST_CHECKED);
		}
		int get_value() const
		{
			for (int idx = 0; idx < m_radios.size(); ++idx)
			{
				if (m_radios[idx]->GetCheck())
				{
					int value = m_values[idx];
					return value;
				}
			}
			throw std::logic_error("There must be 1 selected radio button in a group");
		}
		void set_value(int idx_select)
		{
			for (int idx = 0; idx < m_radios.size(); ++idx)
			{
				int value = m_values[idx];
				m_radios[idx]->SetCheck(value == idx_select);
			}
		}
		RadioButtonGroup& operator<<(int idx_select)
		{
			set_value(idx_select);
			return *this;
		}
		RadioButtonGroup& operator>>(int& value)
		{
			value = get_value();
			return *this;
		}
	};



}
