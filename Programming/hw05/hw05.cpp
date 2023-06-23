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

    Plant() : type(' '), name(""), cost(0), hp(0), freq(0), val(0) {}

    Plant(char t, std::string n, int c, int h, int f = 0, int v = 0) : type(t), name(n), cost(c), hp(h), freq(f), val(v) {}
};

class Zombie {
private:
    const int id;

public:
    Zombie(int id) : id(id) {}

    int getId() const {
        return id;
    }
};

class Land {
public:
    std::vector<Zombie*> zombies;
    Plant* plant = nullptr;
};

class Game {
private:
    int numberOfLands;
    int numberOfZombies;
    std::vector<Plant> plants;
    std::vector<Land> lands;
    int playerLand;
    int playerMoney = 150;

public:
    Game() : numberOfLands(8), numberOfZombies(3), playerLand(7) {
        loadPlants();
    }

    void cleanUpZombies() {
        for (auto& land : lands) {
            for (auto& zombie : land.zombies) {
                delete zombie;
            }
        }
    }

    void start() {
        printWelcome();
        configureGame();
        printRules();
        pressAnyKeyToContinue();
        while (true) {
            // Add the rest of the game loop here
            printGameBoard();
            waitForPlayerChoice();
            // if (isGameOver())
            // {
            //     break;
            // }
        }
    }

    void printWelcome() {
        std::cout << "-----------------------------" << std::endl;
        std::cout << "|     Plants vs. Zombies     |" << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

    int readIntegerInput(int min, int max, int defaultValue) {
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            return defaultValue;
        }

        int intValue = std::stoi(input);

        if (intValue < min || intValue > max) {
            return defaultValue;
        }

        return intValue;
    }

    void configureGame() {
        std::cout << "Number of lands on the map (1-10, default: 8)...>";
        numberOfLands = readIntegerInput(1, 10, 8);

        std::cout << "Number of zombies on the map (1-10, default: 3)...>";
        numberOfZombies = readIntegerInput(1, 10, 3);

        // Resize lands and clear any previous zombies
        lands.resize(numberOfLands);
        for (auto& land : lands) {
            for (auto& zombie : land.zombies) {
                delete zombie;
            }
            land.zombies.clear();
        }

        for (int i = 0; i < numberOfZombies; ++i) {
            int landIndex = std::rand() % numberOfLands;
            lands[landIndex].zombies.push_back(new Zombie(i));
        }

        playerLand = std::rand() % numberOfLands;
    }

    void printRules() {
        std::cout << "=============================================================================" << std::endl;
        std::cout << "Plants vs. Zombies Rule:" << std::endl;
        std::cout << "\nHow to win:\n  (1) All zombies are dead.\n  (2) At least one plant is live.\n  (3) The number of dead bomb plants cannot exceed the number of zombies." << std::endl;
        std::cout << "\nHow to lose:\n  All plants are dead." << std::endl;
        std::cout << "=============================================================================" << std::endl;
    }

    void loadPlants() {
        std::ifstream file("plants.txt");
        std::string line;

        while (std::getline(file, line)) {
            Plant plant;
            std::stringstream ss(line);
            std::string tempCost;

            ss >> plant.type;
            ss >> plant.name;
            ss >> tempCost;
            tempCost.erase(std::remove(tempCost.begin(), tempCost.end(), '$'), tempCost.end()); // Remove dollar sign
            plant.cost = std::stoi(tempCost);
            ss >> plant.hp;

            if (plant.type == 'C') {
                ss >> plant.freq >> plant.val;
            }
            else if (plant.type == 'S') {
                plant.freq = 0;
                ss >> plant.val;
            }
            else if (plant.type == 'B') {
                plant.freq = 0;
                plant.val = 50;
            }
            else if (plant.type == 'H') {
                plant.freq = 0;
                ss >> plant.val;
            }

            plants.push_back(plant);
        }
    }

    void printGameBoard() {
        for (int i = 0; i < numberOfLands; ++i) {
            std::cout << "[" << i << "]";
            std::string occupants(numberOfZombies + 1, ' ');
            if (playerLand == i) {
                occupants[0] = '*';
            }
            for (int j = 0; j < numberOfZombies; ++j) {
                auto it = std::find_if(lands[i].zombies.begin(), lands[i].zombies.end(),
                                    [&j](const Zombie *z) { return z->getId() == j; });
                occupants[j + 1] = (it != lands[i].zombies.end()) ? ('0' + (*it)->getId()) : ' ';
            }
            if (lands[i].plant != nullptr) {
                std::cout << "{" << occupants << "}" << lands[i].plant->type << std::endl;
            } else {
                std::cout << "{" << occupants << "}Empty" << std::endl;
            }
        }
        std::cout << "------------------------------------------------" << std::endl;

        std::cout << "Zombie information:" << std::endl;
        for (int i = 0; i < numberOfZombies; ++i) {
            std::cout << "[" << i << "] Damage: 15 HP:" << std::string(40, '*') << std::endl;
        }
        std::cout << "================================================" << std::endl;

        for (int i = 0; i < int(plants.size()); ++i) {
            std::cout << "[" << i << "] " << plants[i].name << " $" << plants[i].cost << " HP: " << plants[i].hp;
            if (plants[i].type == 'C') {
                std::cout << " - gives $" << plants[i].val << " every " << plants[i].freq << " rounds";
            }
            else if (plants[i].type == 'S') {
                std::cout << " - gives " << plants[i].val << " damage points";
            }
            else if (plants[i].type == 'B') {
                std::cout << " - gives " << plants[i].val << " damage points";
            }
            else if (plants[i].type == 'H') {
                std::cout << " - gives all your plants " << plants[i].val << " HP back.";
            }
            std::cout << std::endl;
        }
        std::cout << "================================================" << std::endl;
    }

    void clearConsole() {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    void pressAnyKeyToContinue() {
        std::cout << "請按任意鍵繼續 . . .";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        clearConsole();
    }

    // TODO: Implement this function.
    void waitForPlayerChoice() {
        std::cout << "\nplayer $150:    Enter your choice (4 to give up, default: 4)...>";
        int playerChoice = readIntegerInput(0, 4, 4);
        pressAnyKeyToContinue();
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}