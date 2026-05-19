
# Generazione di V.A. continue - Esercitazione 2

# Parte 1
Data la seguente p.d.f.:
$$f_X(x) =\begin{cases}
2x, & 0 \leq x \leq 1 \\
0,  & \text{altrove}
\end{cases}$$
1 - Verificare che $f_{X}(x)$ è una densità di probabilità.
Per verificare se la $f_X(x)$ sia una densità di probabilità basta verificare:
- Non negatività: $$f_{X}(x) \geq 0 \quad \forall \space x$$
- Normalizzazione: $$\int_{-\infty}^{\infty} f_{X}(x) \, dx = 1$$
Per la Non negatività possiamo vedere subito che è sempre positiva visto che la p.d.f. restituisce sempre valori positivi. 
Invece per la Normalizzazione basta riflettere sul fatto che la p.d.f. è zero ovunque tranne che in $[0,1]$, quindi basta calcolare l'integrale:$$\int_{0}^{1}2x \,dx = [x^2]_{0}^{1} = 1 - 0 = 1$$
Abbiamo cosi verificato le due proprietà.

2 - Calcolare il valor medio statistico $\mathbb{E}[X]$.
Per calcolare il valor medio statistico di questa p.d.f. basta usare la definizione:  $$\mathbb{E} \triangleq \int_{-\infty}^{+\infty}x\cdot\underbrace{f_{X}(x)}_{\text{p.d.f}}\space dx$$
Che come abbiamo fatto in precedenza basta calcolare l'integrale nel intervallo $[0,1]$:$$\int_{0}^{1}x\cdot2x \,dx = \left[ \frac{2x^3}{3} \right]_{0}^{1} = \frac{2}{3}$$
3 - Calcolare la funzione di distribuzione cumulativa $F_{X}(x)$.
Per definizione la p.d.f. non è altro che la derivata della cumulativa, ergo per trovare la c.d.f. mi basta andare ad integrare la p.d.f. come:$$\int_{0}^{x}2t \,dt = [t^2]_{0}^{x} = x^2$$
Quindi la cumulativa è definita come:
$$F_X(x) =\begin{cases}
0,  & x < 0 \\
x^2, & 0 \leq x \leq 1 \\
1,  & x>1
\end{cases}$$

4 - Determinare la funzione inversa $F_{X}^{-1}(u)$.
Per trovare l'inversa della cumulativa basta:$$u = x^2 \quad \Rightarrow \quad\sqrt{ u } = \sqrt{ x^2 } \quad \Rightarrow \quad x = \sqrt{ u }$$ Quindi l'inversa della cumulativa è definita come:$$F_{X}^{-1}(u) = \sqrt{ u }$$

# Parte 2 - 3
Per trovare i valori della PDF empirica usa il metodo del Istogramma, che è gia stato spiegato nella esercitazione 5 di Matlab (modulo 1).
Si vedeno gli allegati `exercise1.c` e il plot `exercise1_plot.pdf`


# Homework
Seguiamo lo stesso principio della parte 1 dell'esercitazione:
Data la seguente PDF:
$$f_Y(y) =\begin{cases}
3y^2, & 0 \leq y \leq 1 \\
0,  & \text{altrove}
\end{cases}$$
#### 1 - Verificare che $f_{Y}(y)$ è una densità di probabilità.
Per verificare se la $f_X(x)$ sia una densità di probabilità basta verificare:
- Non negatività: $$f_{Y}(y) \geq 0 \quad \forall \space y$$
- Normalizzazione: $$\int_{-\infty}^{\infty} f_{Y}(y) \, dy = 1$$
Per la Non negatività possiamo vedere subito che è sempre positiva visto che la PDF restituisce sempre valori positivi. 
Invece per la Normalizzazione basta riflettere sul fatto che la PDF è zero ovunque tranne che in $[0,1]$, quindi basta calcolare l'integrale:$$\int_{0}^{1}3y^2 \,dy = [y^3]_{0}^{1} = 1 - 0 = 1$$
Abbiamo cosi verificato le due proprietà.

#### 2 - Calcolare il valor medio statistico $\mathbb{E}[Y]$.
Per calcolare il valor medio statistico di questa PDF basta usare la definizione:  $$\mathbb{E} \triangleq \int_{-\infty}^{+\infty}y\cdot\underbrace{f_{Y}(y)}_{\text{p.d.f}}\space dy$$
E come abbiamo fatto in precedenza calcoliamo l'integrale nel intervallo $[0,1]$:$$\mathbb{E}[Y] = \int_{0}^{1}y\cdot3y^2 \,dy = \left[ \frac{3y^4}{4} \right]_{0}^{1} = \frac{3}{4}$$

#### 3 - Calcolare la funzione di distribuzione cumulativa $F_{Y}(y)$.
Per definizione la PDF non è altro che la derivata della cumulativa, ergo per trovare la CDF integriamo la PDF come:$$\int_{0}^{y}3t^2 \,dt = [t^3]_{0}^{y} = y^3$$
Quindi la cumulativa è definita come:
$$F_Y(y) =\begin{cases}
0,  & y < 0 \\
y^3, & 0 \leq y \leq 1 \\
1,  & y>1
\end{cases}$$

#### 4 - Determinare la funzione inversa $F_{Y}^{-1}(u)$.
Per trovare l'inversa della cumulativa basta:$$u = y^3 \quad \Rightarrow \quad\sqrt[3]{ u } = \sqrt[3]{ y^3 } \quad \Rightarrow \quad y = \sqrt[3]{ u }$$ Quindi l'inversa della cumulativa è definita come:$$F_{Y}^{-1}(u) = \sqrt[3]{ u }$$

#### 5 / 6 - Implementare una funzione C rand_poly() ...
Si vedano gli allegati `homework.c` e il plot `homework_plot.pdf`