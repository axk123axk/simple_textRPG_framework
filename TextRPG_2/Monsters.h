#ifndef MONSTERS_H  // Include-Guard, um doppelte Einbindung zu verhindern
#define MONSTERS_H

//Monster  {NAME, HP, DMG, DEF, ACCURACY, GRANTED XP, FLEE POSIBLE 1=YES, MONSTER LVL


std::vector<std::variant<int, std::string>> MonsterID0 = { "Sheep", 45, 5, 1, 17, 50, 1, 4 };
std::vector<std::variant<int, std::string>> MonsterID1 = { "Door", 400, 0, 4, 20, 0, 1, 0 };

std::vector<std::vector<std::variant<int, std::string>>> monsterVectors = { MonsterID0, MonsterID1 };

//Monster in Raeumen am leben
std::vector<bool> MonsterAliveRoom0 = { true, true };
std::vector<bool> MonsterAliveRoom1 = {  };
std::vector<std::vector<bool>> MonsterAlive = { MonsterAliveRoom0, MonsterAliveRoom1 };

//Namen der Monster
std::vector < std::string > NameMonster = { "Sheep","Door" };

//ASCII Art Monster
std::vector<std::string> MosterID0Art = {
    "   _.-..",
    " ,'9 )\\)-.,.--.",
    " -.|           .",
    "   \\,      ,    \\)",
    "     .  )._\\   (\\",
    "      |//   -,//",
    "      ]||    //\"",
    "       \"\"    \"\""
};

std::vector<std::string> MosterID1Art = {
    "_____________",
    "|  \\     /  |",
    "|   \\   /   |",
    "|    \\ /    |",
    "| O   X     |",
    "|    / \\    |",
    "|   /   \\   |",
    "|  /     \\  |"
};

std::vector < std::vector<std::string>> MonsterArt = { MosterID0Art,MosterID1Art };

//Aggro Monster
std::vector <bool> AggroMonster = { false, false };


#endif