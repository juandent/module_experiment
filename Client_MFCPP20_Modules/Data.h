#pragma once

#include <sqlite_orm/sqlite_orm.h>
#include <chrono>


import util;


using namespace std::string_literals;

enum class AcknowledgementType
{
	None, Partial, Full
};


struct Location
{
	int id;
	std::string name;
	std::string url;
	std::string email;

	std::string simple_dump() const
	{
		std::string str = std::to_string(id) + " - "s + name + " - "s + url + " " + email;
		return str;
	}

	std::string getPassword(std::chrono::year_month_day ymd);

};


struct Password
{
	int id;
	std::string password;
	std::chrono::sys_days begining_date;
	int fkey_location;

	std::string simple_dump() const
	{
		std::string str = std::to_string(id) + " - "s + password + " "s + Util::to_string(begining_date);
		return str;
	}
};

template<typename T>
struct is_persistent
{
	static constexpr bool value = false;
};

template<>
struct is_persistent<Location>
{
	static constexpr bool value = true;
};

template<>
struct is_persistent<Password>
{
	static constexpr bool value = true;
};

/////////////////////////////////////////////////////////////////
///
///

using namespace sqlite_orm;

using als_l = alias_l<Location>;
using als_p = alias_p<Password>;



inline auto getPasswordWhereClauseAlias(int location_id)
{
	using namespace sqlite_orm;
	auto passwordWhere = (c(alias_column<als_p>(&Password::fkey_location)) == location_id);
	return passwordWhere;
}

inline auto getPasswordWhereClauseNoAlias(int location_id)
{
	using namespace sqlite_orm;
	auto passwordWhere = (c(&Password::fkey_location) == location_id);
	return passwordWhere;
}


namespace orm
{
	using namespace sqlite_orm;
	using namespace std::chrono;
	using namespace std;

	inline auto& storage()
	{
		using namespace sqlite_orm;
		using namespace std::chrono;
		using namespace std;
		static constexpr const char* db_name{ "C:\\Users\\juan_\\OneDrive\\Tokens\\Client.sqlite" };

		static int flag = 0;

		static auto storage =
			make_storage(db_name,
				make_table("Location",
					make_column("id_location", &Location::id, autoincrement(), primary_key()),
					make_column("name", &Location::name),
					make_column("url", &Location::url),
					make_column("email", &Location::email)),
				make_table("Password",
					make_column("id_password", &Password::id, autoincrement(), primary_key()),
					make_column("password", &Password::password),
					make_column("begin_date", &Password::begining_date),
					make_column("fkey_location", &Password::fkey_location),
					foreign_key(&Password::fkey_location).references(&Location::id)));


		if (flag == 0)
		{
			flag = 1;
			storage.sync_schema(true);
		}

		return storage;
	}

}