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
};




int main() {
    InventoryManager item1("Laptop", 10, 999.99);
    InventoryManager item2("Smartphone", 25, 499.99);
    InventoryManager item3("Tablet", 15, 299.99);

    item1.displayInventory();
    item2.displayInventory();
    item3.displayInventory();
}