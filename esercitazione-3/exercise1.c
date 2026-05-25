/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es3 - Parte 1 - Fasori e segnali complessi
 * Purpose:  Generate N samples of a discrete-time phasor by sampling a
 *           continuous phasor at frequency Fs, save the real and
 *           imaginary parts to a CSV file to later plot
 */

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define N 1000

int main() {
    double complex samples[N];
    double A = 1, f0 = 20.0, Fs = 1000.0;

    // Generate the samples
    for (int i = 0; i < N; i++) {
        samples[i] = A * cexp(I * (2 * M_PI * f0 * i / Fs));
    }

    FILE *fp;
    if ((fp = fopen("phasor.csv", "w")) == NULL) {
        perror("Error while creating the file!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        fprintf(fp, "%.15lf,%.10lf\n", creal(samples[i]), cimag(samples[i]));
    }

    fclose(fp);

    return 0;
}
