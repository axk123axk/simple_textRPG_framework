#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <conio.h>
#include <variant>
#include <random>
#include "InitializeConsole.h"
#include "Monsters.h"
#include "GlobalVaraiables.h"

#include <map>

// Neighbour Room // North // East // South // West
std::vector <int> NeighbourRooms0 = { -1,-1,-1,-1};
std::vector <int> NeighbourRooms1 = { -1,-1,0,2 };
std::vector <int> NeighbourRooms2 = { -1,1,4,-1 };
std::vector <int> NeighbourRooms3 = { -1,-1,6,-1};
std::vector <int> NeighbourRooms4 = { 2,-1,-1,-1};
std::vector <int> NeighbourRooms5 = { -1,-1,-1,-1 };
std::vector <int> NeighbourRooms6 = { 3,-1,-1,-1 };
std::vector <int> NeighbourRooms[] = { NeighbourRooms0,NeighbourRooms1,NeighbourRooms2,NeighbourRooms3,NeighbourRooms4,NeighbourRooms5,NeighbourRooms6 };

//Name // Description // Req. Intelligence // Permanent 1=YES// Equipment Type -1=NONE 0=Chest 1=Hands 2=Legs 3=Feet 4=Weapon// Strehgth// Dexterity//Stamina //Intelligence// Defence
std::vector<std::variant<int, std::string>> Item0 = {"Hammer","A simple Hammer, which can be used to smash things.",5,1,4,2,0,0,0,0};
std::vector<std::variant<int, std::string>> Item1 = { "Small healing potion","Grants 50 HP on use.",5,0,-1,0,0,0,0,0};
std::vector<std::variant<int, std::string>> Item2 = { "key","An old key, quite heavy. This key might unlock a door or open a chest.",3,0,-1,0,0,0,0,0 };
std::vector<std::variant<int, std::string>> Item3 = { "Note","A Note, multiple times folded.",12,1,-1,0,0,0,0,0 };
std::vector<std::variant<int, std::string>> Item4 = { "Tome of Defence","Upon the spine of the book are depicted various combat stances. After studying it, a new ability is granted.",5,0,-1,0,0,0,0,0 };


std::vector<std::variant<int, std::string>> Items[] = { Item0,Item1, Item2, Item3, Item4};

std::vector<int> IRoom0 = { 2,3 };
std::vector<int> IRoom1 = { 4 };
std::vector<int> ItemsInRoom[] = { IRoom0, IRoom1 };

std::vector<int> DRoom0 = { 0 };
std::vector<int> DRoom1 = {  };
std::vector<int> DropsInRoom[] = { DRoom0, DRoom1 };

std::vector<int> MRoom0 = { 0, 1 };
std::vector<int> MRoom1 = { 0 };
std::vector<int> MonstersInRoom[] = { MRoom0, MRoom1 };

std::vector<std::string> RoomDescription
= { 
"You wake up in a dimly lit, cold room. The air is heavy with the smell of damp stone and stale air. As your eyes adjust to the darkness, you notice rough, uneven stone walls surrounding you, barely illuminated by a faint flickering light from an unknown source. The floor beneath you is hard and covered in dust, as if no one has stepped foot here in years. To the north, you see a sturdy wooden door, worn and scratched, its iron hinges rusted.It's the only visible exit from the room, but as you try the handle, it doesn't budge—it’s locked.The door feels unnaturally heavy, and despite your best efforts, it won't give way. A sense of unease settles in as you realize you might not be alone down here. The rest of the room is sparse.There’s a broken chair in the corner, a few scattered papers near your feet, and an old, unlit lantern on a small table beside the wall.Other than that, the room seems devoid of any other furniture or obvious clues.The only sounds you hear are your own breathing and the distant dripping of water echoing through the silence.", 
"As you step through the door, the hinges groaning in protest, you find yourself in a narrow passageway. The air here feels just as stale as the room behind you, but the space is slightly more open. The stone walls continue, lined with faint cracks and patches of moss, and the ground beneath your feet is uneven, with the occasional stone jutting out. To your left, the passage leads west into a darker corridor, barely visible in the faint light.The floor slopes slightly downward in that direction, and you can hear a faint sound of trickling water echoing from somewhere in the distance. To your right, the passage heads east, where the air feels a bit cooler, though the way ahead is obscured by shadow.There are no signs or markings to guide you, and both paths seem equally uninviting.The silence around you feels heavy, broken only by the occasional drip of water and the soft scuffling of your footsteps."
};

std::vector<std::string> AttackOptions = {"Hit"};


std::vector <int> Inventory = {0,1};
std::map<int, int> InventoryMap;


void DropItem(int ItemID)
{
    ItemsInRoom[currentRoom].push_back(ItemID);
}

void RespawnMonster(int Room, int MonsterID)
{
    int i = 0;
    while (i < MonstersInRoom[Room].size())
    {
        if (MonstersInRoom[Room][i] == MonsterID && MonsterAlive[Room][i] == false)
        { MonsterAlive[Room][i]=true; }
        i++;
    }

}


std::vector<std::string> CreateInterfaceStrings()
{
    std::vector<std::string> Interface;
    int counteri = 0;
    int laenge = MaxCharaktersWidth - 5;
    std::string Kopf = "";
    Kopf += "\n\n   ┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "   ├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "   └";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "   │";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    Interface.push_back(Kopf);
    Interface.push_back(Quer);
    Interface.push_back(Fuss);
    Interface.push_back(Koerper);
    return Interface;
}

void AddAttack(std::string attack) 
{
    int i = 0;
    int k = 0;
    while (i < AttackOptions.size())
    {
        if (AttackOptions[i] == attack)
        {
            k = 1;
        }
        i++;
    }
    if (k == 0)
    {
        AttackOptions.push_back(attack);
    }
}


void InfoFrame(int pos, std::string text)
{
    std::vector<std::string> ItemInterface;
    int counteri = 0;
    int laenge = 44;
    std::string Kopf = "";
    Kopf += "┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "└";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "│";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    ItemInterface.push_back(Kopf);
    ItemInterface.push_back(Quer);
    ItemInterface.push_back(Fuss);
    ItemInterface.push_back(Koerper);

    int hoehe = 10;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(24, counterii + 11+pos); std::cout << ItemInterface[0]; }
        if (counterii == 2) { SetCursorPosition(24, counterii + 11 + pos); std::cout << ItemInterface[1]; }
        if (counterii == hoehe - 1) { SetCursorPosition(24, counterii + 11 + pos); std::cout << ItemInterface[2]; }
        if (counterii != 0 && counterii != 2 && counterii != hoehe - 1) { SetCursorPosition(24, counterii + 11 + pos); std::cout << ItemInterface[3]; }
        counterii++;
    }
    SetCursorPosition(26, 12+pos);
    std::cout << "\033[30m\033[47m" << "Info" << "\033[0m";
    SetCursorPosition(26, 15+pos);
    int maxWidth = 42;
    int startX = 26;
    int lineLength = 0;
    int startY = 14 + pos;
    int currentY = startY;
    int i = 0;
    int k = 0;
    int lastSpace = 0;
    while (text.length() > 0) {
        SetCursorPosition(startX, currentY);
        if (text.length() < maxWidth) { std::cout << text; lastrow = currentY + 1; break; }
        while (k <= lastSpace) {
            while (i <= maxWidth) {
                if (i <= text.length()) {
                    if (text[i] == ' ') { lastSpace = i; }
                    i++;
                }
                else { i = maxWidth; }
            }
            std::cout << text[k];
            k++;
        }
        if (lastSpace <= text.length()) {

            text.erase(0, lastSpace + 1);
            currentY++;
            k = 0;
            i = 0;
            lastSpace = 0;
        }

    }

    char input = 0;
    while (true) {
        SetCursorPosition(0, 0);
        char input = _getch();
        if (input == 13) { break; }
    }
}

