/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es7 - Parte 1-2-3 - Fast Fourier Transform (FFT)
 * Purpose:  Implement the radix-2 DIF FFT algorithm using a butterfly
 *           function and bit reversal to correctly order the output,
 *           as a drop-in replacement for the DFT function.
 */

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void fft(const double complex *x, double complex *X, int N);
void butterfly(const double complex *a, double complex *b, double complex W);
void bit_reversal(const double complex *out, double complex *X, int N);

int main() {
    return 0;
}

void fft(const double complex *x, double complex *X, int N) {
    double complex in[N], out[N]; // VLA
    // Temporary buffers for the butterfly inputs and outputs
    double complex a[2], b[2];
    double complex W;

    for (int n = 0; n < N; n++)
        in[n] = x[n];

    // Cycle through the stages
    for (int m = N; m >= 2; m /= 2) {
        // Cycle through the k group of the m stage
        for (int k = 0; k < N / m; k++) {
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
            for (int n = 0; n < N; n++)
                in[n] = out[n];
    }
    bit_reversal(out, X, N);
}

void butterfly(const double complex *a, double complex *b, double complex W) {
    b[0] = a[0] + a[1];
    b[1] = (a[0] - a[1]) * W;
}

void bit_reversal(const double complex *out, double complex *X, int N) {
    // nbits = log2(N)
    int nbits = 0, N1 = N;
    while (N1 >>= 1)
        nbits++;

    for (int i = 0; i < N; i++) {
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