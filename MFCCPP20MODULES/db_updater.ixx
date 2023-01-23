module;

#pragma once
#include <sqlite_orm/sqlite_orm.h>


export module db_updater;


export {

    template<typename Storage>
    struct DbUpdater {
        sqlite3* db = nullptr;
        Storage& storage;

        DbUpdater(Storage& storage) :storage(storage) {
            storage.on_open = [&db = this->db](sqlite3* p) {
                db = p;
            };
        }
        ~DbUpdater() {
            storage.on_open = nullptr;
        }
        void update() {
            bool opened = storage.is_opened() || !storage.get_autocommit();
            if (opened)  throw std::logic_error("Schema update cannot be done in an open connection or inside an active transaction!");
            try {
                storage.open_forever();

                set_pragma("foreign_keys", false, db);

                storage.begin_exclusive_transaction();

                auto res = storage.sync_schema_simulate(true);
                res = storage.sync_schema(true);

                set_pragma("foreign_keys", true, db);
                storage.commit();
            }
            catch (const std::exception& ex) {
                auto s = ex.what();
                std::ignore = s;
                set_pragma("foreign_keys", true, db);
                storage.rollback();
                throw;
            }

        }

    private:
        template<class T>
        void set_pragma(const std::string& name, const T& value, sqlite3* db = nullptr) {
            std::stringstream ss;
            ss << "PRAGMA " << name << " = " << value;
            sqlite_orm::internal::perform_void_exec(db, ss.str());
        }
    };

}
