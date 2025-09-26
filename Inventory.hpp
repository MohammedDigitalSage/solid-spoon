#pragma once

#include <vector>
#include "Item.hpp"

class Inventory {
public:
    Inventory(const std::vector<std::vector<Item>>& items = std::vector<std::vector<Item>>(10, std::vector<Item>(10)), Item* equipped = nullptr);

    Item* getEquipped() const;
    void equip(Item* itemToEquip);
    void discardEquipped();
    const std::vector<std::vector<Item>>& getItems() const;
    float getWeight() const;
    size_t getCount() const;
    Item at(size_t row, size_t col) const;
    bool store(size_t row, size_t col, const Item& pickup);

    Inventory(const Inventory& rhs);
    Inventory(Inventory&& rhs) noexcept;
    Inventory& operator=(const Inventory& rhs);
    Inventory& operator=(Inventory&& rhs) noexcept;
    ~Inventory() noexcept;

private:
    std::vector<std::vector<Item>> inventory_grid_;
    Item* equipped_;
    float weight_;
    size_t item_count_;
};
