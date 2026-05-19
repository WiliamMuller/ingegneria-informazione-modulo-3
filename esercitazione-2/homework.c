/*
 * Author:   Wiliam Eduard Muller
 * Exercise: Homework - Generazione di V.A. continue
 * Purpose:  Generate N samples of the specified R.V. (Polynomial Distribution)
 *           and using the Histogram method find the values of the Empirical PDF
 *           to later plot against the Theoretical PDF
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000
#define NBINS 100
#define H (1.0 / NBINS) // Width of each bin

double randu();
double rand_poly();

int main() {
    int counts[NBINS] = {0};
    double sum = 0.0;
    double mean;
    FILE *fp;
    if ((fp = fopen("histogram_hw.csv", "w")) == NULL) {
        perror("Error while creating the file!\n");
        exit(EXIT_FAILURE);
    }

    // Set the seed for random number generation via rand() function
    srand((unsigned) time(NULL));

    for (int i = 0; i < N; i++) {
        double y = rand_poly();
        // Find the bin where the sample falls
        int k = (int) (y / H);
        counts[k]++;
        sum += y;
    }

    for (int k = 0; k < NBINS; k++) {
        double y_mid = (k + 0.5) * H;
        // Normalization to get the empirical PDF (area = 1)
        double f = counts[k] / (N * H);
        fprintf(fp, "%.15lf,%.15lf\n", y_mid, f);
    }

    mean = sum / N;

    printf("Valor medio statistico teorico: %lf\n", 3. / 4.);
    printf("Media campionaria: %lf\n", mean);
    printf("Scostamento: %lf\n", 3. / 4. - mean);

    fclose(fp);

    return 0;
}

double randu() {
    return ((double) rand() + 1.0) / ((double) RAND_MAX + 2.0);
}

double rand_poly() {
    return cbrt(randu());
}
