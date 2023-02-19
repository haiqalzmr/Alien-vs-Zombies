// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: T10L 
// Names: MUHAMMAD AMIRUL HAIQAL BIN ZAMERI | MUHAMMAD AFIF JAZIMIN BIN IDRIS | LEE JUN YAO
// IDs: 1211104232 | 1211103419 | 1211103763 
// Emails: 1211104232@student.mmu.edu.my | 1211103419@student.mmu.edu.my | 1211103763@student.mmu.edu.my
// Phones: 011-53540207 | 010-5376195 | 011-23523686 
// ********************************************************* 

// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT10L
// Names: LEE JUN YAO | MUHAMMAD AMIRUL HAIQAL BIN ZAMERI | MUHAMMAD AFIF JAZIMIN BIN IDRIS
// IDs: 1211103763 | 1211104232 | 1211103419
// Emails: 1211103763@STUDENT.MMU.EDU.MY | 1211104232@STUDENT.MMU.EDU.MY | 1211103419@STUDENT.MMU.EDU.MY
// Phones: 01123523686 | 01153540207 | 0105376195
// *********************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cctype>

// helper variables
int rows;
int columns;
int zombies;
int alienHealth;
int alienDamage;
int alienX, alienY;
int zombiesHealth[10];
int zombiesDamage[10];
int ranges[10];
int zombiesX[10];
int zombiesY[10];


using namespace std;


void displayHealth();
void alienMove(string direction);
void alienMove(string direction, int r, int c);
void zombieMove(int z);
int Pause();
bool validPosition(int r, int c);
void hitpod(int r, int c);
void attack(int z, int r, int c, int range);
void resetPath();


int main()
{
    // Seed the random number generator
    srand(time(0));

    // Initial value
    rows = 5;
    columns = 9;
    zombies = 5;
    alienDamage = 0;

    StartUp();
    customSetting();

    alienHealth = (rand() % 5) * 50 + 150;
    grid = new char *[rows];
    for (int i = 0; i < rows; i++)
        grid[i] = new char[columns];

    board();

    string command;
    bool endGame = false;
    do
    {
        displayBoard();
       
}

void resetPath()
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            if (grid[i][j] == '.') // If a cell contains a period ('.'), it is replaced with a randomly selected character from the array "characters" with 8 elements. The random character is selected using the "rand() % 8" expression, which returns a random integer between 0 and 7.
                grid[i][j] = characters[rand() % 8];
        }
    }
}

void attack(int z, int r, int c, int range) // Checks if the alien is within the zombie's attack range by calculating the absolute difference between the alien's row and column coordinates and the zombie's coordinates and comparing it to the range
{
    if ((abs(r - alienX) <= range) && (abs(c - alienY) <= range))
    {
        cout << "Zombie " << z + 1 << " attacks Alien with damage " << zombiesDamage[z] << "\n";
        alienHealth -= zombiesDamage[z];
    }
    else
    {
        cout << "Zombie cannot attack. Alien is out of range.\n\n";
    }
}

void hitpod(int r, int c) // Keeps track of the index of the zombie closest to the hitpod, and that zombie takes damage of 10. The health of each zombie is stored in an array named "zombiesHealth"
{
    int i, minDistance = 99, minDisIndex, distance;
    for (i = 0; i < zombies; i++)
    {
        distance = (abs(zombiesX[i] - r) + abs(zombiesY[i] - c));
        if (minDistance > distance)
        {
            minDistance = distance;
            minDisIndex = i;
        }
    }

    cout << "Zombie " << minDisIndex + 1 << " is closest to the pod. It gets a damage of 10.\n\n";
    zombiesHealth[minDisIndex] -= 10;
    if (zombiesHealth[minDisIndex] <= 0) // If the damage taken reduces a zombie's health to 0 or less, the function outputs a message indicating that the zombie has died and updates its position to (-1, -1)
    {
        cout << "Zombie " << minDisIndex + 1 << "Died.\n\n";
        zombiesX[minDisIndex] = -1;
        zombiesY[minDisIndex] = -1;
    }
}

bool validPosition(int r, int c)
{
    if (alienX == r && alienY == c)
        return false;

    for (int i = 0; i < zombies; i++)
        if (zombiesX[i] == r && zombiesY[i] == c)
            return false;
    return true;
}

