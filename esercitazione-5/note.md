# Trasformata Discreta di Fourier (DFT) - Esercitazione 5

# Campionamento e DFT

Consideriamo il segnale x(t) identicamente nullo per:
$$x(t) = 0 \quad \forall\, t \notin [0, T]$$

Il segnale è passa-basso con frequenza massima $f_m$. Si prelevano $N$ campioni nell'intervallo $[0, T]$ con periodo di campionamento $\Delta t$ e frequenza di campionamento $F_s$:
$$\Delta t = \frac{1}{F_s}, \qquad F_s \geq 2f_m$$

Il campionamento nel dominio del tempo provoca una ripetizione periodica nello spettro con periodo $F_s$:
$$X_s(f) = \sum_{k=-\infty}^{+\infty} X(f - k F_s)$$

I campioni temporali vengono raccolti nel vettore:
$$\mathbf{z} = \bigl(x[0],\, x[1],\, \ldots,\, x[N-1]\bigr)$$

La DFT restituisce il vettore spettrale:
$$\mathbf{X} = \bigl(X[0],\, X[\Delta f],\, \ldots,\, X[(N-1)\Delta f]\bigr)$$

dove la spaziatura spettrale (risoluzione in frequenza) è:
$$\Delta f = \frac{1}{T}$$

I campioni dello spettro sono distribuiti nell'intervallo $[0, F_s]$ con passo $\Delta f$. Si nota la **dualità** tempo-frequenza:
$$\underbrace{\Delta t = \frac{1}{F_s}}_{\text{passo temporale}} \qquad \longleftrightarrow \qquad \underbrace{\Delta f = \frac{1}{T}}_{\text{passo spettrale}}$$

Da cui definiamo la finestra di Nyquist come:
$$\left[0,\, \frac{F_s}{2}\right]$$

I campioni nell'intervallo $\left[\dfrac{F_s}{2},\, F_s\right]$ corrispondono all'alias delle frequenze negative:
$$X\!\left[k\Delta f\right] \text{ per } k > \frac{N}{2} \quad \longleftrightarrow \quad \text{alias di } X\!\left[(k-N)\Delta f\right]$$

Matematicamente la DFT viene definita come:$$X[k] = \sum_{n=0}^{N-1}x[n]e^{-j 2\pi kn/N}, \qquad k = 0, \dots,N-1$$
Possiamo poi definire la costante di rotazione (twiddle factor) $W_{N}=e^{-j2\pi/N}$ da cui otteniamo la forma compatta:$$X[k] = \sum_{n=0}^{N-1}x[n]W_{N}^{kn}, \qquad k = 0, \dots,N-1$$
Il costo computazione è $O(N^2)$.

Un esempio di funzionamento della DFT:
Prendiamo $N=4$ campioni per semplicità con $F_s = 4$ Hz e $f_0 = 1$ Hz,
quindi $\Delta f = 1$ Hz. I campioni del coseno sono:
$$x[n] = \cos\left(\frac{2\pi \cdot n}{4}\right)$$

$$
\begin{align*}
x[0] &= \cos(0) = 1 \\
x[1] &= \cos(\pi/2) = 0 \\
x[2] &= \cos(\pi) = -1 \\
x[3] &= \cos(3\pi/2) = 0
\end{align*}
$$

Per $k=1$ (frequenza $f_0 = 1$ Hz):
$$X[1] = \sum_{n=0}^{3} x[n] \cdot e^{-j2\pi n/4}$$

$$
\begin{align*}
n=0: &\quad 1 \cdot 1 = 1 \\
n=1: &\quad 0 \cdot e^{-j\pi/2} = 0 \\
n=2: &\quad -1 \cdot e^{-j\pi} = -1 \cdot (-1) = 1 \\
n=3: &\quad 0 \cdot e^{-j3\pi/2} = 0
\end{align*}
$$

$$\text{Somma} = 1 + 0 + 1 + 0 = 2 \quad \Rightarrow \quad \textbf{picco!}$$

Per $k=0$ (frequenza 0 Hz):

$$
X[0] = \sum_{n=0}^{3} x[n] \cdot e^{0} = 1 + 0 + (-1) + 0 = 0
\quad \Rightarrow \quad \textbf{zero!}
$$