void DrawSimpleInterfaceFrame()
{
    std::vector<std::string> Interfacei = CreateInterfaceStrings();
    int hoehe = MaxCharaktersHeight - 1;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { std::cout << Interfacei[0]; }
        if (counterii == hoehe - 5) { std::cout << Interfacei[1]; }
        if (counterii == hoehe - 1) { std::cout << Interfacei[2]; }
        if (counterii != 0 && counterii != hoehe - 5 && counterii != hoehe - 1) { std::cout << Interfacei[3]; }
        counterii++;
    }
    counterii = 2;
    while (counterii < hoehe - 2) {
        SetCursorPosition(MaxCharaktersWidth - 25, counterii);
        if (counterii == 2) { std::cout << "┬"; }
        if (counterii == hoehe - 3) { std::cout << "┴"; }
        if (counterii != hoehe - 3 && counterii != 2) { std::cout << "│"; }
        counterii++;
    }
    std::vector<std::string> Commands = { "go north","go east","go south","go west","inventory","stats","look around","take <item>","attack <Monster>"};
        int i = 0;
        SetCursorPosition(MaxCharaktersWidth-23, 4);
        std::cout << "\033[30m\033[47m" << "Available Commands:" << "\033[0m" << std::endl;
    while (i < Commands.size()) { SetCursorPosition(MaxCharaktersWidth - 23, 6 + 2*i); std::cout << Commands[i]; i++; }

    SetCursorPosition(6, hoehe - 1);
    std::cout << "Awaiting Command: ";
}

void DisplayTextOnScreen(std::string& text) {
    int maxWidth = MaxCharaktersWidth - 32;
    int startX = 6;
    int lineLength = 0;
    currentY = lastrow;
    if (currentY > MaxCharaktersHeight - 6) {
        currentY = 4;
        system("cls");
        DrawSimpleInterfaceFrame();
    }
    int i = 0;
    int k = 0;
    int lastSpace = 0;
    while (text.length() > 0) {
        SetCursorPosition(startX, currentY);
        if (text.length() < maxWidth) { std::cout << text; lastrow = currentY + 1; break; }
        while (k <= lastSpace) {
            while (i <= maxWidth) {
                if (i <= text.length()) {
                    if (text[i] == ' ') { lastSpace = i; }
                    i++;
                }
                else { i = maxWidth; }
            }
            std::cout << text[k];
            k++;
        }
        if (lastSpace <= text.length()) {

            text.erase(0, lastSpace + 1);
            currentY++;
            k = 0;
            i = 0;
            lastSpace = 0;
        }

    }

}

std::string GenerateRoomDescripton(int currentRoom)
{
    std::string tempRoomDescription = "";
    tempRoomDescription += RoomDescription[currentRoom];
    tempRoomDescription += "\n\n";
    tempRoomDescription += "\033[C\033[C\033[C\033[C\033[C\033[C";
    int k = 0;
    while (k < MonsterAlive[currentRoom].size())
    {
        if (MonsterAlive[currentRoom][k] = true)
        {
            tempRoomDescription += "There is a ";
            int monsterid = MonstersInRoom[currentRoom][k];
            tempRoomDescription += std::get<std::string>(monsterVectors[monsterid][0]);
            tempRoomDescription += " in the Room. It appears to be ";
            if (AggroMonster[monsterid] == true) { tempRoomDescription += "hostile."; }
            else { tempRoomDescription += "friendly. "; }
        }
        k++;
    }
    return tempRoomDescription;
}

void CallNewRoom(int dir) {
    if (NeighbourRooms[currentRoom][dir] != -1) {
        currentRoom = NeighbourRooms[currentRoom][dir];
        system("cls");
        DrawSimpleInterfaceFrame();
        lastrow = 4;
        std::string tempDescription=GenerateRoomDescripton(currentRoom);
        DisplayTextOnScreen(tempDescription);
        lastrow = lastrow + 5;
        }
    else { std::string msg="You are not able to go this direction.";
    system("cls");
    DrawSimpleInterfaceFrame();
    lastrow = 4;
    DisplayTextOnScreen(msg);
    }
}


std::vector<std::string> CreateInventoryStrings()
{
    std::vector<std::string> InventoryInterface;
    int counteri = 0;
    int laenge = MaxCharaktersWidth - 36;
    std::string Kopf = "";
    Kopf += "   ┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "   ├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "   └";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "   │";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    InventoryInterface.push_back(Kopf);
    InventoryInterface.push_back(Quer);
    InventoryInterface.push_back(Fuss);
    InventoryInterface.push_back(Koerper);
    return InventoryInterface;
}

void DrawInventoryFrame()
{
    std::vector<std::string> Interfacei = CreateInventoryStrings();
    int hoehe = MaxCharaktersHeight - 9;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(10, counterii+5); std::cout << Interfacei[0]; }
        if (counterii == 2) { SetCursorPosition(10, counterii + 5); std::cout << Interfacei[1]; }
        if (counterii == hoehe - 1) { SetCursorPosition(10, counterii + 5); std::cout << Interfacei[2]; }
        if (counterii != 0 && counterii != 2 && counterii != hoehe - 1) { SetCursorPosition(10, counterii +5); std::cout << Interfacei[3]; }
        counterii++;
    }
}

void DisplayItemDescription(int pos, int itemnr) {
    std::vector<std::string> ItemInterface;
    int counteri = 0;
    int laenge = 44;
    std::string Kopf = "";
    Kopf += "┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "└";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "│";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    ItemInterface.push_back(Kopf);
    ItemInterface.push_back(Quer);
    ItemInterface.push_back(Fuss);
    ItemInterface.push_back(Koerper);

    int hoehe = 8;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(24, counterii + 9 + pos); std::cout << ItemInterface[0]; }
        if (counterii == 2) { SetCursorPosition(24, counterii + 9 + pos); std::cout << ItemInterface[1]; }
        if (counterii == hoehe - 1) { SetCursorPosition(24, counterii + 9 + pos); std::cout << ItemInterface[2]; }
        if (counterii != 0 && counterii != 2 && counterii != hoehe - 1) { SetCursorPosition(24, counterii + 9 + pos); std::cout << ItemInterface[3]; }
        counterii++;
    }
    SetCursorPosition(26, 10 + pos);
    std::cout << "\033[30m\033[47m" << std::get<std::string>(Items[itemnr][0]) << "\033[0m";

    int maxWidth = 42;
    int startX = 26;
    int lineLength = 0;
    int startY = 12 + pos;
    int currentY = startY;
    int i = 0;
    int k = 0;
    int lastSpace = 0;
    auto text = std::get<std::string>(Items[itemnr][1]);
    while (text.length() > 0) {
        SetCursorPosition(startX, currentY);
        if (text.length() < maxWidth) { std::cout << text; lastrow = currentY + 1; break; }
        while (k <= lastSpace) {
            while (i <= maxWidth) {
                if (i <= text.length()) {
                    if (text[i] == ' ') { lastSpace = i; }
                    i++;
                }
                else { i = maxWidth; }
            }
            std::cout << text[k];
            k++;
        }
        if (lastSpace <= text.length()) {

            text.erase(0, lastSpace + 1);
            currentY++;
            k = 0;
            i = 0;
            lastSpace = 0;
        }

    }

    char input=0;
    while (true) {
        SetCursorPosition(0,0);
        char input = _getch();
        if (input == 13) { break; }
    }
}

void ItemEffect(int pos, int itemnr)
{
    //Hammer
    if (itemnr == 0) {
        if (currentRoom == 0) 
        {
            NeighbourRooms[0][0] = 1;
            InfoFrame(pos, "Thou take up the hammer and, with all thy might, smitest upon the lock. Forthwith, the door seems to be open now.");
        }
    
    }
    //Small Healing Potion
    if (itemnr == 1) {
        if (MaxPlayerHP - CurrentPlayerHP < 50) { 
            int AmountHealed = MaxPlayerHP - CurrentPlayerHP;
            CurrentPlayerHP = MaxPlayerHP; 
            std::string text="You used the small healing potion and got ";
            text += std::to_string(AmountHealed);
            text += " HP.";
            InfoFrame(pos, text); }
        else {
            CurrentPlayerHP = CurrentPlayerHP + 50; 
            InfoFrame(pos, "You used the small healing potion and got 50 HP.");
              } 
    }
    //Tome of Defence
    if (itemnr == 4) {
            AddAttack("Defend");
            InfoFrame(pos, "After thorough study and diligent practice, you attain the ability known as Defend. This skill, once mastered, shall serve thee in warding off thy foes, fortifying thy stance in the heat of battle.");

    }
}

void UseItem(int pos, int itemnr)
{
    ItemEffect(pos, itemnr);
    if (std::get<int>(Items[itemnr][3]) == 0) {
        auto it = std::find(Inventory.begin(), Inventory.end(), itemnr);
        if (it != Inventory.end()) {
            Inventory.erase(it);
        }
    }
}