void zombieMove(int z)
{
    int num;
    cout << "\nZombie " << z + 1 << "\'s turn.\n";
    while (true)
    {
        num = rand() % 4;
        ////Checks if the move is within the grid boundary and if the new position is not occupied by the alien or another zombie
        if (num == 0 && !boundary(zombiesX[z] - 1, zombiesY[z]) && validPosition(zombiesX[z] - 1, zombiesY[z]))
        { // If the move is valid, the grid is updated, the zombie's new position is recorded
            grid[zombiesX[z] - 1][zombiesY[z]] = grid[zombiesX[z]][zombiesY[z]];
            grid[zombiesX[z]][zombiesY[z]] = ' ';
            zombiesX[z]--;
            cout << "\nZombie " << z + 1 << " moves up\n";
            break;
        }
        else if (num == 1 && !boundary(zombiesX[z] + 1, zombiesY[z]) && validPosition(zombiesX[z] + 1, zombiesY[z]))
        {
            grid[zombiesX[z] + 1][zombiesY[z]] = grid[zombiesX[z]][zombiesY[z]];
            grid[zombiesX[z]][zombiesY[z]] = ' ';
            zombiesX[z]++;
            cout << "\nZombie " << z + 1 << " moves down\n";
            break;
        }
        else if (num == 2 && !boundary(zombiesX[z], zombiesY[z] - 1) && validPosition(zombiesX[z], zombiesY[z] - 1))
        {
            grid[zombiesX[z]][zombiesY[z] - 1] = grid[zombiesX[z]][zombiesY[z]];
            grid[zombiesX[z]][zombiesY[z]] = ' ';
            zombiesY[z]--;
            cout << "\nZombie " << z + 1 << " moves left\n";
            break;
        }
        else if (num == 3 && !boundary(zombiesX[z], zombiesY[z] + 1) && validPosition(zombiesX[z], zombiesY[z] + 1))
        {
            grid[zombiesX[z]][zombiesY[z] + 1] = grid[zombiesX[z]][zombiesY[z]];
            grid[zombiesX[z]][zombiesY[z]] = ' ';
            zombiesY[z]++;
            cout << "\nZombie " << z + 1 << " moves right\n";
            break;
        }
    }

    attack(z, zombiesX[z], zombiesY[z], ranges[z]); // attack on the alien is attempted with the range z
}

void alienMove(string direction) // moves the alien in a particular direction (up, down, left, or right) based on the input string argument. The function first resets the alien's trail, then moves the alien in the given direction by calling the alienMove function and passing it the direction, the new x-coordinate and y-coordinate. After the alien move, the trail is reset again and the zombie moves are executed one by one.
{
    alienDamage = 0;
    if (direction == "up")
        alienMove(direction, alienX - 1, alienY);
    else if (direction == "down")
        alienMove(direction, alienX + 1, alienY);
    else if (direction == "left")
        alienMove(direction, alienX, alienY - 1);
    else if (direction == "right")
        alienMove(direction, alienX, alienY + 1);
    alienDamage = 0;
    cout << "Alien Move Ends. Reseting trail...\n\n";
    Pause();
    resetPath();
    for (int i = 0; i < zombies; i++)
    {
        if (zombiesHealth[i] > 0)
        {
            displayBoard();
            zombieMove(i);
            Pause();
        }
    }
}

