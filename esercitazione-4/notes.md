# Segnali periodici come somme di fasori - Esercitazione 4

Dato un segnale periodico, esso può essere sviluppato come somma di fasori:$$x(t) = \sum _{n = -\infty}^{\infty}c_{n}e^{j2\pi nf_{0}t}$$
Di per se però i coefficenti possono essere complessi seppure il segnale $x(t)$ sia reale ed ricordiamo la simmetria Hermitiana:$$x(t) \in \mathbb{R} \quad \Longrightarrow \quad c_{n}^{*} = c_{-n}$$
Nel caso in cui x(t) sia complesso, lo posso scrivere come:$$x(t) = \sum _{n=-\infty}^{\infty}|c_{n}|e^{j(2\pi nf_{0}t + arg(c_{n}))}$$
# Parte 1

Il segnale preso in considerazione è un onda a dente di sega con periodo $T$ ($f_{0} = \frac{1}{T}$) :$$x(t) = A\frac{t}{T} \qquad 0 \leq t < T$$
Graficamente:
![[Pasted image 20260523041723.png|697]]

Andando a sostituire troviamo che quando:$$\begin{align*} t = 0 &\quad \Longrightarrow \quad x(t) = 0 \\ t = T &\quad \Longrightarrow \quad x(t) = A \end{align*} $$
Quindi è lineare, oltre a ciò dallo sviluppo in serie di furie sappiamo che:
$$c_{n} =\begin{cases}
\frac{A}{2}, & n = 0 \\
j\frac{A}{2\pi n}, & n \neq 0 \\
\end{cases} $$
Infatti questi vengono già forniti nel testo della esercitazione, comunque se li dovessimo trovare basta calcolare:$$c_{n} = \frac{1}{T} \int_{T} x(t)e^{-j2\pi nf_{0}t} \, dt $$
Dove $T$ indica che l'integrale deve essere calcolato da $0$ a $T$.

Andiamo ora ad analizzare il modulo $|c_{n}|$:$$|c_{n}| = j\frac{A}{2\pi n} = |j| \frac{A}{2\pi|n|} = \frac{A}{2\pi|n|}$$
Che varrà (modulo scompare per $n$ positivi):$$|c_{n}| = \begin{cases} \frac{A}{2\pi n}, & n > 0 \\ \frac{A}{2\pi |n|}, & n < 0    \end{cases}$$
E di seguito l'argomento $arg(c_{n})$:$$arg(c_{n}) = arg\left( j \frac{A}{2\pi n} \right) = arg\left( \frac{j}{n} \right) + arg\left( \frac{A}{2\pi} \right) = arg\left( \frac{j}{n} \right)$$
Che a sua volta varrà:$$arg(c_{n}) = \begin{cases} +\frac{\pi}{2}, & n > 0 \\ -\frac{\pi}{2}, & n < 0    \end{cases}$$
Ora ci conviene separare gli $n$ positivi  da $n$ negativi:$$x(t) = \sum_{n=-\infty}^{-1} \frac{A}{2\pi|n|} e^{j\left( 2\pi n f_{0}t - \pi/2 \right)} + \frac{A}{2} + \sum_{n=1}^{\infty} \frac{A}{2\pi n} e^{j\left( 2\pi n f_{0}t + \pi/2 \right)} $$
Dove il termine $\frac{A}{2}$ rappresenta il valore per $c_{0}$.

Ma dato che per valori di $n$ grandi il contributo diventa sempre più trascurabile, possiamo approssimare:$$x(t) \approx \sum_{n=-L}^{-1} \frac{A}{2\pi|n|} e^{j\left( 2\pi n f_{0}t - \pi/2 \right)} + \frac{A}{2} + \sum_{n=1}^{L} \frac{A}{2\pi n} e^{j\left( 2\pi n f_{0}t + \pi/2 \right)} $$
Essendo $x(t)$ reale, vale la simmetria Hermitiana per cui le parti immaginarie si cancellano reciprocamente.

Si veda il codice sorgente `exercise1.c` e i plot `exersice1_plot.pdf`.

All'aumentare di L l'approssimazione è sempre migliore, dove sono presenti le discontinuità avviene il fenomeno di Gibbs (elongazione).

# Parte 2

In questo caso il segnale considerato è complesso e ha forma: 
$$x(t) = \begin{cases} 
1, & 0 \leq t < \frac{T}{4} \\
j, & \frac{T}{4} \leq t < \frac{T}{2} \\
-1, & \frac{T}{2} \leq t < \frac{3T}{4} \\
-j, & \frac{3T}{4} \leq t < T \\
\end{cases}$$

Quindi nel primo quarto di periodo ($\frac{1}{4}T$), il segnale vale $1$, quindi nel piano complesso ha parte reale $\Re\{x(t)\} = 1$ , e parte immaginaria $\Im\{x(t)\} = 0$, e cosi via per gli altri punti.

Come prima possiamo usare la serie di Fourier per trovare i coefficenti $c_{n}$ del segnale (essendo periodico):
$$c_{n} = \frac{1}{T} \int_{T} x(t)e^{-j2\pi nf_{0}t} \, dt $$

Da cui spezzando l'integrale nei 4 sottoperiodi dove $x(t)$ è costante e calcolando, si ottiene che i coefficenti non sono nulli solo per:$$n=4k+1 \qquad k \in \mathbb{Z}$$

E hanno espressione:$$c_{4k+1} = \frac{2}{\pi(4k+1)}(1-j)=\frac{2\sqrt{ 2 }}{\pi(4k+1)}e^{-j\pi/4}$$
Possiamo quindi scrivere:$$x(t) = \sum_{k=-\infty}^{+\infty} \frac{2\sqrt{ 2 }}{\pi(4k+1)} e^{j\left( 2\pi (4k+1) f_{0}t - \pi/4 \right)} \approx \sum_{k=-K}^{+K} \frac{2\sqrt{ 2 }}{\pi(4k+1)} e^{j\left( 2\pi (4k+1) f_{0}t - \pi/4 \right)}$$
In modo simile a quanto fatto prima.

Si veda il codice sorgente `exercise2.c` e i plot `exersice2_plot.pdf`.

# Homework

Simile alla parte 1, il segnale ora considerato è un onda triangolare:$$x(t) = \begin{cases} 
\frac{2A}{T}t, & 0 \leq t < \frac{T}{2} \\
2A- \frac{2A}{T}t, & \frac{T}{2} \leq t < T \\
\end{cases}$$
Come prima possiamo trovare i coefficenti con la solita serie di Fourier, ma come tutte le altre parti sono già forniti:$$c_{n} = \begin{cases} 
\frac{A}{2}, & n=0 \\
-\frac{2A}{\pi^2n^2}, & n \space \space \text{dispari} \\
0, & n \space \space \text{pari} \\
\end{cases}$$
Il ragionamento è simile alla parte 1, per cui il segnale approssimato varrà:
$$x(t) \approx \frac{A}{2} + \sum_{n=-L}^{L} -\frac{2A}{\pi^2n^2} e^{j\left( 2\pi n f_{0}t\right)} \qquad n \space \space \text{dispari} $$

Si veda il codice sorgente `homework.c`.
