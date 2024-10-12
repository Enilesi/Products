#include "db.h"
#include <pqxx/pqxx>
#include <fstream>

void execute_query(pqxx::work& txn, const std::string& query) {
    txn.exec(query);
}

std::map<std::string, std::string> accessing_env() {
    std::map<std::string, std::string> env;
    std::ifstream file(".env");
    if (!file) {
        return env;
    }
    std::string line_read;
    while (std::getline(file, line_read)) {
        int equal_pos = line_read.find('=');
        if (equal_pos != std::string::npos) {
            std::string key = line_read.substr(0, equal_pos);
            std::string value = line_read.substr(equal_pos + 1);
            env[key] = value;
        }
    }
    return env;
}

int insert_company(pqxx::work& txn, const Company& company) {
    std::string company_name=company.get_company_name();
    std::string query = "INSERT INTO companies (name) VALUES ($1) RETURNING id;";
    pqxx::result res = txn.exec_params(query,company_name);
    return res[0][0].as<int>();
}

int insert_store(pqxx::work& txn, const Store& store) {
    std::string store_name = store.get_store_name() ;
    std::string query = "INSERT INTO stores (name) VALUES ($1) RETURNING id;";
    pqxx::result res = txn.exec_params(query,store_name);
    return res[0][0].as<int>();
}

void associate_store_with_company(pqxx::work& txn, int store_id, int company_id) {
    std::string id_company=std::to_string(company_id);
    std::string id_store=std::to_string(store_id);
    std::string query = "INSERT INTO company_stores (company_id, store_id) VALUES ($1,$2);";
    pqxx::result res = txn.exec_params(query,id_store,id_company);
}

int insert_item(pqxx::work& txn, const std::shared_ptr<Item>& item) {
    std::string item_name = item->get_name();
    int item_quantity = item->get_quantity();
    double item_price = item->get_price();
    std::string item_type = item->get_type();
    std::string item_brand = item->get_brand();
    std::string extra_info = "{}";
    
    std::string query = "INSERT INTO items (name, quantity, price, type, brand, extra_info) VALUES ($1, $2, $3, $4, $5, $6) RETURNING id;";
    pqxx::result res = txn.exec_params(query, item_name, item_quantity, item_price, item_type, item_brand, extra_info);
    return res[0][0].as<int>();
}


void associate_item_with_store(pqxx::work& txn, int item_id, int store_id) {
    std::string id_store=std::to_string(store_id);
    std::string id_item=std::to_string(item_id);
    std::string query = "INSERT INTO store_items (store_id, item_id) VALUES ($1,$2);";
    pqxx::result res = txn.exec_params(query,id_store,id_item);
}

void save_to_database(const std::shared_ptr<InventoryManager>& manager) {
    try {
        auto env = accessing_env();
        std::string connection_string = "host=" + env["DB_HOST"] +
                                        " port=" + env["DB_PORT"] +
                                        " dbname=" + env["DB_NAME"] +
                                        " user=" + env["DB_USER"] +
                                        " password=" + env["DB_PASSWORD"] +
                                        " connect_timeout=30 sslmode=prefer target_session_attrs=read-write";
        std::cout << connection_string << std:: endl;
        pqxx::connection C(connection_string);
        
        pqxx::work txn(C);

        for (const auto& company : manager->get_companies()) {
            int company_id = insert_company(txn, *company);
            for (const auto& store : company->get_stores()) {
                int store_id = insert_store(txn, *store);
                associate_store_with_company(txn, store_id, company_id);
                for (const auto& item : store->get_items()) {
                    int item_id = insert_item(txn, item);
                    associate_item_with_store(txn, item_id, store_id);
                }
            }
        }

        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
