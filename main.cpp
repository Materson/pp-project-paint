#include<stdlib.h>
#include"conio2.h"

/* Uwaga: w docelowym programie nalezy zadeklarowac odpowiednie
   stale, na przyklad po to, aby wyeliminowac z programu
   wartosci numeryczne umieszczajac w ich miejsce
   dobrze dobrane identyfikatory */

#define START_C_X 40
#define START_C_Y 12
#define START_M_X 55
#define START_M_Y 1

#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

typedef struct
{
    int x;
    int y;
}coordinate_t;

typedef struct
{
    char key_code[32] = "kod klawisza: 0x";
    int arrows = 0;
    coordinate_t co = {START_M_X, START_M_Y};
}menu_t;



void displayMenu(menu_t menu,char zn)
{
    textcolor(LIGHTGRAY);
    gotoxy(menu.co.x, menu.co.y);
    cputs("q = wyjscie");
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

int main() {
    menu_t menu;
	int zn = 0, c_x = START_C_X, c_y = START_C_Y, attr = LIGHTGRAY, back = BLACK;

	// je¿eli program jest kompilowany w czystym jêzyku C
	// proszê odkomentowaæ poni¿sz¹ liniê
	// Conio2_Init();
	settitle("Mateusz Szymanowski 165319");

	do {
		textbackground(BLACK);
		clrscr();

		displayMenu(menu, zn);

		gotoxy(c_x, c_y);
		textcolor(attr);
		textbackground(back);
		putch('*');

		zn = getch();
		switch(zn)
		{
        case 0:
            menu.arrows = 1;
            zn = getch();
            if(zn == UP) c_y--;
            else if(zn == DOWN) c_y++;
            else if(zn == LEFT) c_x--;
            else if(zn == RIGHT) c_x++;
            break;
        case ' ':
             attr = (attr + 1) % 16;
             break;
        case 0x0d:
            back = (back + 1) % 16;
            break;
		}

	} while (zn != 'q');

    textcolor(LIGHTGRAY);
    textbackground(BLACK);
	return 0;
	}
