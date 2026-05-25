/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es4 - Parte 1 - Segnali periodici come somme di fasori
 * Purpose:  Generate N samples of a sawtooth wave approximated as a finite
 *           sum of complex phasors (Fourier series, L terms), save the real and
 *           imaginary parts to a CSV file to later plot
 */

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main() {
    double complex x[N];
    double f0 = 50.0, A = 1.0, Fs = 10000.0;
    int L;

    do {
        printf("Inserire L >= 1:\n");
        scanf("%d", &L);
    } while (L < 1);

    for (int i = 0; i < N; i++) {
        x[i] = A / 2.0;
        // Sum the negative part
        for (int n = -L; n <= -1; n++) {
            x[i] += A / (2.0 * M_PI * abs(n)) *
                    cexp(I * (2 * M_PI * n * f0 * i / Fs - M_PI / 2.0));
        }
        // Sum the positive part
        for (int n = 1; n <= L; n++) {
            x[i] += A / (2.0 * M_PI * n) *
                    cexp(I * (2 * M_PI * n * f0 * i / Fs + M_PI / 2.0));
        }
    }

    FILE *fp;
    if ((fp = fopen("fourier.csv", "w")) == NULL) {
        perror("Error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        fprintf(fp, "%.15lf,%.15lf\n", creal(x[i]), cimag(x[i]));
    }

    fclose(fp);

    return 0;
}