#include<stdlib.h>
#include"conio2.h"
#include"typedefs.cpp"

/* Uwaga: w docelowym programie nalezy zadeklarowac odpowiednie
   stale, na przyklad po to, aby wyeliminowac z programu
   wartosci numeryczne umieszczajac w ich miejsce
   dobrze dobrane identyfikatory */

void displayMenu(menu_t menu, char zn, status_t status)
{
    textcolor(TEXT_COLOR);
    gotoxy(menu.co.x, menu.co.y);

    switch(status)
    {
    case DEFAULT:
        cputs("esc = wyjscie");
        gotoxy(menu.co.x, menu.co.y+1);
        cputs("strzalki = poruszanie");
        gotoxy(menu.co.x, menu.co.y+2);
        cputs("spacja = zmiana koloru");
        gotoxy(menu.co.x, menu.co.y+3);
        cputs("n = nowy obraz");
        gotoxy(menu.co.x, menu.co.y+4);
        break;
    case DRAW:
        cputs("esc = wyjscie");
        gotoxy(menu.co.x, menu.co.y+1);
        cputs("strzalki = poruszanie");
        gotoxy(menu.co.x, menu.co.y+2);
        cputs("spacja = zmiana koloru");
        gotoxy(menu.co.x, menu.co.y+3);
        break;
    }

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

	gotoxy(menu.co.x, menu.co.y+4);
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
    textbackground(CONSOLE_BACKGROUND);
    textcolor(TEXT_COLOR);
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

    pic.status = DRAW;

    return pic;
}

void displayPicture(picture_t pic)
{
    cursor_t pencil;
    pencil.co.x=START_P_X;
    pencil.co.y=START_P_Y;
    for(int i=0; i<pic.h;i++)
    {
        pencil.co.x=START_P_X;
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

void draw(picture_t pic, cursor_t pencil)
{
    int x,y;
    x = pencil.co.x-START_P_X;
    y = pencil.co.y-START_P_Y;
    if(x >= 0 && x < pic.w && y >= 0 && y < pic.h )
        pic.pixels[y][x]=pencil.background;
}

int main() {
    menu_t menu;
    cursor_t cursor;
    picture_t pic;
	int zn = 0;
	textcolor(TEXT_COLOR);

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
            displayMenu(menu,zn, pic.status);
            break;
        case DRAW:
            displayMenu(menu, zn, pic.status);
            displayPicture(pic);
            break;
        case DRAW_LINE:

            break;
        case DRAW_RECTANGLE:

            break;
        }

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
            pic = initPicture();
            break;
        case 'm':
            draw(pic,cursor);
            break;
		}


	} while (zn != ESC);

    textcolor(LIGHTGRAY);
    textbackground(BLACK);
	return 0;
	}
