#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Base
{
public:
    int x, y, health;

    Base(int x, int y, int health) : x(x), y(y), health(health) {}
};

class Hero
{
public:
    int id, x, y;

    Hero(int id, int x, int y) : id(id), x(x), y(y) {}
};

class Monster
{
public:
    int id, x, y, health, vx, vy, near_base, threat_for;

    Monster(int id, int x, int y, int health, int vx, int vy, int near_base, int threat_for)
        : id(id), x(x), y(y), health(health), vx(vx), vy(vy), near_base(near_base), threat_for(threat_for) {}
};

double distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

Monster *find_nearest_monster(vector<Monster> &monsters, Hero &hero)
{
    Monster *nearest_monster = nullptr;
    double min_distance = 1e9;

    for (auto &monster : monsters)
    {
        if (monster.threat_for == 1)
        {
            double dist = distance(hero.x, hero.y, monster.x, monster.y);
            if (dist < min_distance)
            {
                min_distance = dist;
                nearest_monster = &monster;
            }
        }
    }

    return nearest_monster;
}

int main()
{
    int base_x, base_y;
    cin >> base_x >> base_y;
    cin.ignore();
    int heroes_per_player;
    cin >> heroes_per_player;
    cin.ignore();

    while (1)
    {
        vector<Base> bases;
        for (int i = 0; i < 2; i++)
        {
            int health, mana;
            cin >> health >> mana;
            cin.ignore();
            bases.emplace_back(i == 0 ? base_x : 17630 - base_x, i == 0 ? base_y : 9000 - base_y, health);
        }

        int entity_count;
        cin >> entity_count;
        cin.ignore();

        vector<Hero> heroes;
        vector<Monster> monsters;
        for (int i = 0; i < entity_count; i++)
        {
            int id, type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for;
            cin >> id >> type >> x >> y >> shield_life >> is_controlled >> health >> vx >> vy >> near_base >> threat_for;
            cin.ignore();

            if (type == 1)
            {
                heroes.emplace_back(id, x, y);
            }
            else if (type == 0)
            {
                monsters.emplace_back(id, x, y, health, vx, vy, near_base, threat_for);
            }
        }

        for (auto &hero : heroes)
        {
            Monster *nearest_monster = find_nearest_monster(monsters, hero);
            if (nearest_monster)
            {
                cout << "MOVE " << nearest_monster->x << " " << nearest_monster->y << endl;
            }
            else
            {
                cout << "WAIT" << endl;
            }
        }
    }
}