void ChangePlayerStatPoints(int itemnr)
{
    //Name // Description // Req. Intelligence // Permanent 1=YES// Equipment Type -1=NONE 0=Chest 1=Hands 2=Legs 3=Feet 4=Weapon// Strength// Dexterity//Stamina //Intelligence// Defence
    if (LastItem != -1&& itemnr!=-1)
    {
        Strength = Strength - std::get<int>(Items[LastItem][5]) + std::get<int>(Items[itemnr][5]);
        Dexterity = Dexterity - std::get<int>(Items[LastItem][6]) + std::get<int>(Items[itemnr][6]);
        Stamina = Stamina - std::get<int>(Items[LastItem][7]) + std::get<int>(Items[itemnr][7]);
        Intelligence = Intelligence - std::get<int>(Items[LastItem][8]) + std::get<int>(Items[itemnr][8]);
        PlayerDefence = PlayerDefence - std::get<int>(Items[LastItem][9]) + std::get<int>(Items[itemnr][9]);
    }
    if (LastItem != -1 && itemnr == -1)
    {
        Strength = Strength - std::get<int>(Items[LastItem][5]);
        Dexterity = Dexterity - std::get<int>(Items[LastItem][6]);
        Stamina = Stamina - std::get<int>(Items[LastItem][7]);
        Intelligence = Intelligence - std::get<int>(Items[LastItem][8]);
        PlayerDefence = PlayerDefence - std::get<int>(Items[LastItem][9]);
    }
    if (LastItem == -1&&itemnr!=-1)
    {
        Strength = Strength + std::get<int>(Items[itemnr][5]);
        Dexterity = Dexterity + std::get<int>(Items[itemnr][6]);
        Stamina = Stamina + std::get<int>(Items[itemnr][7]);
        Intelligence = Intelligence + std::get<int>(Items[itemnr][8]);
        PlayerDefence = PlayerDefence + std::get<int>(Items[itemnr][9]);
    }
}

void ShowPossibleEquipments(int type) {
    std::vector <int> TempInventory;
    std::map<int, int> TempInventoryMap;
    int j = 0;
    while (j < Inventory.size())
    {
      if(std::get<int>(Items[Inventory[j]][4])==type)
      {
          TempInventory.push_back(Inventory[j]);
      }
      j++;
    }
start:
    DrawInventoryFrame();
    SetCursorPosition(16, 6);
    std::cout << "\033[30m\033[47m" << "Possible Equipment:" << "\033[0m";
    int k = 0;
    int tempcount;
    std::vector <int> ItemsInInventory;
    for (const auto& item : TempInventory) {
        TempInventoryMap[item]++;  // Erhöhe den Zähler für das aktuelle Element
    }
    for (const auto& [key, value] : TempInventoryMap) {
        SetCursorPosition(18, 9 + k);
        ItemsInInventory.push_back(key);
        std::cout << std::get<std::string>(Items[key][0]) << " (" << value << "x)";  // Gibt den Schlüssel aus
        k++;
    }
    SetCursorPosition(18, 9 + k);
    std::cout << "unequip";
    SetCursorPosition(18, 9 + k+1);
    std::cout << "exit menu";
    tempcount = k + 2;
    int cursorPosition = 0;
    while (true) {
        for (int i = 0; i < tempcount; ++i) {
            SetCursorPosition(16, 9 + i);
            if (i == cursorPosition) {
                std::cout << "> ";
            }
            else { std::cout << " "; }
        }
        SetCursorPosition(0, 0);
        char input = _getch();
        if (input == 72) { // Nach oben (Pfeiltaste hoch)
            cursorPosition = (cursorPosition - 1 + tempcount) % tempcount;
        }
        else if (input == 80) { // Nach unten (Pfeiltaste runter)
            cursorPosition = (cursorPosition + 1) % tempcount;
        }
        else if (input == 13) { // Entertaste
            if (cursorPosition <tempcount-2) {
                if (type == 0)
                {
                    LastItem = EquippedChest;
                    EquippedChest = ItemsInInventory[cursorPosition];
                }
                if (type == 1)
                {
                    LastItem = EquippedHands;
                    EquippedHands = ItemsInInventory[cursorPosition];
                }
                if (type == 2)
                {
                    LastItem = EquippedLegs;
                    EquippedLegs = ItemsInInventory[cursorPosition];
                }
                if (type == 3)
                {
                    LastItem = EquippedFeet;
                    EquippedFeet = ItemsInInventory[cursorPosition];
                }
                if (type == 4)
                {
                    LastItem = EquippedWeapon;
                    EquippedWeapon = ItemsInInventory[cursorPosition];
                }
                TempInventoryMap.clear();
                ChangePlayerStatPoints(ItemsInInventory[cursorPosition]);
                break;
            }
            if (cursorPosition == tempcount-2)
            {
                if (type == 0)
                {
                    LastItem = EquippedChest;
                    EquippedChest = -1;
                }
                if (type == 1)
                {
                    LastItem = EquippedHands;
                    EquippedHands = -1;
                }
                if (type == 2)
                {
                    LastItem = EquippedLegs;
                    EquippedLegs = -1;
                }
                if (type == 3)
                {
                    LastItem = EquippedFeet;
                    EquippedFeet = -1;
                }
                if (type == 4)
                {
                    LastItem = EquippedWeapon;
                    EquippedWeapon = -1;
                }
                TempInventoryMap.clear();
                ChangePlayerStatPoints(-1);
                break;

            }
            if (cursorPosition == tempcount-1) {
                TempInventoryMap.clear();
                //    system("cls");
                //    DrawSimpleInterfaceFrame(); 
                break;
            }
        }
    }
}

void EquipmentInfo(int pos)
{
    std::vector<std::string> ItemInterface;
    std::vector<std::string> Commands = { "inspect equipment","equip item","exit" };
    std::vector<std::string> Slot = { "chest","hands","legs", "feet", "weapon"};
    int counteri = 0;
    int laenge = 24;
    std::string Kopf = "";
    Kopf += "┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "└";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "│";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    ItemInterface.push_back(Kopf);
    ItemInterface.push_back(Quer);
    ItemInterface.push_back(Fuss);
    ItemInterface.push_back(Koerper);

    int hoehe = 7;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(20, counterii + 8 + 3*pos); std::cout << ItemInterface[0]; }
        if (counterii == 2) { SetCursorPosition(20, counterii + 8 + 3*pos); std::cout << ItemInterface[1]; }
        if (counterii == hoehe - 1) { SetCursorPosition(20, counterii + 8 + 3*pos); std::cout << ItemInterface[2]; }
        if (counterii != 0 && counterii != 2 && counterii != hoehe - 1) { SetCursorPosition(20, counterii + 8 + 3*pos); std::cout << ItemInterface[3]; }
        counterii++;
    }
    SetCursorPosition(22, 9 + 3*pos);
    std::cout << "\033[30m\033[47m" << Slot[pos] << "\033[0m";

    int l = 0;
    while (l < Commands.size()) {
        SetCursorPosition(23, 11 + 3*pos + l);
        std::cout << Commands[l];
        l++;
    }

    int tempcount;
    tempcount = Commands.size();
    int cursorPosition = 0;
    while (true) {
        for (int i = 0; i < tempcount; ++i) {
            SetCursorPosition(21, 8 + 3*pos + l + i);
            if (i == cursorPosition) {
                std::cout << "> ";
            }
            else { std::cout << " "; }
        }
        SetCursorPosition(0, 0);
        char input = _getch();
        if (input == 72) { // Nach oben (Pfeiltaste hoch)
            cursorPosition = (cursorPosition - 1 + tempcount) % tempcount;
        }
        else if (input == 80) { // Nach unten (Pfeiltaste runter)
            cursorPosition = (cursorPosition + 1) % tempcount;
        }
        else if (input == 13) { // Entertaste
            int itemnr;
            if (pos == 0) { itemnr = EquippedChest; }
            if (pos == 1) { itemnr = EquippedHands; }
            if (pos == 2) { itemnr = EquippedLegs; }
            if (pos == 3) { itemnr = EquippedFeet; }
            if (pos == 4) { itemnr = EquippedWeapon; }
            if (cursorPosition == 0) {
                if (itemnr != -1) {
                    DisplayItemDescription(pos, itemnr);
                }
                break;
            }
            if (cursorPosition == 1) {
                ShowPossibleEquipments(pos);

                break;
            }
            if (cursorPosition == 2) {
                break;
            }

        }
    }
}

