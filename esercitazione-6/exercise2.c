/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es6 - Parte 1 - Spettri di rumore bianco e rumore colorato
 * Purpose:  Generate Nx realizations of a red noise signal by filtering white
 *           noise through an IIR integrator approximation, estimate the power
 *           spectrum as the sample mean of |Yi[k]|^2 over Nx realizations and
 *           save the index k and values S[k] to a CSV file.
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <stdlib.h>

#define M 256
#define Nx 10000
#define b 0.99

void dft(const double complex *x, double complex *X, int N);
double randu();

int main() {
    double complex x[M];
    double complex y[M];
    double complex Y[M];
    double S[M] = {0.0};

    srand((unsigned) time(NULL));

    for (int i = 0; i < Nx; i++) {
        for (int n = 0; n < M; n++) {
            // Map the values from [0,1] to [-1,1]
            x[n] = -1.0 + 2.0 * randu();
        }

        // IIR filtering to approximate the behaviour of an integrator
        y[0] = x[0];
        for (int n = 1; n < M; n++) {
            y[n] = x[n] + b * y[n - 1];
        }

        dft(y, Y, M);
        for (int k = 0; k < M; k++) {
            S[k] += cabs(Y[k]) * cabs(Y[k]);
        }
    }

    for (int k = 0; k < M; k++) {
        S[k] = S[k] / Nx;
    }

    FILE *fp;
    if ((fp = fopen("red_noise.csv", "w")) == NULL) {
        perror("Error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

    for (int k = 0; k < M; k++) {
        fprintf(fp, "%d,%.15lf\n", k, S[k]);
    }

    fclose(fp);
    return 0;
}

void dft(const double complex *x, double complex *X, int N) {
    for (int k = 0; k < N; k++) {
        double complex s = 0.0 + 0.0 * I;
        for (int n = 0; n < N; n++) {
            double theta = -2.0 * M_PI * k * n / (double) N;
            s += x[n] * cexp(I * theta);
        }
        X[k] = s;
    }
}

double randu() {
    return ((double) rand() + 1.0) / ((double) RAND_MAX + 2.0);
}