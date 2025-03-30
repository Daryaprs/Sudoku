#include <iostream>
#include <time.h>
#include "clui.h"
using namespace std;
struct game
{
    const char *name = "null";
    int userIndex;
    int gameIndex;
    int sudoku[9][9];
    int min;
    int sec;
    int level;
    int mistakes = 0;
    int correct = 0;
    int incorrect = 0;
};
struct user
{
    const char *name;
    int Index;
    int gamesCount = 0;
};
game games[100][100];
int length(char *str)
{
    int length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}

bool compare(const char *u1, const char *u2)
{
    if (length(const_cast<char *>(u1)) != length(const_cast<char *>(u2)))
        return false;
    else
    {
        for (int i = 0; i < length(const_cast<char *>(u1)); i++)
        {
            if (u1[i] != u2[i])
                return false;
        }
    }
    return true;
}
void sudoku(game &, user *);
void menu(user *);
void esc(game &Game, user *User)
{
    clear_screen();
    cursor_to_pos(get_window_rows() / 2, get_window_cols() / 2 - 20);
    change_color_rgb(245, 92, 10);
    cout << "The game is paused. Press the Esc key to continue.";
    reset_color();

    int n = getch();
    if (n == 27)
    {
        clear_screen();
        sudoku(Game, User);
        return;
    }
    else if (n == 115)
    {
        User->name = "null";
        delay(200);
        clear_screen();
        char *Name = new char[100];
        cursor_to_pos(get_window_rows() / 2 - 1, get_window_cols() / 2 - 5);
        const char *null = "null";
        change_color_rgb(7, 140, 3);
        if (compare(null, Game.name))
        {
            cout << "Saving...";
            cursor_to_pos(get_window_rows() / 2, get_window_cols() / 2 - 5);
            change_color_rgb(240, 100, 19);
            cout << "mistakes: " << Game.mistakes;
            cursor_to_pos(get_window_rows() / 2 + 1, get_window_cols() / 2 - 5);
            change_color_rgb(30, 166, 7);
            cout << "correct: " << Game.correct;
            cursor_to_pos(get_window_rows() / 2 + 2, get_window_cols() / 2 - 5);
            change_color_rgb(214, 13, 13);
            cout << "incorrect: " << Game.incorrect;
            cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 2 - 15);
            change_color_rgb(245, 92, 10);
            cout << "Choose a name for your game: ";
            reset_color();
            cin >> Name;
            Game.name = Name;
            User->gamesCount++;
            clear_screen();
            menu(User);
        }
        else
        {
            cursor_to_pos(get_window_rows() / 2 - 1, get_window_cols() / 2 - 15);
            change_color_rgb(7, 140, 3);
            cout << "Saving...(press m for menu, any key for changing name)";
            cursor_to_pos(get_window_rows() / 2, get_window_cols() / 2 - 5);
            change_color_rgb(240, 100, 19);
            cout << "mistakes: " << Game.mistakes;
            cursor_to_pos(get_window_rows() / 2 + 1, get_window_cols() / 2 - 5);
            change_color_rgb(30, 166, 7);
            cout << "correct: " << Game.correct;
            cursor_to_pos(get_window_rows() / 2 + 2, get_window_cols() / 2 - 5);
            change_color_rgb(214, 13, 13);
            cout << "incorrect: " << Game.incorrect;
            int m = getch();
            if (m == 109)
            {
                clear_screen();
                menu(User);
                return;
            }

            change_color_rgb(245, 92, 10);
            cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 2 - 15);
            cout << "Choose a name for your game: ";
            reset_color();
            cin >> Name;
            Game.name = Name;
            clear_screen();
            menu(User);
        }
    }
}

