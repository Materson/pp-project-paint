#include<stdlib.h>
#include"conio2.h"
#include"typedefs.cpp"

/* Uwaga: w docelowym programie nalezy zadeklarowac odpowiednie
   stale, na przyklad po to, aby wyeliminowac z programu
   wartosci numeryczne umieszczajac w ich miejsce
   dobrze dobrane identyfikatory */

void displayMenu(menu_t menu, char zn, picture_t pic)
{
    textcolor(TEXT_COLOR);
    gotoxy(menu.co.x, menu.co.y);

    switch(pic.status)
    {
    case DEFAULT:
        cputs("esc = wyjscie");
        gotoxy(menu.co.x, menu.co.y+1);
        cputs("n = nowy obraz");
        gotoxy(menu.co.x, menu.co.y+2);
        break;
    case DRAW:
        cputs("esc = wyjscie");
        gotoxy(menu.co.x, menu.co.y+1);
        cputs("n = nowy obraz");
        gotoxy(menu.co.x, menu.co.y+2);
        cputs("strzalki = poruszanie");
        gotoxy(menu.co.x, menu.co.y+3);
        cputs("spacja = postaw kolor");
        gotoxy(menu.co.x, menu.co.y+4);
        cputs("0-9, q,w,e,r,t,y = zmiana koloru");
        gotoxy(menu.co.x, menu.co.y+5);
        cputs("Nazwa obrazu: "); cputs(pic.name);
        gotoxy(menu.co.x, menu.co.y+6);
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

void gettxt(char *text)
{
    int zn = NULL, i = 0;
    while(zn != ENTER && i<(MAX_NAME - 1))
    {
        zn = getch();
        if((zn >= 'a' && zn <= 'z') ||
           (zn >= 'A' && zn <= 'Z') ||
           (zn >= '0' && zn <= '9') ||
           (zn == '(' || zn == ')'))
        {
            text[i] = zn;
            putch(zn);
            i++;
        }
    }
    text[i] = '\0';
    cputs("\n");
}

picture_t initPicture()
{
    picture_t pic;
    textbackground(CONSOLE_BACKGROUND);
    textcolor(TEXT_COLOR);
    clrscr();
    gotoxy(1,1);

    cputs("Podaj nazwe obrazka: ");

    do
    {
        gettxt(pic.name);
    }while(pic.name[0] == NULL);

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
            pic.pixels[i][j] = DEFAULT_MATRIX;
        }

    pic.status = DRAW;

    return pic;
}

void changeColor(cursor_t *pencil, int zn)
{
    for(int i=0; i < sizeof(pencil->colors)/sizeof(pencil->colors[0]); i++)
    {
        if(zn == pencil->colors[i])
        {
            textbackground(i);
            pencil->background = i;
            break;
        }
    }
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
	textcolor(LIGHTGRAY);

	// je�eli program jest kompilowany w czystym j�zyku C
	// prosz� odkomentowa� poni�sz� lini�
	// Conio2_Init();
	settitle("Mateusz Szymanowski 165319");

    do {
		textbackground(CONSOLE_BACKGROUND);
		clrscr();

		displayMenu(menu,zn, pic);

        switch(pic.status)
        {
        case DRAW:
            displayPicture(pic);
            break;
        case DRAW_LINE:

            break;
        case DRAW_RECTANGLE:

            break;
        }

		gotoxy(cursor.co.x, cursor.co.y);
		textcolor(BLACK);
		textbackground(cursor.background);
		putch(cursor.value);

		zn = getch();
		switch(zn)
		{
        case 0:
            menu.arrows = 1;
            zn = getch();
            if(zn == RIGHT) cursor.co.x = (cursor.co.x - START_P_X + 1) % pic.w + START_P_X;
            else if(zn == DOWN) cursor.co.y = (cursor.co.y - START_P_Y + 1) % pic.h + START_P_Y;
            if(zn == UP) if((cursor.co.y = (cursor.co.y - 1)) < START_P_Y) cursor.co.y = START_P_Y + pic.h - 1;
            if(zn == LEFT) if((cursor.co.x = (cursor.co.x  - 1)) < START_P_X) cursor.co.x = START_P_X + pic.w - 1;
            break;
        case 'n':
            pic = initPicture();
            cursor.co.x = START_P_X;
            cursor.co.y = START_P_Y;
            break;
        case ' ':
            if(pic.status == DRAW)
                draw(pic,cursor);
            break;
        default:
            changeColor(&cursor, zn);
		}

	} while (zn != ESC);

    textcolor(LIGHTGRAY);
    textbackground(BLACK);
	return 0;
	}
