#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Inventory.hpp"

class Player {
private:
    Inventory inventory_;
    std::string name_;

public:
    // constructor
    Player(const std::string& name, const Inventory& inventory = Inventory());

    // copy constructor
    Player(const Player& rhs);

    // move constructor
    Player(Player&& rhs) noexcept;

    // copy assignment
    Player& operator=(const Player& rhs);

    // move assignment
    Player& operator=(Player&& rhs) noexcept;

    // destructor (default is fine)
    ~Player() = default;

    // getters
    std::string getName() const;
    Inventory& getInventoryRef();
};

#endif
