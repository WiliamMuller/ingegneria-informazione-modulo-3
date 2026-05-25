/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es4 - Parte 2 - Segnali periodici come somme di fasori
 * Purpose:  Generate N samples of a complex periodic signal approximated as a
 *           finite sum of complex phasors (Fourier series, K terms), save the
 *           real and imaginary parts to a CSV file to later plot
 */

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 200

int main() {
    double complex x[N];
    double f0 = 50.0, Fs = 10000.0;
    int K;

    do {
        printf("Inserire K >= 1:\n");
        scanf("%d", &K);
    } while (K < 1);

    for (int i = 0; i < N; i++) {
        x[i] = 0.0 + I * 0.0;
        for (int k = -K; k <= K; k++) {
            x[i] += sqrt(2.0) * 2.0 / (M_PI * (4.0 * k + 1.0)) *
                    cexp(I * (2.0 * M_PI * (4.0 * k + 1.0) * f0 * i / Fs -
                              M_PI / 4.0));
        }
    }

    FILE *fp;
    if ((fp = fopen("fourier_complex.csv", "w")) == NULL) {
        perror("Error while creating the file!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        fprintf(fp, "%.15lf,%.15lf\n", creal(x[i]), cimag(x[i]));
    }

    fclose(fp);

    return 0;
}