void ItemInfo(int pos, int itemnr)
{
    std::vector<std::string> ItemInterface;
    std::vector<std::string> Commands = { "inspect","use","exit"};
    int counteri = 0;
    int laenge = 24;
    std::string Kopf = "";
    Kopf += "┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "└";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "│";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    ItemInterface.push_back(Kopf);
    ItemInterface.push_back(Quer);
    ItemInterface.push_back(Fuss);
    ItemInterface.push_back(Koerper);

    int hoehe = 7;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(20, counterii + 8+pos); std::cout << ItemInterface[0]; }
        if (counterii == 2) { SetCursorPosition(20, counterii + 8+ pos); std::cout << ItemInterface[1]; }
        if (counterii == hoehe - 1) { SetCursorPosition(20, counterii + 8+ pos); std::cout << ItemInterface[2]; }
        if (counterii != 0 && counterii != 2 && counterii != hoehe - 1) { SetCursorPosition(20, counterii + 8+ pos); std::cout << ItemInterface[3]; }
        counterii++;
    }
    SetCursorPosition(22, 9+pos);
    std::cout << "\033[30m\033[47m" << std::get<std::string>(Items[itemnr][0]) << "\033[0m";

    int l = 0;
    while (l < Commands.size()) {
        SetCursorPosition(23, 11 + pos+l);
        std::cout <<Commands[l];
        l++;
    }

    int tempcount;
    tempcount = Commands.size();
    int cursorPosition = 0;
    while (true) {
        for (int i = 0; i < tempcount; ++i) {
            SetCursorPosition(21, 8+pos+l + i);
            if (i == cursorPosition) {
                std::cout << "> ";
            }
            else { std::cout << " "; }
        }
        SetCursorPosition(0, 0);
        char input = _getch();
        if (input == 72) { // Nach oben (Pfeiltaste hoch)
            cursorPosition = (cursorPosition - 1 + tempcount) % tempcount;
        }
        else if (input == 80) { // Nach unten (Pfeiltaste runter)
            cursorPosition = (cursorPosition + 1) % tempcount;
        }
        else if (input == 13) { // Entertaste
            if (cursorPosition == 0) {
                DisplayItemDescription(pos,itemnr);
                break;
            }
            if (cursorPosition == 1) {
                UseItem(pos,itemnr);
                break;
            }
            if (cursorPosition == 2) {
                break;
            }

        }
    }
}

void DisplayInventory() {
    start:
    DrawInventoryFrame();
    SetCursorPosition(16, 6);
    std::cout << "\033[30m\033[47m" << "Your current Inventory:" << "\033[0m";
    int k = 0;
    int tempcount;
    std::vector <int> ItemsInInventory;
    for (const auto& item : Inventory) {
        InventoryMap[item]++;  // Erhöhe den Zähler für das aktuelle Element
    }
    for (const auto& [key, value] : InventoryMap) {
        SetCursorPosition(18, 9 + k);
        ItemsInInventory.push_back(key);
        std::cout << std::get<std::string>(Items[key][0]) << " (" << value << "x)";  // Gibt den Schlüssel aus
        k++;
    }
    SetCursorPosition(18, 9 + k);
    std::cout << "exit menu";
    tempcount = k+1;
    int cursorPosition=0;
    while (true) {
        for (int i = 0; i < tempcount; ++i) {
            SetCursorPosition(16, 9 + i);
            if (i == cursorPosition) {
                std::cout << "> ";
            }
            else { std::cout << " "; }
        }
        SetCursorPosition(0,0);
        char input = _getch();
        if (input == 72) { // Nach oben (Pfeiltaste hoch)
                cursorPosition = (cursorPosition - 1 + tempcount) % tempcount;
        }
        else if (input == 80) { // Nach unten (Pfeiltaste runter)
            cursorPosition = (cursorPosition + 1) % tempcount;
        }
        else if (input == 13) { // Entertaste
            if (cursorPosition != k) {
                ItemInfo(cursorPosition,ItemsInInventory[cursorPosition]);
                InventoryMap.clear();
                goto start;
            }
            else {
                InventoryMap.clear();
            //    system("cls");
            //    DrawSimpleInterfaceFrame(); 
                break; }
        }
    }
  }

void DrawBarDiagramm(float part,float max,int StartX,int StartY,int laenge) {

    std::vector<std::string> ItemInterface;
    int counteri = 0;
    std::string Kopf = "";
    Kopf += "┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "└";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "│";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    ItemInterface.push_back(Kopf);
    ItemInterface.push_back(Fuss);
    ItemInterface.push_back(Koerper);

    int hoehe = 3;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(StartX, counterii + StartY); std::cout << ItemInterface[0]; }
        if (counterii == hoehe - 1) { SetCursorPosition(StartX, counterii + StartY); std::cout << ItemInterface[1]; }
        if (counterii != 0 && counterii != 2 && counterii != hoehe - 1) { SetCursorPosition(StartX, counterii + StartY); std::cout << ItemInterface[2]; }
        counterii++;
    }
    int percentage = part / max*laenge;
    int i = 0;
    while (i < percentage) {
        SetCursorPosition(StartX+1+i, StartY+1);
        std::cout << "█";
        i++;
    }
    while (i < laenge)
    {
        SetCursorPosition(StartX + 1 + i, StartY + 1);
        std::cout << " ";
        i++;
    }
}

void DisplayPlayerStats() {
    system("cls");
    DrawSimpleInterfaceFrame();
    lastrow = 4;
    DrawInventoryFrame();
    SetCursorPosition(16, 6);
    std::cout << "\033[30m\033[47m" << "Character information:" << "\033[0m";
    SetCursorPosition(16, 9);
std::cout << "Name:";
SetCursorPosition(31, 9);
std::cout << PlayerName<<"  (Level "<< level<<")";
    SetCursorPosition(16, 11);
std::cout << "Health points:";
SetCursorPosition(31, 11);
std::cout << CurrentPlayerHP << "/" << MaxPlayerHP;
DrawBarDiagramm(CurrentPlayerHP, MaxPlayerHP, 18, 13,50);
SetCursorPosition(16, 17);
std::cout << "Strength:";
SetCursorPosition(31, 17);
std::cout << Strength;
SetCursorPosition(16, 19);
std::cout << "Dexterity:";
SetCursorPosition(31, 19);
std::cout << Dexterity;
SetCursorPosition(16, 21);
std::cout << "Intelligence:";
SetCursorPosition(31, 21);
std::cout << Intelligence;
SetCursorPosition(16, 23);
std::cout << "Stamina:";
SetCursorPosition(31, 23);
std::cout << Stamina;
SetCursorPosition(16, 25);
std::cout << "EXP:";
SetCursorPosition(31, 25);
std::cout << CurrentXP<<"/"<<XPForLvlUp;
DrawBarDiagramm(CurrentXP, XPForLvlUp, 18, 27, 50);
char input = 0;
while (true) {
    SetCursorPosition(0, 0);
    char input = _getch();
    if (input == 13) { break; }
}
system("cls");
DrawSimpleInterfaceFrame();
}


