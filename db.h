#ifndef DB_H
#define DB_H

#include <pqxx/pqxx>
#include <map>
#include <memory>
#include "products.h"

void execute_query(pqxx::work& txn, const std::string& query);
std::map<std::string, std::string> accessing_env();
int insert_company(pqxx::work& txn, const Company& company);
int insert_store(pqxx::work& txn, const Store& store);
void associate_store_with_company(pqxx::work& txn, int store_id, int company_id);
int insert_item(pqxx::work& txn, const std::shared_ptr<Item>& item);
void associate_item_with_store(pqxx::work& txn, int item_id, int store_id);
void save_to_database(const std::shared_ptr<InventoryManager>& manager);

#endif
