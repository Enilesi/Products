#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>



class Item {
private:
    int item_id;
    std::string item_name;
    int quantity;
    double price;

public:
    Item(std::string i_n = "", int q = 0, double p = 0.0, int i = 0) 
        : item_id(i), item_name(i_n), quantity(q), price(p) {}

    virtual void display_inventory() const {
        std::cout << "Item ID: " << item_id
                  << ", Name: " << item_name
                  << ", Quantity: " << quantity
                  << ", Price: $" << price << std::endl;
    }

    virtual std::string get_type() const { return "Generic"; }
    virtual std::string get_brand() const { return "Generic"; }

    void modify_quantity(int amount) {
        quantity += amount;
    }

    const std::string& get_name() const { return item_name; }
    int get_id() const { return item_id; }
    int get_quantity() const { return quantity; }
    double get_price() const { return price; }
};

class Store {
private:
    int store_id;
    std::string store_name;
    std::vector<std::shared_ptr<Item>> items;

public:
    Store(std::string s_n = "", int s_i = 0) : store_id(s_i), store_name(s_n) {}

    void display_store_items() const {
        std::cout << "Store ID: " << store_id
                  << ", Name: " << store_name << std::endl;
        for (const auto& item : items) {
            item->display_inventory();
        }
    }

    void add_item(std::shared_ptr<Item> item) {
        items.push_back(item);
    }

    bool remove_item(int id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->get_id() == id) {
                items.erase(it);
                return true;
            }
        }
        return false;
    }

    int get_id() const { return store_id; }
    const std::string& get_store_name() const { return store_name; }
    const std::vector<std::shared_ptr<Item>>& get_items() const { return items; }
};

class Company {
private:
    int company_id;
    std::string company_name;
    std::vector<std::shared_ptr<Store>> stores;

public:
    Company(std::string c_n = "", int c_i = 0) : company_id(c_i++), company_name(c_n) {}

    void display_company_stores() const {
        std::cout << "Company ID: " << company_id
                  << ", Name: " << company_name << std::endl;
        for (const auto& store : stores) {
            store->display_store_items();
        }
    }

    void add_store(std::shared_ptr<Store> store) {
        stores.push_back(store);
    }

    void remove_store(int id) {
        for (auto it = stores.begin(); it != stores.end(); ++it) {
            if ((*it)->get_id() == id) {
                stores.erase(it);
                return;
            }
        }
    }

    const std::string& get_company_name() const { return company_name; }
    int get_company_id() const { return company_id; }
    const std::vector<std::shared_ptr<Store>>& get_stores() const { return stores; }
};

class InventoryManager {
private:
    static std::shared_ptr<InventoryManager> instance;
    std::vector<std::shared_ptr<Company>> companies;

    InventoryManager() {}

public:
    static std::shared_ptr<InventoryManager> get_instance() {
        if (!instance) {
            instance = std::shared_ptr<InventoryManager>(new InventoryManager());
        }
        return instance;
    }

    void add_company(std::shared_ptr<Company> company) {
        companies.push_back(company);
    }

    void remove_company(int id) {
        auto it = std::remove_if(companies.begin(), companies.end(), [id](std::shared_ptr<Company> company) {
            return company->get_company_id() == id;
        });
        if (it != companies.end()) {
            companies.erase(it);
        }
    }

    void display_all_companies() const {
        for (const auto& company : companies) {
            company->display_company_stores();
        }
    }

    const std::vector<std::shared_ptr<Company>>& get_companies() const {
        return companies;
    }
};

// The above line has been removed

class Laptop : public Item {
private:
    std::string brand;
    std::string processor;
    int ram;
    int storage;

public:
    Laptop(std::string i_n, int q, double p, std::string b, std::string proc, int r, int s)
        : Item(i_n, q, p), brand(b), processor(proc), ram(r), storage(s) {}

    void display_inventory() const override {
        std::cout << "Laptop - ID: " << get_id()
                  << ", Name: " << get_name()
                  << ", Brand: " << brand
                  << ", Processor: " << processor
                  << ", RAM: " << ram << "GB"
                  << ", Storage: " << storage << "GB"
                  << ", Quantity: " << get_quantity()
                  << ", Price: $" << get_price() << std::endl;
    }

    std::string get_type() const override { return "Laptop"; }
    std::string get_brand() const override { return brand; }
};

class ItemFactory {
public:
    static std::shared_ptr<Item> create_item(std::string type, std::string name, int quantity, double price, std::string brand, std::string spec1 = "", int spec2 = 0, bool spec3 = false) {
        if (type == "Laptop") {
            return std::make_shared<Laptop>(name, quantity, price, brand, spec1, spec2, spec3);
        }
        return nullptr;
    }
};

#endif
