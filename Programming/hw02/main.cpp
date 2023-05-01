int main()
{
    int baseX, baseY;
    cin >> baseX >> baseY;
    cin.ignore();
    Player::base_init(baseX);

    int heroesPerPlayer;
    cin >> heroesPerPlayer;
    cin.ignore();
    int turn = 0;
    while (1)
    {
        cin >> Player::my_health >> Player::my_mana;
        cin.ignore();
        cin >> Player::enemy_health >> Player::enemy_mana;
        cin.ignore();

        int entityCount;
        cin >> entityCount;
        cin.ignore();

        for (int i = 0; i < entityCount; ++i)
        {
            int id, type, x, y, shieldLife, isControlled, health, vx, vy, nearBase, threatFor;
            cin >> id >> type >> x >> y >> shieldLife >> isControlled >> health >> vx >> vy >> nearBase >> threatFor;
            cin.ignore();
            Player::input(id, type, x, y, shieldLife, isControlled, health, vx, vy, nearBase, threatFor);
        }
        int clip = 2;
        Player::enable_previous_info(clip);

        Player::sort_monsters(Player::monsters, Player::near_mybase);

        for (int i = 0; i < 3; ++i)
        {
            if (Player::monsters.size() > 0)
            {
                if (Player::monsters[0] - Player::my_Base < 4000 && Player::canWind(Player::my_heros[i], Player::monsters[0]))
                {
                    Player::cast_wind(Player::enemy_Base.get_X(), Player::enemy_Base.get_Y());
                }
                else
                {
                    Player::chase_monster(Player::monsters[i]);
                }
            }
            else
            {
                pair<int, int> randomPosition;
                if (i == 0)
                {
                    randomPosition = Player::random_pos_circle(50000);
                }
                else if (i == 1)
                {
                    randomPosition = Player::random_pos_circle(80000);
                }
                else if (i == 2)
                {
                    randomPosition = Player::random_pos_circle(50000);
                }
                cout << "MOVE " << randomPosition.first << " " << randomPosition.second << endl;
            }
        }
        Player::clearVector();
    }
}
