module;

#include <sqlite_orm/sqlite_orm.h>
#include <cassert>
#include <string>
#include <iostream>
#include <chrono>
#include <format>
#include <sstream>
#include <regex>



export module date_binding;


#if __cpp_lib_chrono >= 201907L && __cpp_lib_format >= 201907L

///////////////////////////////
/// local_days binding as TEXT
/// ///////////////////////////


/*
 * need to get local time via zoned_time; this is the true today() function because it uses current_zone()
 */

export  std::chrono::local_days today() {
        namespace chr = std::chrono;

        auto now_point = chr::system_clock::now();

        auto tpLoc = chr::zoned_time{ chr::current_zone(), now_point }.get_local_time();
        auto day = chr::floor<chr::days>(tpLoc);

        return day;
    }

    /**
     *  This is the date we want to map to our sqlite db.
     *  Let's make it `TEXT`
     */

     //  also we need transform functions to make string from local_days
    std::string localDaysToString(std::chrono::local_days pt) {
        auto r = std::format("{:%F}", pt);
        return r;
    }

    /**
     *  and local_days from string. This function has nullable result cause
     *  string can be an invalid local_days.
     *  Of course we won't allow this to happen but as developers we must have
     *  a scenario for this case.
     *  These functions are just helpers. They will be called from several places
     *  that's why I placed it separatedly. You can use any transformation type/form
     */
    std::optional<std::chrono::local_days> localDaysFromString(const std::string& s) {
        using namespace std::literals;
        using namespace std::chrono;

        std::stringstream ss{ s };
        std::chrono::local_days tt;
        ss >> std::chrono::parse("%F"s, tt);
        if (!ss.fail()) {
            return { tt };
        }
        return std::nullopt;
    }

    /**
     *  This is where magic happens. To tell sqlite_orm how to act
     *  with local_days we have to create a few service classes
     *  specializations (traits) in sqlite_orm namespace.
     */
export  namespace sqlite_orm {

        /**
         *  First of all is a type_printer template class.
         *  It is responsible for sqlite type string representation.
         *  We want local_days to be `TEXT` so let's just derive from
         *  text_printer. Also there are other printers: real_printer and
         *  integer_printer. We must use them if we want to map our type to `REAL` (double/float)
         *  or `INTEGER` (int/long/short etc) respectively.
         */
        template<>
        struct type_printer<std::chrono::local_days> : public text_printer {};

        /**
         *  This is a binder class. It is used to bind c++ values to sqlite queries.
         *  Here we have to create local_days string representation and bind it as string.
         *  Any statement_binder specialization must have `int bind(sqlite3_stmt*, int, const T&)` function
         *  which returns bind result. Also you can call any of `sqlite3_bind_*` functions directly.
         *  More here https://www.sqlite.org/c3ref/bind_blob.html
         */
        template<>
        struct statement_binder<std::chrono::local_days> {

            int bind(sqlite3_stmt* stmt, int index, const std::chrono::local_days& value) const {
                return statement_binder<std::string>().bind(stmt, index, localDaysToString(value));
            }
        };

        /**
         *  field_printer is used in `dump` and `where` functions. Here we have to create
         *  a string from mapped object.
         */
        template<>
        struct field_printer<std::chrono::local_days> {
            std::string operator()(const std::chrono::local_days& t) const {
                return localDaysToString(t);
            }
        };

        /**
         *  This is a reverse operation: here we have to specify a way to transform string received from
         *  database to our local_days object. Here we call `localDaysFromString` and throw `std::runtime_error` if it returns null.
         *  Every `row_extractor` specialization must have `extract(const char*)`, `extract(sqlite3_stmt *stmt, int columnIndex)`
         *	and `extract(sqlite3_value* value)`
         *  functions which return a mapped type value.
         */
        template<>
        struct row_extractor<std::chrono::local_days> {
            std::chrono::local_days extract(const char* row_value) const {
                if (row_value) {
                    auto sd = localDaysFromString(row_value);
                    if (sd) {
                        return sd.value();
                    }
                    else {
                        throw std::runtime_error("incorrect date string (" + std::string(row_value) + ")");
                    }
                }
                else {
                    // ! row_value
                    throw std::runtime_error("incorrect date string (nullptr)");
                }
            }

            std::chrono::local_days extract(sqlite3_stmt* stmt, int columnIndex) const {
                auto str = sqlite3_column_text(stmt, columnIndex);
                return this->extract((const char*)str);
            }
            std::chrono::local_days extract(sqlite3_value* row_value) const {
                auto characters = (const char*)(sqlite3_value_text(row_value));
                return extract(characters);
            }
        };
    }

    ////////////////////////////////
    /// end local_days binding as TEXT
    ////////////////////////////////

#endif
