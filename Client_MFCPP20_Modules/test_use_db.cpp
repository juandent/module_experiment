// #include "pch.h"
#include <chrono>
// #include "Client_MFCPP20_Modules.h"
// #include "ControlsTest.h"



#include <sqlite_orm\sqlite_orm.h>
// #include "..\GridCtrl\JDGridCtrl.h"

import persistent_passwords;
// import control_contents;
// import date_binding;
// import orm_util;
// import grids_contents;
// using namespace orm_util;
using namespace persistent_passwords;
// using namespace sqlite_orm;
// using namespace control_contents;

#if 1  // internal compiler error
inline auto& db_ = persistent_passwords::database();
#endif

void test_db()
{
	auto passwords = db.get_all<Password>();

	Location loc{ 1, "Amazon", "www.amazon.com", "juan@juandent.com" };


	db.replace(loc);


	std::chrono::sys_days hoy = today();
	std::chrono::local_seconds ahora = timestamp();

	Password pwd{ -1, "xy65", hoy, 1,  ahora };

	pwd.id = db.insert(pwd);

	auto str = pwd.simple_dump();

	db_.get_all<Password>();

	// db_type db = database();
	// auto vec = db.get_all<Password>();
	//auto vec = database().get_all<Password>();

}