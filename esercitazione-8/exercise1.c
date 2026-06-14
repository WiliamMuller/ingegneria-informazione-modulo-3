/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Es8 - Parte 1-2 - Rappresentazione Fixed-Point e Err. di Quant.
 * Purpose:  Convert N evenly spaced values in [-1,1) from double to
 *           Q m.n fixed-point format and back, compute the quantization
 *           error for each sample and save x, X, x_tilde and e to a CSV file to
 *           later plot.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int16_t double_to_Q(double x, int n);
double Q_to_double(int16_t X, int n);

int main() {
    const int n = 15;
    FILE *fp;
    if ((fp = fopen("quantization.csv", "w")) == NULL) {
        perror("Error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "x,X,xtilde,e\n");

    for (int i = 0; i < N; i++) {
        double x = -1.0 + 2.0 * ((double) i) / N;
        int16_t X = double_to_Q(x, n);
        double xtilde = Q_to_double(X, n);
        double e = x - xtilde;
        fprintf(fp, "%.15lf,%d,%.15lf,%.15lf\n", x, X, xtilde, e);
    }

    fclose(fp);
    return 0;
}

int16_t double_to_Q(double x, int n) {
    return (int16_t) (x * (1 << n)); // 1 << n = 2^n
}

double Q_to_double(int16_t X, int n) {
    return (double) X / (1 << n);
}