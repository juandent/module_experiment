module;


#include <sqlite_orm/sqlite_orm.h>
#include <chrono>


export module storage;

import date_binding;
import fixed_point;


export {


	template<typename Storage>
	class orm
	{
		Storage& m_storage;
		std::string m_db_file_name;
	public:
		orm(Storage& storage, std::string db_file_name) : m_storage(storage), m_db_file_name(std::move(db_file_name)) {}
		const std::string& file_name() const { return m_db_file_name; }
		Storage& storage() { return m_storage; }
	};

}