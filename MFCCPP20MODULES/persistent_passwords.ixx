module;


#include <sqlite_orm/sqlite_orm.h>
#include <chrono>



export module persistent_passwords;


export import util;
export import date_binding;
export import sysdate_binding;
export import fixed_point;
export import date_time_binding;


export namespace persistent_passwords
{
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
		std::chrono::local_days begining_date;
		int fkey_location;
		std::chrono::local_seconds begining_timestamp;
		std::chrono::zoned_seconds zoned_point; //     zoned_time<std::chrono::seconds>

		std::string simple_dump() const
		{
			std::string str = std::to_string(id) + " - "s + password + " "s + util::to_string(begining_date) + " - " + util::to_string(begining_timestamp);

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
	using namespace std::chrono;
	using namespace std;

	using als_l = alias_l<Location>;
	using als_p = alias_p<Password>;

	auto& database()
	{
		using namespace sqlite_orm;
		using namespace std::chrono;
		using namespace std;
		static constexpr const char* db_name{ "Tokens.sqlite" };

		static int flag = 0;

		static auto storage =
			make_storage(db_name,
				make_table("Location",
					make_column("id_location", &Location::id, primary_key().autoincrement()),
					make_column("name", &Location::name),
					make_column("url", &Location::url),
					make_column("email", &Location::email)),
				make_table("Password",
					make_column("id_password", &Password::id, primary_key().autoincrement()),
					make_column("password", &Password::password),
					make_column("begin_date", &Password::begining_date),
					make_column("fkey_location", &Password::fkey_location),
					make_column("timestamp", &Password::begining_timestamp),
					foreign_key(&Password::fkey_location).references(&Location::id)));


		if (flag == 0)
		{
			flag = 1;
			storage.sync_schema(true);
		}

		return storage;
	}
	using db_type = decltype(database());

	inline db_type& db = database();

}

#if 1   // enable produces internal compiler error when used
export inline auto& test()
{
	static int ret = 0;
	return ret;
}
#endif
