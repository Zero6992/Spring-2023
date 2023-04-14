#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

// Entity Types
enum EntityType
{
    MONSTER = 0,
    MY_HERO = 1,
    OPPONENT_HERO = 2
};

enum ActionType
{
    WAIT,
    MOVE,
    SPELL_WIND,
    SPELL_SHIELD,
    SPELL_CONTROL
};

class GameState
{
public:
    std::vector<Hero> myHeroes;
    std::vector<Hero> opponentHeroes;
    std::vector<Monster> monsters;
    int myBaseHealth;
    int opponentBaseHealth;

    GameState(/* Other parameters, if needed */)
    {
        // Initialize heroes, monsters, and base health
        // ...
    }
};

class Action
{
public:
    ActionType actionType;
    int heroId;
    int x, y;
    int targetId;

    Action(ActionType actionType, int heroId, int x = 0, int y = 0, int targetId = -1)
        : actionType(actionType), heroId(heroId), x(x), y(y), targetId(targetId) {}
};

// Entity class
class Entity
{
public:
    int id, type, x, y, shieldLife, isControlled, health, vx, vy, nearBase, threatFor;
    Entity(int id, int type, int x, int y, int shieldLife, int isControlled, int health, int vx, int vy, int nearBase, int threatFor)
        : id(id), type(type), x(x), y(y), shieldLife(shieldLife), isControlled(isControlled), health(health), vx(vx), vy(vy), nearBase(nearBase), threatFor(threatFor) {}
};

class Hero
{
public:
    int id;
    Hero(int id) : id(id) {}
    void wait()
    {
        std::cout << "WAIT" << std::endl;
    }
    void move(int x, int y)
    {
        std::cout << "MOVE " << x << " " << y << std::endl;
    }
    void castWind(int x, int y)
    {
        std::cout << "SPELL WIND " << x << " " << y << std::endl;
    }
    void castShield(int entityId)
    {
        std::cout << "SPELL SHIELD " << entityId << std::endl;
    }
    void castControl(int entityId, int x, int y)
    {
        std::cout << "SPELL CONTROL " << entityId << " " << x << " " << y << std::endl;
    }
};

class Monster
{
public:
    int id;
    int x, y;
    int health;
    int vx, vy;

    Monster(int id, int x, int y, int health, int vx, int vy)
        : id(id), x(x), y(y), health(health), vx(vx), vy(vy) {}
};

class Target
{
public:
    int id;
    double priority;

    Target(int id, double priority) : id(id), priority(priority) {}
};

class Node
{
public:
    Node *parent;
    std::vector<Node *> children;
    Action action;
    int visits;
    double totalValue;

    Node(Node *parent, const Action &action)
        : parent(parent), action(action), visits(0), totalValue(0) {}

    // TODO: Implement addChild, selectBestChild, updateValue methods
};

std::vector<Action> generateLegalActions(const GameState &gameState, const Hero &hero)
{
    std::vector<Action> legalActions;

    // Generate WAIT action
    legalActions.emplace_back(ActionType::WAIT, hero.id);

    // Generate MOVE actions (in this example, we use a fixed step size)
    const int stepSize = 400;
    for (int x = hero.x - stepSize; x <= hero.x + stepSize; x += stepSize)
    {
        for (int y = hero.y - stepSize; y <= hero.y + stepSize; y += stepSize)
        {
            legalActions.emplace_back(ActionType::MOVE, hero.id, x, y);
        }
    }

    // Generate SPELL actions
    // TODO: Check spell-specific conditions (e.g., mana, cooldowns)
    // WIND spell
    for (const auto &target : gameState.monsters)
    {
        legalActions.emplace_back(ActionType::SPELL_WIND, hero.id, target.x, target.y);
    }
    for (const auto &target : gameState.myHeroes)
    {
        legalActions.emplace_back(ActionType::SPELL_SHIELD, hero.id, -1, -1, target.id);
    }
    // CONTROL spell
    for (const auto &target : gameState.opponentHeroes)
    {
        legalActions.emplace_back(ActionType::SPELL_CONTROL, hero.id, target.x, target.y, target.id);
    }

    return legalActions;
}

GameState applyAction(const GameState &gameState, const Action &action)
{
    GameState newGameState = gameState;
    // TODO: Apply the action to the gameState and return the resulting gameState
    // ...
}

double evaluateGameState(const GameState &gameState)
{
    // TODO: Evaluate the gameState and return its value
    // ...
}

Action MCTS(const GameState &rootGameState, int iterations)
{
    Node *rootNode = new Node(nullptr, / dummy action / Action{});
    for (int i = 0; i < iterations; ++i)
    {
        // Selection
        Node *currentNode = rootNode;
        while (!currentNode->children.empty())
        {
            currentNode = currentNode->selectBestChild();
        }

        // Expansion
        std::vector<Action> legalActions = generateLegalActions(currentNode->gameState);
        for (const Action &action : legalActions)
        {
            GameState childGameState = applyAction(currentNode->gameState, action);
            Node *childNode = new Node(currentNode, action);
            currentNode->addChild(childNode);
        }

        // Simulation
        Node *randomChild = currentNode->children[rand() % currentNode->children.size()];
        double value = evaluateGameState(randomChild->gameState);

        // Backpropagation
        while (randomChild != nullptr)
        {
            randomChild->updateValue(value);
            randomChild = randomChild->parent;
        }
    }

    // Choose the best action
    Action bestAction = rootNode->selectBestChild()->action;
    delete rootNode;
    return bestAction;
}

