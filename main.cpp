#include <iostream>
#include <chrono>
#include "Player.hpp"
#include "Guild.hpp" // assume Guild is given

using namespace std;
using namespace std::chrono;

int main() {
    // small inventory
    Player p1("SmallGuy");

    // big inventory (2000x2000)
    vector<vector<Item>> bigItems(2000, vector<Item>(2000, Item()));
    Inventory bigInv(bigItems);
    Player p2("BigGuy", bigInv);

    Guild g1, g2;

    // test copying small player
    auto start = high_resolution_clock::now();
    g1.addPlayer(p1); // copy
    auto end = high_resolution_clock::now();
    cout << "Copy small: " << duration_cast<microseconds>(end - start).count() << "us\n";

    // test moving small player
    start = high_resolution_clock::now();
    g2.addPlayer(std::move(p1)); // move
    end = high_resolution_clock::now();
    cout << "Move small: " << duration_cast<microseconds>(end - start).count() << "us\n";

    // test copying big player
    start = high_resolution_clock::now();
    g1.addPlayer(p2); // copy
    end = high_resolution_clock::now();
    cout << "Copy big: " << duration_cast<microseconds>(end - start).count() << "us\n";

    // test moving big player
    start = high_resolution_clock::now();
    g2.addPlayer(std::move(p2)); // move
    end = high_resolution_clock::now();
    cout << "Move big: " << duration_cast<microseconds>(end - start).count() << "us\n";

    return 0;
}
