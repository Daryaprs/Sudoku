#include <iostream>
#include <time.h>
#include "clui.h"
using namespace std;
struct game {
    char* name="null";
    int userIndex;
    int gameIndex;
    int sudoku[9][9];
    int min;
    int sec;
    int level;
    int mistakes=0;
    int correct=0;
    int incorrect=0;

};
struct user {
    char* name;
    int Index;
    int gamesCount=0;
};
game games[100][100];
int length(char* str)
{
    int length=0;
    while (str[length]!='\0')
    {
        length++;
    }
    return length;
}

bool compare(char* u1 , char* u2)
{
    if (length(u1)!=length(u2))
    return false;
    else
    {
        for(int i=0 ; i < length(u1) ; i++)
        {
            if (u1[i]!=u2[i])
            return false;
        }
    }
    return true;
}
void sudoku(game& , user*);
void menu(user*);
void esc(game &Game, user* User)
{
    clear_screen();
    cursor_to_pos(get_window_rows()/2, get_window_cols()/2-20);
    change_color_rgb(245, 92, 10);
    cout<<"The game is paused. Press the Esc key to continue.";
    reset_color();
    int n = getch();
    if(n==27)
    {
        clear_screen();
        sudoku(Game, User);
        return;
    }
    else if(n==115)
    {
        delay(200);
        clear_screen();
        char* Name = new char[100];
        cursor_to_pos(get_window_rows()/2-1, get_window_cols()/2-5);
        char* null = new char[4];
        null="null";
        change_color_rgb(7, 140, 3);
        if(compare(null, Game.name))
        {
            cout<<"Saving...";
            cursor_to_pos(get_window_rows()/2, get_window_cols()/2-5);
            change_color_rgb(240, 100, 19);
            cout<<"mistakes: "<<Game.mistakes;
            cursor_to_pos(get_window_rows()/2+1, get_window_cols()/2-5);
            change_color_rgb(30, 166, 7);
            cout<<"correct: "<<Game.correct;
            cursor_to_pos(get_window_rows()/2+2, get_window_cols()/2-5);
            change_color_rgb(214, 13, 13);
            cout<<"incorrect: "<<Game.incorrect;
            cursor_to_pos(get_window_rows()/2+3, get_window_cols()/2-15);
            change_color_rgb(245, 92, 10);
            cout<<"Choose a name for your game: ";
            reset_color();
            cin>>Name;
            Game.name = Name;
            User->gamesCount++;
            clear_screen();
            menu(User);
        }
        else
        {
            cursor_to_pos(get_window_rows()/2-1, get_window_cols()/2-15);
            change_color_rgb(7, 140, 3);
            cout<<"Saving...(press m for menu, any key for changing name)";
            cursor_to_pos(get_window_rows()/2, get_window_cols()/2-5);
            change_color_rgb(240, 100, 19);
            cout<<"mistakes: "<<Game.mistakes;
            cursor_to_pos(get_window_rows()/2+1, get_window_cols()/2-5);
            change_color_rgb(30, 166, 7);
            cout<<"correct: "<<Game.correct;
            cursor_to_pos(get_window_rows()/2+2, get_window_cols()/2-5);
            change_color_rgb(214, 13, 13);
            cout<<"incorrect: "<<Game.incorrect;
            int m = getch();
            if(m==109)
            {
                clear_screen();
                menu(User);
                return;
            }
            
            change_color_rgb(245, 92, 10);
            cursor_to_pos(get_window_rows()/2+3, get_window_cols()/2-15);
            cout<<"Choose a name for your game: ";
            reset_color();
            cin>>Name;
            Game.name = Name;
            clear_screen();
            menu(User);
            
        }
        
        
    }
}

