#include <crow.h>
#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "src/DataBase.cpp"

// Function to query all usernames from the users table
std::vector<std::string> get_usernames(sqlite3* db) {
    std::vector<std::string> usernames;
    const char* query = "SELECT username FROM users;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return usernames;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (username) {
            usernames.emplace_back(username);
        }
    }

    sqlite3_finalize(stmt);
    return usernames;
}

int main() {
    crow::SimpleApp app;
    // Define the database connection
    const Database db;

    // Route for index.html
    CROW_ROUTE(app, "/")
    ([db]() {
        crow::mustache::context ctx;

        // Get all user data from the users table
        std::vector<std::vector<std::string>> data = db.get_data("users");


        // Pass the usernames to the template context
        ctx["users"] = data;
        // Debugging
        for (const auto& row : data) {
            for (const auto& value : row) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
        // Render the template
        auto page = crow::mustache::load_unsafe(TEMPLATE_DIR "/index.html");
        return page.render(ctx);
    });

    app.port(8080).multithreaded().run();


    return 0;
}
