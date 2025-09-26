#include "Inventory.hpp"
#include <stdexcept>

static void recalcStats(const std::vector<std::vector<Item>>& grid, float& weight, size_t& count) {
    weight = 0.0f;
    count = 0;
    for (const auto& row : grid) {
        for (const auto& item : row) {
            if (item.getType() != ItemType::NONE) {
                weight += item.getWeight();
                ++count;
            }
        }
    }
}

Inventory::Inventory(const std::vector<std::vector<Item>>& items, Item* equipped)
    : inventory_grid_(items), equipped_(equipped), weight_(0.0f), item_count_(0) {
    recalcStats(inventory_grid_, weight_, item_count_);
}

Inventory::Inventory(const Inventory& rhs)
    : inventory_grid_(rhs.inventory_grid_), equipped_(nullptr),
      weight_(rhs.weight_), item_count_(rhs.item_count_) {
    if (rhs.equipped_) {
        equipped_ = new Item(*rhs.equipped_);
    }
}

Inventory::Inventory(Inventory&& rhs) noexcept
    : inventory_grid_(std::move(rhs.inventory_grid_)),
      equipped_(rhs.equipped_),
      weight_(rhs.weight_),
      item_count_(rhs.item_count_) {
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0.0f;
    rhs.item_count_ = 0;
    rhs.inventory_grid_.clear();
}

Inventory& Inventory::operator=(const Inventory& rhs) {
    if (this != &rhs) {
        delete equipped_;
        equipped_ = nullptr;

        inventory_grid_ = rhs.inventory_grid_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        if (rhs.equipped_) {
            equipped_ = new Item(*rhs.equipped_);
        }
    }
    return *this;
}

Inventory& Inventory::operator=(Inventory&& rhs) noexcept {
    if (this != &rhs) {
        delete equipped_;
        equipped_ = nullptr;

        inventory_grid_ = std::move(rhs.inventory_grid_);
        equipped_ = rhs.equipped_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        rhs.equipped_ = nullptr;
        rhs.weight_ = 0.0f;
        rhs.item_count_ = 0;
        rhs.inventory_grid_.clear();
    }
    return *this;
}

Inventory::~Inventory() noexcept {
    delete equipped_;
    equipped_ = nullptr;
}

Item* Inventory::getEquipped() const {
    return equipped_;
}

void Inventory::equip(Item* itemToEquip) {
    equipped_ = itemToEquip;
}

void Inventory::discardEquipped() {
    if (equipped_) {
        delete equipped_;
        equipped_ = nullptr;
    }
}

const std::vector<std::vector<Item>>& Inventory::getItems() const {
    return inventory_grid_;
}

float Inventory::getWeight() const {
    return weight_;
}

size_t Inventory::getCount() const {
    return item_count_;
}

Item Inventory::at(size_t row, size_t col) const {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size()) {
        throw std::out_of_range("Index out of bounds in Inventory::at");
    }
    return inventory_grid_[row][col];
}

bool Inventory::store(size_t row, size_t col, const Item& pickup) {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size()) {
        throw std::out_of_range("Index out of bounds in Inventory::store");
    }
    if (inventory_grid_[row][col].getType() != ItemType::NONE) {
        return false;
    }
    inventory_grid_[row][col] = pickup;
    recalcStats(inventory_grid_, weight_, item_count_);
    return true;
}
