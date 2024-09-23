#include <iostream>
#include <cstdlib> 

void load_env_file(const std::string& filename);

int main() {
    load_env_file(".env");
    const char* db_host = std::getenv("DB_HOST");
    const char* db_port = std::getenv("DB_PORT");
    const char* db_name = std::getenv("DB_NAME");
    const char* db_user = std::getenv("DB_USER");
    const char* db_password = std::getenv("DB_PASSWORD");

    if (!db_host || !db_port || !db_name || !db_user || !db_password) {
        std::cerr << "One or more environment variables are not set." << std::endl;
        return 1;
    }

    std::cout << "Connecting to database at " << db_host << ":" << db_port << std::endl;
    std::cout << "Database: " << db_name << ", User: " << db_user << std::endl;

    
    return 0;
}
