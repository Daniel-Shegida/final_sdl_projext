/*
 ============================================================================
 Name        : final project - not alpha /just testing.c
 Author      : daniel
 Version     : 0.000000
 Copyright   : Use at your own risk
 Description : testing to running windows
 ============================================================================
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#if defined(__MINGW32__)
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

// list for bushes
typedef struct list {
    int x  ;
    int y ;
    struct list *next;
} list;

int rubbish;
list *last = NULL;
list *head = NULL;
list *current = NULL;
// function for adding bush's coordinates
void projectenterprise (short x,short y) {

    list *futureLast = (list*)malloc(sizeof(list));
    futureLast->next = NULL;
    futureLast->x = x;
    futureLast->y = y;

    if  (last != NULL)
    {
        last->next = futureLast;
        futureLast->next = NULL;
    }
    else {
        // puts("   Initialization of list  ");
        head = futureLast;
    }

    last = futureLast;

}


SDL_Texture* sprite_sheet3;
// текущий кадр анимации
int anim_phase = 0;
// фаза анимации (бег, стояние на месте ...)
int anim_type = 0;
// количество кадров анимации для данного типа
int anim_phase_max[16] = { 13, 8, 10, 10, 10, 6, 4, 7, 13, 8, 10, 10, 10, 6, 4,
        7 };
// время с предыдущего кадра анимации
uint32_t last_frame;
// время в мс на 1 кадр
#define frame_time  50
// Размеры окна для вывода
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
// ABC FOR WORD VERSION 0.01 should be in function but later
const float ax = 60;
const int ay = 355;
const float bx = 112.5;
const int by = 355;
const float cx = 165;
const int cy = 355;
const float dx = 217.5;
const int dy = 355;
const float ex = 270;
const int ey = 355;
const float fx = 322.5;
const int fy = 355;
const float gx = 375;
const int gy = 355;
const float hx = 427.5;
const int hy = 355;
const float ix = 480;
const int iy = 355;
const float jx = 532.5;
const int jy = 355;

const float kx = 60;
const int ky = 427;
const float lx = 112.5;
const int ly = 427;
const float mx = 165;
const int my = 427;
const float nx = 217.5;
const int ny = 427;
const float ox = 270;
const int oy = 427;
const float qx = 322.5;
const int qy = 427;
const float px = 375;
const int py = 427;
const float rx = 427.5;
const int ry = 427;
const float sx = 480;
const int sy = 427;
const float tx = 533;
const int ty = 427;

const float ux = 60;
const int uy = 499;
const float vx = 112.5;
const int vy = 499;
const float wx = 165;
const int wy = 499;
const float xx = 217.5;
const int xy = 499;
const float yx = 270;
const int yy = 499;
const float zx = 322.5;
const int zy = 499;


// путь к файлу с картинкой, содержащей файлы движения
static const char sprite[] = "resources/adventurer.png";
// путь к файлу с картинкой, содержащей файлы движения
static const char sprite2[] = "resources/alphabet.jpg";
static const char sprite3[] = "resources/bushy.jpg";
// увеличение выводимых спрайтов (в данном примере исходно 32х32)
float LeftRight = 50;
float UpDown = 50;
short LeftOrRight = 1;
//
float LeftRight2 = 100;
float UpDown2 = 100;
// Функция для инициализации библиотеки и создания окна
int initSDL();
// функция для проведения завершения работы библиотеки и освобождения всех ресурсов
void closeSDL();
// загрузка изображения
SDL_Texture* loadImage(char imagePath[]);



// Указатель на структуру, описывающую окно для вывода графики
SDL_Window* window = NULL;
// Указательн на структуру, описывающую механизм отрисовки в окне с применением аппаратного ускорения
SDL_Renderer* renderer = NULL;
SDL_Renderer* renderer2 = NULL;
// указатель на поверхность (surface), на которой мы будем рисовать и выводить её в окне
SDL_Surface* screenSurface = NULL;

// Переенные для хранения анимации персонажа
SDL_Texture* sprite_sheet;
// Переенные для хранения анимации персонажа
SDL_Texture* sprite_sheet2;
// текущий кадр анимации

uint32_t last_frame;
// время в мс на 1 кадр
#define frame_time  50

int main (int argc, char *argv[]) {
    int buffer ;
    int buffer2;
    int phase = 1;
    FILE *inFile;
    inFile = fopen("perfomance.txt","r");
    int colour = 0;
    int resx = 640;
    int resy = 480;
    // Инициализируем библиотеку SDL
    if (initSDL(colour,resx,resy) > 1) {
        printf("Error in initialization.\n");
    } else {
        // scanning preference and get ready to change them
        fscanf(inFile,"%d %d %d", &colour,&resx,&resy);
        fclose(inFile);
      //  printf("%d %d %d", colour,resx,resy);
        FILE  *outFile;
        outFile = fopen("perfomance.txt","w");
        // Загружаем картирнку из файла
        //abc image
        sprite_sheet2 = loadImage(sprite2);
        SDL_Rect obj_size2, screen_size2;
        int quit = 0;
        // Структура для хранения информации о событии
        SDL_Event event;
        // Основной цикл программы, выход из которого происходит при
        // появлении события выхода (от ОС или по нажатию ESC)
        while (quit == 0) {
            // Ждём появления события
            while (SDL_PollEvent(&event) != 0) {
                // При его появлении проверяем тип
                if (event.type == SDL_QUIT)
                    // Если событие выхода (сигнал от ОС, что приложение
                    // нужно завершить), меняем флаг выхода
                    quit = 1;
                else if (event.type == SDL_KEYDOWN) {
                    // Если это нажатие на клавишу клавиатуры, смотрим код
                    // нажатой клавиши
                    switch (event.key.keysym.sym) {
                    case SDLK_y:
                        // phase 1 - changing preferance or not
                        // phase 2  to is choosing what change
                        //phase 3 and 4 is changing res or background color
                        if ((phase ==1))
                        {
                       //     printf (    "    phase  1   -  yes  %d %d %d ",colour,resx,resy);
                            phase = 2;
                        }
                        break;
                    case SDLK_q:
                        if ((phase ==3))
                        {
                         //   printf (    "    phase  3   -  left  %d %d %d ",colour,resx,resy);
                            resx= 800;
                            resy = 640;
                            phase = 1;
                        }
                        break;
                    case SDLK_g:
                        if ((phase ==3))
                        {
                          //  printf (    "    phase  3   -  right  %d %d %d ",colour,resx,resy);
                            resx= 640;
                            resy = 480;
                            phase  =1;
                        }
                        break;
                    case SDLK_w:
                        if (phase ==4)
                        {
                         //   printf (    "    phase  4   -  left  %d %d %d ",colour,resx,resy);
                            colour = 255;
                          //  printf("hooray %d",colour);
                            phase = 1;
                        }
                        break;
                    case SDLK_b:
                        if (phase == 4)
                        {
                           // printf (    "    phase  4   -  right  %d %d %d ",colour,resx,resy);
                            colour = 0;
                           // printf("hooray %d",colour);
                            phase = 1;
                        }
                        break;
                    case SDLK_n:
                        if ((phase ==1))
                        {
                           // printf (    "    phase  1   -  no  %d %d %d ",colour,resx,resy);
                            fprintf (outFile,"%d %d %d ",colour,resx,resy);
                            quit = 1;
                        }
                        break;
                    case SDLK_r:
                        if ((phase ==2))
                        {
                          //  printf (    "    phase  2   -  res  %d %d %d ",colour,resx,resy);
                            phase = 3;
                        }
                        break;

                    case SDLK_c:
                        if (phase ==2)
                        {
                            printf (    "    phase  2   -  colour  %d %d %d ",colour,resx,resy);
                            phase = 4;
                        }

                        break;
                    case SDLK_ESCAPE:
                        // Нажата клавиша ESC, меняем флаг выхода
                        quit = 1;
                        break;
                    }
                }
            }
            // часть картинки с нужным кадром анимации
            obj_size2.x = 60 ;
            obj_size2.y = 355 ;
            obj_size2.h = 48;
            obj_size2.w = 40;
            // место для вывода кадра анимации и его увеличение
            screen_size2.h = 30 ;
            screen_size2.w = 30 ;

            SDL_RenderClear(renderer);


            if (phase == 1){
                //do
                screen_size2.x  = 50;
                screen_size2.y = 20;
                obj_size2.x = dx;
                obj_size2.y = dy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 80;
                screen_size2.y = 20;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                //u want
                screen_size2.x  = 140;
                screen_size2.y = 20;
                obj_size2.x = yx;
                obj_size2.y = yy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 170;
                screen_size2.y = 20;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 200;
                screen_size2.y = 20;
                obj_size2.x = ux;
                obj_size2.y = uy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 260;
                screen_size2.y = 20;
                obj_size2.x = wx;
                obj_size2.y = wy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 290;
                screen_size2.y = 20;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 320;
                screen_size2.y = 20;
                obj_size2.x = nx;
                obj_size2.y = xy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 350;
                screen_size2.y = 20;
                obj_size2.x = tx;
                obj_size2.y = ty;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                // to
                screen_size2.x  = 410;
                screen_size2.y = 20;
                obj_size2.x = tx;
                obj_size2.y = ty;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 440;
                screen_size2.y = 20;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                //change
                screen_size2.x  = 200;
                screen_size2.y = 80;
                obj_size2.x = cx;
                obj_size2.y = cy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 230;
                screen_size2.y = 80;
                obj_size2.x = hx;
                obj_size2.y = hy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 260;
                screen_size2.y = 80;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 290;
                screen_size2.y = 80;
                obj_size2.x = nx;
                obj_size2.y = ny;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 320;
                screen_size2.y = 80;
                obj_size2.x = gx;
                obj_size2.y = gy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 350;
                screen_size2.y = 80;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                // yes
                screen_size2.x  = 140;
                screen_size2.y = 400;
                obj_size2.x = yx;
                obj_size2.y = yy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 170;
                screen_size2.y = 400;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 200;
                screen_size2.y = 400;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                //no
                screen_size2.x  = 400;
                screen_size2.y = 400;
                obj_size2.x = nx;
                obj_size2.y = ny;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 430;
                screen_size2.y = 400;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                //press
                screen_size2.x  = 230;
                screen_size2.y = 200;
                obj_size2.x = px;
                obj_size2.y = py;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 260;
                screen_size2.y = 200;
                obj_size2.x = rx;
                obj_size2.y = ry;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 290;
                screen_size2.y = 200;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 310;
                screen_size2.y = 200;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 340;
                screen_size2.y = 200;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 170;
                screen_size2.y = 350;
                obj_size2.x = yx;
                obj_size2.y = yy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 415;
                screen_size2.y = 350;
                obj_size2.x = nx;
                obj_size2.y = ny;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
            }


            if (phase == 2){
                // what
                screen_size2.x  = 50;
                screen_size2.y = 20;
                obj_size2.x = wx;
                obj_size2.y = wy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 80;
                screen_size2.y = 20;
                obj_size2.x = hx;
                obj_size2.y = hy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 110;
                screen_size2.y = 20;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 140;
                screen_size2.y = 20;
                obj_size2.x = tx;
                obj_size2.y = ty;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                //do

                screen_size2.x  = 200;
                screen_size2.y = 20;
                obj_size2.x = dx;
                obj_size2.y = dy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 230;
                screen_size2.y = 20;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                //want

                screen_size2.x  = 290;
                screen_size2.y = 20;
                obj_size2.x = wx;
                obj_size2.y = wy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 320;
                screen_size2.y = 20;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 350;
                screen_size2.y = 20;
                obj_size2.x = nx;
                obj_size2.y = ny;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 380;
                screen_size2.y = 20;
                obj_size2.x = tx;
                obj_size2.y = ty;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                //to

                screen_size2.x  = 440;
                screen_size2.y = 20;
                obj_size2.x = tx;
                obj_size2.y = ty;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 470;
                screen_size2.y = 20;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                //change

                screen_size2.x  = 200;
                screen_size2.y = 80;
                obj_size2.x = cx;
                obj_size2.y = cy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 230;
                screen_size2.y = 80;
                obj_size2.x = hx;
                obj_size2.y = hy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 260;
                screen_size2.y = 80;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 290;
                screen_size2.y = 80;
                obj_size2.x = nx;
                obj_size2.y = ny;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 320;
                screen_size2.y = 80;
                obj_size2.x = gx;
                obj_size2.y = gy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 350;
                screen_size2.y = 80;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                //res
                screen_size2.x  = 40;
                screen_size2.y = 400;
                obj_size2.x = rx;
                obj_size2.y = ry;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 70;
                screen_size2.y = 400;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 100;
                screen_size2.y = 400;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                // colour

                screen_size2.x  = 360;
                screen_size2.y = 400;
                obj_size2.x = cx;
                obj_size2.y = cy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 390;
                screen_size2.y = 400;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 420;
                screen_size2.y = 400;
                obj_size2.x = lx;
                obj_size2.y = ly;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 450;
                screen_size2.y = 400;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 480;
                screen_size2.y = 400;
                obj_size2.x = ux;
                obj_size2.y = uy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 510;
                screen_size2.y = 400;
                obj_size2.x = rx;
                obj_size2.y = ry;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                //press
                screen_size2.x  = 230;
                screen_size2.y = 200;
                obj_size2.x = px;
                obj_size2.y = py;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 260;
                screen_size2.y = 200;
                obj_size2.x = rx;
                obj_size2.y = ry;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 290;
                screen_size2.y = 200;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 310;
                screen_size2.y = 200;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 340;
                screen_size2.y = 200;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 70;
                screen_size2.y = 350;
                obj_size2.x = rx;
                obj_size2.y = ry;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 430;
                screen_size2.y = 350;
                obj_size2.x = cx;
                obj_size2.y = cy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);


            }

            if  (phase == 3){
                screen_size2.x  = 50;
                screen_size2.y = 20;
                obj_size2.x = wx;
                obj_size2.y = wy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 80;
                screen_size2.y = 20;
                obj_size2.x = hx;
                obj_size2.y = hy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 110;
                screen_size2.y = 20;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 140;
                screen_size2.y = 20;
                obj_size2.x = tx;
                obj_size2.y = ty;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 200;
                screen_size2.y = 20;
                obj_size2.x = rx;
                obj_size2.y = ry;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 230;
                screen_size2.y = 20;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 260;
                screen_size2.y = 20;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 320;
                screen_size2.y = 20;
                obj_size2.x = tx;
                obj_size2.y = ty;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 350;
                screen_size2.y = 20;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 410;
                screen_size2.y = 20;
                obj_size2.x = mx;
                obj_size2.y = my;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 440;
                screen_size2.y = 20;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 470;
                screen_size2.y = 20;
                obj_size2.x = kx;
                obj_size2.y = ky;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 500;
                screen_size2.y = 20;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);



                screen_size2.x  = 40;
                screen_size2.y = 400;
                obj_size2.x = bx;
                obj_size2.y = by;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 70;
                screen_size2.y = 400;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 100;
                screen_size2.y = 400;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 130;
                screen_size2.y = 400;
                obj_size2.x = xx;
                obj_size2.y = xy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 160;
                screen_size2.y = 400;
                obj_size2.x = gx;
                obj_size2.y = gy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 190;
                screen_size2.y = 400;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 220;
                screen_size2.y = 400;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 390;
                screen_size2.y = 400;
                obj_size2.x = gx;
                obj_size2.y = gy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);


                screen_size2.x  = 420;
                screen_size2.y = 400;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 450;
                screen_size2.y = 400;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 480;
                screen_size2.y = 400;
                obj_size2.x = xx;
                obj_size2.y = xy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 510;
                screen_size2.y = 400;
                obj_size2.x = yx;
                obj_size2.y = yy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 540;
                screen_size2.y = 400;
                obj_size2.x = bx;
                obj_size2.y = by;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 570;
                screen_size2.y = 400;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                //press
                screen_size2.x  = 230;
                screen_size2.y = 200;
                obj_size2.x = px;
                obj_size2.y = py;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 260;
                screen_size2.y = 200;
                obj_size2.x = rx;
                obj_size2.y = ry;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 290;
                screen_size2.y = 200;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 310;
                screen_size2.y = 200;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 340;
                screen_size2.y = 200;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 130;
                screen_size2.y = 350;
                obj_size2.x = qx;
                obj_size2.y = qy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 480;
                screen_size2.y = 350;
                obj_size2.x = gx;
                obj_size2.y = gy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);


            }

            if (phase == 4){
                screen_size2.x  = 50;
                screen_size2.y = 20;
                obj_size2.x = wx;
                obj_size2.y = wy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 80;
                screen_size2.y = 20;
                obj_size2.x = hx;
                obj_size2.y = hy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 110;
                screen_size2.y = 20;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 140;
                screen_size2.y = 20;
                obj_size2.x = tx;
                obj_size2.y = ty;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 200;
                screen_size2.y = 20;
                obj_size2.x = bx;
                obj_size2.y = by;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 230;
                screen_size2.y = 20;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 260;
                screen_size2.y = 20;
                obj_size2.x = kx;
                obj_size2.y = ky;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 320;
                screen_size2.y = 20;
                obj_size2.x = tx;
                obj_size2.y = ty;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 350;
                screen_size2.y = 20;
                obj_size2.x = ox;
                obj_size2.y = oy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 410;
                screen_size2.y = 20;
                obj_size2.x = mx;
                obj_size2.y = my;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 440;
                screen_size2.y = 20;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 470;
                screen_size2.y = 20;
                obj_size2.x = kx;
                obj_size2.y = ky;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 500;
                screen_size2.y = 20;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);



                screen_size2.x  = 40;
                screen_size2.y = 400;
                obj_size2.x = bx;
                obj_size2.y = by;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 70;
                screen_size2.y = 400;
                obj_size2.x = lx;
                obj_size2.y = ly;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 100;
                screen_size2.y = 400;
                obj_size2.x = ax;
                obj_size2.y = ay;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 130;
                screen_size2.y = 400;
                obj_size2.x = cx;
                obj_size2.y = cy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 160;
                screen_size2.y = 400;
                obj_size2.x = kx;
                obj_size2.y = ky;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);



                screen_size2.x  = 390;
                screen_size2.y = 400;
                obj_size2.x = wx;
                obj_size2.y = wy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);


                screen_size2.x  = 420;
                screen_size2.y = 400;
                obj_size2.x = hx;
                obj_size2.y = hy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 450;
                screen_size2.y = 400;
                obj_size2.x = ix;
                obj_size2.y = iy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 480;
                screen_size2.y = 400;
                obj_size2.x = tx;
                obj_size2.y = ty;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 510;
                screen_size2.y = 400;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
                //press
                screen_size2.x  = 230;
                screen_size2.y = 200;
                obj_size2.x = px;
                obj_size2.y = py;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 260;
                screen_size2.y = 200;
                obj_size2.x = rx;
                obj_size2.y = ry;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 290;
                screen_size2.y = 200;
                obj_size2.x = ex;
                obj_size2.y = ey;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 310;
                screen_size2.y = 200;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 340;
                screen_size2.y = 200;
                obj_size2.x = sx;
                obj_size2.y = sy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 100;
                screen_size2.y = 350;
                obj_size2.x = bx;
                obj_size2.y = by;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);

                screen_size2.x  = 465;
                screen_size2.y = 350;
                obj_size2.x = wx;
                obj_size2.y = wy;
                SDL_RenderCopy(renderer, sprite_sheet2, &obj_size2, &screen_size2);
            }
            SDL_RenderPresent(renderer);
        }
        fclose (outFile);
    }
    closeSDL();
    // Инициализируем библиотеку SDL
    if (initSDL(colour,resx,resy) > 1) {
        printf("Error in initialization.\n");
    } else {
        // Загружаем картирнку из файла
        sprite_sheet = loadImage(sprite);
        sprite_sheet3 = loadImage(sprite3);

        SDL_Rect obj_size, screen_size;
        SDL_Rect obj_size3, screen_size3;
        last_frame=SDL_GetTicks();

        int quit = 0;
        // Структура для хранения информации о событии
        SDL_Event event;
        // Основной цикл программы, выход из которого происходит при
        // появлении события выхода (от ОС или по нажатию ESC)
        while (quit == 0) {
            // Ждём появления события
            while (SDL_PollEvent(&event) != 0) {
                // При его появлении проверяем тип
                if (event.type == SDL_QUIT)
                    // Если событие выхода (сигнал от ОС, что приложение
                    // нужно завершить), меняем флаг выхода
                    quit = 1;
                else if (event.type == SDL_KEYDOWN) {
                    // Если это нажатие на клавишу клавиатуры, смотрим код
                    // нажатой клавиши
                    switch (event.key.keysym.sym) {
                    case SDLK_a:
                        anim_phase=0;
                        if (LeftOrRight == 1)  anim_type = 2;
                        else anim_type = 10;
                        break;
                    case SDLK_s:
                        if (anim_type != 15) {anim_type++; anim_phase=0;}
                        break;
                    case SDLK_d:
                        if (anim_type != 0) {anim_type--; anim_phase=0;}
                        break;
                    case SDLK_UP:
                        if (UpDown != 1)
                        {
                            UpDown --;
                            LeftRight = LeftRight + 0.5;
                            if (LeftOrRight == 1)  anim_type = 5;
                            else anim_type = 13;
                        }
                        break;
                    case SDLK_DOWN:
                        if (UpDown != 200)
                        {
                            UpDown ++;
                            LeftRight = LeftRight - 0.5;
                            if (LeftOrRight == 1)  anim_type = 6;
                            else anim_type = 14;
                        }
                        break;
                    case SDLK_LEFT:
                        if (LeftRight != 1) {LeftRight --;anim_type =9;LeftOrRight = 0;}
                        break;
                    case SDLK_RIGHT:
                        if (LeftRight != 400) {LeftRight++;anim_type =1;LeftOrRight = 1;}
                        break;
                    case SDLK_f:
                        buffer =  rand() % 555;
                        buffer2 =  rand() % 399;
                        projectenterprise(buffer,buffer2);
                        break;
                    case SDLK_ESCAPE:
                        // Нажата клавиша ESC, меняем флаг выхода
                        quit = 1;
                        break;
                    }
                }
            }
            // отрисовка картинки с новым кадром анимации
            // проверка прошедшего времени:
            if ((SDL_GetTicks()- last_frame) >= frame_time) {
                anim_phase++;
                if (anim_phase >= anim_phase_max[anim_type]) anim_phase = 0;
                last_frame = SDL_GetTicks();
            }

            // часть картинки с нужным кадром анимации
            obj_size.x = 32 * anim_phase;
            obj_size.y = 32 * anim_type;
            obj_size.h = 32;
            obj_size.w = 32;
            // место для вывода кадра анимации и его увеличение
            screen_size.x = 32 + LeftRight;
            screen_size.y = 32 + UpDown;
            screen_size.h = 32 + UpDown;
            screen_size.w = 32 + UpDown;
            // часть картинки с нужным кадром анимации
            obj_size3.x = 0;
            obj_size3.y = 0;
            obj_size3.h = 55;
            obj_size3.w = 55;
            // место для вывода кадра анимации и его увеличение

            screen_size3.h = 60 ;
            screen_size3.w = 60 ;

            current = head;
            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, sprite_sheet, &obj_size, &screen_size);
            // Выводим буфер на экран
            while (current != NULL){
                screen_size3.x =current->x;
                screen_size3.y =current->y;
                SDL_RenderCopy(renderer, sprite_sheet3, &obj_size3, &screen_size3);
                // Выводим буфер на экран
                current = current->next;
            }
            SDL_RenderPresent(renderer);
        }

    }
    closeSDL();
    return 0;
}

int initSDL(int colour,int resx,int resy) {
    int success = 1;
    // Инициализируем библиотеку SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // при появлении ошибки выводим её описание
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = 0;
    } else {
        // После успешной инициализации создаём окно для вывода графики
        window = SDL_CreateWindow("SDL example", SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, resx, resy, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            // выводим ошибку, если создать окно не удалось
            printf("Window could not be created! SDL_Error: %s\n",
                    SDL_GetError());
            success = 0;
        } else {
            // Инициализируем библиотеку загрузки изображений (только для JPG)
            int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n",
                        IMG_GetError());
                success = 0;
            }
            // Получаем поверхность для рисования
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                // выводим ошибку, если создать окно не удалось
                printf("Renderer could not be created! SDL_Error: %s\n",
                        SDL_GetError());
                success = 0;
            } else {
                // Задаём цвет отрисовки
                SDL_SetRenderDrawColor(renderer, colour, colour, colour, colour);
            }
        }
    }
    return success;
}

void closeSDL() {
    // Закрываем окно и освобождаем все выделенные ему ресурсы
    SDL_DestroyWindow(window);
    // Завершаем работу библиотеки и освобождаем все выделенные ей ресурсы
    SDL_Quit();
}

SDL_Texture* loadImage(char imagePath[]) {
    printf("%s\n", imagePath);
    SDL_Texture *newTexture;
    // Загружаем изображение
    SDL_Surface* loadedSurface = IMG_Load(imagePath);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", imagePath,
                IMG_GetError());
    } else {
        // Если успешно загрузили, преобразуем загруженную поверхность в формат экранной
        // Если этого не сделать, то при каждом выводе будет проводится преобразование
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to load texture %s! SDL Error: %s\n", imagePath,
                    SDL_GetError());
        } else
            // если успешно, возвращаем указатель на поверхность с изображенеим
            return newTexture;
        // Удаляем загруженную поверхность
        SDL_FreeSurface(loadedSurface);
    }
    return NULL;
}



