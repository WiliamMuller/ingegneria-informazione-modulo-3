# Fasori e segnali complessi - Esercitazione 3

Per creare numeri complessi bisogna includere l'header `#include <complex.h>`.
Il motivo per cui si usa tipo `double` invece che `float` davanti al tipo `complex`,  è dovuta alla precisione infatti:

- `float complex`   precisione decimale ~ 6-9

- `double complex` precisione decimale ~ 13-15

Per i `float`, una volta superata la settima cifra decimale la sua precisione non è più garantita, per questo useremo il tipo `double`.

Possiamo rappresentare un numero complesso nella sua forma cartesiana oppure polare, ma in ogni caso verrà **SEMPRE** memorizzato nella forma cartesiana (parte reale e immaginaria, ergo converte in automatico da forma polare a forma cartesiana).
Di seguito un esempio in C:
```
#include <complex.h>

// Forma Cartesiana
double complex z = 3.0 - 4.0*I;

// Forma Polare
#include <math.h>

double r = 2.0;
double theta = M_PI/4;
double complex z = r * cexp(I * theta);
```

Per estrarre le parti di un numero complesso possiamo usare le seguenti funzioni:
```
// Parte reale e parte immaginaria
creal(z), cimag(z);

// Cogniugato
conj(z);

// Modulo e argomento
cabs(z), carg(z);
```

Nelle slides, viene definito l'argomento di un numero complesso come:$$arg(z) = atan2(\Im(z), \Re(z))$$
Che semplicemente è una funzione della analisi complessa, infatti l'argomento non è sempre l'arcotangente di z (fatto di meno importanza).

Ricordiamo poi che un fasore non è altro che un punto nel piano complesso che scorre nel tempo sulla circonferenza di raggio A con velocità angolare $\omega = 2\pi f_{0}$ e fase iniziale $\phi$: $$x(t) = Ae^{j2\pi f_{0}t + \phi}$$
La rotazione dipende dal valore di $f_{0}$, se è positiva allora rotazione antioraria (fase aumenta nel tempo), se è negativa rotazione oraria (fase diminuisce nel tempo).

Se voglio generare i campioni di un fasore con frequenze di campionamento $f_{s}$, gli istanti di campionamento sono a:$$0, \quad T_{s}, \quad 2T_{s}, \quad \dots$$
oppure equivalentemente:$$0, \quad \frac{1}{f_{s}}, \quad \frac{2}{f_{s}}, \quad \dots$$
Per n-esimo campione devo sostituire $$t \space = \space \frac{n}{f_s} \qquad  \space f_{s}\geq2f_{0}$$

# Parte 1
Si veda il codice sorgente `exercise1.c` e i plot `exercise1_plot.pdf`

# Parte 2

Si veda il codice sorgente `exercise2.c` e i plot `exercise2_plot.pdf`

# Parte 3

#### Interpretazione dei grafici (fatta alla lavagna)

Sviluppiamo:
$$x_n = e^{j2\pi \cdot 20 \cdot n/F_s} + 0.8\, e^{j2\pi \cdot 21 \cdot n/F_s}$$
Raccogliamo $e^{j2\pi \cdot 20.5 \cdot n/F_s}$: $$x_n = e^{j2\pi \cdot 20.5 \cdot n/F_s} \left( e^{-j2\pi \cdot 0.5 \cdot n/F_s} + 0.8\, e^{+j2\pi \cdot 0.5 \cdot n/F_s} \right)$$
Poniamo $\theta = 2\pi \cdot 0.5 \cdot n/F_s$ e chiamiamo $Z$ il termine tra parentesi: $$Z = e^{-j\theta} + 0.8\, e^{j\theta}$$
Ricordiamo poi che per trovare il modulo:
$$
|x_n| = \underbrace{|e^{j2\pi \cdot 20.5 \cdot n/F_s}|}_{=1} \cdot |Z| = |Z|$$
Ergo devo solo calcolare il modulo di $Z$ che si calcola come $|Z| = \sqrt{Z \cdot Z^*}$:
$$\begin{align*}
Z \cdot Z^* &= \left(e^{-j\theta} + 0.8\, e^{j\theta}\right)\left(e^{j\theta} + 0.8\, e^{-j\theta}\right) \\
            &= 1 + 0.8\,e^{-j2\theta} + 0.8\,e^{j2\theta} + 0.64 \\
            &= 1.64 + 1.6\cos(2\theta)
\end{align*}$$
Quindi:
$$|x_n| = \sqrt{1.64 + 1.6\cos(2\pi n / F_s)}$$
La somma di due fasori produce un segnale con modulo **periodico** con frequenza pari alla differenza delle due frequenze $∣f2−f1∣=1$ Hz — questo è il **fenomeno del battimento**. Il modulo oscilla tra un massimo di $A1+A2=1.8$  e un minimo di $∣A1−A2∣=0.2$ con periodo di 1 secondo.

Il segnale si può scrivere come:
$$x_n = |x_n| \cdot e^{j(2\pi \cdot 20.5 \cdot n/F_s + \arg(Z_n))}$$

Dove:
- $|x_n|$ è il modulo variabile che produce il battimento
- $e^{j2\pi \cdot 20.5 \cdot n/F_s}$​ è il termine di rotazione alla frequenza media 20.5 Hz
- $\arg(Z_n)$  è la fase di $Z$ che varia lentamente e contribuisce poco rispetto alla rotazione principale

Complessivamente si ha un punto che **ruota nel piano complesso** a circa 20.5 Hz su una circonferenza il cui raggio si contrae ed espande periodicamente ogni secondo tra 0.2 e 1.8 — da cui la traiettoria ad anello che si vede nel plot, dove i colori indicano lo scorrere del tempo.

# Homework

Si veda il codice sorgente `homework.c` e i plot `homework_plot.pdf`

#### Interpretazione dei grafici

Segue la stessa logica della parte 3 dell'esercitazione, infatti il segnale è:
 $$x_n = (1 + 0.5\cos(2\pi f_m n/F_s)) e^{j2\pi f_0 n/F_s}$$

Possiamo determinare che:
- Il termine $e^{j2\pi f_{0}n/Fs}$​ è un fasore che ruota a $f_{0}​=20$ Hz, da cui la traiettoria circolare sul piano complesso

- Il termine $(1+0.5\cos(2πf_{m}​n/Fs​))$ è il modulo, che oscilla tra $[0.5, 1.5]$ con frequenza $f_{m} = 2$ Hz, da cui il plot del modulo è una sinusoide con periodo $T = 0.5$ s.

- La traiettoria del punto $x_{n}$ sul piano complesso è una "anello" (simile a quella della parte 2), il punto ruota a 20 Hz ma il raggio oscilla tra $[0.5, 1.5]$ con frequenze $2$ Hz.

Complessivamente rappresenta un fasore con modulazione di ampiezza (AM), il raggio non è costante (come nella parte 1 dove si trattava un fasore puro), ma bensì varia in modo sinusoidale.
