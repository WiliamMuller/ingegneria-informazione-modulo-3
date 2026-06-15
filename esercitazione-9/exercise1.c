/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es9 - Parte 1-2 - Filtro FIR in Virgola Fissa
 * Purpose:  Filter N samples of a sinusoidal signal using a fixed-point FIR
 *           filter with M coefficients in Q1.15 format and save the sampling
 *           time, the input sample and filtered output to a CSV file.
 */

#include "FIR_coeff.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int16_t FIR(int16_t X, int16_t *H, int n);
int16_t double_to_Q(double x, int n);
double Q_to_double(int16_t X, int n);

int main() {
    FILE *fp;
    double f0, A = 0.5;
    int Fs = 1000;
    const int n = 15;

    printf("Frequenza sinusoide = ");
    scanf("%lf", &f0);

    int16_t H[M];
    for (int i = 0; i < M; i++) {
        H[i] = double_to_Q(h[i], n);
    }

    if ((fp = fopen("FIR.csv", "w")) == NULL) {
        perror("Error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        double x = A * cos(2 * M_PI * f0 * i / Fs);
        int16_t X = double_to_Q(x, n);
        int16_t Y = FIR(X, H, n);
        double y = Q_to_double(Y, n);
        fprintf(fp, "%.15lf,%.15lf,%.15lf\n", (double) i / Fs, x, y);
    }

    fclose(fp);

    return 0;
}

int16_t FIR(int16_t X, int16_t *H, int n) {
    static int16_t dlX[M] = {0};

    int32_t Y = 0;
    dlX[0] = X;

    for (int i = 0; i < M; i++) {
        Y += (int32_t) dlX[i] * (int32_t) H[i];
    }

    // Shift the delay line to make room for the next sample
    for (int i = M - 1; i > 0; i--) {
        dlX[i] = dlX[i - 1];
    }

    return (int16_t) (Y >> n);
}

int16_t double_to_Q(double x, int n) {
    return (int16_t) (x * (1 << n)); // 1 << n = 2^n
}

double Q_to_double(int16_t X, int n) {
    return (double) X / (1 << n);
}
