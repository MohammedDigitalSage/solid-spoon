#include "Player.hpp"

// Constructor
Player::Player(const std::string& name, const Inventory& inventory)
    : name_(name), inventory_(inventory) {}

// Copy constructor
Player::Player(const Player& rhs)
    : name_(rhs.name_), inventory_(rhs.inventory_) {}

// Move constructor
Player::Player(Player&& rhs) noexcept
    : name_(std::move(rhs.name_)), inventory_(std::move(rhs.inventory_)) {}

// Copy assignment
Player& Player::operator=(const Player& rhs) {
    if (this != &rhs) {
        name_ = rhs.name_;
        inventory_ = rhs.inventory_;
    }
    return *this;
}

// Move assignment
Player& Player::operator=(Player&& rhs) noexcept {
    if (this != &rhs) {
        name_ = std::move(rhs.name_);
        inventory_ = std::move(rhs.inventory_);
    }
    return *this;
}

// Getters
std::string Player::getName() const {
    return name_;
}

Inventory& Player::getInventoryRef() {
    return inventory_;
}