void DisplayCharakterEquipment() {
    system("cls");
    DrawSimpleInterfaceFrame();
    int tempw = MaxCharaktersWidth;
    MaxCharaktersWidth = 85;
    int temph = MaxCharaktersHeight;
    MaxCharaktersHeight = 36;
    lastrow = 4;
    Start:
    DrawInventoryFrame();
    SetCursorPosition(16, 6);
    std::cout << "\033[30m\033[47m" << "Your current equipment" << "\033[0m";
    SetCursorPosition(34, 8);
    std::cout << "str";
    SetCursorPosition(38, 8);
    std::cout << "dex";
    SetCursorPosition(42, 8);
    std::cout << "sta";
    SetCursorPosition(46, 8);
    std::cout << "int";
    SetCursorPosition(50, 8);
    std::cout << "def";
    SetCursorPosition(18, 9);
    std::cout << "chest:";
    SetCursorPosition(20, 10);
    if (EquippedChest == -1)
    {
        std::cout << "(none)";
        SetCursorPosition(35, 10);
        std::cout << "-";
        SetCursorPosition(39, 10);
        std::cout << "-";
        SetCursorPosition(43, 10);
        std::cout << "-";
        SetCursorPosition(47, 10);
        std::cout << "-";
        SetCursorPosition(51, 10);
        std::cout << "-";
    }
    else {
        std::cout << std::get<std::string>(Items[EquippedChest][0]);
        SetCursorPosition(35, 10);
        std::cout << std::get<int>(Items[EquippedChest][5]);
        SetCursorPosition(39, 10);
        std::cout << std::get<int>(Items[EquippedChest][6]);
        SetCursorPosition(43, 10);
        std::cout << std::get<int>(Items[EquippedChest][7]);
        SetCursorPosition(47, 10);
        std::cout << std::get<int>(Items[EquippedChest][8]);
        SetCursorPosition(51, 10);
        std::cout << std::get<int>(Items[EquippedChest][9]);
    }

    SetCursorPosition(18, 13);
    std::cout << "hands:";
    SetCursorPosition(20, 14);
    if (EquippedHands == -1)
    {
        std::cout << "(none)";
        SetCursorPosition(35, 14);
        std::cout << "-";
        SetCursorPosition(39, 14);
        std::cout << "-";
        SetCursorPosition(43, 14);
        std::cout << "-";
        SetCursorPosition(47, 14);
        std::cout << "-";
        SetCursorPosition(51, 14);
        std::cout << "-";
    }
    else {
        std::cout << std::get<std::string>(Items[EquippedHands][0]);
        SetCursorPosition(35, 14);
        std::cout << std::get<int>(Items[EquippedHands][5]);
        SetCursorPosition(39, 14);
        std::cout << std::get<int>(Items[EquippedHands][6]);
        SetCursorPosition(43, 14);
        std::cout << std::get<int>(Items[EquippedHands][7]);
        SetCursorPosition(47, 14);
        std::cout << std::get<int>(Items[EquippedHands][8]);
        SetCursorPosition(51, 14);
        std::cout << std::get<int>(Items[EquippedHands][9]);
    }
    SetCursorPosition(18, 17);
    std::cout << "legs:";
    SetCursorPosition(20, 18);
    if (EquippedLegs == -1)
    {
        std::cout << "(none)";
        SetCursorPosition(35, 18);
        std::cout << "-";
        SetCursorPosition(39, 18);
        std::cout << "-";
        SetCursorPosition(43, 18);
        std::cout << "-";
        SetCursorPosition(47, 18);
        std::cout << "-";
        SetCursorPosition(51, 18);
        std::cout << "-";
    }
    else {
        std::cout << std::get<std::string>(Items[EquippedLegs][0]);
        SetCursorPosition(35, 18);
        std::cout << std::get<int>(Items[EquippedLegs][5]);
        SetCursorPosition(39, 18);
        std::cout << std::get<int>(Items[EquippedLegs][6]);
        SetCursorPosition(43, 18);
        std::cout << std::get<int>(Items[EquippedLegs][7]);
        SetCursorPosition(47, 18);
        std::cout << std::get<int>(Items[EquippedLegs][8]);
        SetCursorPosition(51, 18);
        std::cout << std::get<int>(Items[EquippedLegs][9]);
    }
    SetCursorPosition(18, 21);
    std::cout << "feet:";
    SetCursorPosition(20, 22);
    if (EquippedFeet == -1)
    {
        std::cout << "(none)";
        SetCursorPosition(35, 22);
        std::cout << "-";
        SetCursorPosition(39, 22);
        std::cout << "-";
        SetCursorPosition(43, 22);
        std::cout << "-";
        SetCursorPosition(47, 22);
        std::cout << "-";
        SetCursorPosition(51, 22);
        std::cout << "-";
    }
    else {
        std::cout << std::get<std::string>(Items[EquippedFeet][0]);
        SetCursorPosition(35, 22);
        std::cout << std::get<int>(Items[EquippedFeet][5]);
        SetCursorPosition(39, 22);
        std::cout << std::get<int>(Items[EquippedFeet][6]);
        SetCursorPosition(43, 22);
        std::cout << std::get<int>(Items[EquippedFeet][7]);
        SetCursorPosition(47, 22);
        std::cout << std::get<int>(Items[EquippedFeet][8]);
        SetCursorPosition(51, 22);
        std::cout << std::get<int>(Items[EquippedFeet][9]);
    }
    SetCursorPosition(18, 25);
    std::cout << "weapon:";
    SetCursorPosition(20, 26);
    if (EquippedWeapon == -1)
    {
        std::cout << "(none)";
        SetCursorPosition(35, 26);
        std::cout << "-";
        SetCursorPosition(39, 26);
        std::cout << "-";
        SetCursorPosition(43, 26);
        std::cout << "-";
        SetCursorPosition(47, 26);
        std::cout << "-";
        SetCursorPosition(51, 26);
        std::cout << "-";
    }
    else {
        std::cout << std::get<std::string>(Items[EquippedWeapon][0]);
        SetCursorPosition(35, 26);
        std::cout << std::get<int>(Items[EquippedWeapon][5]);
        SetCursorPosition(39, 26);
        std::cout << std::get<int>(Items[EquippedWeapon][6]);
        SetCursorPosition(43, 26);
        std::cout << std::get<int>(Items[EquippedWeapon][7]);
        SetCursorPosition(47, 26);
        std::cout << std::get<int>(Items[EquippedWeapon][8]);
        SetCursorPosition(51, 26);
        std::cout << std::get<int>(Items[EquippedWeapon][9]);
    }
    SetCursorPosition(18, 29);
    std::cout << "Exit Menu";

    int cursorPosition = 0;
    while (true) {
                for (int i = 0; i < 6; ++i) {
            SetCursorPosition(16, 9 + 4 * i);
            if (i == cursorPosition) {
                std::cout << "> ";
            }
            else { std::cout << " "; }
        }
        SetCursorPosition(0, 0);
        char in = _getch();
        if (in == 72) { // Nach oben (Pfeiltaste hoch)
            cursorPosition = (cursorPosition + 6 - 1) % 6;
        }
        else if (in == 80) { // Nach unten (Pfeiltaste runter)
            cursorPosition = (cursorPosition + 1) % 6;
        }
        else if (in == 13) { //Enter
            if (cursorPosition == 5)
            {
                MaxCharaktersWidth = tempw;
                MaxCharaktersHeight = temph;
                break;
            }
            else { EquipmentInfo(cursorPosition); 
            goto Start;
            }
        }
    }
    system("cls");
    DrawSimpleInterfaceFrame();
}

void LookAround(){
    system("cls");
    DrawSimpleInterfaceFrame();
    int i=0;
    int k=0;
    while (i < ItemsInRoom[currentRoom].size())
    {
        int value = std::get<int>(Items[ItemsInRoom[currentRoom][i]][2]);
        if (value <= Intelligence)
        {
            k++;
        }
        i++;
    }
    i = 0;
    if (k == 0) {
        std::string msg = "As thou dost take a closer survey of the chamber, thou discern'st naught of interest nor of possible utility.";
        DisplayTextOnScreen(msg);
    }
    if (k == 1) {
        std::string msg = "As thou dost take a closer survey of the chamber, you see the following item:";
        DisplayTextOnScreen(msg);
        currentY++;
        currentY++;
        while (i < ItemsInRoom[currentRoom].size())
        {
            int value = std::get<int>(Items[ItemsInRoom[currentRoom][i]][2]);
            if (value <= Intelligence)
            {
                SetCursorPosition(6, currentY);
                std::cout << "- " << std::get<std::string>(Items[ItemsInRoom[currentRoom][i]][0]);
                currentY++;
            }
            i++;
        }

    }
    if (k > 1) {
        std::string msg = "As thou dost take a closer survey of the chamber, you see the following items:";
        DisplayTextOnScreen(msg);
        currentY++;
        currentY++;
        while (i < ItemsInRoom[currentRoom].size())
        {
            int value = std::get<int>(Items[ItemsInRoom[currentRoom][i]][2]);
            if (value <= Intelligence)
            {
                SetCursorPosition(6, currentY);
                std::cout << "- " << std::get<std::string>(Items[ItemsInRoom[currentRoom][i]][0]);
                currentY++;
                currentY++;
            }
            i++;
        }

    }
}

