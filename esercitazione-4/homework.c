/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es4 - Homework - Segnali periodici come somme di fasori
 * Purpose:  Generate N samples of a triangle wave approximated as a finite
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

        for (int n = -L; n <= L; n++) {
            if (n == 0)
                continue;
            if (n % 2 == 0)
                continue;
            x[i] += ((-2 * A) / (M_PI * M_PI * n * n)) *
                    cexp(I * (2 * M_PI * n * f0 * i / Fs));
        }
    }

    FILE *fp;
    if ((fp = fopen("homework.csv", "w")) == NULL) {
        perror("Error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        fprintf(fp, "%.15lf,%.15lf\n", creal(x[i]), cimag(x[i]));
    }

    fclose(fp);

    return 0;
}