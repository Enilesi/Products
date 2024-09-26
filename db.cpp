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
    std::string query = "INSERT INTO companies (name) VALUES ('" 
                        + company.get_company_name() + "') RETURNING id;";
    pqxx::result res = txn.exec(query);
    return res[0][0].as<int>();
}

int insert_store(pqxx::work& txn, const Store& store) {
    std::string query = "INSERT INTO stores (name) VALUES ('" + store.get_store_name() 
                        + "') RETURNING id;";
    pqxx::result res = txn.exec(query);
    return res[0][0].as<int>();
}

void associate_store_with_company(pqxx::work& txn, int store_id, int company_id) {
    std::string query = "INSERT INTO company_stores (company_id, store_id) VALUES (" 
                        + std::to_string(company_id) + ", " + std::to_string(store_id) + ");";
    execute_query(txn, query);
}

int insert_item(pqxx::work& txn, const std::shared_ptr<Item>& item) {
    std::string extra_info = "{}";
    std::string query = "INSERT INTO items (name, quantity, price, type, brand, extra_info) VALUES ('" +
                        item->get_name() + "', " + std::to_string(item->get_quantity()) + ", " +
                        std::to_string(item->get_price()) + ", '" + item->get_type() + "', '" +
                        item->get_brand() + "', '" + extra_info + "') RETURNING id;";
    pqxx::result res = txn.exec(query);
    return res[0][0].as<int>();
}

void associate_item_with_store(pqxx::work& txn, int item_id, int store_id) {
    std::string query = "INSERT INTO store_items (store_id, item_id) VALUES ("
                         + std::to_string(store_id) + ", " + std::to_string(item_id) + ");";
    execute_query(txn, query);
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
