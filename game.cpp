#include <stdio.h>
#include "TXlib.h"

class Map
{
public:
    int q[20][10];
public:
    Map(); //constructor
    ~Map();             //distructor
    void Draw();
    int get_pixel(int x, int y);
    HDC mapper;

};



class Person
{
private:
    HDC Dest;
public:
    int xP, yP;
private:
    int aP, bP; // xP - x êîîðäèíàòà êàðòèíêè ïåðñîíàæà íà õîëñòå, ïîëîæåíèå ØÀÐÀ íà ÝÊÐÀÍÅ, aP - øèðèíà
    // øàðà ÍÀ ÝÊÐÀÍÅ
    HDC pers;        // ïåðåìåííàÿ, â êîòîðóþ êëàäåòñÿ êàðòèíêà ïåðñîíàæà
    int xS, yS, aS, bS; // xS - õ êîîðä. SpriteØÈÒÀ, êîîðäèíàòà íà ÊÀÐÒÈÍÊÅ ÊÎÍÊÐÅÒÍÎÃÎ ÏÎËÎÆÅÍÈß
    // êîîðäèíàòû x - ñëåâà int Map::get_pixel(int x, int y)
                            //y - ñâåðõó íà÷èíàåòñÿ,    0________x
                                         //           |1 2 3 4 5
                                         //           |2
                                         //          y|3
    // aS - âûñîòà (ØÈÐÈÍÀ) êàðòèíêè íà ñïðàéøèòå
    // bS - âûñîòà (ÄËÈÍÀ) êàðòèíêè íà ñïðàéòøèòå

    COLORREF Color;
    int check;
    int ii;
    int jj;
public:
    Person();
    ~Person();
    void move_Person(Map &Raz);
    void draw_Person();
    void edit_Sprite();
    int get_pixelmap(int x, int y);

};

main ()
{
    int bufx, bufy, ans;
    txCreateWindow(1000, 500);
    Person One;
    Map Raz;
    printf ("Ïðèâåò, äîéäè äî àëìàçèêà ñ ïîìîùüþ ñòðåëî÷êè è óâèäåøü, ÷òî ïðîèçîéäåò : >");
    while(GetAsyncKeyState(VK_ESCAPE)==0)
    {
       txClear();
       Raz.Draw();
       One.move_Person(Raz);
       One.draw_Person();
       if (Raz.get_pixel(One.xP, One.yP)==3)
       break;
       txSleep(100);
    }
}
int Map::get_pixel(int x, int y)
{
    int i;
    int j;
    i=x/50;
    j=y/50;
    return q[i][j];
}

Person::Person()
{
    Dest = txDC();
    xP = 0;
    yP = 0;
    aP = 50;
    bP = 50;
    pers = txLoadImage("pic.bmp");
    xS = 0;
    yS = 0;
    aS = 60;
    bS = 90;

    Color = TX_WHITE;
    check = 0;
    ii = 0;
    jj = 0;
}

Person::~Person()
{
    txDeleteDC (pers);
}



Map::Map()
{
   int w[10][20] = {
   { 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
   { 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
   { 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
   { 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
   { 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0},
   { 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0},
   { 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
   { 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0},
   { 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3} };
   for (int i=0; i<20; i++)
        for (int j=0; j<10; j++)
        {
            q[i][j]=w[j][i];
        }
        mapper = txLoadImage("almaz.bmp");
//        One.set_pixel(i, j)==
}
Map::~Map()
{
    txDeleteDC (mapper);

}

void Map::Draw()
{
    for (int i=0; i<20; i++)
        for (int j=0; j<10; j++)
        {
            if (q[i][j]==0)
                txSetFillColor (TX_GREEN);
            else if (q[i][j]==3)
            {
                Win32::TransparentBlt (txDC(), i*50, j*50, 50, 50, mapper, 0, 0, 50, 50, TX_BLACK);
                continue;
            }
            else
                txSetFillColor (TX_BLUE);
            txRectangle (i*50, j*50, i*50+50, j*50+50);
        }
    txSetFillColor (TX_RED);
    txRectangle (0*50, 0*50, 0*50+50, 0*50+50);
   // txSetFillColor (TX_ORANGE);
    //txRectangle (19*50, 9*50, 19*50+50, 9*50+50);
}

void Person::move_Person(Map &Raz)  //xS - êîîðä íà ñïðàéòøèòå ïî øèðèíå yS - êîîðä íà ñïðàéòøèòå ïî äëèíå
{
    if (GetAsyncKeyState(VK_UP))
    {
        check=1;
        if ((yP>0))
        {
            if (Raz.get_pixel(xP, yP-50)==0||Raz.get_pixel(xP, yP-50)==3)
            {
                yS=90;
                xS=xS+60;
                if (xS>180)
                    xS=0;
                yP=yP-50;
                jj=jj-1;
            }
        }
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        check=2;
        if (yP<450)
        {
            if (Raz.get_pixel(xP, yP+50)==0||Raz.get_pixel(xP, yP+50)==3)
            {
                yS=0;
                xS=xS+60;
                if (xS>180)
                    xS=0;
                yP=yP+50;
                jj=jj-1;
            }
        }
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        check=3;
        if (xP>0)
        {
            if (Raz.get_pixel(xP-50, yP)==0||Raz.get_pixel(xP-50, yP)==3)
            {
                yS=180;
                xS=xS+60;
                if (xS>180)
                    xS=0;
                xP=xP-50;
                ii=ii-1;
            }
        }
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        check=4;
        if (xP<950)
        {
            if (Raz.get_pixel(xP+50, yP)==0||Raz.get_pixel(xP+50, yP)==3)
            {
                yS=270;
                xS=xS+60;
                if (xS>180)
                    xS=0;
                xP=xP+50;
            }
        }
    }
    if (Raz.get_pixel(xP, yP)==3)
    {
//        Raz.set_pixel(
    }
};

void Person::draw_Person()
{
    Win32::TransparentBlt (Dest, xP, yP, aP, bP, pers, xS, yS, aS, bS, Color);
};
