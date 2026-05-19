/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Parte 2 - Generazione di V.A. continue
 * Purpose:  Generate N samples of the specified R.V. (Linear Distribution) and
 *           using the Histogram method find the values of the Empirical PDF to
 *           later plot against the Theoretical PDF
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000
#define NBINS 100
#define H (1.0 / NBINS) // Width of each bin

double randu();
double rand_linear();

int main() {
    int counts[NBINS] = {0};
    double sum = 0.0;
    double mean;
    FILE *fp;
    if ((fp = fopen("histogram.csv", "w")) == NULL) {
        perror("Error while creating the file!\n");
        exit(EXIT_FAILURE);
    }

    // Set the seed for random number generation via rand() function
    srand((unsigned) time(NULL));

    for (int i = 0; i < N; i++) {
        double x = rand_linear();
        // Find the bin where the sample falls
        int k = (int) (x / H);
        counts[k]++;
        sum += x;
    }

    for (int k = 0; k < NBINS; k++) {
        double x_mid = (k + 0.5) * H;
        // Normalization to get the empirical PDF (area = 1)
        double f = counts[k] / (N * H);
        fprintf(fp, "%.15lf,%.15lf\n", x_mid, f);
    }

    mean = sum / N;

    printf("Valor medio statistico teorico: %lf\n", 2. / 3.);
    printf("Media campionaria: %lf\n", mean);
    printf("Scostamento: %lf\n", 2. / 3. - mean);

    fclose(fp);

    return 0;
}

double randu() {
    return ((double) rand() + 1.0) / ((double) RAND_MAX + 2.0);
}

double rand_linear() {
    return sqrt(randu());
}
