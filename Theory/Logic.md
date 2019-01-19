# Logika

#### Podstawy z początków studiów i z liceum.

1. Negacja:

```
  A| T | F |;
 ~A| F | T |;
```

2. Koniunkcja -> 

```
       | A = F | A = T |
 B = F |   F   |   F   |;
 B = T |   F   |   T   |;
```

> Koniunkcja czyli &/^/i jest wyłącznie prawdziwa, jeżeli wszystkie zdania ją tworzące są prawdziwe.

3. Alternatywa -> 

```
       | A = F | A = T |
 B = F |   F   |   T   |;
 B = T |   T   |   T   |;
```

> Alternatywa czyli |/v/lub jest prawdziwa, jeżeli jedno ze zdań ją tworzące jest prawdziwe.

4. Implikacja ->

```
       | A = F | A = T |
 B = F |   T   |   F   |;
 B = T |   T   |   T   |;
```

> Implikacja czyli to/=> jest nieprawdziwa, wyłącznie gdy zdanie prawdziwe stwierdza fałszywość innego zdania.

5. Równoważność ->

```
       | A = F | A = T |
 B = F |   T   |   F   |;
 B = T |   F   |   T   |;
```

> Rownoważność czyli <=> jest prawdziwa, jeżeli zdanie fałszywe stwierdza fałszywość innego zdania lub zdanie prawdziwe stwierdza prawdziwość innego zdania.

6. Kilka definicji

**Literałem** jest zdanie postaci A lub ~A, gdzie A to zdanie proste
**Klauzulą** jest alternatywa literałów, czyli zdanie postaci L*1* v ... v L*n*, gdzie L*i* jest literałem

## Sprowadzanie zdania złożonego do zbioru klauzul

1. A <=> B == (A => B) ^ (B => A)
2. A => B == ~A v B
3. ~(A*1* v ... v A*n*) == ~A*1* ^ ... ^ ~A*n*
4. ~(A*1* ^ ... ^ A*n*) == ~A*1* v ... v ~A*n*
5. (A*1* ^ ... ^ A*n*) v (B*1* ^ ... ^ B*m*) == A(i=1..n, j=1..m) (A*i* v B*j*)

## Język logiki predykatów, obiekty

- *stałe*, np. Jan lub 5, wskazujące obiekty z pewnego uniwersum, zapisywane jako liczby lub słowa z wielkiej litery
- *zmienne*, np. *x*,*y*,*nazwisko*, oznaczają ogólne obiekty, zapisywane małymi literami
- *funkcje*, np. Plus(2,3), Nastepnik(x), Ojciec(Jan), przypisują pewnym obiektom inne obiekty
- *termy*, jest to ogólne pojęcie obejmujące stałe, zmienne oraz funkcje

### Predykaty

**Predykatem** jest wyrażenie postaci PRED(t*1*, ... , t*n*), które przypisuje termom t*1*,...,t*n* prawdę lub fałsz:
DODATNIA(x), OJCIEC(Jan), WIEKSZY(x^2 + 1, 7), PADA

Typowe zapisy predykatu: 
- *prefiksowy*: PRED(arg1, arg2, ...)
- *infiksowy*: arg1 PRED arg2 lub arg1 PRED(arg2, arg3, ...)
- *listowy*: (PRED, arg1, arg2, ...)
- z domyślnym JEST lub MA, postaci (arg1, ...) np. (Kowalski, Wiek, 25, Wzrost, 175)

Semantyka predykatu
- Znaczenie predykatu jest określone przez użytkownika
- Warto zby zapis był intuicyjny; warto unikać predykatów postaci MATKA(Anna, Agata)

