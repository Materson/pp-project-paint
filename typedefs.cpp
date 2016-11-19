#include"conio2.h"

#define START_C_X 40
#define START_C_Y 12
#define START_M_X 1
#define START_M_Y 1

#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
#define ESC 0x1b
#define ENTER 0x0d

#define CONSOLE_BACKGROUND BLACK


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
    status_t status = DEFAULT;
}menu_t;

typedef struct
{
    coordinate_t co = {START_C_X, START_C_Y};
    char value = '*';
    int color = LIGHTGRAY;
    int background = BLACK;
    status_t status = DEFAULT;
}cursor_t;
