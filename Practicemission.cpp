
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <ctime>
using namespace std;

#define LIM_TXT 255

struct ClickCoords
{
    int clickX;
    int clickY;
};

struct Teleport
{
    char teleport = 't';
};

struct TeleportCoords
{
    int x;
    int y;
};

struct Experience
{
    int lvl = 1;
    int exp = 0;
    int nextLevelExp = 0;
};

void readFile1(char border[13][28])
{
    char szTxtFile[] = "level1.txt";
    ifstream file;
    file.open(szTxtFile);
    if (!file.is_open())
        exit(0);

    file.getline(border[0], LIM_TXT);
    for (int i = 1; i < 12; i++)
        file.getline(border[i], LIM_TXT);
    file.getline(border[12], LIM_TXT);

    file.close();
}

void readFile2(char border[13][28])
{
    char szTxtFile[] = "level2.txt";
    ifstream file;
    file.open(szTxtFile);
    if (!file.is_open())
        exit(0);

    file.getline(border[0], LIM_TXT);
    for (int i = 1; i < 12; i++)
        file.getline(border[i], LIM_TXT);
    file.getline(border[12], LIM_TXT);

    file.close();
}

void printTable(Experience& exp)
{
    cout << "Уровень " << exp.lvl << endl;
    cout << "Опыт:  " << exp.exp << "/" << exp.nextLevelExp << endl;
}

void printArray(char border[13][28])
{
    for (int i = 0; i < 12; i++)
    {
        cout << border[i] << endl;
    }
}

void clickKeysLogic(ClickCoords& clCoords, char border[13][28], int& px, int& py, char& key)
{
    switch (key)
    {
    case 'w':
        clCoords.clickX--;
        if (border[clCoords.clickX][clCoords.clickY] == '#')
        {
            clCoords.clickX = px;
            clCoords.clickY = py;
        }
        break;
    case 's':
        clCoords.clickX++;
        if (border[clCoords.clickX][clCoords.clickY] == '#')
        {
            clCoords.clickX = px;
            clCoords.clickY = py;
        }
        break;
    case 'd':
        clCoords.clickY++;
        if (border[clCoords.clickX][clCoords.clickY] == '#')
        {
            clCoords.clickX = px;
            clCoords.clickY = py;
        }
        break;
    case 'a':
        clCoords.clickY--;
        if (border[clCoords.clickX][clCoords.clickY] == '#')
        {
            clCoords.clickX = px;
            clCoords.clickY = py;
        }
        break;
    }
}

void eatingFruitLogic(ClickCoords& clCoords, Experience& exp, char border[13][28], int& stx, int& sty)
{
    if (border[clCoords.clickX][clCoords.clickY] == border[stx][sty])
    {
        exp.exp += 15;

        while (border[stx][sty] != ' ')
        {
            stx = (rand() % 10) + 1;
            sty = (rand() % 25) + 1;
        }

    }
}

void levelUpLogic(Experience& exp)
{
    exp.nextLevelExp = sqrt(exp.lvl) * 100;
    if (exp.exp >= exp.nextLevelExp)
    {
        exp.lvl++;
        exp.exp -= exp.nextLevelExp;
    }
}

void spawnerTeleport(TeleportCoords& telCoords, Teleport& tel, char border[13][28])
{
    border[telCoords.x][telCoords.y] = tel.teleport;
}

void telepotLogic(TeleportCoords& telCoords, Teleport& tel, char border[13][28], ClickCoords& clCoords, int& stx, int& sty)
{
    if (border[clCoords.clickX][clCoords.clickY] == border[telCoords.x][telCoords.y])
    {
        while (border[clCoords.clickX][clCoords.clickY] != ' ' || border[telCoords.x][telCoords.y] != ' ')
        {
            clCoords.clickX = (rand() % 10) + 1;
            clCoords.clickY = (rand() % 25) + 1;
            telCoords.x = (rand() % 10) + 1;
            telCoords.y = (rand() % 25) + 1;
        }
    }

    if (border[telCoords.x][telCoords.y] == border[stx][sty])
    {
        telCoords.x = (rand() % 10) + 1;
        telCoords.y = (rand() % 25) + 1;
    }

    while (border[telCoords.x][telCoords.y] == '#' || border[telCoords.x][telCoords.y] == '.')
    {
        telCoords.x = 7;
        telCoords.y = 12;
        if (border[telCoords.x][telCoords.y] == border[stx][sty])
        {
            telCoords.x = (rand() % 10) + 1;
            telCoords.y = (rand() % 25) + 1;
        }
    }
}

