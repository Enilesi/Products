#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Item {
private:
    static int next_id;
    int item_id;
    std::string item_name;
    int quantity;
    double price;

public:
    Item(std::string i_n = "", int q = 0, double p = 0.0) {
        item_id = next_id++;
        item_name = i_n;
        quantity = q;
        price = p;
    }

    void display_inventory() const {
        std::cout << "Item ID: " << item_id 
                  << ", Name: " << item_name 
                  << ", Quantity: " << quantity 
                  << ", Price: $" << price << std::endl;
    }

    void modify_quantity(int amount) {
            quantity += amount;
    }

    const std::string& get_name() const { return item_name; }
    const int get_id() const { return item_id; }
    int get_quantity() const { return quantity; }
    double get_price() const { return price; }
};

int Item::next_id = 1;

class Store {
private:
    static int next_id;
    int store_id;
    std::string store_name;
    std::vector<Item> items;

public:
    Store(std::string s_n = "", std::vector<Item> i = {}) {
        store_id = next_id++;
        store_name = s_n;
        items = i;
    }

    void display_store_items() const {
        std::cout << "Store ID: " << store_id 
                  << ", Name: " << store_name << std::endl;
        for (const auto& item : items) {
            item.display_inventory();
        }
    }

    void add_item(const Item& item) {
        items.push_back(item);
    }

    void remove_item(int id) {
        items.erase(std::remove_if(items.begin(), items.end(), [id](const Item& item) {
             return item.get_id() == id; 
             }), items.end());
    }

    const int get_id() const { return store_id; }
    const std::string& get_store_name() const { return store_name; }
};

int Store::next_id = 1;

class Company {
private:
    static int next_id;
    int company_id;
    std::string company_name;
    std::vector<Store> stores;

public:
    Company(std::string c_n = "", std::vector<Store> s = {}) {
        company_id = next_id++;
        company_name = c_n;
        stores = s;
    }

    void display_company_stores() const {
        std::cout << "Company ID: " << company_id 
                  << ", Name: " << company_name << std::endl;
        for (const auto& store : stores) {
            store.display_store_items();
        }
    }

    void add_store(const Store& store) {
        stores.push_back(store);
    }

    void remove_store(int id) {
        stores.erase(std::remove_if(stores.begin(), stores.end(),[id](const Store& store) {
            return store.get_id() == id; 
            }),stores.end());
    }

    const std::string& get_company_name() const { return company_name; }
    const int get_company_id() const { return company_id; }
};

int Company::next_id = 1;

class InventoryManager {
private:
    std::vector<Company> companies;

public:
    void add_company(const Company& company) {
        companies.push_back(company);
    }

    void remove_company(int id) {
        companies.erase(std::remove_if(companies.begin(), companies.end(),[id](const Company& company) {
            return company.get_company_id() == id;
            }), companies.end());
    }

    void display_all_companies() const {
        for (const auto& company : companies) {
            company.display_company_stores();
        }
    }
};

int main() {
    Item item1("Laptop", 10, 999.99);
    Item item2("Smartphone", 25, 499.99);
    Item item3("Tablet", 15, 299.99);

    item1.modify_quantity(5);
    item2.modify_quantity(-10);

    Store store1("Store1");
    store1.add_item(item1);
    store1.add_item(item2);
    store1.add_item(item3);

    std::cout << "\ninitial store1 items:\n";
    store1.display_store_items();

    store1.remove_item(item2.get_id());
    std::cout << "\nafter removing item2:\n";
    store1.display_store_items();

    Company comp1("Comp1");
    comp1.add_store(store1);

    std::cout << "\ninitial company stores:\n";
    comp1.display_company_stores();

    comp1.remove_store(store1.get_id());
    std::cout << "\nafter removing store1:\n";
    comp1.display_company_stores();

    InventoryManager all_companies;
    all_companies.add_company(comp1);

    std::cout << "\ninitial companies:\n";
    all_companies.display_all_companies();

    all_companies.remove_company(comp1.get_company_id());
    std::cout << "\nafter removing comp1:\n";
    all_companies.display_all_companies();

    return 0;
}
