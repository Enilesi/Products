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
    int stores_number = 0;

public:
    Item(std::string i_n = "", int q = 0, double p = 0.0, int i=0)
        : item_id(i), item_name(i_n), quantity(q), price(p) {}

    virtual void display_inventory() const {
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


class Store {
private:
    int store_id;
    std::string store_name;
    std::vector<std::shared_ptr<Item>> items;

public:
    Store(std::string s_n = "", int s_i) : store_id(s_i++), store_name(s_n) {}

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


class Company {
private:
    int company_id;
    std::string company_name;
    std::vector<std::shared_ptr<Store>> stores;

public:
    Company(std::string c_n = "", int c_i=0) : company_id(c_i++), company_name(c_n) {}

    void display_company_stores() const {
        std::cout  << "Company ID: " << company_id 
                  << ", Name: " << company_name << std::endl;
        for (const auto& store : stores) {
            std::cout << std::endl;
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
            std:: cout << std::endl;
            company->display_company_stores();
            std:: cout << std::endl;
        }
    }
};

std::shared_ptr<InventoryManager> InventoryManager::instance = nullptr;

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
};

class Smartphone : public Item {
private:
    std::string brand;
    std::string os;
    int storage;

public:
    Smartphone(std::string i_n, int q, double p, std::string b, std::string o, int s)
        : Item(i_n, q, p), brand(b), os(o), storage(s) {}

    void display_inventory() const override {
        std::cout << "Smartphone - ID: " << get_id()
                  << ", Name: " << get_name() 
                  << ", Brand: " << brand 
                  << ", OS: " << os 
                  << ", Storage: " << storage << "GB"
                  << ", Quantity: " << get_quantity()
                  << ", Price: $" << get_price() << std::endl;
    }
};

class TV : public Item {
private:
    std::string brand;
    int size;
    std::string resolution;

public:
    TV(std::string i_n, int q, double p, std::string b, int s, std::string res)
        : Item(i_n, q, p), brand(b), size(s), resolution(res) {}

    void display_inventory() const override {
        std::cout << "TV - ID: " << get_id()
                  << ", Name: " << get_name() 
                  << ", Brand: " << brand 
                  << ", Size: " << size << " inches"
                  << ", Resolution: " << resolution
                  << ", Quantity: " << get_quantity()
                  << ", Price: $" << get_price() << std::endl;
    }
};

class Camera : public Item {
private:
    std::string brand;
    int megapixels;
    bool is_dslr;

public:
    Camera(std::string i_n, int q, double p, std::string b, int mp, bool dslr)
        : Item(i_n, q, p), brand(b), megapixels(mp), is_dslr(dslr) {}

    void display_inventory() const override {
        std::cout << "Camera - ID: " << get_id()
                  << ", Name: " << get_name() 
                  << ", Brand: " << brand 
                  << ", Megapixels: " << megapixels
                  << ", DSLR: " << (is_dslr ? "Yes" : "No")
                  << ", Quantity: " << get_quantity()
                  << ", Price: $" << get_price() << std::endl;
    }
};

class Tablet : public Item {
private:
    std::string brand;
    int storage;
    bool supports_pen;

public:
    Tablet(std::string i_n, int q, double p, std::string b, int s, bool sp)
        : Item(i_n, q, p), brand(b), storage(s), supports_pen(sp) {}

    void display_inventory() const override {
        std::cout << "Tablet - ID: " << get_id()
                  << ", Name: " << get_name()
                  << ", Brand: " << brand
                  << ", Storage: " << storage << "GB"
                  << ", Pen Support: " << (supports_pen ? "Yes" : "No")
                  << ", Quantity: " << get_quantity()
                  << ", Price: $" << get_price() << std::endl;
    }
};

class Watch : public Item {
private:
    std::string brand;
    bool waterproof;
    bool has_gps;

public:
    Watch(std::string i_n, int q, double p, std::string b, bool w, bool gps)
        : Item(i_n, q, p), brand(b), waterproof(w), has_gps(gps) {}

    void display_inventory() const override {
        std::cout << "Watch - ID: " << get_id()
                  << ", Name: " << get_name()
                  << ", Brand: " << brand
                  << ", Waterproof: " << (waterproof ? "Yes" : "No")
                  << ", GPS: " << (has_gps ? "Yes" : "No")
                  << ", Quantity: " << get_quantity()
                  << ", Price: $" << get_price() << std::endl;
    }
};

class Gaming : public Item {
private:
    std::string brand;
    std::string type;

public:
    Gaming(std::string i_n, int q, double p, std::string b, std::string t)
        : Item(i_n, q, p), brand(b), type(t) {}

    void display_inventory() const override {
        std::cout << "Gaming - ID: " << get_id()
                  << ", Name: " << get_name()
                  << ", Brand: " << brand
                  << ", Type: " << type
                  << ", Quantity: " << get_quantity()
                  << ", Price: $" << get_price() << std::endl;
    }
};

class Accessories : public Item {
private:
    std::string brand;
    std::string type;

public:
    Accessories(std::string i_n, int q, double p, std::string b, std::string t)
        : Item(i_n, q, p), brand(b), type(t) {}

    void display_inventory() const override {
        std::cout << "Accessories - ID: " << get_id()
                  << ", Name: " << get_name()
                  << ", Brand: " << brand
                  << ", Type: " << type
                  << ", Quantity: " << get_quantity()
                  << ", Price: $" << get_price() << std::endl;
    }
};

class ItemFactory {
public:
    static std::shared_ptr<Item> create_item(std::string type, std::string name, int quantity, double price, std::string brand, std::string spec1 = "", int spec2 = 0, bool spec3 = false) {
        if (type == "Laptop") {
            return std::make_shared<Laptop>(name, quantity, price, brand, spec1, spec2, spec3);
        } else if (type == "Smartphone") {
            return std::make_shared<Smartphone>(name, quantity, price, brand, spec1, spec2);
        } else if (type == "TV") {
            return std::make_shared<TV>(name, quantity, price, brand, spec2, spec1);
        } else if (type == "Camera") {
            return std::make_shared<Camera>(name, quantity, price, brand, spec2, spec3);
        } else if (type == "Tablet") {
            return std::make_shared<Tablet>(name, quantity, price, brand, spec2, spec3);
        } else if (type == "Watch") {
            return std::make_shared<Watch>(name, quantity, price, brand, spec3, spec2);
        } else if (type == "Gaming") {
            return std::make_shared<Gaming>(name, quantity, price, brand, spec1);
        } else if (type == "Accessories") {
            return std::make_shared<Accessories>(name, quantity, price, brand, spec1);
        }
        return nullptr;
    }
};

int main() {
    auto manager = InventoryManager::get_instance();

    auto laptop = std::make_shared<Laptop>("Gaming Laptop", 10, 1500.99, "Halienware", "Hintel i7", 16, 512);
    auto smartphone = std::make_shared<Smartphone>("Ghalaxy S21", 20, 999.99, "Sansung", "Handroid", 128);
    auto tv = std::make_shared<TV>("Smart TV", 5, 899.99, "ELG", 55, "4K");
    auto camera = std::make_shared<Camera>("DSLR Camera", 7, 1200.00, "Canonic", 24, true);
    auto tablet = std::make_shared<Tablet>("hiPad Pro", 15, 799.99, "Capple", 256, true);
    auto watch = std::make_shared<Watch>("Capple Watch", 30, 399.99, "Capple", true, true);
    auto accessory = std::make_shared<Accessories>("Laptop Bag", 30, 59.99, "HiPi", "Bag");
    auto gaming = std::make_shared<Gaming>("Gaming Mouse", 100, 49.99, "Logictech", "Mouse");

    auto store1 = std::make_shared<Store>("Laltex");
    store1->add_item(laptop);
    store1->add_item(smartphone);
    store1->add_item(camera);

    auto store2 = std::make_shared<Store>("Cemag Showroom");
    store2->add_item(tablet);
    store2->add_item(watch);

    auto store3 = std::make_shared<Store>("Medina Ghalaxy");
    store3->add_item(smartphone);
    store3->add_item(tv);

    auto comp1 = std::make_shared<Company>("Laltex & Medina Ghalaxy");
    comp1->add_store(store1);
    comp1->add_store(store3);

    auto comp2 = std::make_shared<Company>("Cemag");
    comp2->add_store(store2);

    auto store4 = std::make_shared<Store>("Phlanco");
    store4->add_item(accessory);
    store4->add_item(gaming);

    auto comp3 = std::make_shared<Company>("Phlanco");
    comp3->add_store(store4);

    manager->add_company(comp1);
    manager->add_company(comp2);
    manager->add_company(comp3);

    manager->display_all_companies();

    return 0;
}
