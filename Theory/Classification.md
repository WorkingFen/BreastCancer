# Klasyfikacja i klasyfikatory

## Maszyny wektorów nośnych
   > Support Vector Machines - SVM

Klasyfikator na podstawie danych buduje funkcję:
   - f(x) > 0 -> x należy do Klasy
   - f(x) <= 0 -> x nie należy do Klasy

### SVM - przypadek liniowo separowalny

x*i* - i-ty obraz
y*i* = 1     jeśli x*i* należy do Klasy
y*i* = -1    jeśli x*i* nie należy do Klasy

Funkcja rozgraniczająca: 

```
f(x) = w^T * x - b
(w,b) = arg min(w,b)||w||^2
```

przy ograniczeniach:

```
w^T * xi - b >= 1 dla xi należacego do Klasy
w^T * xi - b <= -1 dla xi nie należącego do Klasy
```

Inaczej, przy ograniczeniach: (w^T * x*i* - b) * y*i* >= 1
> Jest to kryterium minimalizacji

### SVM - przypadek nieseparowalny liniowo

Funkcja rozgraniczająca:

```
f(x)=w^T * x - b
(w,b) = arg min(w,b) Suma(i) Xsi(i) + Alfa||w||^2, gdzie Alfa > 0
```

Przy ograniczeniach dla każdego i:

```
Xsi(i) >= 0
(w^T * xi - b) * yi >= 1 - Xsi(i)
```

Wniosek z powyższego: Xsi(i) = max{1-f(x*i*) * y*i*, 0}

Twierdzenie o reprezentacji: w = Suma(i) Alfa(i) * y*i* * x*i*, gdzie Alfa(i) != 0, tylko dla i należącego do SVs

### SVM - postać nieliniowa

Zasady są takie same, ale jest nowa przestrzeń

```
z = Fi(x)
w = Suma(i) Alfa(i) * y*i* * Fi(x*i*)
f(x) = w^T * Fi(x) - b
```

(Alfa(1..N), b) = arg min(Alfa(1..N), b) Suma(i) max{1-f(x*i*) * y*i*, 0} + Lambda||w||^2

Stąd wynika -> f(x) = Suma(i)(Alfa(i) * y*i* * Fi(x*i*)^T) * Fi(x) - b

### Jądra SVM

Fi(x)^T * Fi(y) = k(x,y)

- liniowe: k(x,y) = x^T * y
- wielomianowe: k(x,y) = (1+x^T * y)^d, d>0
- gaussowskie (RBF): k(x,y) = exp(- ||x-y||^2 / 2ð^2)

#### SVM z jądrem gaussowskim

(Alfa(1..N), b) = arg min(Alfa(1..N), b) Suma(i) max{1 - f(x*i*) * y*i*, 0} + Lambda||w||^2

f(x) = Suma(i) Alfa(i) * y*i* * exp(-||x*i* - x||^2 / 2ð^2) -> Należy to zapamiętać!

## Indukcja drzew decyzyjnych

- Baza danych przypadków z ich klasyfikacją
- Na jej podstawie -> Mechanizm decyzyjny w formie drzewa

Na przykład, czy Tiger Woods gra w golfa?

		      Pogoda
		/	|	 \
 	       /        |         \
	Pochmurno      Pada	   Słonecznie
	    /           |              \
           /            |               \
       X(Gra)	    Wietrznie	        Wilgotność
                    /     \              /      \
                   /       \            /        \
		 Tak        Nie        <=75      >75
                  |          |          |         |
	      X(Nie gra)     X(Gra)    X(Gra)    X(Nie gra)\

### Algorytm ID3

Funkcja ID3 ( **C**: Zbiór klas, **R**: Zbiór atrybutów poza klasą, **S**: Zbiór obiektów )

1. Jeśli **S** = Null: zwróc błąd
2. Jeśli wszystkie obiekty w **S** są tej samej klasy:
   - zwróć węzeł zawierający tylko tę klasę
3. Jeśli **R** = Null:
   - zwróć węzeł zawierający klasę najczęstszą w **S**
