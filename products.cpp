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

    const std::string& getStoreName() const { return store_name; }
};




int main() {
    InventoryManager item1("Laptop", 10, 999.99);
    InventoryManager item2("Smartphone", 25, 499.99);
    InventoryManager item3("Tablet", 15, 299.99);

    item1.displayInventory();
    item2.displayInventory();
    item3.displayInventory();

    Store store1("Store1",{item1,item2,item3});
    store1.displayStoreItems();
}