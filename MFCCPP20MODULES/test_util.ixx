module;

#include <compare>
//#include <string>
//#include <iostream>
//#include <compare>


export module tester;

import util;


export void useUtil()
{
#if 0
	monetary::MoneytaryAssistent ast;
	Colones money{ 1000.02 };
	auto str2 = ast.put(money, 16);
	auto str = ast.putNumberAsCR(money, 16);
	auto dlrs = ast.putDollars(money, 16);
#endif

	util::MoneytaryHelper helper;
	Colones colones{ 1000.02 };
	auto str = helper.putColones(colones, 16);
	Dolares dolares{ 2008.5 };
	auto sstr = helper.putDollars(dolares, 16);

	//util::MoneytaryHelper helper;
	// util::MoneytaryAssistent helper;
	// Colones money{ 1000.02 };
	// auto ex = util::to_string(money);
	// auto str = helper.put(money,16);
	//auto str = helper.putColones(money, 16);

//	Money col = helper.getColones(str);

	auto colon = helper.getColones("4,500.55");
	str = helper.putColones(colon, 16);

	auto dolar = helper.getDollars("$23,800.75");
	str = helper.putDollars(dolar, 16);
}