void TakeItem(std::string& item) 
{
    system("cls");
    DrawSimpleInterfaceFrame();
    int i = 0;
    int k = -1;
    while (i < ItemsInRoom[currentRoom].size())
    {
        int value = std::get<int>(Items[ItemsInRoom[currentRoom][i]][2]);
        if (value <= Intelligence)
        {
            if (std::get<std::string>(Items[ItemsInRoom[currentRoom][i]][0]) == item) {
                k = i;
            }
        }
        i++;
    }
            if (k != -1)
        {
            Inventory.push_back(ItemsInRoom[currentRoom][k]);
        ItemsInRoom[currentRoom].erase(ItemsInRoom[currentRoom].begin() + k);
    }
            if (k == -1)
            {
                std::string msg = "There is no such an Item in this Room.";
                DisplayTextOnScreen(msg);
            }
}

void DrawAsciiArt(int monsterid)
{
    int i = 0;
    while (i < MonsterArt[monsterid].size())
    {
        SetCursorPosition(MaxCharaktersWidth - 53, 14+i);
        std::cout << MonsterArt[monsterid][i];
            i++;
    }

}


void BattleFrame(int CurrentMonsterHP, int MaxMonsterHP, std::string& CurrentMonsterName, int monsterid) {


    DrawInventoryFrame();
    SetCursorPosition(16, 6);
    std::cout << "\033[30m\033[47m" << "A Battle begins" << "\033[0m";
    SetCursorPosition(MaxCharaktersWidth - 53, 8);
    std::cout << CurrentMonsterName;
    SetCursorPosition(MaxCharaktersWidth - 53, 9);
    std::cout << CurrentMonsterHP << " / " << MaxMonsterHP;
    DrawBarDiagramm(CurrentMonsterHP, MaxMonsterHP, MaxCharaktersWidth - 55, 10, 30);
    DrawBarDiagramm(CurrentPlayerHP, MaxPlayerHP, 15, MaxCharaktersHeight - 13, 30);
    DrawAsciiArt(monsterid);
    SetCursorPosition(17, MaxCharaktersHeight - 15);
    std::cout << PlayerName;
    SetCursorPosition(17, MaxCharaktersHeight - 14);
    std::cout << CurrentPlayerHP << " / " << MaxPlayerHP;
    SetCursorPosition(18, MaxCharaktersHeight - 9);
    std::cout << "Attack";
    SetCursorPosition(18, MaxCharaktersHeight - 8);
    std::cout << "Item";
    SetCursorPosition(18, MaxCharaktersHeight - 7);
    std::cout << "Flee";

}

int DealAttackDamage(int Attack) 
{
    int Damage;
        std::string UsedAttack = AttackOptions[Attack];
        if (UsedAttack == "Hit")
        {
            Damage=Strength+1;
        }
        if (UsedAttack == "Defend")
        {
            Damage = -1;
        }
        return Damage;
}

int AttackWindow() {
    std::vector<std::string> ItemInterface;
    int counteri = 0;
    int laenge = 44;
    std::string Kopf = "";
    Kopf += "┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "└";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "│";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    ItemInterface.push_back(Kopf);
    ItemInterface.push_back(Quer);
    ItemInterface.push_back(Fuss);
    ItemInterface.push_back(Koerper);

    int hoehe = 14;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(24, counterii + MaxCharaktersHeight - 20); std::cout << ItemInterface[0]; }
        if (counterii == 2) { SetCursorPosition(24, counterii + MaxCharaktersHeight - 20); std::cout << ItemInterface[1]; }
        if (counterii == hoehe - 1) { SetCursorPosition(24, counterii + MaxCharaktersHeight - 20); std::cout << ItemInterface[2]; }
        if (counterii != 0 && counterii != 2 && counterii != hoehe - 1) { SetCursorPosition(24, counterii + MaxCharaktersHeight - 20); std::cout << ItemInterface[3]; }
        counterii++;
    }
    SetCursorPosition(26, MaxCharaktersHeight - 19);
    std::cout << "\033[30m\033[47m" << "Attackmenu" << "\033[0m";
    int i=0;
    while (i < AttackOptions.size()) 
    {
        SetCursorPosition(28, MaxCharaktersHeight - 16+i);
        std::cout << AttackOptions[i];
        i++;
    }
   // SetCursorPosition(28, MaxCharaktersHeight - 16 + i);
   // std::cout << "exit menu";
    int cursorPosition = 0;
    while (true) {
        for (int i = 0; i < (AttackOptions.size()); ++i) {
            SetCursorPosition(26, MaxCharaktersHeight - 16 + i);
            if (i == cursorPosition) {
                std::cout << "> ";
            }
            else { std::cout << " "; }
        }
        SetCursorPosition(0, 0);
        char input = _getch();
        if (input == 72) { // Nach oben (Pfeiltaste hoch)
            cursorPosition = (cursorPosition - 1) % (AttackOptions.size());
        }
        else if (input == 80) { // Nach unten (Pfeiltaste runter)
            cursorPosition = (cursorPosition + 1) % (AttackOptions.size());
        }
        else if (input == 13) { // Entertaste
            int Dmg;
               Dmg= DealAttackDamage(cursorPosition);
               return Dmg;
                break;
              }
        else if (input == 27) { // ESC
            break;
        }
    }

}

void VictoryFrame(int monsterid, int GrantedXP) 
{
    std::vector<std::string> ItemInterface;
    int counteri = 0;
    int laenge = 44;
    std::string Kopf = "";
    Kopf += "┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "└";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "│";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    ItemInterface.push_back(Kopf);
    ItemInterface.push_back(Quer);
    ItemInterface.push_back(Fuss);
    ItemInterface.push_back(Koerper);

    int hoehe = 8;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(24, counterii + 19); std::cout << ItemInterface[0]; }
        if (counterii == 2) { SetCursorPosition(24, counterii + 19); std::cout << ItemInterface[1]; }
        if (counterii == hoehe - 1) { SetCursorPosition(24, counterii + 19); std::cout << ItemInterface[2]; }
        if (counterii != 0 && counterii != 2 && counterii != hoehe - 1) { SetCursorPosition(24, counterii + 19); std::cout << ItemInterface[3]; }
        counterii++;
    }
    SetCursorPosition(26, 20);
    std::cout << "\033[30m\033[47m" << "Victory!" << "\033[0m";
    SetCursorPosition(26, 22);
    std::cout << "You defeated the "<< std::get<std::string>(monsterVectors[monsterid][0])<<".";
    SetCursorPosition(26, 24);
    std::cout << "Your Charakter gains " << GrantedXP << " XP.";

start:;

    char input = 0;
    while (true) {
        SetCursorPosition(0, 0);
        char input = _getch();
        if (input == 13) { break; }
    }
}

int CalculateMonsterDamage(int monsterid)
{
    int MonsterDamage=0;
    std::random_device rd;  // Zufälliger Seed
    std::mt19937 gen(rd()); // Mersenne-Twister Zufallsgenerator
    std::uniform_int_distribution<> distr(1, 20); // Verteilung für Zahlen von 1 bis 20
    int a = distr(gen);
    int b = distr(gen);
    if (std::get<int>(monsterVectors[monsterid][4]) > a) { MonsterDamage = 0; }
    else {
        if (b == 20) {
            MonsterDamage = std::get<int>(monsterVectors[monsterid][2]) * 2;
        }
        else { MonsterDamage = std::get<int>(monsterVectors[monsterid][2]); }
    }
    return MonsterDamage;
}

void InfoFrameDealtDamage(int Damage, int monsterid) 
{
    std::vector<std::string> ItemInterface;
    int counteri = 0;
    int laenge = 44;
    std::string Kopf = "";
    Kopf += "┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "└";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "│";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    ItemInterface.push_back(Kopf);
    ItemInterface.push_back(Quer);
    ItemInterface.push_back(Fuss);
    ItemInterface.push_back(Koerper);

    int hoehe = 8;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(26, counterii + 19); std::cout << ItemInterface[0]; }
        if (counterii == 2) { SetCursorPosition(26, counterii + 19); std::cout << ItemInterface[1]; }
        if (counterii == hoehe - 1) { SetCursorPosition(26, counterii + 19); std::cout << ItemInterface[2]; }
        if (counterii != 0 && counterii != 2 && counterii != hoehe - 1) { SetCursorPosition(26, counterii + 19); std::cout << ItemInterface[3]; }
        counterii++;
    }
    SetCursorPosition(28, 20);
    std::cout << "\033[30m\033[47m" << "Info" << "\033[0m";
    SetCursorPosition(28, 22);
    std::cout << "You dealt " << Damage << " damage to the " << std::get<std::string>(monsterVectors[monsterid][0]) << ".";

    char input = 0;
    while (true) {
        SetCursorPosition(0, 0);
        char input = _getch();
        if (input == 13) { break; }
    }
}