bool compareTargets(const Target &a, const Target &b)
{
    return a.priority > b.priority;
}

double distance(int x1, int y1, int x2, int y2)
{
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

int main()
{
    int baseX, baseY, heroesPerPlayer;
    std::cin >> baseX >> baseY >> heroesPerPlayer;

    std::vector<Hero> myHeroes;
    for (int i = 0; i < heroesPerPlayer; ++i)
    {
        myHeroes.emplace_back(i);
    }

    while (true)
    {
        int baseHealth, mana, entityCount;
        std::cin >> baseHealth >> mana >> entityCount;

        std::vector<Entity> entities;
        for (int i = 0; i < entityCount; ++i)
        {
            int id, type, x, y, shieldLife, isControlled, health, vx, vy, nearBase, threatFor;
            std::cin >> id >> type >> x >> y >> shieldLife >> isControlled >> health >> vx >> vy >> nearBase >> threatFor;
            entities.emplace_back(id, type, x, y, shieldLife, isControlled, health, vx, vy, nearBase, threatFor);
        }

        // Process the game state and decide
        // actions for your heroes

        // Example: Move all heroes towards the center of the map
        for (Hero &hero : myHeroes)
        {
            hero.move(17630 / 2, 9000 / 2);
        }

        std::vector<Target> targets;
        for (const Entity &entity : entities)
        {
            if (entity.type == MONSTER)
            {
                double priority = (entity.health * 1000.0) / distance(entity.x, entity.y, baseX, baseY);
                targets.emplace_back(entity.id, priority);
            }
        }

        // 2. Move heroes
        std::sort(targets.begin(), targets.end(), compareTargets);
        for (Hero &hero : myHeroes)
        {
            bool targetFound = false;
            for (const Target &target : targets)
            {
                auto it = std::find_if(entities.begin(), entities.end(), [&](const Entity &e)
                                       { return e.id == target.id; });
                if (it != entities.end())
                {
                    double distToTarget = distance(hero.id, it->x, it->y);
                    if (distToTarget < 800)
                    {
                        hero.move(it->x, it->y);
                        targetFound = true;
                        break;
                    }
                }
            }

            if (!targetFound)
            {
                hero.move(17630 / 2, 9000 / 2);
            }
        }

        // 3. Use spells
        for (Hero &hero : myHeroes)
        {
            // Check if enough mana to cast spells
            if (mana >= 10)
            {
                // Find closest monster to base
                int closestMonsterId = -1;
                double minDistance = std::numeric_limits<double>::max();

                for (const Entity &entity : entities)
                {
                    if (entity.type == MONSTER)
                    {
                        double distToBase = distance(entity.x, entity.y, baseX, baseY);
                        if (distToBase < minDistance)
                        {
                            minDistance = distToBase;
                            closestMonsterId = entity.id;
                        }
                    }
                }

                if (closestMonsterId != -1)
                {
                    // Cast WIND spell to push away the closest monster
                    auto it = std::find_if(entities.begin(), entities.end(), [&](const Entity &e)
                                           { return e.id == closestMonsterId; });
                    if (it != entities.end() && distance(hero.x, hero.y, it->x, it->y) <= 1280)
                    {
                        hero.castWind(it->x, it->y);
                        mana -= 10;
                    }
                }

                // Cast SHIELD on heroes with low health
                if (mana >= 10)
                {
                    for (Hero &heroToShield : myHeroes)
                    {
                        if (heroToShield.health < 10 && distance(hero.x, hero.y, heroToShield.x, heroToShield.y) <= 2200)
                        {
                            hero.castShield(heroToShield.id);
                            mana -= 10;
                            break;
                        }
                    }
                }
                // Cast CONTROL on enemy heroes
                if (mana >= 10)
                {
                    for (const Entity &entity : entities)
                    {
                        if (entity.type == OPPONENT_HERO && distance(hero.x, hero.y, entity.x, entity.y) <= 2200)
                        {
                            // Move enemy hero away from the center
                            hero.castControl(entity.id, entity.x - 1000, entity.y);
                            mana -= 10;
                            break;
                        }
                    }
                }
            }

            // 4. Optimize hero actions
            for (Hero &hero : myHeroes)
            {
                Action bestAction = MCTS(gameState, /*iterations*/ 1000);

                switch (bestAction.actionType)
                {
                case WAIT:
                    std::cout << "WAIT" << std::endl;
                    break;
                case MOVE:
                    std::cout << "MOVE " << bestAction.x << "" << bestAction.y << std::endl;
                    break;
                case SPELL_WIND:
                    std::cout << "SPELL WIND " << bestAction.x << " " << bestAction.y << std::endl;
                    break;
                case SPELL_SHIELD:
                    std::cout << "SPELL SHIELD " << bestAction.targetId << std::endl;
                    break;
                case SPELL_CONTROL:
                    std::cout << "SPELL CONTROL " << bestAction.targetId << " " << bestAction.x << " " << bestAction.y << std::endl;
                    break;
                default:
                    std::cout << "WAIT" << std::endl;
                }
            }
        }
        // TODO: Further optimize hero actions based on the current game state and remaining base health
    }

    return 0;
}
