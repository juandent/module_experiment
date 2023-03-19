module;

//#include "pch.h"

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxdisp.h>        // MFC Automation classes


#include <debugapi.h>
#include <cassert>
#include <chrono>
#include <array>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <filesystem>
#include <locale>



#include <GridCellBase.h>
#include <sstream>
#include <format>


export module monetary;
import util;
import fixed_point;
import date_as_string;


// redundant - please eliminate when compiler stops giving internal error
export namespace monetary {

	using namespace std;

	struct MoneytaryAssistent
	{
	private:
		util::costaRicaNumPunct* m_posSignEliminator;
		locale m_usLoc;
		locale m_crLoc;
		ostringstream m_usOs;
		ostringstream m_crOs;
		istringstream m_usIs;
		istringstream m_crIs;

		const money_put<char>& m_usMoney_put;
		const money_put<char>& m_crMoney_put;

		const num_put<char>& m_usNumber_put;
		const num_put<char>& m_crNumber_put;

		ostringstream& setw(ostringstream& os, int size)
		{
			using type = decltype(std::setw(size));
			type s = std::setw(size);
			os << s;
			return os;
		}
	public:
		MoneytaryAssistent()
			: m_posSignEliminator{ new util::costaRicaNumPunct{ "" } },
#ifndef PLAYING_WITH_LOCALES
			m_usLoc{ "en-US" }, m_crLoc{ locale{"sp-ES"}.combine<numpunct<char>>(locale{"sp-CR"}), //, m_posSignEliminator
			},
#else
			m_usLoc{ "en-US" }, m_crLoc{ m_usLoc, m_posSignEliminator },
#endif
			m_usMoney_put{ use_facet<money_put<char>>(m_usLoc) }, m_crMoney_put{ use_facet<money_put<char>>(m_crLoc) },
			m_usNumber_put{ use_facet<num_put<char>>(m_usLoc) }, m_crNumber_put{ use_facet<num_put<char>>(m_crLoc) }
		{
			m_usOs << showbase;
			m_usOs.imbue(m_usLoc);

			m_crOs << showbase;
			m_crOs.imbue(m_crLoc);

			m_usIs.imbue(m_usLoc);
			m_crIs.imbue(m_crLoc);


#ifdef PLAYING_WITH_LOCALES
			//m_crLoc = m_crLoc.combine<numpunct<char>>(locale{"sp-ES"});
			//m_crOs.imbue(m_crLoc);
			//m_crIs.imbue(m_crLoc);
#endif
		}
#if 0	// just testing
		string put(Money money, int width)
		{
			// m_crOs.str("");
			// m_crOs << right << setw(width);
			ostringstream usOs{ "   " };

			usOs.imbue(std::locale("en-US"));

			using type = decltype(std::setw(width));
			type s = std::setw(width);
			usOs << s;
			usOs << std::right;

			//m_crOs << std::right;
			//m_crOs << "";
			//m_crOs << std::setw(width);
			auto& f = std::use_facet<std::money_put<char>>(usOs.getloc());
			f.put(usOs, false, usOs, ' ', 3400.55);


//			m_usMoney_put.put(m_crOs, false, m_crOs, ' ', 100 * money.getAsLongDouble());
			//auto temp = m_crOs.str();
			return "Hi";
		}
#endif

		string putNumberAsCR(Money money, int width)
		{
			m_crOs.str("");
			setw(m_crOs, width);
			m_crOs << right;											// << setw(width);
			auto value = money.rep() / (long double)money.scale_;
			m_crNumber_put.put(m_crOs, m_crIs, ' ', value);
			auto temp = m_crOs.str();
			return temp;
		}
		string putColones(Money money, int width)
		{
			m_crOs.str("");
			setw(m_crOs, width);
			m_crOs << right;

			m_crMoney_put.put(m_crOs, false, m_crOs, ' ', 100 * money.getAsLongDouble()); //   money.rep()
			auto temp = m_crOs.str();
			return temp;
		}
		string putDollars(Money money, int width)
		{
			m_usOs.str("");
			setw(m_usOs, width);
			m_usOs << right;
			m_usMoney_put.put(m_usOs, false, m_usOs, ' ', 100 * money.getAsLongDouble());	// money.rep());
			auto temp = m_usOs.str();
			return temp;
		}
		Money getColones(const std::string& asColones)
		{
			m_crIs.str(asColones);
			auto readVal = 0.0L;
			m_crIs >> get_money(readVal);
			return Money(readVal);
		}
		Money getDollars(const std::string& asDollars)
		{
			m_crIs.str(asDollars);
			auto readVal = 0.0L;
			m_crIs >> get_money(readVal);
			return Money(readVal);
		}
	};
}
