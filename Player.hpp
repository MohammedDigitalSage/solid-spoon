#pragma once

#include <string>
#include "Inventory.hpp"

class Player {
public:
    Player(const std::string& name, const Inventory& inventory = Inventory());

    std::string getName() const;
    Inventory& getInventoryRef();

    Player(const Player& rhs);
    Player(Player&& rhs) noexcept;
    Player& operator=(const Player& rhs);
    Player& operator=(Player&& rhs) noexcept;
    ~Player() noexcept = default;

private:
    std::string name_;
    Inventory inventory_;
};
