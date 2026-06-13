# Spettri di rumore bianco e rumore colorato - Esercitazione 5

# Parte 1

Data la variabile aleatoria Uniforme $X \sim U[-1,1]$, si realizzano $N_{x}$ vettori $x$ di lunghezza $N=256$ i quali elementi sono realizzazioni della V.A. $X$ fornita.

Tramite la formula:$$S[k] = \frac{1}{N_{x}} \sum_{i = 0}^{N_{x}-1}|X_{i}[k]|^2$$
Andiamo a calcolare il valor medio campionario, ovvero la stima dello spettro di potenza medio del segnale, dove i $X_{i}$ non sono altro che la $X_{i} = \text{DFT}(x_{i})$.

All aumentare delle realizzazioni $N_{x}$ il valore ottenuto converge allo spettro di potenza teorico, che per il _rumore bianco_ è _costante per tutti i k_.

Si veda il codice sorgente `exercise1.c` e i plot `exersice1_plot.pdf`.

# Parte 2

A differenza del rumore bianco, in un rumore colorato, alcune componenti dello spettro prevalgono su altre (quindi i campioni nel tempo $t$ del segnale non sono più indipendenti), da cui si nota come lo spettro non è più piatto.

Di base tutti i rumori colorati possono essere ottenuti dal rumore bianco, per esempio, Il _rumore rosso_ è proporzionale a $\frac{1}{f^2}$ rispetto al rumore bianco.

Infatti processando un rumore bianco attraverso un sistema LTI (quindi un filtro), riusciamo ad ottenere un rumore rosso (ovvero un rumore a basse frequenze).

Per cui otteniamo:$$G_{y}(f) = G_{x}(f) \cdot |H(f)|^2$$
Dove l'ingresso $G_{x}(f) = \text{costante}$ è del rumore bianco (detta funzione "piatta").
Da cui l'uscita $G_{y}(f)$ sarà:
$$G_{y}(f) = \text{costante} \, \cdot \, |H(f)|^2$$

Per ottenere il fattore $\frac{1}{f^2}$ che definisce il rumore rosso abbiamo bisogno di un integratore:$$H(f) = \frac{1}{j2\pi f} \quad \longrightarrow \quad |H(f)|^2 = \frac{1}{4\pi^2f^2}$$
Il problema di usare l'integratore come FDT è che questo è instabile, infatti nella realtà si usa un filtro che approssima bene la sua funzione, infatti posso elaborare i campioni:$$x_{0},x_{1},x_{2},\dots \quad\to\quad y_{0},y_{1},y_{2},\dots$$
ottenendo cosi:$$y_{n} = x_{n} + b \cdot y_{n-1} \qquad \qquad n=1,\dots,N-1$$
dove $b=0.99$ ed $x_{0} = y_{0}$. Si somma $x_{n}$ ad una forma ritardata di $y_{n}$ moltiplicata per $b$.
Questa elaborazione è di fatto dovuta ad un filtro IIR che è approssimabile ad un integratore.

Si veda il codice sorgente `exercise2.c` e i plot `exercise2_plot.pdf`.

# Homework

Semplicemente bisogna sostituire la V.A. Uniforme $X \sim U[-1,1]$ con la V.A. Gaussiana $X \sim N[0, \sigma^2]$ con $\sigma = 1$, generando cosi un rumore bianco Gaussiano, da cui si ottiene il rumore rosso con la stessa metodologia della parte 2.

Si veda il codice sorgente `homework1.c` e `homework2.c` e i plot `homework1_plot.pdf` e `homework2_plot.pdf`.
