#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class Item {
private:
    static int next_id;
    int item_id;
    std::string item_name;
    int quantity;
    double price;
    int stores_number = 0;

public:
    Item(std::string i_n = "", int q = 0, double p = 0.0)
        : item_id(next_id++), item_name(i_n), quantity(q), price(p) {}

    void display_inventory() const {
        std::cout << "Item ID: " << item_id 
                  << ", Name: " << item_name 
                  << ", Quantity: " << quantity 
                  << ", Price: $" << price << std::endl;
    }

    void modify_quantity(int amount) {
        quantity += amount;
    }

    void add_store_to_the_number() {
        ++stores_number;
    }

    void remove_a_store_from_the_number() {
        --stores_number;
    }

    const std::string& get_name() const { return item_name; }
    int get_id() const { return item_id; }
    int get_quantity() const { return quantity; }
    double get_price() const { return price; }
    int get_stores_number() const { return stores_number; }
};

int Item::next_id = 1;

class Store {
private:
    static int next_id;
    int store_id;
    std::string store_name;
    std::vector<std::shared_ptr<Item>> items;

public:
    Store(std::string s_n = "") : store_id(next_id++), store_name(s_n) {}

    void display_store_items() const {
        std::cout << "Store ID: " << store_id 
                  << ", Name: " << store_name << std::endl;
        for (const auto& item : items) {
            item->display_inventory();
        }
    }

    void add_item(std::shared_ptr<Item> item) {
        item->add_store_to_the_number();
        items.push_back(item);
    }

    bool remove_item(int id) {
        auto it = std::remove_if(items.begin(), items.end(),
            [id](std::shared_ptr<Item> item) {
                if (item->get_id() == id) {
                    item->remove_a_store_from_the_number();
                    return true;
                }
                return false;
            });
        bool removed = (it != items.end());
        items.erase(it, items.end());
        return removed;
    }

    int get_id() const { return store_id; }
    const std::string& get_store_name() const { return store_name; }
};

int Store::next_id = 1;

class Company {
private:
    static int next_id;
    int company_id;
    std::string company_name;
    std::vector<std::shared_ptr<Store>> stores;

public:
    Company(std::string c_n = "") : company_id(next_id++), company_name(c_n) {}

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
        auto it = std::remove_if(stores.begin(), stores.end(), [id](std::shared_ptr<Store> store) {
            return store->get_id() == id;
        });
        if (it != stores.end()) {
            stores.erase(it);
        }
    }

    const std::string& get_company_name() const { return company_name; }
    int get_company_id() const { return company_id; }
};

int Company::next_id = 1;

class InventoryManager {
private:
    std::vector<std::shared_ptr<Company>> companies;

public:
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
};

int main() {
    auto item1 = std::make_shared<Item>("Laptop", 10, 999.99);
    auto item2 = std::make_shared<Item>("Smartphone", 25, 499.99);
    auto item3 = std::make_shared<Item>("Tablet", 15, 299.99);

    item1->modify_quantity(5);
    item2->modify_quantity(-10);

    auto store1 = std::make_shared<Store>("Store1");
    store1->add_item(item1);
    store1->add_item(item2);
    store1->add_item(item3);

    std::cout << "\nstore1 items:\n";
    store1->display_store_items();

    store1->remove_item(item2->get_id());
    std::cout << "\nafter removing item2:\n";
    store1->display_store_items();

    auto comp1 = std::make_shared<Company>("Comp1");
    comp1->add_store(store1);

    std::cout << "\n company stores:\n";
    comp1->display_company_stores();

    comp1->remove_store(store1->get_id());
    std::cout << "\nafter removing store1:\n";
    comp1->display_company_stores();

    InventoryManager all_companies;
    all_companies.add_company(comp1);

    std::cout << "\ninitial companies:\n";
    all_companies.display_all_companies();

    all_companies.remove_company(comp1->get_company_id());
    std::cout << "\nafter removing comp1:\n";
    all_companies.display_all_companies();
    item2.reset();

    return 0;
}
