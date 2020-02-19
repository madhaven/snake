#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int right=2, left=-2, up=3, down=-3, length=3, score=0, speed=10;
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct location
{
    int direction, x, y;
}snake[10000], food;
void intro()
{
    int i;
    system("mode 75, 45");
    gotoxy(32, 23);
    printf("LET'S PLAY SNAKE");
    gotoxy(29, 26);
    printf("(Hold SPACE to pause)");
    gotoxy(29, 26);
        getch();
    printf("                     ");
    gotoxy(33, 23);
    printf("                ");
    gotoxy(30, 23);
    printf("Select your Level : ");
    while(1)
    {
        printf("%d", speed);
        if (getch()=='\r')
            break;
        if (speed==10)
            printf("\b \b\b \b");
        else printf("\b \b");
        if (GetAsyncKeyState(VK_DOWN)&&(speed>1))
        {
            getch();
            speed--;
        }
        else if (GetAsyncKeyState(VK_UP)&&(speed<10))
        {
            getch();
            speed++;
        }
    }
    switch (speed)
    {
    case 1:speed=10; break;
    case 2:speed=9; break;
    case 3:speed=8; break;
    case 4:speed=7; break;
    case 5:speed=6; break;
    case 6:speed=5; break;
    case 7:speed=4; break;
    case 8:speed=3; break;
    case 9:speed=2; break;
    case 10:speed=1; break;
    }
    gotoxy(30, 23);
    printf("                      ");
    gotoxy(38-5, 0);
    printf("SNAKE GAME");
    gotoxy(1, 1);
    printf("Score : %d", score);
    //_sleep(500);
    gotoxy(2, 2);printf("%c", (char)218); ///border creation
    gotoxy(2, 42); printf("%c", (char)192);
    gotoxy(72, 2); printf("%c", (char)191);
    gotoxy(72, 42); printf("%c", (char)217);
    for (i=3; i<72; i++)
    {
        gotoxy(i, 2);
        printf("%c", (char)196);
        gotoxy(i, 42);
        printf("%c", (char)196);
    }
    for (i=3; i<42; i++)
    {
        gotoxy(2, i);
        printf("%c", (char)179);
        gotoxy(72, i);
        printf("%c", (char)179);
    }
}
char displaystraight(int dir)
{
    if ((dir==right)||(dir==left))
        return (char)205;
    else return (char)186;
}
char displaybend(int a, int b)
{
    if (((b==right)&&(a==up))||((b==down)&&(a==left)))
        return (char)188;
    else if (((b==right)&&(a==down))||((b==up)&&(a==left)))
        return (char)187;
    else if (((b==left)&&(a==up))||((b==down)&&(a==right)))
        return (char)200;
    else if (((b==up)&&(a==right))||((b==left)&&(a==down)))
        return (char)201;
}
void move()
{
        int i;
        for (i=0; i<length; i++) ///displays snake's body
        {
            gotoxy(snake[i].x, snake[i].y);
            if (i==0)
                printf("%c", '%');//64
            else  if (snake[i].direction==snake[i-1].direction)
                printf("%c", displaystraight(snake[i].direction));
            else printf("%c", displaybend(snake[i-1].direction, snake[i].direction));
        }

        if (GetAsyncKeyState(VK_SPACE))
            while (getch()!=' ')
                ;
        _sleep(50+(speed-1)*10); ///delay+

        gotoxy(snake[length-1].x, snake[length-1].y);
        printf(" "); ///erases the tail end.

        for (i=length-1; i>0; i--) ///shifts positions for each step
        {
            snake[i].x=snake[i-1].x;
            snake[i].y=snake[i-1].y;
            snake[i].direction=snake[i-1].direction;
        }
        if (GetAsyncKeyState(VK_UP)&&(snake[0].direction%2==0)) ///head movement algorithm
        {
            //getch();
            snake[0].direction=up;
            snake[0].y--;
        }
        else if (GetAsyncKeyState(VK_DOWN)&&(snake[0].direction%2==0))
        {
            //getch();
            snake[0].direction=down;
            snake[0].y++;
        }
        else if (GetAsyncKeyState(VK_RIGHT)&&(snake[0].direction%3==0))
        {
            //getch();
            snake[0].direction=right;
            snake[0].x++;
        }
        else if (GetAsyncKeyState(VK_LEFT)&&(snake[0].direction%3==0))
        {
            //getch();
            snake[0].direction=left;
            snake[0].x--;
        }

        else if (snake[0].direction==right)
            snake[0].x++;
        else if (snake[0].direction==left)
            snake[0].x--;
        else if (snake[0].direction==up)
            snake[0].y--;
        else if (snake[0].direction==down)
            snake[0].y++;
    ending:;

}
void makefood()
{
    int i;
    //srand();
    food.x=3+rand()%69;
    food.y=3+rand()%39;
    for(i=0; i<length; i++)
    {
        if ((food.x==snake[i].x)&&(food.y==snake[i].y))
            makefood();
    }
}
int hit()
{
    int i;
    for (i=1; i<length; i++)
        if ((snake[0].x==snake[i].x)&&(snake[0].y==snake[i].y))
            return 1;
    if ((snake[0].x==2)||(snake[0].x==72)||(snake[0].y==2)||(snake[0].y==42))
        return 1;
    else if ((snake[0].x==food.x)&&(snake[0].y==food.y))
        return -1;
    else return 0;
}
int main()
{
    int i;
    intro();
    snake[0].direction=right; /// initialization
    snake[0].x=35;
    snake[0].y=20;
    snake[1].direction=right;
    snake[1].x=34;
    snake[1].y=20;
    snake[2].direction=right;
    snake[2].x=33;
    snake[2].y=20;
    makefood();
    while (1)
    {
        gotoxy(food.x, food.y);
        printf("@");
        move();
        int z;
        /**GOD MODE
        for (z=0; z<length; z++)
        {gotoxy(0, z); printf("snake[%d] = %d, %d", z, snake[z].x, snake[z].y); }
        //getch();*/
        if (hit()==1)
        {
            _sleep(500);
            gotoxy(32, 23);
            printf("YOUR SCORE IS : %d", score);
            _sleep(2000);
            exit(0);
        }
        else if (hit()==-1)
        {
            score++;
            length++;
            gotoxy(9, 1);
            printf("%d", score);
            makefood();
        }
    }
    return 0;
}
