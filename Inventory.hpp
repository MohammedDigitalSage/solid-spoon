#pragma once

#include <vector>
#include "Item.hpp"

using ItemGrid = std::vector<std::vector<Item>>;

class Inventory {
public:
    Inventory(const ItemGrid& items = ItemGrid(10, std::vector<Item>(10)), Item* equipped = nullptr);

    Item* getEquipped() const;
    void equip(Item* itemToEquip);
    void discardEquipped();
    ItemGrid getItems() const;
    float getWeight() const;
    size_t getCount() const;
    Item at(size_t row, size_t col) const;
    bool store(size_t row, size_t col, const Item& pickup);

    Inventory(const Inventory& rhs);
    Inventory(Inventory&& rhs) noexcept;
    Inventory& operator=(const Inventory& rhs);
    Inventory& operator=(Inventory&& rhs) noexcept;
    ~Inventory();

private:
    ItemGrid inventory_grid_;
    Item* equipped_;
    float weight_;
    size_t item_count_;
};
