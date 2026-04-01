#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 100

double randu();
int rand_bern(double p);
int rand_bino(int n, double p);

int main() {
    double p, vect[M];
    int n;

    srand(time(NULL));

    do {
        printf("Inserire un valore di p (0:1): ");
        scanf("%lf", &p);
    } while (p >= 1 || p <= 0);

    do {
        printf("Inserire un valore di n (>0): ");
        scanf("%d", &n);
    } while (n <= 0);

    for (int i = 0; i < M; i++) {
        vect[i] = rand_bino(n, p);
    }

    double sample_avg = 0;
    for (int i = 0; i < M; i++) {
        sample_avg += vect[i] / (double)M;
    }
    printf(
        "Con la generazione di M: %d campioni di V.A. Binomiale otteniamo:\n",
        M);
    printf("La media campionaria: %.2lf\nIl valore medio statistico: %.2lf\n",
           sample_avg, (n * p));

    return 0;
}

double randu() { return ((double)rand() + 1.0) / ((double)RAND_MAX + 2.0); }

int rand_bern(double p) { return randu() <= p ? 1 : 0; }

int rand_bino(int n, double p) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += rand_bern(p);
    }
    return sum;
}
