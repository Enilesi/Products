#include "products.h"
#include "db.h"

std::shared_ptr<InventoryManager> InventoryManager::instance = nullptr;


int main() {
    auto manager = InventoryManager::get_instance();

    std::shared_ptr<Item> laptop = ItemFactory::create_item("Laptop", "Gaming Laptop", 10, 1500.99, "Halienware", "Hintel i7", 16, 512);
    std::cout <<laptop->get_id()<< "\n\n";
    auto smartphone = ItemFactory::create_item("Smartphone", "Ghalaxy S21", 20, 999.99, "Sansung", "Handroid", 128);
    auto tv = ItemFactory::create_item("TV", "Smart TV", 5, 899.99, "ELG", "4K", 55);

    auto camera = ItemFactory::create_item("Camera", "DSLR Camera", 7, 1200.00, "Canonic", "", 24, true);
    auto tablet = ItemFactory::create_item("Tablet", "hiPad Pro", 15, 799.99, "Capple", "", 256, true);
    auto watch = ItemFactory::create_item("Watch", "Capple Watch", 30, 399.99, "Capple", "", true, true);

    auto accessory = ItemFactory::create_item("Accessories", "Laptop Bag", 30, 59.99, "HiPi", "Bag");
    auto gaming = ItemFactory::create_item("Gaming", "Gaming Mouse", 100, 49.99, "Logictech", "Mouse");

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

    save_to_database(manager);

    // manager->display_all_companies();

    return 0;
}
