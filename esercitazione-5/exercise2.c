/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es5 - Parte 2 - Trasformata Discreta di Fourier (DFT)
 * Purpose:  Generate N samples of a sinusoidal signal at f0=2015 Hz (not on
 *           the DFT frequency grid), compute its DFT and save the index,
 *           frequency, real part, imaginary part and modulus of each spectral
 *           sample to a CSV file to observe spectral leakage
 */

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M 256

void dft(const double complex *x, double complex *X, int N);

int main() {
    double complex x[M];
    double complex X[M];
    double Fs = 8000.0, f0 = 2015.0;

    for (int n = 0; n < M; n++) {
        x[n] = cos(2 * M_PI * f0 * n / Fs);
    }

    FILE *fp;
    if ((fp = fopen("DFT_SP.csv", "w")) == NULL) {
        perror("Error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

    dft(x, X, M);
    for (int k = 0; k < M; k++) {
        fprintf(fp, "%d,%lf,%lf,%lf,%lf\n", k, k * Fs / (double) M, creal(X[k]),
                cimag(X[k]), cabs(X[k]));
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

// Qunado le frequenze del sengale non coincidono con quelle della DFT sia
// questo fenomeno, ovvero un po di energia va prima e dopo, interessa tutto lo
// spettoro, quindi non piu tutti i punto =0 e poi linea, qua si distribuisci un
// po d'appertutto. fenomeno di distribuzione d'energia su bin vicini