void sudoku(game &gamestruct, user *User)
{
    int mainSudoku[9][9] = {{4,8,0,0,0,0,6,0,3},{1,0,6,0,8,0,0,0,0},{0,0,0,0,0,5,0,1,0},{7,5,4,1,2,0,0,8,6},{0,3,0,9,5,0,0,0,0},{6,0,9,8,7,0,5,3,2},{0,4,0,0,6,0,0,0,0},{0,0,7,0,0,8,1,0,5},{0,0,0,0,3,7,0,6,9}};
    int solved[9][9] = {{4,8,5,7,1,2,6,9,3}, {1,7,6,3,8,9,2,5,4}, {2,9,3,6,4,5,7,1,8}, {7,5,4,1,2,3,9,8,6}, {8,3,2,9,5,6,4,7,1}, {6,1,9,8,7,4,5,3,2}, {9,4,8,5,6,1,3,2,7}, {3,6,7,2,9,8,1,4,5}, {5,2,1,4,3,7,8,6,9}};
    int m=0;
    for(int i=0 ; i<9 ; i++)
    {   
        int n=0;
        
        for(int j=0; j<9 ; j++)
        {
            cursor_to_pos(get_window_rows()/2 -5+m,get_window_cols()/2-4+n);
            cout<<gamestruct.sudoku[i][j];
            if((j+1)%3==0)
            n+=3;
            else
            n+=2;
        }
        if((i+1)%3==0)
        m+=2;
        else
        m++;
    }
    int firstrow = get_window_rows()/2 -5;
    int firstcol = get_window_cols()/2 -4;
    cursor_to_pos(firstrow , firstcol);
    int curs;
    do{
        curs=getch();
        if(curs==97)
        {
            if(get_cursor_y()-1>=firstcol)
            {
                if((get_cursor_y()==firstcol+7)||(get_cursor_y()==firstcol+14))
                cursor_backward(3);
                else
                cursor_backward(2);
            }
            
        }
        else if(curs==100)
        {
            if (get_cursor_y()+2<=firstcol+19)
            {
                if((get_cursor_y()==firstcol+4)||(get_cursor_y()==firstcol+11))
                cursor_forward(3);
                else
                cursor_forward(2);
            }
        }
        else if(curs==119)
        {
            if(get_cursor_x()-1>=firstrow)
            {
                if((get_cursor_x()==firstrow+4)||(get_cursor_x()==firstrow+8))
                cursor_up(2);
                else
                cursor_up(1);
            }
        }
        else if(curs==115)
        {
            if(get_cursor_x()+1<=firstrow+10)
            {
                if ((get_cursor_x()==firstrow+2)||(get_cursor_x()==firstrow+6))
                cursor_down(2);
                else
                cursor_down(1);
            }
            
        }
        else if(curs>=49&&curs<=57)
        {
            int y = get_cursor_x()-firstrow;
            int x = get_cursor_y()-firstcol;
            if(x>=0&&x<=4)
            x/=2;
            else if(x>=7&&x<=11)
            x/=2;
            else if(x>=14&&x<=18)
            x=x/2-1;
            if(y>2&&y<=6)
            y-=1;
            if(y>6)
            y-=2;
            int result=1;
            if (mainSudoku[y][x]!=0)
            {
                save_cursor();
                cursor_to_pos(firstrow-2, firstcol + 3);
                cout<<"Fixed Number!";
                delay(1000);
                cursor_to_pos(firstrow-2, firstcol + 3);
                cout<<"             ";
                restore_cursor();
                continue;
            }
            for(int i=0 ; i<3 ; i++)
            {
                for(int j=0 ; j<3 ; j++)
                {
                    if(gamestruct.sudoku[(y/3)*3+i][(x/3)*3+j]==(curs-48))
                    {
                        result=0;
                        break;
                    }
                }
            }
            if(result==0)
            {
                save_cursor();
                cursor_to_pos(firstrow-2, firstcol + 6);
                cout<<"Wrong!";
                gamestruct.mistakes++;
                delay(1000);
                cursor_to_pos(firstrow-2, firstcol + 6);
                cout<<"      ";
                restore_cursor();
                continue;
            }
            for(int i=0; i<9; i++)
            {
                if((gamestruct.sudoku[i][x]==(curs-48))||(gamestruct.sudoku[y][i]==(curs-48)))
                {
                    result=0;
                    break;
                }
            }
            if(result==0)
            {
                save_cursor();
                cursor_to_pos(firstrow-2, firstcol + 6);
                cout<<"Wrong!";
                gamestruct.mistakes++;
                delay(1000);
                cursor_to_pos(firstrow-2, firstcol + 6);
                cout<<"      ";
                restore_cursor();
                continue;
            }
            else
            {
                cout<<curs-48;
                if(gamestruct.sudoku[y][x]==0)
                {
                    if(solved[y][x]==(curs-48))
                    gamestruct.correct++;
                    else
                    gamestruct.incorrect++;
                }
                else
                {
                    if(gamestruct.sudoku[y][x]==solved[y][x])
                    {
                        if(solved[y][x]!=(curs-48))
                        {
                            gamestruct.correct--;
                            gamestruct.incorrect++;
                        }
                    }
                    else
                    {
                        if(solved[y][x]==(curs-48))
                        {
                            gamestruct.correct++;
                            gamestruct.incorrect--;
                        }
                    }
                }
                gamestruct.sudoku[y][x]=curs-48;
                cursor_backward(1);
            }
            
        }
        else if (curs==48)
        {
            int y = get_cursor_x()-firstrow;
            int x = get_cursor_y()-firstcol;
            if(x>=0&&x<=4)
            x/=2;
            else if(x>=7&&x<=11)
            x/=2;
            else if(x>=14&&x<=18)
            x=x/2-1;
            if(y>2&&y<=6)
            y-=1;
            if(y>6)
            y-=2;
            if(mainSudoku[y][x]==0)
            {
                cout<<0;
                gamestruct.sudoku[y][x]=0;
                cursor_backward(1);
            }
        }
        else if(curs==27)
        {
            esc(gamestruct, User);
            return;
        }

        
    }
    while(true);


}

