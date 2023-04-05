module;

#include <compare>
#include <string>
#include <cassert>
//#include <iostream>
//#include <compare>


export module tester;

import util;
import date_time_binding;

//using namespace std::literal;
using namespace util;

export void useUtil()
{
	util::MoneytaryHelper helper;
	Colones colones{ 1000.02 };
	auto str = helper.putColones(colones);
	Dolares dolares{ 20083.5 };
	auto sstr = helper.putDollars(dolares);


	auto colon = helper.getColones("¢4,500.55");
	str = helper.putColones(colon,16);

	assert(ltrim_copy(str) == "¢4,500.55");

	auto dolar = helper.getDollars("$23,800.75");
	str = helper.putDollars(dolar,16);
	assert(ltrim_copy(str) == "$23,800.75");

	getting_money::main();

	//auto n = now();
}
