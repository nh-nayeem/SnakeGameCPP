#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>

#define N 100
#define R 25
#define C 75
using namespace std;

int headX,headY;
int score;
bool running;
int foodX,foodY;
int _MAP[R][C];
char dir;
queue<int> tailX;
queue<int> tailY;

int gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  return 0;
}
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void clear_pos(int x,int y){ gotoxy(x,y);cout<<' ';}
void draw_pos(int x,int y,char c) { gotoxy(x,y);cout<<c; }

void rand_food()
{
    srand(time(0));
    foodX=(rand()%(C-2))+1;
    foodY=(rand()%(R-2))+1;
}

void init()
{
    running=true;
    for(int i=0;i<R;i++)
    {
        for(int j=0;j<C;j++)
        {
            if(i==0 || j==0 || i==R-1 || j==C-1 )
            {
                gotoxy(j,i);
                cout<<(char)219;
            }
            _MAP[i][j]=0;
        }
    }
    headX=C/2;
    headY=R/2;
    dir='d';
    tailX.push(headX-1);tailY.push(headY);
    tailX.push(headX-2);tailY.push(headY);
    rand_food();
}

void MOVE(char c)
{
    if((dir!='a' && c=='d')||(dir!='d' && c=='a')||(dir!='w' && c=='s')||(dir!='s' && c=='w'))
        dir=c;
    if(dir=='d')
    {
        headX=(headX+1)%(C-1);
        headX+=(headX==0);
    }
    else if( dir=='a' )
    {
        headX--;
        headX+=(headX==0)*(C-2);

    }
    else if(dir=='s')
    {
        headY=(headY+1)%(R-1);
        headY+=(headY==0);
    }
    else if(dir=='w')
    {
        headY--;
        headY+=(headY==0)*(R-2);
    }

    draw_pos(headX,headY,79);
    draw_pos(foodX,foodY,148);

    if(_MAP[headY][headX])
    {
        running=false;
        return;
    }
    _MAP[headY][headX]=1;
    if(headX==foodX && headY==foodY)
    {
        score++;
        rand_food();
    }
    else
    {
        int tx=tailX.front();tailX.pop();
        int ty=tailY.front();tailY.pop();
        _MAP[ty][tx]=0;
        clear_pos(tx,ty);
    }
    tailX.push(headX);
    tailY.push(headY);
    draw_pos(foodX,foodY,148);
}

void run()
{
    int level=0;
    cout<<"\n\n\n\t\t        Snake game made by Nayeem\n ";
    cout<<"\n\n\n\t\t      which level u want to play(0-3)\n\n\t\t\t\t= ";
    cin>>level;
    level=min(3,max(0,level));
    system("cls");
    init();
    //remove_cursor();
    char ch='d';
    //getch();
    while(running)
    {
        if(kbhit())
        {
            ch=getch();
        }
        MOVE(ch);
        if(dir=='w' || dir=='s') Sleep(50-level*10);
        Sleep(200-level*50);
    }
    system("cls");
    cout<<"\n\n\n\n\n\n\t\t\t\tGame over..\n\n\t\t\t      final score = "<<score<<"\n\n\n\t\t\t";
    system("pause");
}
int main()
{
    //ios::sync_with_stdio(false);
    //remove_cursor();
    ShowConsoleCursor(false);
    system("C:\\Windows\\system32\\mode con: cols=76 lines=26");
    system("COLOR 0C");
    run();
	return 0;
}
