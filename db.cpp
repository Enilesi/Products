#include <pqxx/pqxx>
#include <iostream>
#include <fstream>
#include <map>
#include <string>


std::map<std::string, std::string> accessing_env(){
    std::map<std::string,std::string> env;
    std::ifstream file(".env");
    if(!file){
        std::cerr << "Opening .env file error" << std::endl;
        return env;
    }
    
    std::string line_read;
    while(std::getline(file,line_read)){
        int equal_pos=line_read.find('=');

        if (equal_pos != std::string::npos){
            std::string key=line_read.substr(0,equal_pos);
            std::string value=line_read.substr(equal_pos+1);
            env[key]=value;
        }
    }
    return env;
}


int main() {
    try {
        auto env = accessing_env();
        std::string connection_string = "host=" + env["DB_HOST"]  +
                                        " port=" + env["DB_PORT"] +
                                        " dbname=" + env["DB_NAME"] +
                                        " user=" + env["DB_USER"] + 
                                        " password=" + env["DB_PASSWORD"] + 
                                        " connect_timeout=30 sslmode=prefer target_session_attrs=read-write";
        
        pqxx::connection C(connection_string);
        if (C.is_open()) {
            pqxx::nontransaction N(C);
            pqxx::result R(N.exec("SELECT * FROM companies"));

            for (auto row : R) {
                std::cout << row[1].as<std::string>() << std::endl;
            }
        } else {
            std::cerr << "Can't open database" << std::endl;
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
