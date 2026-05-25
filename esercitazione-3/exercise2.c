/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es3 - Parte 2 - Fasori e segnali complessi
 * Purpose:  Generate N samples of a sum of two discrete-time phasors, save the
 *           real, imaginary and modulus of each sample to a CSV file to later
 *           plot
 */

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 2000

int main() {
    double complex samples[N];
    double A1 = 1, A2 = 0.8, f1 = 20.0, f2 = 21.0, Fs = 1000.0;

    // Generate the samples
    for (int i = 0; i < N; i++) {
        samples[i] = (A1 * cexp(I * (2 * M_PI * f1 * i / Fs)) +
                      A2 * cexp(I * (2 * M_PI * f2 * i / Fs)));
    }

    FILE *fp;
    if ((fp = fopen("beat.csv", "w")) == NULL) {
        perror("Error while creating the file!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        fprintf(fp, "%.15lf,%.15lf,%.15lf\n", creal(samples[i]),
                cimag(samples[i]), cabs(samples[i]));
    }
    fclose(fp);

    return 0;
}
