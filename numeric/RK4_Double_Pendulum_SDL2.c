#include <stdio.h>
#include <math.h>
#include <SDL.h>

void F(float, float*, float*);
void RK4_next(int, float, float, float*, float*);
void RK4_output(int, float, float[]);
void add(int, float[], float[]);
void mul(int len, float[], float);
void copy(int, float[], float[]);
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

const float g = 10;
const float m_1 = 1, m_2 = 1;
const float L_1 = 80, L_2 = 80;

const int width = 400, height = 400;

int main(int argc, char *argv[])
{
    float h = 0.01;                         // Time Step
    float DP_0[4] = {2, 2, 0, 0};           // Initial Condition
    int x1, x2, y1, y2;
    int xo = width/2, yo = height/2;
    float DP[4];
    RK4_next(4, h, 1, DP_0, DP);

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    int posX = 100, posY = 100;
    SDL_bool loopShouldStop = SDL_FALSE;

    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("Double Pendulum", posX, posY, width, height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);

    while (!loopShouldStop)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    loopShouldStop = SDL_TRUE;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillCircle(renderer, xo, yo, 2);
        SDL_RenderDrawLine(renderer, xo, yo, x1, y1);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

        x1 = (int)(L_1*sin(DP[0])+xo);
        y1 = (int)(L_1*cos(DP[0])+yo);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillCircle(renderer, x1, y1, 10);

        x2 = (int)(x1+L_2*sin(DP[1]));
        y2 = (int)(y1+L_2*cos(DP[1]));
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillCircle(renderer, x2, y2, 10);

        SDL_RenderPresent(renderer);

        RK4_next(4, 0.01, 1, DP, DP);
        SDL_Delay(1);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

void F(float t, float Y[], float dYdt[]) {
    /**
    Y[0] = theta_1(t)
    Y[1] = theta_2(t)
    Y[2] = dY[0] = d/dt(theta_1(t)) = omega_1(t)
    Y[3] = dY[1] = d/dt(theta_2(t)) = omega_2(t)
    **/
    dYdt[0] = Y[2];
    dYdt[1] = Y[3];
    dYdt[2] = (-1*g*(2*m_1+m_2)*sin(Y[0])-m_2*g*sin(Y[0]-2*Y[1])
             -2*sin(Y[0]-Y[1])*m_2*(pow(Y[3],2)*L_2+pow(Y[2],2)*L_1*cos(Y[0]-Y[1])))/
            (L_1*(2*m_1+m_2-m_2*cos(2*Y[0]-2*Y[1])));
    dYdt[3] = ((2*sin(Y[0]-Y[1]))*((pow(Y[2],2)*L_1*(m_1+m_2))+
             g*(m_1+m_2)*cos(Y[0])+pow(Y[3],2)*L_2*m_2*cos(Y[0]-Y[1])))/
            (L_2*(2*m_1+m_2-m_2*cos(2*Y[0]-2*Y[1])));
}

void RK4_next(int len, float h, float t, float Y[], float Y_next[]) {
    float K1[len], K2[len], K3[len], K4[len], TEMP[len];

    /** K1 = F(t, Y) **/
    F(t, Y, K1);

    /** K2 = F(t+h/2, Y+h/2*K1) **/
    copy(len, TEMP, K1);
    mul(len, TEMP, h/2);
    add(len, TEMP, Y);
    F(t+h/2, TEMP, K2);

    /** K3 = F(t+h/2, Y+h/2*K2) **/
    copy(len, TEMP, K2);
    mul(len, TEMP, h/2);
    add(len, TEMP, Y);
    F(t+h/2, TEMP, K3);

    /** K4 = F(t+h, Y+h*K3) **/
    copy(len, TEMP, K3);
    mul(len, TEMP, h);
    add(len, TEMP, Y);
    F(t+h, TEMP, K4);

    /** Y_next = Y+h/6*(K1+2*K2+2*K3+K4) **/
    copy(len, TEMP, K2);
    add(len, TEMP, K3);
    mul(len, TEMP, 2);
    add(len, TEMP, K1);
    add(len, TEMP, K4);
    mul(len, TEMP, h/6);
    add(len, TEMP, Y);
    copy(len, Y_next, TEMP);

}


/******* A <- A+B *******/
void add(int len, float A[], float B[]) {
    for (int i=0; i<len; i++) {
        A[i] = A[i] + B[i];
    }
}

/******* A <- k*A *******/
void mul(int len, float A[], float k) {
    for (int i=0; i<len; i++) {
        A[i] = A[i] * k;
    }
}

/******* COPY <- ORIGINAL *******/
void copy(int len, float COPY[], float ORIGINAL[]) {
    for (int i=0; i<len; i++) {
        COPY[i] = ORIGINAL[i];
    }
}

/******* Midpoint Circle Algorithm for SDL2 *******/
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}
