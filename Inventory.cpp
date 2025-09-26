#include "Inventory.hpp"
#include <iostream>

// helper function: recalc weight + item count
static void recalcStats(const std::vector<std::vector<Item>>& grid, float& weight, size_t& count) {
    weight = 0;
    count = 0;
    for (auto& row : grid) {
        for (auto& item : row) {
            if (item.getType() != ItemType::NONE) { // only count real items
                weight += item.getWeight();
                count++;
            }
        }
    }
}

// constructor
Inventory::Inventory(const std::vector<std::vector<Item>>& items, Item* equipped)
    : inventory_grid_(items), equipped_(equipped) {
    recalcStats(inventory_grid_, weight_, item_count_);
}

// copy constructor
Inventory::Inventory(const Inventory& rhs) {
    inventory_grid_ = rhs.inventory_grid_;
    if (rhs.equipped_) {
        equipped_ = new Item(*rhs.equipped_); // deep copy
    } else {
        equipped_ = nullptr;
    }
    weight_ = rhs.weight_;
    item_count_ = rhs.item_count_;
}

// move constructor
Inventory::Inventory(Inventory&& rhs) noexcept {
    inventory_grid_ = std::move(rhs.inventory_grid_);
    equipped_ = rhs.equipped_;
    weight_ = rhs.weight_;
    item_count_ = rhs.item_count_;

    // reset rhs
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0;
    rhs.item_count_ = 0;
}

// copy assignment
Inventory& Inventory::operator=(const Inventory& rhs) {
    if (this != &rhs) {
        // clean old equipped
        delete equipped_;

        inventory_grid_ = rhs.inventory_grid_;
        if (rhs.equipped_) {
            equipped_ = new Item(*rhs.equipped_);
        } else {
            equipped_ = nullptr;
        }
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
    }
    return *this;
}

// move assignment
Inventory& Inventory::operator=(Inventory&& rhs) noexcept {
    if (this != &rhs) {
        delete equipped_;

        inventory_grid_ = std::move(rhs.inventory_grid_);
        equipped_ = rhs.equipped_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        rhs.equipped_ = nullptr;
        rhs.weight_ = 0;
        rhs.item_count_ = 0;
    }
    return *this;
}

// destructor
Inventory::~Inventory() {
    delete equipped_;
}

// getters
Item* Inventory::getEquipped() const { return equipped_; }
std::vector<std::vector<Item>> Inventory::getItems() const { return inventory_grid_; }
float Inventory::getWeight() const { return weight_; }
size_t Inventory::getCount() const { return item_count_; }

// equip item
void Inventory::equip(Item* itemToEquip) {
    equipped_ = itemToEquip; // don't delete old one (instructions said so)
}

// discard equipped item
void Inventory::discardEquipped() {
    if (equipped_ != nullptr) {
        delete equipped_;
        equipped_ = nullptr;
    }
}

// access item
Item Inventory::at(size_t row, size_t col) const {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size()) {
        throw std::out_of_range("Invalid index in Inventory::at");
    }
    return inventory_grid_[row][col];
}

// store item
bool Inventory::store(size_t row, size_t col, const Item& pickup) {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size()) {
        throw std::out_of_range("Invalid index in Inventory::store");
    }
    if (inventory_grid_[row][col].getType() != ItemType::NONE) {
        return false; // already something there
    }
    inventory_grid_[row][col] = pickup;
    recalcStats(inventory_grid_, weight_, item_count_);
    return true;
}
