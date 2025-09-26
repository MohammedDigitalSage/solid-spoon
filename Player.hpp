#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Inventory.hpp"

class Player {
private:
    Inventory inventory_; // Player's inventory
    std::string name_;    // Player's name

public:
    /**
    * @brief Constructs a Player with the given identifier.
    * @param name A const. string reference to be the player name
    * @param inventory A const ref. to an Inventory to copy
    * and setup a Player's inventory_ member. If none provided,
    * default value of a default constructed Inventory
    */
    Player(const std::string& name, const Inventory& inventory = Inventory());

    // Big Five
    Player(const Player& rhs);                // Copy constructor
    Player(Player&& rhs) noexcept;            // Move constructor
    Player& operator=(const Player& rhs);     // Copy assignment
    Player& operator=(Player&& rhs) noexcept; // Move assignment
    ~Player() = default;                      // Default destructor

    // Accessors
    std::string getName() const;
    Inventory& getInventoryRef(); // returns reference (not const)
};

#endif
