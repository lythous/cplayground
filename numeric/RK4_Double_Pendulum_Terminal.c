#include <stdio.h>
#include <math.h>

void F(float, float*, float*);
void RK4(int, float, float, float[]);
void RK4_next(int, float, float, float*, float*);
void print_out(int, float, float[]);
void add(int, float[], float[]);
void mul(int len, float[], float);
void copy(int, float[], float[]);

int main(void) {
    printf("sss\n");
    float Y_0[1] = {0};
    RK4(1, 0.0, 1.0, Y_0);
    return 0;
}

void RK4(int len, float t_init, float t_fin, float Y_init[]) {
    float h = 0.01;
    float t = t_init;
    float Y[len];
    float Y_next[len];
    int i;

    copy(len, Y, Y_init);
    while (t<=t_fin) {
        RK4_next(len, h, t, Y, Y_next);
        print_out(len, t, Y_next);
        copy(len, Y_next, Y);
        t += h;
    }
}

void print_out(int len, float t, float Y[]) {
    printf("\n%f", t);
    for (int i=0; i<len; i++) {
        printf(",\t%f", Y[i]);
    }
}

void F(float t, float Y[], float dY[]) {
    dY[0] = pow(t, 3)*exp(-2*t) - 2*Y[0];
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
