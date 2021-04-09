#include <iostream>
#include <conio.h> /*This is for input*/
#include <windows.h>
using namespace std;
bool GameOver; /*The Counstant for the game */
const int width = 20, height = 20;
int x, y, fruitx, fruity, Score;
int tailX[100], tailY[100], nTail;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir; /*Holds the direction of the snake*/
void Setup()
{
    GameOver = false;
    dir = STOP;
    x = width / 2; /*Holds the snake head at the centre*/
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    Score = 0;
}
void Draw()
{
    system("cls");                      /*This will maintain the map of the game*/
    for (int i = 0; i < width + 2; i++) /*This is the map of the game */
    {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 )
            {
                cout << "#";
            }
            if (i == y && j == x) /*Here this will place the O at the centre */
            {
                cout << "O";
            }
            else if (i == fruity && j == fruitx) /*This will spawn the F at the random place*/
            {
                cout << "F";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout <<".";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
            if( j == width - 1)
            {
                cout<<"#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;
    cout << "---SCORE---" << Score << endl;
}
void Input()
{
    if (_kbhit()) /*This kbhit will return a boolian value if key is been pressed or not*/
    {
        switch (_getch()) /*This will return the acsci value of the key we press(_getch)*/
        {
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'q':
            system("PAUSE");
            break;
        }
    }
}
void Logic()
{
    int privX = tailX[0];   /*This is for following the tail*/
    int privY = tailY[0];
    int priv2X, priv2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        priv2X = tailX[i];
        priv2Y = tailY[i];
        tailX[i] = privX;
        tailY[i] = privY;
        privX = priv2X;
        privY = priv2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
        default:
		break;
    }
    // if (x > width || x < 0 || y > height || y < 0)
    // {
    //     GameOver = true;
    // }
    if(x>=width) x=0; else if(x < 0) x=width-1;
    if(y>=height) y=0; else if(y < 0) y=height-1;
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            GameOver = true;
        }
    }
    if (x == fruitx && y == fruity) /*This part when we hit the F*/
    {
        Score += 10;
        fruitx = rand() % width;
        fruity = rand() % width;
        nTail++;
    }
}

int main()
{
    Setup();
    GameOver = false;
    while (!GameOver)
    {
        Draw();
        Input();
        Logic();
        //Sleep(60);
        
    }
    return 0;
}