bool isValidMove(int sudoku[9][9], int row, int col, int num)
{
    for (int x = 0; x < 9; x++)
    {
        if (sudoku[row][x] == num || sudoku[x][col] == num)
            return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (sudoku[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

bool isGameComplete(int sudoku[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku[i][j] == 0)
                return false;
        }
    }
    return true;
}

void sudoku(game &gamestruct, user *User)
{
    int mainSudoku[9][9] = {{4, 8, 0, 0, 0, 0, 6, 0, 3}, {1, 0, 6, 0, 8, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 5, 0, 1, 0}, {7, 5, 4, 1, 2, 0, 0, 8, 6}, {0, 3, 0, 9, 5, 0, 0, 0, 0}, {6, 0, 9, 8, 7, 0, 5, 3, 2}, {0, 4, 0, 0, 6, 0, 0, 0, 0}, {0, 0, 7, 0, 0, 8, 1, 0, 5}, {0, 0, 0, 0, 3, 7, 0, 6, 9}};
    clear_screen();

    int m = 0;
    for (int i = 0; i < 9; i++)
    {
        int n = 0;
        for (int j = 0; j < 9; j++)
        {
            cursor_to_pos(get_window_rows() / 2 - 5 + m, get_window_cols() / 2 - 4 + n);
            if (gamestruct.sudoku[i][j] == 0)
                cout << "0"; // Print empty cells as 0
            else
                cout << gamestruct.sudoku[i][j];
            if ((j + 1) % 3 == 0)
                n += 3;
            else
                n += 2;
        }
        if ((i + 1) % 3 == 0)
            m += 2;
        else
            m++;
    }

    int firstrow = get_window_rows() / 2 - 5;
    int firstcol = get_window_cols() / 2 - 4;
    int currentRow = firstrow;
    int currentCol = firstcol;
    cursor_to_pos(currentRow, currentCol);

    int curs;
    do
    {
        curs = getch();
        int y = currentRow - firstrow;
        int x = (currentCol - firstcol) / 2;

        if ((currentCol - firstcol) % 8 == 6 || (currentRow - firstrow) % 4 == 3)
        {
            continue;
        }

        if (curs == 'a')
        {
            if (currentCol - 2 >= firstcol)
            {
                cursor_to_pos(currentRow, currentCol);
                if (gamestruct.sudoku[y][x] == 0)
                    cout << "0"; // Restore empty cell as 0
                else
                    cout << gamestruct.sudoku[y][x];
                if ((currentCol - firstcol) % 8 == 6)
                    currentCol -= 3;
                else
                    currentCol -= 2;
                cursor_to_pos(currentRow, currentCol);
            }
        }
        else if (curs == 'd')
        {
            if (currentCol + 2 <= firstcol + 20)
            {
                cursor_to_pos(currentRow, currentCol);
                if (gamestruct.sudoku[y][x] == 0)
                    cout << "0"; // Restore empty cell as 0
                else
                    cout << gamestruct.sudoku[y][x];
                if ((currentCol - firstcol) % 8 == 4)
                    currentCol += 3;
                else
                    currentCol += 2;
                cursor_to_pos(currentRow, currentCol);
            }
        }
        else if (curs == 'w')
        {
            if (currentRow - 1 >= firstrow)
            {
                cursor_to_pos(currentRow, currentCol);
                if (gamestruct.sudoku[y][x] == 0)
                    cout << "0"; // Restore empty cell as 0
                else
                    cout << gamestruct.sudoku[y][x];
                currentRow -= ((currentRow - firstrow) % 4 == 3) ? 2 : 1;
                cursor_to_pos(currentRow, currentCol);
            }
        }
        else if (curs == 's')
        {
            if (currentRow + 1 <= firstrow + 12)
            {
                cursor_to_pos(currentRow, currentCol);
                if (gamestruct.sudoku[y][x] == 0)
                    cout << "0"; // Restore empty cell as 0
                else
                    cout << gamestruct.sudoku[y][x];
                currentRow += ((currentRow - firstrow) % 4 == 2) ? 2 : 1;
                cursor_to_pos(currentRow, currentCol);
            }
        }
        else if (curs >= '1' && curs <= '9')
        {
            int num = curs - '0';
            if (gamestruct.sudoku[y][x] == 0)
            {
                if (isValidMove(gamestruct.sudoku, y, x, num))
                {
                    gamestruct.sudoku[y][x] = num;
                    cout << num;
                    cursor_backward(1);
                }
                else
                {
                    gamestruct.mistakes++;
                    cursor_to_pos(get_window_rows() - 2, 1);
                    change_color_rgb(214, 13, 13);
                    cout << "Mistakes: " << gamestruct.mistakes;
                    reset_color();

                    if (gamestruct.mistakes >= 3)
                    {
                        cursor_to_pos(get_window_rows() / 2, get_window_cols() / 2 - 10);
                        change_color_rgb(214, 13, 13);
                        cout << "Game Over! You lost the game.";
                        reset_color();
                        delay(2000);
                        clear_screen();
                        menu(User);
                        return;
                    }
                }
            }
        }
        else if (curs == '0')
        {
            if (gamestruct.sudoku[y][x] != 0)
            {
                gamestruct.sudoku[y][x] = 0;
                cout << "0"; // Clear cell as 0
                cursor_backward(1);
            }
        }
        else if (curs == 27)
        {
            esc(gamestruct, User);
            return;
        }
        else
        {
            continue; // Ignore invalid inputs
        }

        if (isGameComplete(gamestruct.sudoku))
        {
            cursor_to_pos(get_window_rows() / 2, get_window_cols() / 2 - 10);
            change_color_rgb(30, 166, 7);
            cout << "Congratulations! You completed the Sudoku!";
            reset_color();
            delay(2000);
            clear_screen();
            menu(User);
            return;
        }

        delay(100);
    } while (true);
}

void startgame(user *User)
{
    int n;
    do {
        clear_screen();
        cursor_to_pos(1, get_window_cols() / 2 - 5);
        change_color_rgb(10, 18, 242);
        cout << "Select the game level: " << endl;
        reset_color();
        cursor_to_pos(3, get_window_cols() / 2);
        cout << "1: ";
        cursor_to_pos(4, get_window_cols() / 2);
        cout << "2: ";
        cursor_to_pos(5, get_window_cols() / 2);
        cout << "3: ";
        change_color_rgb(10, 204, 17);
        cursor_to_pos(3, get_window_cols() / 2 + 3);
        cout << "Easy";
        cursor_to_pos(4, get_window_cols() / 2 + 3);
        change_color_rgb(227, 182, 20);
        cout << "Medium";
        cursor_to_pos(5, get_window_cols() / 2 + 3);
        change_color_rgb(227, 20, 20);
        cout << "Hard";
        reset_color();
        n = getch() - 48;

        if (n >= 1 && n <= 3)
        {
            games[User->Index][User->gamesCount].level = n;
            delay(200);
            clear_screen();
            int Sudoku[9][9] = {{4, 8, 0, 0, 0, 0, 6, 0, 3}, {1, 0, 6, 0, 8, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 5, 0, 1, 0}, {7, 5, 4, 1, 2, 0, 0, 8, 6}, {0, 3, 0, 9, 5, 0, 0, 0, 0}, {6, 0, 9, 8, 7, 0, 5, 3, 2}, {0, 4, 0, 0, 6, 0, 0, 0, 0}, {0, 0, 7, 0, 0, 8, 1, 0, 5}, {0, 0, 0, 0, 3, 7, 0, 6, 9}};
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                    games[User->Index][User->gamesCount].sudoku[i][j] = Sudoku[i][j];
            }
            games[User->Index][User->gamesCount].userIndex = User->Index;
            sudoku(games[User->Index][User->gamesCount], User);
            return;
        }
        else
        {
            clear_screen();
            cursor_to_pos(1, get_window_cols() / 2 - 10);
            change_color_rgb(214, 13, 13);
            cout << "Invalid level. Please select 1, 2, or 3.";
            reset_color();
            delay(1000);
        }
    } while (true);
}

void menu(user *User)
{
    int n;
    do {
        clear_screen();
        cursor_to_pos(1, get_window_cols() / 2 - 10);
        change_color_rgb(70, 235, 52);
        cout << "Let's Play Sudoku!" << endl;
        reset_color();
        cursor_to_pos(3, get_window_cols() / 2 - 15);
        change_color_rgb(52, 98, 235);
        cout << "<Game Options>" << endl;
        reset_color();
        cursor_to_pos(5, get_window_cols() / 2 - 30);
        change_color_rgb(242, 10, 10);
        cout << "1: Start a New Game" << endl;
        cursor_to_pos(6, get_window_cols() / 2 - 30);
        change_color_rgb(19, 221, 240);
        cout << "2: Play a Saved Game" << endl;
        cursor_to_pos(7, get_window_cols() / 2 - 30);
        change_color_rgb(227, 182, 20);
        cout << "3: LeaderBoard" << endl;
        cursor_to_pos(8, get_window_cols() / 2 - 30);
        change_color_rgb(30, 166, 7);
        cout << "4: Exit the Game" << endl;
        reset_color();
        cursor_to_pos(10, get_window_cols() / 2 - 33);
        change_color_rgb(245, 92, 10);
        cout << "Press a number from 1 to 4: ";
        reset_color();
        cursor_to_pos(10, get_window_cols() / 2 - 5);
        n = getch();

        if (n == 49)
        {
            delay(200);
            clear_screen();
            startgame(User);
        }
        else if (n == 50)
        {
            clear_screen();
            char *Name = new char[100];
            for (int i = 0; i < User->gamesCount; i++)
            {
                change_color_rgb(19, 221, 240);
                cursor_to_pos(2 + i, get_window_cols() / 2);
                cout << games[User->Index][i].name << endl;
            }
            cursor_to_pos(2 + User->gamesCount, get_window_cols() / 2 - 20);
            reset_color();
            cout << "Enter the name of the game you want to play: ";
            cin >> Name;
            for (int j = 0; j < User->gamesCount; j++)
            {
                if (compare(Name, games[User->Index][j].name))
                {
                    clear_screen();
                    sudoku(games[User->Index][j], User);
                    return;
                }
            }
            cursor_to_pos(3 + User->gamesCount, get_window_cols() / 2);
            change_color_rgb(214, 13, 13);
            cout << "Invalid name";
            delay(1000);
            clear_screen();
        }
        else if (n == 51)
        {
            clear_screen();
            change_color_rgb(227, 182, 20);
            cout << "LeaderBoard feature is not implemented yet." << endl;
            delay(1000);
            clear_screen();
        }
        else if (n == 52)
        {
            clear_screen();
            change_color_rgb(30, 166, 7);
            cout << "Exiting the game. Goodbye!" << endl;
            delay(1000);
            exit(0);
        }
        else
        {
            clear_screen();
            change_color_rgb(214, 13, 13);
            cout << "Invalid option. Please try again." << endl;
            delay(1000);
        }
    } while (true);
}

void AddUsername(user Users[100], int &userIndex)
{
    if (userIndex >= 100)
    {
        cout << "Maximum number of users reached!" << endl;
        return;
    }

    char *username = new char[100];
    cursor_to_pos(1, get_window_cols() / 2 - 10);
    change_color_rgb(10, 18, 242);
    cout << "Enter your username: ";
    reset_color();
    cursor_to_pos(1, get_window_cols() / 2 + 12);
    cin >> username;

    for (int i = 0; i < userIndex; i++)
    {
        if (compare(Users[i].name, username))
        {
            cursor_to_pos(2, get_window_cols() / 2 - 20);
            cout << "This username is already taken. Please choose another one.";
            delay(1000);
            clear_screen();
            delete[] username;
            AddUsername(Users, userIndex);
            return;
        }
    }

    Users[userIndex].name = username;
    Users[userIndex].Index = userIndex;
    Users[userIndex].gamesCount = 0;
    userIndex++;
    delay(200);
    clear_screen();
    menu(&Users[userIndex - 1]);
}

int main()
{
    user Users[100];
    for (int i = 0; i < 100; i++)
    {
        Users[i].name = nullptr;
        Users[i].Index = -1;
        Users[i].gamesCount = 0;
    }

    int usernameIndex = 0;

    AddUsername(Users, usernameIndex);

    return 0;
}