Questo è quello che succede poi analogamente nella parte 1, ed è il motivo per cui si osservano solo 2 picchi.

Di base poi essendo il coseno una funzione pari e reale, anche la sua DFT è reale e pari (proprietà trasformata di Fourier), quindi la parte immaginaria è **nulla**.

# Parte 1

#### 1) Qual è il range di frequenze osservate dalla DFT?

Il range di frequenze osservabili dalla DFT è:
$$\left[0, F_s\right] \longrightarrow [0, 8\text{ kHz}]$$

#### 2) Qual è la risoluzione in frequenza della DFT, $\Delta f$ ?

Sapendo che:
$$ T = N\Delta t = \frac{N}{F_s} $$

Sostituendo con i valori numerici troviamo che tra un campione in frequenza e un altro la distanza è di:
$$ \Delta f = \frac{1}{T} = \frac{F\_{s}}{N} = 31.25\text { Hz}$$

#### 3) A quale frequenza è associato l’elemento $\mathbf{X}[k] (k= 0,1,...,N-1)\text{ di }\mathbf{X}$ ?

L'elemento $\mathbf{X}[k]$ è associato alla frequenza:
$$f_k = k\Delta f = \frac{k}{T} = \frac{kF_s}{N}$$

#### 4) A quali frequenze si osservano i picchi nello spettro?

I picchi nello spettro si osservano alle frequenze:
$$ f = 2000 \text { Hz e } f = 6000 \text { Hz} $$

#### 5) Perché è presente un picco alla frequenza di 6 kHz?

Il picco a $f = 6 \text { kHz}$ è dovuto al fatto che il segnale $x[n]$ è reale, quindi la sua trasformata ha simmetria Hermitiana:

$$ X[k] = X^{*}[N-k] $$

Poiché la DFT rappresenta le frequenze nel range $[0, F_s]$, la componente a frequenza negativa $-f_0$ viene riportata come:
$$ -f_0 \rightarrow F_s - f_0 = 8000 - 2000 = 6000 \text{ Hz}$$

Ovvero l'alias di $-2000 \text{ Hz}$ nel range $[0, F_s]$

Si veda il codice sorgente `exercise1.c` e i plot `exersice1_plot.pdf`.

# Parte 2

#### 1) Quanto vale il rapporto $\frac{f_0}{\Delta f}$ nel caso precedente e in questo caso?

Nel caso precedente ($f_0 = 2000 \text{ Hz}$), il rapporto vale:
$$ \frac{f_0}{\Delta f} = \frac{2000}{31.25} \approx 64 $$

Invece per questo caso ($f_0 = 2015\text{ Hz}$), vale:
$$ \frac{f_0}{\Delta f} = \frac{2015}{31.25} \approx 64.48 $$

#### 2) Come è cambiato lo spettro a fronte di una piccola variazione della frequenza $f_0$?

Nel caso precedente, con $f_0 = 2000 \,\text{Hz}$, la frequenza del segnale coincideva con una delle frequenze discrete della DFT ($k \cdot \Delta f$), quindi lo spettro presentava due soli picchi (alle frequenze $f_0$ e $F_s - f_0$).

Nel nuovo caso, con $f_0 = 2015 \,\text{Hz}$, la frequenza non è più un multiplo intero di $\Delta f$. Di conseguenza, l'energia del segnale non si concentra più in un singolo picco, ma si distribuisce tra più frequenze adiacenti generando più picchi (di ampiezza minore) attorno alle frequenze "principali".

Infatti se prima i campioni avevano una simmetria perfetta che permetteva la cancellazione dei termini diversi da i specifici 2, ora quella simmetria non c'è più, ergo le cancellazioni non sono mai esatte, per cui si ha energia distribuita sui bin vicini

Si veda il codice sorgente `exercise2.c` e i plot `exersice2_plot.pdf`.

# Homework

Se si aumentato il numero di campioni $N$, la risoluzione in frequenza $\Delta f = F_{s}/N$ diminuisce e l'approssimazione sarà migliore. Infatti per $N = 256$, le frequenze dei bin non corrispondo perfettamente a quelle indicate in tabella (seppur questo non incida nel risultato, infatti tutti i passaggi sono stati eseguiti con lo stesso $N$).

Si veda il codice sorgente `homework.c` e i plot `homework_plot.pdf`.
