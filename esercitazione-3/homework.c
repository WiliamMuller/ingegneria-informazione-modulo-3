/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es3 - Homework - Fasori e segnali complessi
 * Purpose:  Generate N samples of a amplitude-modulated phasor, save the real,
 *           imaginary and modulus of each sample to a CSV file to later plot
 */

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 2000

int main() {
    double complex samples[N];
    double f0 = 20.0, fm = 2.0, Fs = 1000.0;

    // Generate the samples
    for (int i = 0; i < N; i++) {
        samples[i] = ((1 + 0.5 * cos(2 * M_PI * fm * i / Fs)) *
                      cexp(I * (2 * M_PI * f0 * i / Fs)));
    }

    FILE *fp;
    if ((fp = fopen("am_phasor.csv", "w")) == NULL) {
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
