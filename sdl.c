#include <SDL/SDL.h>

#include "ini_flood.h"

void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x=px;
    rect.y=py;
    rect.h=rect.w=size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));/*rect:要填充的表面 rect:制定填充窗口的哪个部分 第三部分：制定比表面的像素格式*/
    SDL_Flip(ecran);//更新窗口
}

void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));/*NULL:填充整个表面*/
    SDL_Flip(ecran);//更新窗口
}

void affiche_jeu(SDL_Surface *ecran, int **a, int s){

    /*显示上面的图案框*/
    int x =0;
    int y = 0;
    int i, j;
    int step = 400 / s;
    for(i = 0; i < s; i++){
        x = 0;
        for(j = 0; j < s; j++){
            switch (a[i][j]){
                case 0:
                    drawRectangle(ecran, x, y, step, 255, 0, 0);
                    break;
                case 1:
                    drawRectangle(ecran, x, y, step, 0, 255, 0);
                    break;
                case 2:
                    drawRectangle(ecran, x, y, step, 0, 0, 255);
                    break;
                case 3:
                    drawRectangle(ecran, x, y, step, 255, 255, 0);
                    break;
                case 4: drawRectangle(ecran, x, y, step, 255, 0, 255);
                    break;
            }
            x += step;
        }
    y += step;
    }
}

int return_number_of_color(int x, int y, int**a, int size) {
        int t1 = x/(400/size);
        int t2 = y/(400/size);
        printf("(%d, %d)->%d\n", t1, t2, a[t1][t2]);
        return a[t1][t2];
    }


int main(int argc, char *argv[]){
    int size;

    int i, j;
    int continuer = 1;
    int getinput = 1;
    SDL_Surface *ecran = NULL;
    SDL_Event event;
    const SDL_VideoInfo* info = NULL;
    SDL_Surface *ima=NULL;

    // initialisation de la fenêtre d'affichage
    if( SDL_Init( SDL_INIT_VIDEO )/*启动声音和视频系统*/ < 0 ) {
        /* Failed, exit. */
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        SDL_Quit( );
    }
    info = SDL_GetVideoInfo( );/*返回当前SDL运行窗口的视频属性信息*/
    if( !info ) {
        /* This should probably never happen. */
        fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
        SDL_Quit( );
    }

    ecran=SDL_SetVideoMode(400, 400, 32, SDL_HWSURFACE);/*???*/
    SDL_WM_SetCaption("Color Flood", NULL);/*设置窗口的标题和ICON图标*/

    fillScreen(ecran, 255, 255, 255);

    while (getinput == 1) {

        SDL_WaitEvent(&event);

        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_a:
                        size = 4;
                        getinput = 0;
                        break;
                    case SDLK_z:
                        size = 5;
                        getinput = 0;
                        break;
                    case SDLK_e:
                        size = 8;
                        getinput = 0;
                        break;
                    case SDLK_ESCAPE:
                        SDL_Quit();
                }
        }
    }

    // SDL_FreeSurface(tips);

    int **a = malloc(size*sizeof(int *));
    for(i = 0; i < size; i++){
        a[i] = malloc(size*sizeof(int));
    }
    ini_flood(a, size);

    affiche_jeu(ecran, a, size);

    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    int x, y;
                    x = event.button.y;
                    y = event.button.x;

                    int color = return_number_of_color(x, y, a, size);

                    propage(a, color, size);
                    affiche_jeu(ecran, a, size);
                    fprintf(stderr,"a\n");
                }
                break;
        }
        if(une_couleur(a, size) == 1)
            continuer = 0;
    }

    SDL_Quit();
    for(i = 0; i < size; i++){
      free(a[i]);
    }
    return 0;
}