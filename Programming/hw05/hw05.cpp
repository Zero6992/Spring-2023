#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <random>

struct Plant {
    char type;
    std::string name;
    int cost;
    int hp;
    int freq;
    int val;
};

class Game {
private:
    int numberOfLands;
    int numberOfZombies;
    std::vector<Plant> plants;
    std::vector<int> zombieLands;
    int playerLand;

public:
    Game() : numberOfLands(8), numberOfZombies(3), playerLand(7) {
        loadPlants();
        // Initialize zombie lands randomly
        for (int i = 0; i < numberOfZombies; ++i) {
            int land = std::rand() % numberOfLands;
            if (land == playerLand || std::count(zombieLands.begin(), zombieLands.end(), land)) {
                --i; // try again
            } else {
                zombieLands.push_back(land);
            }
        }
    }

    void start() {
        printWelcome();
        configureGame();
        printRules();
        waitForAnyKey();
        clearConsole();
        printGameBoard();
        waitForPlayerChoice();
        // Add the rest of the game loop here
    }

    void printWelcome() {
        std::cout << "-----------------------------" << std::endl;
        std::cout << "|     Plants vs. Zombies     |" << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

    void configureGame() {
        std::cout << "Number of lands on the map (1-10, default: 8)...>";
        numberOfLands = readIntegerInput(1, 10, 8);

        std::cout << "Number of zombies on the map (1-10, default: 3)...>";
        numberOfZombies = readIntegerInput(1, 10, 3);

        // Initialize zombie lands
        zombieLands = getRandomDistinctNumbers(numberOfZombies, numberOfLands);

        for (int i = 0; i < numberOfZombies; i++) {
            zombieLands.push_back(rand() % numberOfLands);
        }

        // Initialize player land
        playerLand = rand() % numberOfLands;
    }

    std::vector<int> getRandomDistinctNumbers(int num, int max) {
        std::vector<int> numbers;
        while (numbers.size() < num) {
            int randomNumber = rand() % max;
            if (std::count(numbers.begin(), numbers.end(), randomNumber) == 0) {
                numbers.push_back(randomNumber);
            }
        }
        return numbers;
    }

    int readIntegerInput(int min, int max, int defaultValue) {
        std::string input;
        std::getline(std::cin, input);

        // If input is empty, use default value
        if (input.empty()) {
            return defaultValue;
        }

        int intValue = std::stoi(input);

        // If input is not valid or out of range, use default value
        if (intValue < min || intValue > max) {
            return defaultValue;
        }

        return intValue;
    }

    void printRules() {
        std::cout << "=============================================================================" << std::endl;
        std::cout << "Plants vs. Zombies Rule:" << std::endl;
        std::cout << "\nHow to win:\n  (1) All zombies are dead.\n  (2) At least one plant is live.\n  (3) The number of dead bomb plants cannot exceed the number of zombies." << std::endl;
        std::cout << "\nHow to lose:\n  All plants are dead." << std::endl;
        std::cout << "=============================================================================" << std::endl;
    }

    void waitForAnyKey() {
        std::cout << "Press any key to continue . . .";
        std::cin.get();
    }

    void clearConsole() {
        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif
    }

    void loadPlants() {
        std::ifstream file("plants.txt");
        std::string line;

        while (std::getline(file, line)) {
            Plant plant;
            std::stringstream ss(line);

            ss >> plant.type;
            ss >> plant.name;
            ss >> plant.cost;
            ss >> plant.hp;

            if (plant.type == 'C') {
                ss >> plant.freq >> plant.val;
            } else if (plant.type == 'S') {
                ss >> plant.val;
            } else if (plant.type == 'B') {
                plant.val = 50;
            } else if (plant.type == 'H') {
                ss >> plant.val;
            }

            plants.push_back(plant);
        }
    }

void printGameBoard() {
    std::string spaces = "    ";

    for (int i = 0; i < numberOfLands; ++i) {
        std::cout << "[" << i << "]";

        // Indicate player and zombies
        std::string occupants(numberOfZombies + 1, ' ');  // Create enough space for player and all zombies
        if (playerLand == i) {
            occupants[0] = '*';
        }
        for (int j = 0; j < numberOfZombies; ++j) {
            if (zombieLands[j] == i) {
                occupants[j + 1] = '0' + j;
            }
        }
        std::cout << "{" << occupants << "}Empty" << std::endl;  // Initial state is all "Empty"
    }

        // Print separator
        std::cout << "------------------------------------------------" << std::endl;

        // Print zombie information
        std::cout << "Zombie information:" << std::endl;
        for (int i = 0; i < numberOfZombies; ++i) {
            std::cout << "[" << i << "] Damage: 15 HP:" << std::string(40, '*') << std::endl;
        }
        std::cout << "================================================" << std::endl;

        // Print plant information
        for (int i = 0; i < int(plants.size()); ++i) {
            std::cout << "[" << i << "] " << plants[i].name << " $" << plants[i].cost << " HP: " << plants[i].hp;
            if (plants[i].type == 'C') {
                std::cout << " - gives $" << plants[i].val << " every " << plants[i].freq << " rounds";
            } else if (plants[i].type == 'S') {
                std::cout << " - gives " << plants[i].val << " damage points";
            } else if (plants[i].type == 'B') {
                std::cout << " - gives " << plants[i].val << " damage points";
            } else if (plants[i].type == 'H') {
                std::cout << " - gives all your plants " << plants[i].val << " HP back.";
            }
            std::cout << std::endl;
        }
    }

    void waitForPlayerChoice() {
        std::cout << "\nplayer $150:    Enter your choice (4 to give up, default: 4)...>";
        int playerChoice = readIntegerInput(0, 4, 4);
        // Perform the action according to playerChoice here
    }
};


int main() {
    Game game;
    game.start();
    return 0;
}

