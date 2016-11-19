#include<stdlib.h>
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
		}


	} while (zn != ESC);

    textcolor(LIGHTGRAY);
    textbackground(BLACK);
	return 0;
	}