void startgame(user *User)
{
    int n;
    cursor_to_pos(1, get_window_cols()/2 -5);
    change_color_rgb(10, 18, 242);
    cout<<"Select the game level: "<<endl;
    reset_color;
    cursor_to_pos(3, get_window_cols()/2);
    cout<<"1: ";
    cursor_to_pos(4, get_window_cols()/2);
    cout<<"2: ";
    cursor_to_pos(5, get_window_cols()/2);
    cout<<"3: ";
    change_color_rgb(10, 204, 17);
    cursor_to_pos(3, get_window_cols()/2 +3);
    cout<<"Easy";
    cursor_to_pos(4, get_window_cols()/2 +3);
    change_color_rgb(227, 182, 20);
    cout<<"Medium";
    cursor_to_pos(5, get_window_cols()/2 +3);
    change_color_rgb(227, 20, 20);
    cout<<"Hard";
    reset_color();
    n = getch()-48;
    games[User->Index][User->gamesCount].level = n;
    delay(200);
    clear_screen();
    int Sudoku[9][9] = {{4,8,0,0,0,0,6,0,3},{1,0,6,0,8,0,0,0,0},{0,0,0,0,0,5,0,1,0},{7,5,4,1,2,0,0,8,6},{0,3,0,9,5,0,0,0,0},{6,0,9,8,7,0,5,3,2},{0,4,0,0,6,0,0,0,0},{0,0,7,0,0,8,1,0,5},{0,0,0,0,3,7,0,6,9}}; 
    for(int i=0 ; i<9; i++)
    {
        for(int j=0 ; j<9 ; j++)
        games[User->Index][User->gamesCount].sudoku[i][j]=Sudoku[i][j];
    }
    games[User->Index][User->gamesCount].userIndex = User->Index;
    sudoku(games[User->Index][User->gamesCount], User);
}

void menu(user *User)
{
    int n;
    cursor_to_pos(1, get_window_cols()/2);
    change_color_rgb(70, 235, 52);
    cout<<"Let's Play Sudoku!"<<endl;
    reset_color();
    cursor_to_pos(2, get_window_cols()/2 + 2);
    change_color_rgb(52, 98, 235);
    cout<<"<Game Options>"<<endl;
    reset_color();
    cursor_to_pos(4, get_window_cols()/2 -30);
    cout<<"1: "<<endl;
    cursor_to_pos(5, get_window_cols()/2 -30);
    cout<<"2: "<<endl;
    cursor_to_pos(6, get_window_cols()/2 -30);
    cout<<"3: "<<endl;
    cursor_to_pos(7, get_window_cols()/2 -30);
    cout<<"4: "<<endl;
    cursor_to_pos(4, get_window_cols()/2 -27);
    change_color_rgb(242, 10, 10);
    cout<<"Start a New Game"<<endl;
    cursor_to_pos(5, get_window_cols()/2 -27);
    cout<<"Play a Saved Game"<<endl;
    cursor_to_pos(6, get_window_cols()/2 -27);
    cout<<"LeaderBoard"<<endl;
    cursor_to_pos(7, get_window_cols()/2 -27);
    cout<<"Exit the Game"<<endl;
    reset_color();
    cursor_to_pos(9, get_window_cols()/2 -33);
    cout<<"Press a number from 1 to 4: ";
    cursor_to_pos(9, get_window_cols()/2 -5);
    n=getch();
    if(n==49)
    {
        delay(200);
        clear_screen();
        startgame(User);
    }
    else if(n==50)
    {
        clear_screen();
        char* Name = new char[100];
        for(int i=0 ; i<User->gamesCount ; i++)
        {
            change_color_rgb(19, 221, 240);
            cursor_to_pos(2+i, get_window_cols()/2);
            cout<<games[User->Index][i].name<<endl;
        }
        cursor_to_pos(2+User->gamesCount, get_window_cols()/2-20);
        cout<<"Enter the name of the game you want to play: ";
        reset_color();
        cin>>Name;
        for (int j=0 ; j<User->gamesCount; j++)
        {
            if(compare(Name, games[User->Index][j].name))
            {
                clear_screen();
                sudoku(games[User->Index][j], User);
                return;
            }
        }
        cursor_to_pos(3+User->gamesCount, get_window_cols()/2);
        cout<<"invalid name";
        menu(User);


    }
}

void AddUsername(user Users[100], int &userIndex)
{
    Users[userIndex].name = new char[100];
    cursor_to_pos(1, get_window_cols()/2 -10);
    change_color_rgb(10, 18, 242);
    cout<<"Enter your username: ";
    reset_color();
    cursor_to_pos(1, get_window_cols()/2 +12);
    char* username = new char[100];
    cin>>username;
    for(int i=0 ; i<userIndex ; i++)
    {
        if(compare(Users[i].name, username))
        {
            cursor_to_pos(2, get_window_cols()/2 -20);
            cout<<"This username is already taken. Please choose another one.";
            delay(1000);
            clear_screen();
            AddUsername(Users, userIndex);
            return;
        }
    }
    Users[userIndex].name = username;
    Users[userIndex].Index = userIndex;
    userIndex++;
    delay(200);
    clear_screen();
    menu(&Users[userIndex]);


}

int main()
{
    user Users[100]; 
    int usernameIndex = 0;
    AddUsername(Users, usernameIndex);

    getch();
    return 0;
}


