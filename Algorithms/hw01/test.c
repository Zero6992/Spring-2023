<<<<<<< Updated upstream
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class Entity {
public:
    int id;
    int x, y;

    Entity(int id, int x, int y) : id(id), x(x), y(y) {}

    double distanceTo(Entity &other) {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

class Base : public Entity {
public:
    int health;

    Base(int id, int x, int y, int health) : Entity(id, x, y), health(health) {}
};

class Hero : public Entity {
public:
    int mana;

    Hero(int id, int x, int y) : Entity(id, x, y), mana(0) {}

    void castSpell(const string &spellCommand) {
        cout << spellCommand << endl;
    }
};

class Monster : public Entity {
public:
    int health;
    int vx, vy;
    bool targetingBase;

    Monster(int id, int x, int y, int health, int vx, int vy, bool targetingBase)
        : Entity(id, x, y), health(health), vx(vx), vy(vy), targetingBase(targetingBase) {}
};

class Spell {
public:
    virtual void apply(Entity &caster, Entity &target) = 0;
};

class Wind : public Spell {
public:
    void apply(Entity &caster, Entity &target) override {
        // Apply the push effect to the target
    }
};

class Shield : public Spell {
public:
    void apply(Entity &caster, Entity &target) override {
        // Apply the shield effect to the target
    }
};

class Control : public Spell {
public:
    void apply(Entity &caster, Entity &target) override {
        // Apply the control effect to the target
    }
};

// Function to parse game state and update data structures
void parseGameState(vector<Hero> &heroes, vector<Monster> &monsters) {
    // Read game state from input and update heroes and monsters
}

// Function to decide hero actions based on game state
void makeHeroActions(const vector<Hero> &heroes, const vector<Monster> &monsters) {
    // Implement hero behavior according to new rules, including spell commands (WIND, SHIELD, CONTROL)
    for (const Hero &hero : heroes) {
        // Decide hero action (WAIT, MOVE, SPELL)
=======
#include <stdio.h>

int board[8192][8192];
int current_tile = 0;

void place_tan(int x, int y) {
    board[x][y] = current_tile;
}

void cover_board(int x, int y, int size, int black_x, int black_y) {
    if (size == 2) {
        current_tile++;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (x + i != black_x || y + j != black_y) {
                    place_tan(x + i, y + j);
                }
            }
        }
    } else {
        int half_size = size / 2;
        int new_black_x = black_x < x + half_size ? black_x : x + half_size - 1;
        int new_black_y = black_y < y + half_size ? black_y : y + half_size - 1;
        cover_board(x, y, half_size, new_black_x, new_black_y);

        new_black_x = black_x >= x + half_size ? black_x : x + half_size;
        new_black_y = black_y < y + half_size ? black_y : y +
        half_size - 1;
        cover_board(x + half_size, y, half_size, new_black_x, new_black_y);

        new_black_x = black_x < x + half_size ? black_x : x + half_size - 1;
        new_black_y = black_y >= y + half_size ? black_y : y + half_size;
        cover_board(x, y + half_size, half_size, new_black_x, new_black_y);

        new_black_x = black_x >= x + half_size ? black_x : x + half_size;
        new_black_y = black_y >= y + half_size ? black_y : y + half_size;
        cover_board(x + half_size, y + half_size, half_size, new_black_x, new_black_y);
>>>>>>> Stashed changes
    }
}

int main() {
<<<<<<< Updated upstream
    // Initialization and input handling
    int baseX, baseY;
    int heroesPerPlayer;
    cin >> baseX >> baseY >> heroesPerPlayer;

    vector<Hero> heroes;
    vector<Monster> monsters;

    while (true) {
        // Read and parse the game state
        parseGameState(heroes, monsters);

        // Make hero actions based on game state
        makeHeroActions(heroes, monsters);

        // Output actions for each hero
        for (const Hero &hero : heroes) {
            // Example: output WAIT for all heroes
            cout << "WAIT" << endl;
=======
    int N, L;
    scanf("%d %d", &N, &L);
    int black_grids[N][2];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &black_grids[i][0], &black_grids[i][1]);
        board[black_grids[i][0]][black_grids[i][1]] = 0;
    }

    cover_board(0, 0, L, black_grids[0][0], black_grids[0][1]);

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            printf("%d", board[i][j]);
            if (j < L - 1) {
                printf(" ");
            }
>>>>>>> Stashed changes
        }
    }

    return 0;
}
