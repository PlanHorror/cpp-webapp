#include <crow.h>
#include <iostream>

int main() {
    // Set base directory for templates
    crow::mustache::set_base(".");

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([] {
        // Use TEMPLATE_DIR to load the template
        auto page = crow::mustache::load_unsafe(TEMPLATE_DIR "/template.html");
        return page.render();
    });

    app.port(8080).multithreaded().run();
}
