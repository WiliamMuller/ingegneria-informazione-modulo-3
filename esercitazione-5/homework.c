/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es5 - Homework - Trasformata Discreta di Fourier (DFT)
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

void dft(const double *x, double complex *X, int N);
void get_samples(double *x, int N);
char detect_key(double complex *X, double Fs, int N);
int find_best_bin(double complex *X, int *bins);

int main() {
    double Fs = 8000.0, x[M];
    double complex X[M];
    FILE *fp;

    // Get the samples form the .wav file
    get_samples(x, M);

    if ((fp = fopen("dtmf.csv", "w")) == NULL) {
        perror("Error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

    dft(x, X, M);
    char key = detect_key(X, Fs, M);
    printf("Tasto rilevato: %c\n", key);

    for (int k = 0; k < M / 2; k++) {
        fprintf(fp, "%d,%lf,%lf,%lf,%lf\n", k, k * Fs / (double) M, creal(X[k]),
                cimag(X[k]), cabs(X[k]));
    }

    fclose(fp);
    return 0;
}

void dft(const double *x, double complex *X, int N) {
    for (int k = 0; k < N; k++) {
        double complex s = 0.0 + 0.0 * I;
        for (int n = 0; n < N; n++) {
            double theta = -2.0 * M_PI * k * n / (double) N;
            s += x[n] * cexp(I * theta);
        }
        X[k] = s;
    }
}

void get_samples(double *x, int N) {
    char filename[256];
    FILE *fp;
    int16_t sample;

    printf("Inserire il nome del file WAV: ");
    scanf("%255s", filename);

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

    // Starts reading after the header (44 bytes)
    fseek(fp, 44, SEEK_SET);

    for (int k = 0; k < N; k++) {
        if (fread(&sample, sizeof(int16_t), 1, fp) != 1) {
            printf("Numero di campioni audio insufficiente\n");
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        x[k] = sample / 32768.0;
    }

    fclose(fp);
}

char detect_key(double complex *X, double Fs, int N) {
    double row_freq[4] = {697.0, 770.0, 852.0, 941.0};
    double col_freq[4] = {1209.0, 1336.0, 1477.0, 1633.0};
    char lookup_table[4][4] = {{'1', '2', '3', 'A'},
                               {'4', '5', '6', 'B'},
                               {'7', '8', '9', 'C'},
                               {'*', '0', '#', 'D'}};
    int row_bins[4], col_bins[4];

    // Transform the frequencys into bins
    for (int i = 0; i < 4; i++) {
        row_bins[i] = (int) round(row_freq[i] * N / Fs);
        col_bins[i] = (int) round(col_freq[i] * N / Fs);
    }

    // Find the correct bin
    int best_col_bin = find_best_bin(X, col_bins);
    int best_row_bin = find_best_bin(X, row_bins);

    return lookup_table[best_row_bin][best_col_bin];
}

int find_best_bin(double complex *X, int *bins) {
    int best = 0;
    for (int i = 0; i < 4; i++) {
        if (cabs(X[bins[i]]) > cabs(X[bins[best]]))
            best = i;
    }
    return best;
}