void EndGame() 
{

}

void InfoFrameReceivedDamage(int Damage, int monsterid)
{
    std::vector<std::string> ItemInterface;
    int counteri = 0;
    int laenge = 44;
    std::string Kopf = "";
    Kopf += "┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "└";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "│";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    ItemInterface.push_back(Kopf);
    ItemInterface.push_back(Quer);
    ItemInterface.push_back(Fuss);
    ItemInterface.push_back(Koerper);

    int hoehe = 8;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(26, counterii + 19); std::cout << ItemInterface[0]; }
        if (counterii == 2) { SetCursorPosition(26, counterii + 19); std::cout << ItemInterface[1]; }
        if (counterii == hoehe - 1) { SetCursorPosition(26, counterii + 19); std::cout << ItemInterface[2]; }
        if (counterii != 0 && counterii != 2 && counterii != hoehe - 1) { SetCursorPosition(26, counterii + 19); std::cout << ItemInterface[3]; }
        counterii++;
    }
    SetCursorPosition(28, 20);
    std::cout << "\033[30m\033[47m" << "Info" << "\033[0m";
    SetCursorPosition(28, 22);
    if (Damage > 0) {
        std::cout << "The " << std::get<std::string>(monsterVectors[monsterid][0]) << " dealt " << Damage << " damage to you.";
    }
    else { std::cout << "The attack of the " << std::get<std::string>(monsterVectors[monsterid][0]) << " missed you."; }

    char input = 0;
    while (true) {
        SetCursorPosition(0, 0);
        char input = _getch();
        if (input == 13) { break; }
    }
}

void ManageItemDrops(int monsterid)
{
    int NumberOfDrops = DropsInRoom[currentRoom].size();
    int i = 0;
    while (i < NumberOfDrops)
    {
        DropItem(DropsInRoom[currentRoom][i]);
        i++;
    }
    if (NumberOfDrops == 1) 
    {
        std::string msg = "The ";
        msg += std::get<std::string>(monsterVectors[monsterid][0]);
        msg += " dropped an item.";
        InfoFrame(3, msg);
    }
    if (NumberOfDrops > 1)
    {
        std::string msg = "The ";
        msg += std::get<std::string>(monsterVectors[monsterid][0]);
        msg += " dropped various items.";
        InfoFrame(3, msg);
    }
    DropsInRoom[currentRoom].clear();
}

void CheckSpecialEvent(int monsterid)
{
    if (monsterid == 1)
    {
        NeighbourRooms[0][0] = 1;
        InfoFrame(5, "As you deliver your final blow upon the door, you hear a faint cracking sound. The door now appears to be open.");
            }
}

void Battle(int monsterid,int ii)
{
    int tempw = MaxCharaktersWidth;
    MaxCharaktersWidth = 100;
    int temph = MaxCharaktersHeight;
    MaxCharaktersHeight = 35;
    int MaxMonsterHP = std::get<int>(monsterVectors[monsterid][1]);
    int CurrentMonsterHP = MaxMonsterHP;
    int CurrentMonsterDEF = std::get<int>(monsterVectors[monsterid][3]);
    int GrantedXP;
    if (std::get<int>(monsterVectors[monsterid][7]) >= level)
    {
        GrantedXP = std::get<int>(monsterVectors[monsterid][5]);
    }
    if (std::get<int>(monsterVectors[monsterid][7]) < level && level- std::get<int>(monsterVectors[monsterid][7])<5)
    {
        int divisor = level - std::get<int>(monsterVectors[monsterid][7]);
        GrantedXP = std::get<int>(monsterVectors[monsterid][5])/5*(5-divisor);
    }
    if (level - std::get<int>(monsterVectors[monsterid][7]) >= 5)
    {
        GrantedXP =0;
    }
    std::string CurrentMonsterName = std::get<std::string>(monsterVectors[monsterid][0]);
start:
    BattleFrame(CurrentMonsterHP, MaxMonsterHP, CurrentMonsterName,monsterid);
    int cursorPosition = 0;
    while (CurrentMonsterHP > 0) {
        for (int i = 0; i < 3; ++i) {
            SetCursorPosition(16, MaxCharaktersHeight - 9 + i);
            if (i == cursorPosition) {
                std::cout << "> ";
            }
            else { std::cout << " "; }
        }
        SetCursorPosition(0, 0);
        char input = _getch();
        if (input == 72) { // Nach oben (Pfeiltaste hoch)
            cursorPosition = (cursorPosition+3-1) % 3;
        }
        else if (input == 80) { // Nach unten (Pfeiltaste runter)
            cursorPosition = (cursorPosition + 1) % 3;
        }
        else if (input == 13) { // Entertaste
            if (cursorPosition == 0)
            {
                int Damage;
                bool Defend=false;
                int tempPlayerDefence = PlayerDefence;
                Damage = AttackWindow();
                if (Damage > 0) {
                    Damage = Damage - CurrentMonsterDEF;
                }
                if (Damage == -1)
                {
                    PlayerDefence = PlayerDefence + 5;
                    Defend = true;
                    InfoFrame(3, "You take a defensive stance and prepare for the opponent's next attack.");
                }
                if (Damage < 0) { Damage = 0; }
                if (Defend == false) {
                    CurrentMonsterHP = CurrentMonsterHP - Damage;
                    InfoFrameDealtDamage(Damage, monsterid);
                }
                BattleFrame(CurrentMonsterHP, MaxMonsterHP, CurrentMonsterName,monsterid);
                int cursorPosition = 0;
                if (CurrentMonsterHP < 0) { CurrentMonsterHP = 0; }
                int MonsterDamage;
                MonsterDamage = CalculateMonsterDamage(monsterid) - PlayerDefence;
                if (MonsterDamage < 0) { MonsterDamage = 0; }
                CurrentPlayerHP = CurrentPlayerHP - MonsterDamage;
                InfoFrameReceivedDamage(MonsterDamage, monsterid);
                PlayerDefence = tempPlayerDefence;

                goto start;
            }
            if (cursorPosition == 1) {
                DisplayInventory();
                goto start;
            }
            if (cursorPosition == 2) {
                if(std::get<int>(monsterVectors[monsterid][6])==1)
                {
                InfoFrame(3, "You fled the battle.");
                system("cls");
                lastrow = 4;
                MaxCharaktersWidth = tempw;
                MaxCharaktersHeight = temph;
                DrawSimpleInterfaceFrame();
                break;
                }
                if (std::get<int>(monsterVectors[monsterid][6]) == 0)
                {
                InfoFrame(3, "Escape is not possible.");
                BattleFrame(CurrentMonsterHP, MaxMonsterHP, CurrentMonsterName, monsterid);
                }
            }
            else {
                system("cls");
                lastrow = 4;
                MaxCharaktersWidth = tempw;
                MaxCharaktersHeight = temph;
                DrawSimpleInterfaceFrame();
                break;
            }
        }
    }
    if (CurrentMonsterHP <= 0)
    {
        VictoryFrame(monsterid,GrantedXP);
        BattleFrame(CurrentMonsterHP, MaxMonsterHP, CurrentMonsterName, monsterid);
        ManageItemDrops(monsterid);
        BattleFrame(CurrentMonsterHP, MaxMonsterHP, CurrentMonsterName, monsterid);
        CheckSpecialEvent(monsterid);
        CurrentXP = CurrentXP + GrantedXP;
        MonsterAlive[currentRoom][ii] = false;
        MaxCharaktersWidth = tempw;
        MaxCharaktersHeight = temph;

        system("cls");
        lastrow = 4;

        DrawSimpleInterfaceFrame();
    }
    if (CurrentPlayerHP <= 0)
    {
        EndGame();
    }
}

