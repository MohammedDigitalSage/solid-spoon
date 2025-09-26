#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <stdexcept>
#include "Item.hpp"

class Inventory {
private:
    /** A dynamic grid for storing non-equipped items.
    * Each outer vector represents a row in the grid,
    * while the inner vectors represent columns within those rows.
    */
    std::vector<std::vector<Item>> inventory_grid_;

    // A pointer to a dynamically allocated Item outside of the Player's bag
    Item* equipped_;

    // The total weight of all items in `inventory_grid_`
    float weight_;

    // The total number of non-empty items in `inventory_grid_`
    size_t item_count_;

public:
    /**
    * @brief Constructor with optional parameters for initialization.
    * @param items A const reference to a 2D vector of items.
    * Defaults to a 10x10 grid of default-constructed items, if none provided.
    * @param equipped A pointer to an Item object.
    * Defaults to nullptr, if none provided.
    *
    * @post Initializes members in the following way:
    * 1) Initializes `weight_` as the total weight of all items in `items` (excluding NONE type)
    * 2) Initializes `item_count_` as the count of non-NONE items.
    *
    * NOTE: The `equipped` item is excluded from these calculations.
    */
    Inventory(const std::vector<std::vector<Item>>& items =
                  std::vector<std::vector<Item>>(10, std::vector<Item>(10, Item())),
              Item* equipped = nullptr);

    // Big Five
    Inventory(const Inventory& rhs);               // Copy constructor
    Inventory(Inventory&& rhs) noexcept;           // Move constructor
    Inventory& operator=(const Inventory& rhs);    // Copy assignment
    Inventory& operator=(Inventory&& rhs) noexcept;// Move assignment
    ~Inventory();                                  // Destructor

    // Accessors & Mutators
    Item* getEquipped() const;
    void equip(Item* itemToEquip);
    void discardEquipped();
    std::vector<std::vector<Item>> getItems() const;
    float getWeight() const;
    size_t getCount() const;
    Item at(size_t row, size_t col) const;
    bool store(size_t row, size_t col, const Item& pickup);
};

#endif