#### Główne typy predykatów
- 0-argumentowe, np. PADA, STAN\_ZAGROZENIA, oznaczają zwykle pewien stan, który ogólnie ma miejsce lub nie;
- 1-argumentowe, np. P(obiekt), USZKODZONY(x), BYSTRY(Jan), oznaczają zwykle pewną cechę swojego argumentu
- 2-argumentowe:
  - relacyjne, P(obiekt, obiekt), np. WIEKSZY(x,y)
  - funkcyjne, P(obiekt, wartość), np. WLASCICIEL(Jan, Lexus)
  - wartościujące, P(atrybut, wartość), np. JEST(Obraz, Znieksztalcony)
  - czasowe, P(zdarzenie, zdarzenie), np. x PO y
- 3-argumentowe:
  - funkcyjne, P(arg1, arg2, wartość), np. ODLEGLOSC(Warszawa, Krakow, 300)
  - wartościujące, P(obiekt, atrybut, wartość), np, MA(Abacki, Zarobki, 2000)
  - wartościujące w czasie, P(atrybut, wartość, czas), np. MAXIMUM(Napiecie, 231, 23:10)
- n-argumentowe, każda tabela w relacyjnej bazie danych jest w istocie zbiorem formuł z tym samym predykatem i różnymi argumentami (różne encje)

#### Formuła poprawnie zbudowana rachunków predykatów I rzędu (FPZ)

Definicja. Atomem jest predykat P(...) oraz T i F

Reguły tworzenia FPZ:

1. Atom jest FPZ
2. Jeżeli A i B są FPZ, to formuły ~A, A^B, AvB, A => B, A <=> B są także FPZ
3. Jeżeli A jest FPZ, a *x* jest zmienną indywidualną, to także A*x*(A) i E*x*(A) są FPZ

Przykłady:

- Jan mieszka w białym domu: 
  > MIESZKA(Jan, Dom) ^ KOLOR(Dom, Biały)
- Wszyscy koszykarze są wysocy
  > A*x*(KOSZYKARZ(x) => WZROST(x,Wysoki))
