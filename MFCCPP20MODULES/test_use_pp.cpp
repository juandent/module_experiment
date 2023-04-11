// #include <sqlite_orm\sqlite_orm.h>
#include <chrono>

import persistent_passwords;
// using namespace persistent_passwords;


#if 0  // enable produces internal compiler error
void test_db()
{
	// auto vec = db.get_all<Password>();
	// auto vec = db.get_all<Password>();
	//auto& ret = test();
	namespace chr = std::chrono;

	auto&& tz = chr::get_tzdb();
	auto&& vec = tz.zones;
	for(auto& x : vec)
	{
		
	}

}
#endif

