#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 10000

double randu();
int rand_bern(double p);
int rand_geom(double p);

int main() {
    double p, vect[M];

    srand(time(NULL));

    do {
        printf("Inserire un valore di p (0:1): ");
        scanf("%lf", &p);
    } while (p >= 1 || p <= 0);

    for (int i = 0; i < M; i++) {
        vect[i] = rand_geom(p);
    }

    double sample_avg = 0;
    for (int i = 0; i < M; i++) {
        sample_avg += vect[i] / (double)M;
    }

    printf(
        "Con la generazione di M: %d campioni di V.A. Geometrica otteniamo:\n",
        M);
    printf("La media campionaria: %.2lf\nIl valore medio statistico: %.2lf\n",
           sample_avg, (1 / p));
    return 0;
}

double randu() { return ((double)rand() + 1.0) / ((double)RAND_MAX + 2.0); }

int rand_bern(double p) { return randu() <= p ? 1 : 0; }

int rand_geom(double p) {
    int count = 0;
    for (;;) {
        count++;
        if (rand_bern(p) == 1)
            break;
    }
    return count;
}