- Każdy student zna Javę lub C#
  > A*x*(STUDENT(x) => (ZNA(x, Java) v ZNA(x, C#)))
- Niektórzy ludzie lubią szpinak
  > E*x*(CZLOWIEK(x) ^ LUBI(x, Szpinak))
- Nikt nie lubi podatków
  > ~E*x*LUBI(x, Podatki)

```
 P = "... jest krukiem"
 Q = "... jest czarny"

 Ax(P(x) => Q(x)) Wszystkie kruki są czarne
 Ax(P(x) ^ Q(x)) Każda rzecz jest czarnym krukiem
 Ex(P(x) ^ Q(x)) Niektóre kruki są czarne
 Ex(P(x) => Q(x)) ?
```

Każda pliszka swój ogonek chwali i wariacje:

```
 P = "... jest pliszką"
 Q = "... jest ogonkiem ... (czyimś)"
 R = "... chwali ... (coś)"

 Ax(P(x) => Ey(Q(y,x) ^ R(x,y))) Każda pliszka chwali swój ogonek
 Ax(P(x) => Ay(Q(y,x) => R(x,y))) Każda pliszka chwali wszystko co jest jej ogonkiem
 Ex(P(x) ^ Ay(R(x,y) => Ez(Q(y,z) ^ z != x))) Niektóre pliszki, chwalą tylko cudze ogonki
 Ex(P(x) ^ Ey(R(x,y) ^ Ez(Q(y,z) ^ z!= x))) Niektóre pliszki, chwalą jakiś cudzy ogonek
```

#### Nawiasy i priorytety operacji

- Priorytety
  1. Kwantyfikatory: A E
  2. Negacja ~
  3. Koniunkcja ^/&/i
  4. Alternatywa v/|/lub
  5. Implikacja i równoważność => <=>
  6. Równoważność formuł ==

- Różne konwencje zapisu kwantyfikatorów
  Ax P(x), A*x* P(x), (Ax)P(x), Ax|P(x)

#### Ważniejsze tożsamości dotyczące FPZ

- P <=> Q == (P => Q) ^ (Q => P)
- P => Q == ~P v Q
- P => Q == ~Q => ~P
- ~(Ex)P(x) == (Ax)~P(x)
- ~(Ax)P(x) == (Ex)~P(x)
- (Ax)P(x) == (Ay)P(y)
- (Ex)P(x) == (Ey)P(y)
- (Ax)[S ^ P(x)] == S ^ (Ax)P(x)
- (Ex)[S ^ P(x)] == S ^ (Ex)P(x)
- (Ax)[S v P(x)] == S v (Ax)P(x)
- (Ex)[S v P(x)] == S v (Ex)P(x)
- (Ax)[P(x) ^ Q(x)] == (Ax)P(x) ^ (Ax)Q(x)
- (Ex)[P(x) v Q(x)] == (Ex)P(x) v (Ex)Q(x)

#### Logiki wyższych rzędów

- A*x,y*[(x = y) <=> ((AP)P(x) <=> P(y))]
- A*F,G*[(F = G) <=> ((Ax)F(x) = G(x))]

### Literały i klauzule

Ax(CZLOWIEK(x) => KOBIETA(x) v MEZCZYZNA(x) == 
CZLOWIEK(x) => (KOBIETA(x) v MEZCZYZNA(x)) ==
~CZLOWIEK(x) v KOBIETA(x) v MEZCZYZNA(x)

### Sprawdzanie formuł do klauzul

1. Usunąć <=>, np. przy użyciu P <=> Q == (P => Q) ^ (Q => P)
2. Usunąć =>, np. przy użyciu P => Q == ~P v Q
3. Ograniczyć zakres negacji do iterału, np:
   - ~(A*1* v ... v A*n*) == ~A*1* ^ ... ^ ~A*n*
   - ~(A*1* ^ ... ^ A*n*) == ~A*1* v ... v ~A*n*
   - ~Ax P(x) == Ex ~P(x)
   - ~Ex P(x) == Ax ~P(x)

4. Usunąć kwantyfikatory szczegółowe przez wprowadzenie funkcji Skolema:
   - jeśli Ex nie jest w zasięgu żądanego Ay, to x = Stała
   - jeśli Ex jest w zasięgu pewnych Ay, to x = Funkcja(y)

5. Przekształć formułę do postaci prefiksowej (kwantyfikatory A z lewej)
6. Usunąć kwantyfikatory A
7. Przekształć w koniunkcję alternatyw, np. wg: (A*1* ^ ... ^ A*n*) v (B*1* ^ ... ^ B*m*) == A(i=1..n, j=1..m)(A*i* v B*j*)
8. Zapisać formuły połączone znakiem koniunkcji osobno: G ^ H -> G,H 

### Funkcja i stała Skolema

- Każdy student lubi jakiś wykład ("Ulubiony wykład"):

AxEy(STUDENT(x) => (WYKLAD(y) ^ LUBI(x,y))) -> Ax(STUDENT(x) => WYKLAD(Uw(x)) ^ LUBI(x, Uw(x)))

- Istnieje wykład lubiany przez wszystkich studentów ("Ulubiony wykład wszystkich"):

EyAx(WYKLAD(y) ^ (STUDENT(x) => LUBI(x,y))) -> Ax(WYKLAD(Uww) ^ (STUDENT(x) => LUBI(x, Uww)))

Uwaga: AxEyAzEv P(x,y,z,v) -> AxAz P(x, F(x), z, G(x,z))

#### Przykład: Formuły -> Klauzule

1. Każda pliszka swój ogonek chwali:

> Ax(P(x) => Ey(Q(y,x) ^ R(x,y)))

Krok 2: Ax(~P(x) v Ey(Q(y,x) ^ R(x,y)))
Krok 4: Ax(~P(x) v (Q(F1(x),x) ^ R(x, F1(x))))
Krok 6: ~P(x) v (Q(F1(x),x) ^ R(x, F1(x)))
Krok 7: (~P(x) v Q(F1(x),x)) ^ (~P(x) v R(x,F1(x)))
Krok 8: ~P(x) v Q(F1(x),x), ~P(x) v R(x,F1(x))

Każda pliszka chwali wszystko co jest jej ogonkiem

> Ax(P(x) => Ay(Q(y,x) => R(x,y)))

Krok 2: Ax(~P(x) v Ay(~Q(y,x) v R(x,y)))
Krok 5: Ax,y(~P(x) v ~Q(y,x) v R(x,y))
Krok 6: ~P(x) v ~Q(y,x) v R(x,y)

Niektóre pliszki chwalą tylko cudze ogonki

> Ex(P(x) ^ Ay(R(x,y) => Ez(Q(y,z) ^ z != x)))

Krok 2: Ex(P(x) ^ Ay(~R(x,y) v Ez(Q(y,z) ^ z != x)))
Krok 4: P(S1) ^ Ay(~R(S1, y) v (Q(y, F1(y)) ^ F1(y) != S1))
Krok 5: Ay(P(S1) ^ (~R(S1, y) v (Q(y, F1(y)) ^ F1(y) != S1)))
Krok 6: P(S1) ^ (~R(S1, y) v (Q(y, F1(y)) ^ F1(y) != S1))
Krok 7: P(S1) ^ (~R(S1, y) v Q(y, F1(y))) ^ (~R(S1,y) v F1(y) != S1)
Krok 8: P(S1), ~R(S1, y) v Q(y, F1(y)), ~R(S1, y) v F1(y) != S1

Niektóre pliszki chwalą jakiś cudzy ogonek

> Ex(P(x) ^ Ey(R(x,y) ^ Ez(Q(y,z) ^ z != x)))

Krok 4: P(S1) ^ R(S1, S2) ^ Q(S2, S3) ^ S3 != S1
Krok 8: P(S1), R(S1, S2), Q(S2, S3), S3 != S1

### Podstawienie i unifikacja

- Przykład: 
  - prawdą jest, że A(x) => B(x) oraz A(Pliszka)
  - wynika z tego, że B(Pliszka)
  - ale niekoniecznie B(x)

- W ogólności interesuje nas taka sytuacja:
  - zestawiamy dwie formuły 
  - w obu występuje ten sam predykat
  - poszukujemy postawień zmiennych takich, że:
    - formuły pozostają jak najmniej uszczegółowione
    - wskazany predykat staje się taki sam w obu formułach

#### Podstawienie

__*Podstawieniem*__ nazywa się przypisanie termu do zmiennej. Jeśli przez ð oznaczymy podstawienie ð = { x*1*/t*1*, ..., x*n*/t*n* } to zapis P[ð] = Q będzie oznaczać, że formuła Q powstaje przez zastąpienie każdej zmiennej x*i* w formule P przez term t*i*. Na przykład:

- P(x)[ð] = P(A), ð = {x/A}
- P(x)[ð] = P(F(y)), ð = {x/F(y)}

#### Unifikacja

__*Unifikatorem*__ pary formuł P i Q nazywa się para podstawień ð, ð` doprowadzająca P i Q do wspólnej postaci, czyli spełniająca warunek P[ð] = Q[ð`]

Przykłady:
	P(A,x) <-> P(y,B), ð={x/B}, ð`={y/A}, P(A,B)
P(x,A,F(x)) <-> P(B,y,z), ð={x/B}, ð`={y/A, z/F(B)}, P(B,A,F(B))

Jeżeli dla danej pary formuł udaje się znaleźć unifikator, to znaczy, że są one unifikowalne

#### Wnioskowanie przez rezolucję i zaprzeczenie

1. Rezolucja

- (A v C) ^ (~C v B) => A v B
- (A v C) ^ ~C => A
- C ^ ~C => F

Przykłady:
- (A v B v C) ^ (~A v D v E) => (B v C v D v E)
- (A v B) ^ (A v ~B v C) => (A v C)
- (A v B) ^ (~A v ~B) => (B v ~B) = T
- (A v B v C) ^ (~A v ~B v D) => (B v ~B v C v D) = T

2. Rezolucja w logice predykatów

__*Rezolucja*__ w logice predykatów polega na zastosowaniu następującej implikacji:

(K*1* v A) ^ (~A` v K*2*) => (K*1*[ð] v K*2*[ð`]), gdzie K*1* i K*2* mogą być klauzulami, literałami lub są puste, A oraz A` są unifikowalnymi atomami dla których ð i ð` stanowią najbardziej ogólny unifikator

Dalsze przykłady rezolucji:
- (A(y, F(x)) v B(x,y)) + (~B(x,N) v C(F(x))) -> (A(N,F(x)) v C(F(x)))
- (A(y, F(x)) v B(x,y)) + (~B(N,x) v C(F(x))) -> (A(y, F(N)) v C(F(y)))
- (A(x) v B(F(x,N))) + (~B(F(M,x)) v C(x)) -> (A(M) v C(N))

3. Zaprzeczenie

Jeśli w zbiorze klauzul znalazła się para postaci C oraz ~C, oznacza to, że wiedza jest sprzeczna i w ten sposób zdanie A jest udowodnione. Mamy bowiem wiedzę ogólną B, która jest prawdziwa, ale B ^ ~A = F, co oznacza, że ~A jest fałszywe, czyli A jest prawdziwe.

Algorytm dowodzący formuły A
1. Dodaj do bazy wiedzy ~A
2. Sprowadź bazę wiedzy do postaci koniunkcji klauzul
3. Dodawaj do zbioru klauzul kolejne przy użyciu rezolucji, dopóki:
   1. Daje się znaleźć pary istniejących klauzul, które tworzą nowe klauzule
   2. Wśród klauzul nie ma dwóch takich, że (i) pierwsza z nich jest atomem C, (ii) druga jest zanegowanym atomem ~C`, (iii) atomy C i C` są unifikowalne
4. Jeśli następuje wyjście z pętli na skutek niespełnienia warunku 3.1, oznacza to, że dane są niewystarczające do udowodnienia A. Jeśli wyjście z pętli następuje na skutek niespełnienia warunku 3.2 (udało się znaleźć takie C oraz ~C`), A jest prawdziwe

- Zdania proste stosowalne do danego uniwersum sytuacji:
  - A*1* = "Romek odwiedza Tomka"
  - A*2* = "Edyta odwiedza Tomka"
  - A*3* = "Tomek imprezuje"
  - A*4* = "Tomek rozwija się kulturalnie"
  - A*5* = "Następnego dnia Tomek choruje"

- Wiedza ogólna:
  - A*1* ^ ~A*2* => A*3*
  - A*2* => A*4*
  - A*3* <=> ~A*4*
  - A*3* => A*5*
  - A*4* => ~A*5*

- Fakty obserwowalne:
  - A*5*

- Fakty nieobserwowalne, o które pytamy:
  - ~A*2*

- Rozwiązanie:
  1. Dodajemy A*2* zamiast ~A*2*
  2. Klauzule
     - K*1* = ~A*1* v A*2* v A*3*
     - K*2* = ~A*2* v A*4*
     - K*3* = ~A*3* v ~A*4*
     - K*4* = A*3* v A*4*
     - K*5* = ~A*3* v A*5*
     - K*6* = ~A*4* v ~A*5*
     - K*7* = A*5*
     - K*8* = A*2*
  3. Kolejne klauzule:
     - K*8* ^ K*2* => K*9* = A*4*
     - K*7* ^ K*6* => K*10* = ~A*4*
     - K*9* ^ K*10* => K*11* = F cnd.