void alienMove(string direction, int r, int c)
{
    if (boundary(r, c))
        return; // If the current position is outside the boundaries of the grid, the function returns

    int tr, tc;
    displayBoard();
    if (direction == "up")
        cout << "\nAlien moves Up\n";
    else if (direction == "down")
        cout << "\nAlien moves Down\n";
    else if (direction == "right")
        cout << "\nAlien moves Right\n";
    else if (direction == "left")
        cout << "\nAlien moves Left\n";

    tr = alienX;
    tc = alienY;
    grid[alienX][alienY] = '.';
    alienX = r;
    alienY = c;
    // Current state of the grid, and updates the alien's position and properties (e.g., health, damage) based on the contents of the grid at the new position.
    if (grid[r][c] == '^')
    {
        grid[r][c] = 'A';
        cout << "Alien finds a arrow in upward direction.\n";
        cout << "Alien Damage is increased by 20.\n";
        Pause();
        alienDamage += 20;
        alienMove("up", r - 1, c);
        return;
    }

    else if (grid[r][c] == '>')
    {
        grid[r][c] = 'A';
        cout << "Alien finds a arrow in Right direction.\n";
        cout << "Alien Damage is increased by 20.\n";
        Pause();
        alienDamage += 20;
        alienMove("right", r, c + 1);
        return;
    }

    else if (grid[r][c] == 'v')
    {
        grid[r][c] = 'A';
        cout << "Alien finds a arrow in Downward direction.\n";
        cout << "Alien Damage is increased by 20.\n";
        Pause();
        alienDamage += 20;
        alienMove("down", r + 1, c);
        return;
    }

    else if (grid[r][c] == '<')
    {
        grid[r][c] = 'A';
        cout << "Alien finds a arrow in left direction.\n";
        cout << "Alien Damage is increased by 20.\n";
        Pause();
        alienDamage += 20;
        alienMove("left", r, c - 1);
        return;
    }

    else if (grid[r][c] == 'h')
    {
        cout << "Alien finds a health.\n20 is Added to Alien Health.\n";
        alienHealth += 20;
    }

    else if (grid[r][c] == 'p')
    {
        cout << "Alien finds a pod.\nInflicts 10 damage to nearest Zombie.\n";
        hitpod(r, c);
    }

    else if (grid[r][c] == 'r')
    {
        cout << "Alien finds a rock.\n";
        int a = rand() % 3;
        if (a == 0)
        {
            cout << "Rock was hiding a Pod beneath.\n";
            grid[r][c] = 'p';
        }
        else if (a == 1)
        {
            cout << "Rock was hiding a Health beneath.\n";
            grid[r][c] = 'h';
        }
        else
        {
            cout << "Rock was hiding Nothing beneath.\n";
            grid[r][c] = ' ';
        }
        alienX = tr;
        alienY = tc;
        grid[alienX][alienY] = 'A';
        return;
    }
    // If the new position contains a zombie, the alien will attack and potentially kill the zombie, reducing its health by the alien's damage
    else if (grid[r][c] >= '1' && grid[r][c] <= '9')
    { // grid[r][c] >= '1' && grid[r][c] <= '9' is zombies
        cout << "Alien hits a Zombie.\n";
        cout << "Alien Attacks with damage " << alienDamage << "\n";
        zombiesHealth[grid[r][c] - '0' - 1] -= alienDamage;
        if (zombiesHealth[grid[r][c] - '0' - 1] <= 0)
        {
            cout << "Zombie " << grid[r][c] << " Died.\nAlien continues to move.\n\n";
            zombiesX[grid[r][c] - '0' - 1] = -1;
            zombiesY[grid[r][c] - '0' - 1] = -1;
        }
        else
        {
            alienX = tr;
            alienY = tc;
            grid[alienX][alienY] = 'A';
            return;
        }
    }
    else
        cout << "Alien finds an empty space.\n\n";

    grid[r][c] = 'A'; // move the alien in the same direction until it reaches an empty space or an object that stops its movement.
    Pause();
    if (direction == "up")
        alienMove(direction, r - 1, c);
    else if (direction == "down")
        alienMove(direction, r + 1, c);
    else if (direction == "left")
        alienMove(direction, r, c - 1);
    else if (direction == "right")
        alienMove(direction, r, c + 1);
}

void displayHealth() // Displays the health, damage and range of the alien and the zombies
{
    cout << "\nAlien :     Health " << alienHealth << "\tDamage " << alienDamage << endl;
    for (int i = 0; i < zombies; i++)
    {
        cout << "Zombie " << i + 1 << ":  "
             << " Health " << zombiesHealth[i] << ", Damage " << zombiesDamage[i] << ", Range " << ranges[i] << endl;
    }
}

int ClearScreen()
{
#if defined(_WIN32)
    return std::system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    return std::system("clear");
#endif
}

int Pause() // Pause the game until the user presses any key
{
#if defined(_WIN32)
    return std::system("pause");
#elif defined(__linux__) || defined(__APPLE__)
    return std::system(R"(read -p "Press any key to continue . . . " dummy)");
#endif
}


