#include<stdlib.h>
#include<iostream>
#include"conio2.h"
#include"typedefs.cpp"

/* Uwaga: w docelowym programie nalezy zadeklarowac odpowiednie
   stale, na przyklad po to, aby wyeliminowac z programu
   wartosci numeryczne umieszczajac w ich miejsce
   dobrze dobrane identyfikatory */

void displayMenu(menu_t menu,char zn)
{
    textcolor(LIGHTGRAY);
    gotoxy(menu.co.x, menu.co.y);
    cputs("esc = wyjscie");
	gotoxy(menu.co.x, menu.co.y+2);
	cputs("strzalki = poruszanie");
	gotoxy(menu.co.x, menu.co.y+3);
	cputs("spacja = zmiana koloru");
	gotoxy(menu.co.x, menu.co.y+4);
	cputs("enter = zmiana koloru tla");
	if(menu.arrows) {
		menu.key_code[16] = '0';
		menu.key_code[17] = '0';
		menu.key_code[18] = ' ';
		menu.key_code[19] = '0';
		menu.key_code[20] = 'x';
		itoa(zn, menu.key_code + 21, 16);
		menu.arrows=0;
	} else {
		itoa(zn, menu.key_code + 16, 16);
		}
	gotoxy(menu.co.x, menu.co.y+5);
	cputs(menu.key_code);
}
/*
    return -1 if not a number
*/
int getint()
{
    int w = 0, zn = 0;
    while(1)
    {
        zn = getche();

        if(zn!=ENTER)
        {
            zn-=48;
            if(zn < 0 || zn > 9)
                return -1;
            w = (w*10) + zn;
        }
        else
        {
            cputs("\n");
            return w;
        }

    }
}

picture_t initPicture()
{
    picture_t pic;
    textbackground(BLACK);
    clrscr();
    gotoxy(1,1);

    //get size
    cputs("Podaj rozmiar obrazka\n");
    cputs("Wysokosc: ");
    do
    {
        pic.h = getint();
    }while(pic.h <= 0);

    cputs("Szerokosc: ");
    do
    {
        pic.w = getint();
    }while(pic.w <= 0);

    //create a matrix
    pic.pixels = (char **) malloc(pic.h*pic.w*sizeof(char));
    if(pic.pixels==NULL)
    {
        cputs("Blad przyznania pamieci\n");
    }
    for(int i=0; i<pic.h; i++)
    {
        pic.pixels[i]=(char *)malloc(pic.w*sizeof(char));
        if(pic.pixels[i]==NULL)
        {
            cputs("Blad przyznania pamieci\n");
        }
    }

    //fill matrix default color
    for(int i=0; i<pic.h; i++)
        for(int j=0; j<pic.w; j++)
        {
            pic.pixels[i][j] = WHITE;
        }

    return pic;
}

void drawPicture(picture_t pic)
{
    cursor_t pencil;
    pencil.co.x=START_M_X+32+1;
    pencil.co.y=START_M_Y+6+1;
    for(int i=0; i<pic.h;i++)
    {
        pencil.co.x=START_M_X+32+1;
        for(int j=0; j<pic.w; j++)
        {
            textbackground(pic.pixels[i][j]);
            gotoxy(pencil.co.x, pencil.co.y);
            putch(' ');
            pencil.co.x++;
        }
        pencil.co.y++;
    }
}

int main() {
    menu_t menu;
    cursor_t cursor;
	int zn = 0;

	// je¿eli program jest kompilowany w czystym jêzyku C
	// proszê odkomentowaæ poni¿sz¹ liniê
	// Conio2_Init();
	settitle("Mateusz Szymanowski 165319");

    do {
		textbackground(CONSOLE_BACKGROUND);
		clrscr();

        switch(pic.status)
        {
        case DEFAULT:

        }
		displayMenu(menu, zn);

		gotoxy(cursor.co.x, cursor.co.y);
		textcolor(cursor.color);
		textbackground(cursor.background);
		putch(cursor.value);

		zn = getch();
		switch(zn)
		{
        case 0:
            menu.arrows = 1;
            zn = getch();
            if(zn == UP) cursor.co.y--;
            else if(zn == DOWN) cursor.co.y++;
            else if(zn == LEFT) cursor.co.x--;
            else if(zn == RIGHT) cursor.co.x++;
            break;
        case ' ':
             cursor.color = (cursor.color + 1) % 16;
             break;
        case ENTER:
            cursor.background = (cursor.background + 1) % 16;
            break;
        case 'n':
            picture_t pic = initPicture();
            drawPicture(pic);
            break;
		}


	} while (zn != ESC);

    textcolor(LIGHTGRAY);
    textbackground(BLACK);
	return 0;
	}