void GetInput() {
    std::string input;
    std::getline(std::cin, input);
    lastrow = 4;

    if (input == "go north") { CallNewRoom(0); }
    else if (input == "go east") { CallNewRoom(1); }
    else if (input == "go south") { CallNewRoom(2); }
    else if (input == "go west") { CallNewRoom(3); }
    else if (input == "inventory") { DisplayInventory();        
    system("cls");
    DrawSimpleInterfaceFrame();
    lastrow = 4;
    }
    else if (input == "stats") { DisplayPlayerStats(); }
    else if (input == "look around") { LookAround(); }
    else if (input.substr(0, 4) == "take") { std::string item = input.erase(0, 5); TakeItem(item);}
    else if (input == "TEST") { DisplayCharakterEquipment(); }
    else if (input.substr(0, 6) == "attack") { std::string monster = input.erase(0, 7); 
    int monsterid = MonstersInRoom[currentRoom][0]; 
    int i = 0;
    while (i < MonstersInRoom[currentRoom].size())
    {
        if (monster == std::get<std::string>(monsterVectors[MonstersInRoom[currentRoom][i]][0]) && MonsterAlive[currentRoom][i] == true) { Battle(MonstersInRoom[currentRoom][i], i); }
        else {
            system("cls");
            DrawSimpleInterfaceFrame();
            lastrow = 4;
            std::string msg = "There is no such Monster in the Room";
           // DisplayTextOnScreen(msg);
        }
        i++;
    }

    }
    else {
        system("cls");
        DrawSimpleInterfaceFrame();
        lastrow = 4;
        std::string msg = "There is no such a Command.";
        DisplayTextOnScreen(msg);
    }
    SetCursorPosition(24, MaxCharaktersHeight - 2);
}

void GetPlayerName()
{
    std::vector<std::string> Interface;
    int counteri = 0;
    int laenge = 60;
    std::string Kopf = "";
    Kopf += "   ┌";
    while (counteri < laenge) { Kopf += "─"; counteri++; }
    Kopf += "┐\n";
    counteri = 0;
    std::string Quer = "";
    Quer += "   ├";
    while (counteri < laenge) { Quer += "─"; counteri++; }
    Quer += "┤\n";
    counteri = 0;
    std::string Fuss = "";
    Fuss += "   └";
    while (counteri < laenge) { Fuss += "─"; counteri++; }
    Fuss += "┘\n";
    counteri = 0;
    std::string Koerper = "";
    Koerper += "   │";
    while (counteri < laenge) { Koerper += " "; counteri++; }
    Koerper += "│\n";
    Interface.push_back(Kopf);
    Interface.push_back(Quer);
    Interface.push_back(Fuss);
    Interface.push_back(Koerper);

    int hoehe = 8;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { SetCursorPosition(CenterX-34, CenterY + counterii - 2); std::cout << Interface[0]; }
        if (counterii == hoehe-3) { SetCursorPosition(CenterX - 34, CenterY + counterii - 2); std::cout << Interface[1]; }
        if (counterii == hoehe - 1) { SetCursorPosition(CenterX - 34, CenterY + counterii - 2); std::cout << Interface[2]; }
        if (counterii != 0 && counterii != hoehe - 3&& counterii != hoehe - 1) { SetCursorPosition(CenterX - 34, CenterY + counterii - 2); std::cout << Interface[3]; }
        counterii++;
    }
    SetCursorPosition(CenterX - 28, CenterY);
    std::cout << "Welcome, adventurer! What ist thy Name?";
    SetCursorPosition(CenterX - 28, CenterY + 4);
    std::cout << "Name: ";
    std::string input;
    std::getline(std::cin, input);
    PlayerName = input;
}

void CalculateNewHP()
{
    MaxPlayerHP = 50 + Stamina * 25;
}

void EditStatPoints()
{
    int tempw = MaxCharaktersWidth;
    MaxCharaktersWidth = 105;
    int temph = MaxCharaktersHeight;
    MaxCharaktersHeight = 35;

    bool KeyPressed = true;
        int cursorPosition = 0;
        int TempStrength = Strength;
        int TempDexterity = Dexterity;
        int TempStamina = Stamina;
        int TempIntelligence = Intelligence;
        while (true) {
            Start:
            if (KeyPressed == true)
            {
                DrawInventoryFrame();
                SetCursorPosition(16, 6);
                std::cout << "\033[30m\033[47m" << "Adjust your stats." << "\033[0m";
                SetCursorPosition(20, 10);
                std::cout << "Strength";
                DrawBarDiagramm(Strength, 40, 36, 9, 40);
                SetCursorPosition(22, 11);
                std::cout << "(" << Strength << ")";
                SetCursorPosition(20, 14);
                std::cout << "Dexterity";
                DrawBarDiagramm(Dexterity, 40, 36, 13, 40);
                SetCursorPosition(22, 15);
                std::cout << "(" << Dexterity << ")";
                SetCursorPosition(20, 18);
                std::cout << "Stamina";
                DrawBarDiagramm(Stamina, 40, 36, 17, 40);
                SetCursorPosition(22, 19);
                std::cout << "(" << Stamina << ")";
                SetCursorPosition(20, 22);
                std::cout << "Intelligence";
                DrawBarDiagramm(Intelligence, 40, 36, 21, 40);
                SetCursorPosition(22, 23);
                std::cout << "(" << Intelligence << ")";
                SetCursorPosition(20, 26);
                std::cout << "available status points: " << Statpoints;
                KeyPressed = false;
            }
            for (int i = 0; i < 4; ++i) {
                SetCursorPosition(17, 10 + 4*i);
                if (i == cursorPosition) {
                    std::cout << "> ";
                }
                else { std::cout << " "; }
            }
            SetCursorPosition(0, 0);
            char input = _getch();
            if (input == 72) { // Nach oben (Pfeiltaste hoch)
                cursorPosition = (cursorPosition + 4 - 1) % 4;
                KeyPressed = true;
            }
            else if (input == 80) { // Nach unten (Pfeiltaste runter)
                cursorPosition = (cursorPosition + 1) % 4;
                KeyPressed = true;
            }
            else if (input == 77) { //(Pfeiltaste rechts)
                if (cursorPosition == 0 && Statpoints > 0) { Strength++; Statpoints=Statpoints - 1; }
                if (cursorPosition == 1 && Statpoints > 0) { Dexterity++; Statpoints = Statpoints - 1; }
                if (cursorPosition == 2 && Statpoints > 0) { Stamina++; Statpoints = Statpoints - 1; }
                if (cursorPosition == 3 && Statpoints > 0) { Intelligence++; Statpoints = Statpoints - 1; }
                KeyPressed = true;
            }
            else if (input == 75) { //(Pfeiltaste links)
                if (cursorPosition == 0 && (Strength-TempStrength)>0) { Strength--; Statpoints++; }
                if (cursorPosition == 1 && (Dexterity-TempDexterity)>0) { Dexterity--; Statpoints++; }
                if (cursorPosition == 2 && (Stamina-TempStamina)> 0) { Stamina--; Statpoints++; }
                if (cursorPosition == 3 && (Intelligence-TempIntelligence)> 0) { Intelligence--; Statpoints++; }
                KeyPressed = true;
            }
            else if (input == 13) { //Enter
                if (Statpoints > 0) 
                {
                    InfoFrame(3, "You still have stat points to allocate.");
                    KeyPressed = true;
                    goto Start;
                }

                if (Statpoints == 0)
                {
                    MaxCharaktersWidth = tempw;
                    MaxCharaktersHeight = temph;
                    system("cls");
                    DrawSimpleInterfaceFrame();
                    CalculateNewHP();
                    CurrentPlayerHP = MaxPlayerHP;
                    break;
                }
            }
        }
    
    MaxCharaktersWidth = tempw;
    MaxCharaktersHeight = temph;
}

void CheckLevelUp()
{
    if (CurrentXP > XPForLvlUp) 
    {
        level++;
        CurrentXP = CurrentXP - XPForLvlUp;
        XPForLvlUp = XPForLvlUp + 250 * level;
        InfoFrame(3, "You have reached a new level and earned 5 attribute points as a reward. Use them wisely to enhance your skills and abilities, making you even stronger for the challenges ahead.");
        EditStatPoints();
    }
}


void GameLoop()
{
   // int i=0;
    while (true) {
            GetInput();
            CheckLevelUp();
    }

}

int main(){
    InitializeConsole();
    system("cls");
    GetPlayerName();
    system("cls");
    DrawSimpleInterfaceFrame();
    EditStatPoints();
    std::string tempDescription = GenerateRoomDescripton(currentRoom);
    DisplayTextOnScreen(tempDescription);
    SetCursorPosition(24, MaxCharaktersHeight - 2);
    std::srand(static_cast<unsigned>(std::time(0)));
    GameLoop();
    return 0;
}