4. **D** = atrybut maksymalizujący InfGain(**D**, **S**)
5. d*j* = j-ta wartość tego atrybutu, j=1,2,...
6. S*j* = {o należący do S| D(o) = d*j*}
7. Zwróć drzewo z korzeniem oznaczonym przez **D**, krawędziami d*j*, j=1,2..., prowadzącymi do drzew ID3(**R** - {**D**}, **C**, __S*1*__), ID3(**R** - {**D**}, **C**, __S*2**__), ...

#### InfGain

- Entropia zbioru, f*i* - częstości i-tej klasy 
  - I(**S**) = -Suma(i) f*i* * ln(f*i*)
- Entropia zbioru podzielonego na podzbiory 
  - Inf(**D**, **S**) = Suma(j) |S*j*| / |S| * I(S*j*)
- Zdobycz informacyjna
  - InfGain(**D**, **S**) = I(**S**) - Inf(**D**, **S**)

### Algorytm C4.5

Funkcja C4.5 ( **C**: zbiór klas, **R**: zbiór atrybutów poza klasą, **S**: zbiór obiektów )

1. **T** = ID3
2. Dla każdego liścia T:
   1. Dla każdego węzła *w* na drodze liść-korzeń:
      1. e*0* = oszacowanie błędu testowego w poddrzewie *w*
      2. e*1* = oszacowanie błędu testowego, gdyby *w* zwracał najczęstszą w nim klasę
      3. Jeśli e*0* >= e*1*:
         - Zastąp poddrzewo liściem zwracającym najczęstszą w nim klasę

#### Szacowanie błędu testowego

e*s* - błąd na zbiorze treningowym
e*t* - szacowany błąd na zbiorze testowym

e*t* ~= e*s* + V(e*s* * (1-e*s*)) / |**S**|

### W stronę lasów losowych

- Wadą ID3 jest przeuczenie (overfitting)
- Wadą C4.5 jest nienajlepsza klasyfikacja -> zachłanny sposób wyboru atrybutów w węzłach drzewa

Pomysł: Zbudować wiele różnych drzew na bazie różnych problemów niesprzecznych z danym. Klasyfikacja -> Dominanta klasyfikacji dokonywanych przez drzewa

#### Budowa lasu losowego (random forest)

Procedura createForest( **C**: zbiór klas, **R**: zbiór atrybutów poza klasą, **S**: zbiór obiektów )

1. Dla b=1..B:
   1. S*b* = B obiektów z **S** wylosowanych ze zwracaniem
   2. R*b* = |_ V(|R|) _| atrybutów wylosowanych bez zwracania z **R**
   3. f*b* = drzewo decyzyjne zbudowane na podstawie **C**, __R*b*__, __S*b*__

Funkcja classificate( **o**: obiekt )

1. Dla b=1..B:
   1. c*b* = klasa obiektu **o** wskazana przez f*b*
   2. Zwróć najczęstszą klasę w {c*1*,...,c*B*}

## Gradient Boosting

Zadanie aproksymacji na zbiorze skończonym <x*i*, y*i*>, i należy do {1,...,n}

Modele:
	~f*m*: R^n*x* -> R^n*y*, Gamma(m) należy do R, ~F*m*(x*i*) = Suma(m) Gamma(m) * ~f*m*(x*i*) ~= y*i*

Funkcja straty:
	q*i*: R^n*y* -> R, np. q*i*(y) = 0.5||y-y*i*||^2

W pętli:
- Kolejne ~f*m* poprawia błędy dotychczasowego modelu

### Gradient Boosting - algorytm

1. Inicjalizacja wartością stałą F*0*(x) == arg min(Gamma) Suma(od i=1 do n) q*i*(Gamma) 
2. Dla m=1 do M:
   2.1 Oblicz pseudo-rezidua:
r*i,m* = -[(ð * q*i* * (F*m-1*(x*i*))) / (ð * F*m-1*(x*i*))], i=1,..,n np. r*i,m* = y*i* - F*m-1*(x*i*)
   2.2 Naucz ~f*m* używając <x*i*, r*i,m*>, i=1,..,n jako zbioru treningowego
   2.3 Oblicz Gamma(m), Gamma(m) = arg min(Gamma) Suma(od i=1 do n) q*i* * (F*m-1*(x*i*) + Gamma * ~f*m*(x*i*))
   2.4 F*m*(x) = F*m-1*(x) + Gamma(m) * ~f*m*(x)
3. Zwróć F == F*M*
