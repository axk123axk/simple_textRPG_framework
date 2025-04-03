#ifndef CI_H  // Include-Guard, um doppelte Einbindung zu verhindern
#define CI_H

int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
double MaxCharaktersX = ScreenWidth / 8.2;
int MaxCharaktersWidth = static_cast<int>(MaxCharaktersX);
double MaxCharaktersY = ScreenHeight / 17;
int MaxCharaktersHeight = static_cast<int>(MaxCharaktersY);


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

void DrawSimpleInterfaceFrame()
{
    std::vector<std::string> Interfacei = CreateInterfaceStrings();
    int hoehe = MaxCharaktersHeight;
    int counterii = 0;

    while (counterii < hoehe) {
        if (counterii == 0) { std::cout << Interfacei[0]; }
        if (counterii == hoehe - 5) { std::cout << Interfacei[1]; }
        if (counterii == hoehe - 1) { std::cout << Interfacei[2]; }
        if (counterii != 0 && counterii != hoehe - 5 && counterii != hoehe - 1) { std::cout << Interfacei[3]; }
        counterii++;
    }
    SetCursorPosition(6, hoehe - 1);
    std::cout << "Awaiting Command:";
}

#endif