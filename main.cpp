#include<stdlib.h>
#include"conio2.h"

/* Uwaga: w docelowym programie nalezy zadeklarowac odpowiednie
   stale, na przyklad po to, aby wyeliminowac z programu
   wartosci numeryczne umieszczajac w ich miejsce 
   dobrze dobrane identyfikatory */

int main() {
	int zn = 0, x = 40, y = 12, attr = 7, back = 0, zero = 0;
	char txt[32] = "kod klawisza: 0x";
	// je¿eli program jest kompilowany w czystym jêzyku C
	// proszê odkomentowaæ poni¿sz¹ liniê
	// Conio2_Init();
	settitle("imie nazwisko nr_indeksu");
	do {
		textbackground(BLACK);
		clrscr();
		textcolor(7);
		gotoxy(55, 1);
		cputs("q = wyjscie");
		gotoxy(55, 2);
		cputs("strzalki = poruszanie");
		gotoxy(55, 3);
		cputs("spacja = zmiana koloru");
		gotoxy(55, 4);
		cputs("enter = zmiana koloru tla");
		if(zero) {
			txt[16] = '0';
			txt[17] = '0';
			txt[18] = ' ';
			txt[19] = '0';
			txt[20] = 'x';
			itoa(zn, txt + 21, 16);
		} else {
			itoa(zn, txt + 16, 16);
			}
		gotoxy(55, 5);
		cputs(txt);
		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);
		putch('*');
		zero = 0;
		zn = getch();
		if(zn == 0) {
			zero = 1;
			zn = getch();
			if(zn == 0x48) y--;
			else if(zn == 0x50) y++;
			else if(zn == 0x4b) x--;
			else if(zn == 0x4d) x++;
		} else if(zn == ' ') attr = (attr + 1) % 16;
		else if(zn == 0x0d) back = (back + 1) % 16;
	} while (zn != 'q');

	return 0;
	}
