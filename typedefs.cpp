#include"conio2.h"

#define START_P_X 1
#define START_P_Y 8
#define START_M_X 1
#define START_M_Y 1

#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
#define ESC 0x1b
#define ENTER 0x0d

#define CONSOLE_BACKGROUND DARKGRAY
#define TEXT_COLOR BLACK



typedef enum
{
    DEFAULT,
    DRAW,
    DRAW_LINE,
    DRAW_RECTANGLE,
    OPEN_FILE,
    SELECT_AREA,
    COPY,
    FILL
}status_t;

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

typedef struct
{
    coordinate_t co = {START_P_X, START_P_Y};
    char value = '*';
    int background = BLACK;
    int colors[16] = {'0','1','2','3','4','5','6','7','8','9','q','w','e','r','t','y'};
}cursor_t;

typedef struct
{
    char name[];
    int w=1,h=1;
    char **pixels;
    status_t status = DEFAULT;
}picture_t;