void levelOne(Experience& exp, TeleportCoords& telCoords, Teleport& tel, ClickCoords& clCoords, char border[13][28], int& px, int& py, int& stx, int& sty, char& key)
{
    do
    {
        system("cls");

        readFile1(border);

        border[clCoords.clickX][clCoords.clickY] = '@';
        border[stx][sty] = '$';
        spawnerTeleport(telCoords, tel, border);

        printTable(exp);
        printArray(border);
        cout << "\nЧто бы выйти, нажмите 'e'" << endl;

        key = _getch();
        px = clCoords.clickX;
        py = clCoords.clickY;

        clickKeysLogic(clCoords, border, px, py, key);

        telepotLogic(telCoords, tel, border, clCoords, stx, sty);

        eatingFruitLogic(clCoords, exp, border, stx, sty);

        levelUpLogic(exp);

        if (exp.lvl == 2)
        {
            border = NULL;
            break;
        }

    } while (key != 'e');
}

void levelTwo(Experience& exp, TeleportCoords& telCoords, Teleport& tel, ClickCoords& clCoords, char border[13][28], int& px, int& py, int& stx, int& sty, char& key)
{
    do
    {
        system("cls");

        readFile2(border);

        border[clCoords.clickX][clCoords.clickY] = '@';
        border[stx][sty] = '$';
        spawnerTeleport(telCoords, tel, border);

        printTable(exp);
        printArray(border);
        cout << "\nЧто бы выйти, нажмите 'e'" << endl;

        key = _getch();
        px = clCoords.clickX;
        py = clCoords.clickY;

        clickKeysLogic(clCoords, border, px, py, key);

        telepotLogic(telCoords, tel, border, clCoords, stx, sty);

        eatingFruitLogic(clCoords, exp, border, stx, sty);

        levelUpLogic(exp);

        if (exp.lvl == 3)
        {
            break;
        }

    } while (key != 'e');
}

void menu(Experience& exp, TeleportCoords& telCoords, Teleport& tel, ClickCoords& clCoords, char border[13][28], int& px, int& py, int& stx, int& sty, char& key)
{
    cout << "------------МЕНЮ------------\n[1] -----> Играть\n[2] -----> Выйти" << endl;
    char menKey = _getch();
    switch (menKey)
    {
    case '1':
        levelOne(exp, telCoords, tel, clCoords, border, px, py, stx, sty, key);
        levelTwo(exp, telCoords, tel, clCoords, border, px, py, stx, sty, key);
        if (exp.lvl > 2)
        {
            char szTxt3File[] = "levelend.txt";
            ifstream ff;
            ff.open(szTxt3File);
            if (!ff.is_open())
                exit(0);
            system("cls");
            /////////////////////reading fist file
            cout << "Уровень " << exp.lvl << endl;
            cout << "Опыт:  " << exp.exp << "/Конец" << endl;
            ff.getline(border[0], LIM_TXT);
            for (int i = 1; i < 12; i++)
                ff.getline(border[i], LIM_TXT);
            ff.getline(border[12], LIM_TXT);
            for (int i = 0; i < 12; i++)
            {
                cout << border[i] << endl;
            }
            cout << "\nЧто бы выйти, нажмите 'e'" << endl;
        }
        break;
    case '2': break;
    default: break;
    }
}

int main()
{
    system("chcp 1251");

    ClickCoords clCoords;
    Teleport tel;
    TeleportCoords telCoord;
    Experience newlvl;
    char border[13][28];
    int px, py;   //prev x, prev y
    int stx = 3;
    int sty = 17;

    clCoords.clickX = 7;
    clCoords.clickY = 14;
    telCoord.x = (rand() % 10) + 1;
    telCoord.y = (rand() % 25) + 1;
    char key;

    srand(time(NULL));

    menu(newlvl, telCoord, tel, clCoords, border, px, py, stx, sty, key);

    return 0;
}