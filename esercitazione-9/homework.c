/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es9 - Homework - Filtro FIR in Virgola Fissa
 * Purpose:  Generate N=1024 samples of a two-tone sinusoidal signal
 *           (f1=50 Hz, f2=250 Hz), filter it with a fixed-point FIR in
 *           Q1.15 format, compute the FFT of both input and output and
 *           save the bin index and moduli |X[k]|, |Y[k]| to a CSV file.
 */

#include "FIR_coeff.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define N 1024

int16_t FIR(int16_t X, int16_t *H, int n);
int16_t double_to_Q(double x, int n);
double Q_to_double(int16_t X, int n);

void fft(const double complex *x, double complex *X, int L);
void butterfly(const double complex *a, double complex *b, double complex W);
void bit_reversal(const double complex *out, double complex *X, int L);

int main() {
    FILE *fp;
    double f1 = 50.0, f2 = 250.0, A = 0.25;
    double complex x[N], y[N];
    double complex Xfft[N], Yfft[N];
    int16_t Xq[N], Yq[N];
    int Fs = 1000;
    const int n = 15;

    int16_t H[M];
    for (int i = 0; i < M; i++) {
        H[i] = double_to_Q(h[i], n);
    }

    // Get the signals inside arrays
    for (int i = 0; i < N; i++) {
        x[i] =
            A * cos(2 * M_PI * f1 * i / Fs) + A * cos(2 * M_PI * f2 * i / Fs);
        Xq[i] = double_to_Q(x[i], n);
        Yq[i] = FIR(Xq[i], H, n);
        y[i] = Q_to_double(Yq[i], n);
    }

    fft(x, Xfft, N);
    fft(y, Yfft, N);

    if ((fp = fopen("FFT_FIR.csv", "w")) == NULL) {
        perror("Error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

    for (int k = 0; k < N; k++) {
        fprintf(fp, "%d,%.15lf,%.15lf\n", k, cabs(Xfft[k]), cabs(Yfft[k]));
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

void fft(const double complex *x, double complex *X, int L) {
    double complex in[L], out[L]; // VLA
    // Temporary buffers for the butterfly inputs and outputs
    double complex a[2], b[2];
    double complex W;

    for (int n = 0; n < L; n++)
        in[n] = x[n];

    // Cycle through the stages
    for (int m = L; m >= 2; m /= 2) {
        // Cycle through the k group of the m stage
        for (int k = 0; k < L / m; k++) {
            // Cycle through the butterflies of the k group at the stage m
            for (int j = 0; j < m / 2; j++) {
                a[0] = in[m * k + j];
                a[1] = in[m * k + j + m / 2];
                W = cexp(-I * 2 * M_PI * j / m);
                butterfly(a, b, W);
                out[m * k + j] = b[0];
                out[m * k + j + m / 2] = b[1];
            }
        }
        if (m != 2)
            for (int n = 0; n < L; n++)
                in[n] = out[n];
    }
    bit_reversal(out, X, L);
}

void butterfly(const double complex *a, double complex *b, double complex W) {
    b[0] = a[0] + a[1];
    b[1] = (a[0] - a[1]) * W;
}

void bit_reversal(const double complex *out, double complex *X, int L) {
    // nbits = log2(L)
    int nbits = 0, N1 = L;
    while (N1 >>= 1)
        nbits++;

    for (int i = 0; i < L; i++) {
        int v = i;
        int r = 0;

        // r is the representation of v but with the bits inverted
        for (int j = 0; j < nbits; j++) {
            int bit = v % 2;
            r = r * 2 + bit;
            v = v / 2;
        }
        X[r] = out[i];
    }
}
