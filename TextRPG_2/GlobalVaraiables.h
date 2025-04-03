#ifndef GLOBALVARIABLES_H  // Include-Guard, um doppelte Einbindung zu verhindern
#define GLOBALVARIABLES_H

int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
double MaxCharaktersX = ScreenWidth / 8.2;
int MaxCharaktersWidth = static_cast<int>(MaxCharaktersX);
double MaxCharaktersY = ScreenHeight / 17;
int MaxCharaktersHeight = static_cast<int>(MaxCharaktersY);
double CenterXfl = MaxCharaktersX / 2;
int CenterX = static_cast<int>(CenterXfl);
double CenterYfl = MaxCharaktersY / 2;
int CenterY = static_cast<int>(CenterYfl);

//Global relevante Variablen
int zeile = 3;
int initialize = 0;
int currentRoom = 0;
int lastRoom = 0;
int currentRoomMonsterID = -1;
int lastrow = 4;
int currentY = 4;
int direction = -1;
int CurrentMonsterHP = 0;

//Player Stats
std::string PlayerName = "Player";
int level = 0;
int CurrentXP = 0;
int Statpoints = 20;
int XPForLvlUp = 500;
int Strength = 0;
int Dexterity = 0;
int Stamina = 0;
int Intelligence = 0;
int MaxPlayerHP = 100;
int CurrentPlayerHP = 100;
int PlayerDefence = 1;

//Player Equipment
int EquippedChest = -1;
int EquippedHands = -1;
int EquippedLegs = -1;
int EquippedFeet = -1;
int EquippedWeapon = -1;

int LastItem = -1;

#endif