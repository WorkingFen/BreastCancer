# Uczenie się ze wzmocnieniem

Adaptacja w systemie dynamicznym polega na określaniu stanu systemu dynamicznego (środowiska) przez arbitra oraz decydenta. Arbiter określa czy wykonywane akcje przez decydenta są pozytywne czy negatywne i odpowiednio nagradza decydenta. 
	 ___________
	|    |      > 
Decydent     |	      Środowisko (system dynamiczny)
   ^   <_ __ | __ __
   |         v   | 
   |_ Arbiter <--- 


### Proces Decyzyjny Markowa (PDM)

- Decydent + Środowisko
- Dyskretny czas t = 1,2,...
- Stan x*t*
- Decyzja/Akcja u*t*
- Następny stan x*t+1*
- Nagroda/Wzmocnienie r*t*
- Epizody
- Cel: Maksymalizacja przyszłych nagród

#### PDM formalnie

- Przestrzeń stanów: **x** należy do **X**
- Przestrzeń decyzji: **u** należy do **U**
- Rozkład przejścia stanów P*x*(x*t+1*|x*t*, u*t*)
- Nagrody r*t* = r(u*t*, x*t+1*)
- Stany terminalne epizodów __X*__
- Rozkład stanów początkowych epizodu P*0*
- Środowisko: P*x*, r, __X*__ i P*0*

> Coś ważnego, czyli funkcja wartości-decyzji

Pi -> Polityka uczenia się
Q*Pi*(x,u) = epsilon(Suma(od i=0 do +inf) gamma*i* r*t+i*|x*t* = x, u*t* = u; Pi)

### Q-Learning 

Idea algorytmu:

- Utrzymywana jest funkcja **Q** która ma zbiegać do __Q*__ czyli optymalnej funkcji wartości-decyzji
- Krok algorytmu = krok decydenta w środowisku
- W każdym kroku **Q**(x*t*, u*t*) jest przybliżane do wartości *indkowanej* przez funkcję **Q**

Algorytm: 

0. Dane: Sekwencja {_B_*t*, *t* = 1,2,...} spełniająca warunki, że 
   -Suma(od t>= 1 do +inf) _B_*t* = +inf 
   -Suma(od t>= 1 do +inf) _B_*t*^2 < +inf
1. Wylosuj u*t* na podstawie **Q** i x*t*
2. Wykonaj u*t*, zarejestruj x*t+1* i r*t*
3. Przypisz
   Q(x*t*, u*t*) := Q(x*t*, u*t*) + _B_*t*(r*t* + gamma * Max(u)Q(x*t+1*, u)-Q(x*t*,u*t*))
4. Przypisz t := t+1 i wróć do Punktu 1.

#### Dwie metody wybory decyzji przez algorytm Q-Learning:

1. Strategia E-zachłanna

   P(u*t* = u|x*t*) = E * 1/#U + (1-E) * [u należące do arg max(u)Q(x*t*, u)]/#arg max(u)Q(x*t*, u)

Gdzie # oznacza ilość elementów, a arg max(x) oznacza zbiór argumentów funkcji dla jakich osiąga ona maksimum

Czyli inaczej:
   P(u*t* = u|x*t*) = E * 1/(ilość elementów u) + (1-E) * [u należące do zbioru argumentów u, w której Q(x*t*, u) ma maksimum]/(Ilość elementów u zbioru wyżej opisanego)

2. Strategia Bolzmannowska

   P(u*t* = u|x*t*) = exp(Q(x*t*, u)/T) / Suma(u`należącego do U) exp(Q(x*t*, u`)/T)


