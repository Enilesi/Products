#include <iostream>
#include <vector>
#include <string>

class InventoryManager{
    private:
        std::string item_name;
        int quantity;
        double price;
    public:
        InventoryManager(std::string i_n="", int q=0, double p=0.0){
            item_name=i_n;
            price=p;
            quantity=q;
        }

        void displayInventory() const {
        std::cout << "Item: " << item_name 
                  << ", Quantity: " << quantity 
                  << ", Price:" << price << "$"<< std::endl;
        }
        const std::string& getName() const { return item_name; }
        int getQuantity() const { return quantity; }
        double getPrice() const { return price; }
};

class Store {
    private:
        std::string store_name;
        std::vector<InventoryManager> items;
    public:
        Store(std::string s_n="",std::vector<InventoryManager> i = {}){
            store_name=s_n;
            items=i;
        }
        void displayStoreItems() const {
        std::cout << "Store: " << store_name << std::endl;
        for (const auto& item : items) {
            item.displayInventory();
            }
        }

        void addItem(const InventoryManager& item) {
            items.push_back(item);
        }

        const std::string& getStoreName() const { return store_name; }
};

class Company {
    private:
        std::string company_name;
        std::vector<Store> stores;

    public:
        Company(const std::string c_n="",std::vector<Store> s={}){
            company_name=c_n;
            stores=s;
        } 


        void displayCompanyStores() const {
            std::cout << "Company: " << company_name << std::endl;
            for (const auto& store : stores) {
                store.displayStoreItems();
            }
        }

        void addStore(const Store& store) {
            stores.push_back(store);
        }
        const std::string& getCompanyName() const { return company_name; }
};



int main() {
    InventoryManager item1("Laptop", 10, 999.99);
    InventoryManager item2("Smartphone", 25, 499.99);
    InventoryManager item3("Tablet", 15, 299.99);

    item1.displayInventory();
    item2.displayInventory();
    item3.displayInventory();

    Store store1("Store1",{item1,item2});
    store1.addItem(item3);
    store1.displayStoreItems();

    Company comp1("Comp1");
    comp1.addStore(store1);
    comp1.displayCompanyStores();
}