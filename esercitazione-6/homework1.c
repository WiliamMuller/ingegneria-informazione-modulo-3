/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es6 - Homework 1 - Spettri di rumore bianco e rumore colorato
 * Purpose:  Generate Nx realizations of a white noise signal from a Gaussian
 *           R.V.: X ~ N(0,1), estimate the power spectrum as the
 *           sample mean of |Xi[k]|^2 over Nx realizations and save the
 *           index k and values S[k] to a CSV file.
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <stdlib.h>

#define M 256
#define Nx 10000

void dft(const double complex *x, double complex *X, int N);
double randn(double mu, double sigma);

int main() {
    double complex x[M], X[M];
    double S[M] = {0.0};

    srand((unsigned) time(NULL));

    for (int i = 0; i < Nx; i++) {
        for (int n = 0; n < M; n++) {
            // Sample from a Gaussian random variable N(0, 1)
            x[n] = randn(0.0, 1.0);
        }
        dft(x, X, M);
        for (int k = 0; k < M; k++) {
            S[k] += cabs(X[k]) * cabs(X[k]);
        }
    }

    for (int k = 0; k < M; k++) {
        S[k] = S[k] / Nx;
    }

    FILE *fp;
    if ((fp = fopen("gaussian_white_noise.csv", "w")) == NULL) {
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

double randn(double mu, double sigma) {
    double u1, u2, d, f;
    static double x1, x2;
    static int flag = 0;

    if (flag == 1) {
        flag = !flag;
        return (mu + sigma * (double) x2);
    }

    do {
        u1 = -1 + ((double) rand() / RAND_MAX) * 2;
        u2 = -1 + ((double) rand() / RAND_MAX) * 2;
        d = u1 * u1 + u2 * u2;
    } while (d >= 1 || d == 0);

    f = sqrt((-2 * log(d)) / d);
    x1 = u1 * f;
    x2 = u2 * f;
    flag = !flag;
    return (mu + sigma * (double) x1);
}