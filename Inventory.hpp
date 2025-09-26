#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <stdexcept>
#include "Item.hpp" // we assume Item is given already

class Inventory {
private:
    // 2D grid of items (like a bag)
    std::vector<std::vector<Item>> inventory_grid_;

    // pointer to currently equipped item (like wearing armor/holding weapon)
    Item* equipped_;

    // keep track of total weight
    float weight_;

    // keep track of how many real items we have
    size_t item_count_;

public:
    // constructor (default is 10x10 empty items, nothing equipped)
    Inventory(const std::vector<std::vector<Item>>& items = std::vector<std::vector<Item>>(10, std::vector<Item>(10, Item())),
              Item* equipped = nullptr);

    // copy constructor (deep copy)
    Inventory(const Inventory& rhs);

    // move constructor
    Inventory(Inventory&& rhs) noexcept;

    // copy assignment operator
    Inventory& operator=(const Inventory& rhs);

    // move assignment operator
    Inventory& operator=(Inventory&& rhs) noexcept;

    // destructor
    ~Inventory();

    // getters
    Item* getEquipped() const;
    std::vector<std::vector<Item>> getItems() const;
    float getWeight() const;
    size_t getCount() const;

    // equip item
    void equip(Item* itemToEquip);

    // discard equipped item
    void discardEquipped();

    // access item at row,col
    Item at(size_t row, size_t col) const;

    // store item in grid
    bool store(size_t row, size_t col, const Item& pickup);
};

#endif
