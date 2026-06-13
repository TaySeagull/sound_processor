#include "application.h"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    Application app;
    int result = 0;
    
    try {
        app.configure();
        result = app.start(argc, argv);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;

    } catch (...) {
        std::cerr << "Unknown error occurred\n";
        return 1;
    }
    
    return result;
}