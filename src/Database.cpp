#include <string>
class Database {
private:
    // Database connection
    sqlite3* db;
public:
    Database() {
        // Connect to the database
        if (sqlite3_open(DATABASE_FILE, &db) != SQLITE_OK) {
            std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
            return;
        } else {
            std::cout << "Database connection established" << std::endl;
        }
    }
    // Get all data from table by name of table
    std::vector<std::vector<std::string>> get_data(const std::string& table) const{
        std::vector<std::vector<std::string>> data;
        std::stringstream query;
        query << "SELECT * FROM " << table << ";";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return data;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::vector<std::string> row;
            for (int i = 0; i < sqlite3_column_count(stmt); i++) {
                const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                if (value) {
                    row.emplace_back(value);
                }
            }
            data.emplace_back(row);
        }

        sqlite3_finalize(stmt);
        return data;
    }
};