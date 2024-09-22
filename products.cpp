#include <iostream>
#include <vector>
#include <string>

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

    const std::string& get_company_name() const { return company_name; }
    const int get_company_id() const { return company_id; }
};

int Company::next_id = 1;

int main() {
    Item item1("Laptop", 10, 999.99);
    Item item2("Smartphone", 25, 499.99);
    Item item3("Tablet", 15, 299.99);

    item1.display_inventory();
    item2.display_inventory();
    item3.display_inventory();

    Store store1("Store1", {item1, item2});
    store1.add_item(item3);
    store1.display_store_items();

    Company comp1("Comp1");
    comp1.add_store(store1);
    comp1.display_company_stores();

    return 0;
}
