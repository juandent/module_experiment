#pragma once


#include "Persistent_passwords.h"

class LocationGrid : public CJDGridCtrl
{
	DECLARE_DYNCREATE(LocationGrid)

	const GridId<> m_grid_id;
	std::unique_ptr<IDisplayer> m_displayer;
public:
	LocationGrid() : m_grid_id{ *this } {}

	template<typename T>
	void Initialize(T t)
	{
		auto lines = db.select(columns(
			alias_column<als_l>(&Location::id),
			alias_column<als_l>(&Location::name),
			alias_column<als_l>(&Location::url),
			alias_column<als_l>(&Location::email)),

			where(t),
			order_by(alias_column<als_l>(&Location::name)).asc().collate_nocase());


		std::vector<std::string> headers{ "ID LOCATION", "NAME", "URL", "EMAIL" };

		m_displayer.reset(new JoinedGridDisplayer<decltype(lines[0]), IntegerList<>, IntegerList<>>(*this, std::move(lines), std::move(headers)));
		m_displayer->display();
	}

	int GetIdFromRow(int row) const { return m_grid_id.GetId(row); }
	int GetRowForId(int id) const { return m_grid_id.GetRowForId(id); }
};

