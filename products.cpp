#include <iostream>
#include <vector>
#include <string>

class Item{
    private:
        int item_id;
        std::string item_name;
        int quantity;
        double price;
    public:
        Item(int id = 0,std::string i_n="", int q=0, double p=0.0){
            item_id=id;
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
        const int getId() const { return item_id; }
        int getQuantity() const { return quantity; }
        double getPrice() const { return price; }
};

class Store {
    private:
        int store_id;
        std::string store_name;
        std::vector<Item> items;
    public:
        Store(int id = 0,std::string s_n="",std::vector<Item> i = {}){
            store_id=id;
            store_name=s_n;
            items=i;
        }
        void displayStoreItems() const {
        std::cout << "Store: " << store_name << std::endl;
        for (const auto& item : items) {
            item.displayInventory();
            }
        }

        void addItem(const Item& item) {
            items.push_back(item);
        }
        const int getId() const { return store_id; }
        const std::string& getStoreName() const { return store_name; }
};

class Company {
    private:
        int company_id;
        std::string company_name;
        std::vector<Store> stores;

    public:
        Company(int id = 0,const std::string c_n="",std::vector<Store> s={}){
            company_id=id;
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
        const int getCompanyId() const { return company_id; }
        
};


int main() {
    Item item1(1,"Laptop", 10, 999.99);
    Item item2(2,"Smartphone", 25, 499.99);
    Item item3(3,"Tablet", 15, 299.99);

    item1.displayInventory();
    item2.displayInventory();
    item3.displayInventory();

    Store store1(1,"Store1",{item1,item2});
    store1.addItem(item3);
    store1.displayStoreItems();

    Company comp1(1,"Comp1");
    comp1.addStore(store1);
    comp1.displayCompanyStores();
}