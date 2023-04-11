
#include <chrono>
#include <iostream>
#include <sstream>
#include <ctime>



#include <sqlite_orm\sqlite_orm.h>
// #include "..\GridCtrl\JDGridCtrl.h"

import persistent_passwords;
using namespace persistent_passwords;

#if 1  // internal compiler error
inline auto& db_ = persistent_passwords::database();
#endif

namespace chr = std::chrono;


chr::local_seconds
to_local_time(std::tm const& t)
{
	using namespace std::chrono;
	return local_days{ year{t.tm_year + 1900} / (t.tm_mon + 1) / t.tm_mday } +
		hours{ t.tm_hour } + minutes{ t.tm_min } + seconds{ t.tm_sec };
}


std::tm
to_tm(chr::zoned_seconds tp)
{
	using namespace std;
	using namespace std::chrono;
	auto lt = tp.get_local_time();	// extract local_time
	auto ld = floor<days>(lt);		// extract local_day

	auto dd = lt - ld;		// time since midnight
	hh_mm_ss<seconds> tod{ dd }; 	// extract time fields

	year_month_day ymd{ ld };		// convert to year_month_day
	tm t{};
	t.tm_sec = tod.seconds().count();
	t.tm_min = tod.minutes().count();
	t.tm_hour = tod.hours().count();
	t.tm_mday = (ymd.day() - 0d).count();
	t.tm_mon = (ymd.month() - January).count();
	t.tm_year = (ymd.year() - 1900y).count();
	t.tm_wday = (weekday{ ld } - Sunday).count();
	t.tm_yday = (ld - local_days{ ymd.year() / January / 1 }).count();
	t.tm_isdst = tp.get_info().save != minutes{ 0 };
	return t;
}


void local_system()
{
	namespace chr = std::chrono;
	using namespace std::literals;


	const auto local_time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
	std::ostringstream o;
	o << local_time << '\n';
	auto o_str = o.str();



	auto now = chr::system_clock::now();
	auto today = chr::floor<chr::days>(now);

	chr::year_month_day xx{ today };
	auto z= chr::local_days{ xx };

	auto day = 2021y / 9 / chr::Friday[chr::last];

	chr::local_seconds tpOfficeParty{ chr::local_days{day} - 6h };  // 18:00 the day before
	chr::sys_seconds tpCompanyParty{ chr::sys_days{day} + 17h };    // 17:00 that day
	std::ostringstream os;

	auto zt = chr::zoned_time{ "Europe/Berlin", tpOfficeParty };
	std::tm tm = to_tm(zt);
	auto lt = to_local_time(tm);

	

	os << "Berlin office and Company Party:\n";

	os << " " << chr::zoned_time{ "Europe/Berlin", tpOfficeParty } << "\n";
	os << " " << chr::zoned_time{ "Europe/Berlin", tpCompanyParty } << "\n";

	os << "New York Office and Company party:\n";

	os << " " << chr::zoned_time{ "America/New_York", tpOfficeParty } << "\n";
	os << " " << chr::zoned_time{ "America/New_York", tpCompanyParty } << "\n";

	auto str = os.str();


	auto sysTp = chr::floor<chr::seconds>(chr::system_clock::now());
	auto locTp = chr::current_zone()->to_local(sysTp);
	std::ostringstream oss;
	oss << "sysTp " << sysTp << "\n";
	oss << "locTp " << locTp << "\n";
	// same time_point in different time zones

}


void test_db()
{
	local_system();


	auto passwords = db.get_all<Password>();

	Location loc{ 1, "Amazon", "www.amazon.com", "juan@juandent.com" };


	db.replace(loc);


	std::chrono::local_days hoy = today();
	chr::year_month_day ymd{ hoy };
	std::chrono::local_seconds ahora = date_time();

	Password pwd{ -1, "xy65", hoy, 1,  ahora };

	pwd.id = db.insert(pwd);

	auto str = pwd.simple_dump();

//	db_.get_all<Password>();

	// db_type db = database();
	// auto vec = db.get_all<Password>();
	//auto vec = database().get_all<Password>();

}
