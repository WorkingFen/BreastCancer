# Przeszukiwanie - optymalizacja

W przestrzeni X, istnieje funkcja _f_: która rzutuje przesztrzeń X na przestrzeń liczb rzeczywistych.

### Problem: Znaleźć x które maksymalizuje tę funkcję f

Dla przykładu:
- najlepsze parametry dla procesu technicznego lub ekonomicznego
- najlepszą strukturę procesu takiego jak wyżej
- najlepszą strukturę sieci telekomunikacyjnej

Jest kilka podejść do takiej optymalizacji.

1. Przegląd wszystkich możliwości
   > Dość masochistyczne
2. Metody przeglądowe z eliminacją
   - Na przykład algorytm podziału i oszacowań
3. Metody analityczne
   - Na przykład algorytm gradientów sprzężonych
4. Metody losowe
   - Algorytmy ewolucyjne, genetyczne
   - Symulowane wyżarzanie

# Idea algorytmów ewolucyjnych

Najmniejszym elementem rozważań jest osobnik, którego większa ilość tworzy populację. Tak jak to ma miejsce z kolonią mrówek.

Osobniki te jak żywe organizmy potrafią się reprodukować i wydawać nowe, **odmienne** potomstwo.
> Na tym polega w sumie działanie algorytmów ewolucyjnych

Reprodukcja przebiega za pomocą _krzyżowania_, a także _mutacji_.

> Maksymalizowana przez nas funkcja f, będzie określana funkcją przystosowania osobników

### Ogólny algorytm ewolucyjny

1. Wygeneruj populację początkową **P**
2. Reprodukuj z **P** zbiór osobników **R** 
   > Osobniki ze zbioru **P** powinny się krzyżować między sobą, tworząc zbiór **R**
3. Wybierz z sumy zbiorów **P** i **R** nową populację **P**
4. Jeśli nie jest spełniony warunek stop, wróć do punktu 2, w przeciwnym razie zwróć najlepszego osobnika z **P**

# [Algorytm (1+1)](https://github.com/WorkingFen/PSZTProject/issues/3) 

```
Nasze parametry:
- n -> wymiar X
  - dla przykładu: dla n=2 -> x należący do X = <a,b>
  - dla n=3 -> x należący do X = <a,b,c> itd.
- m -> ilość iteracji po której krok szumu mutuje
- d -> początkowy czynnik szumu, który musi spełniać warunek d>0
```

#### Kroki algorytmu:
1. Wygeneruj pierwszego osobnika _x_ należącego do **X**
2. Wygeneruj potomka _y_ = _x_ + dN(0,1) > y jest zaszumionym osobnikiem x
3. Wybierz _x_ = _f(x)_ > _f(y)_?_x_:_y_
4. Zaktualizuj _Fi_ jako proporcję wybranych y-ków w ciągu ostatnich _m_ iteracji
5. Co _m_-ty krok dokonaj mutacji:

   ```
   d = c1d dla Fi < 1/5
       c2d dla Fi > 1/5
       d   dla Fi = 1/5
   ```
6. Jeśli d < d*min*, zakończ przyjmując _x_ jako wynik; w przeciwnym razie wróć do punktu 2.

> Algorytm działa nieźle dla _m_=10, _c1_=0.82 oraz _c2_=1.2

## Zrównoleglony (1+1)

#### Kroki algorytmu:
1. Wybierz _xr_ należącego do **X**; będzie to wartość dostępna w sposób wyłączny dla wszystkich wątków algorytmu
2. W zbiorze niezależnych wątków realizuj tą samą procedurę:
   - Powtarzaj:
     - _x_ = wynik działania algorytmu (1+1)
     - jeżeli _f(x)_ > _f(xr)_, przypisz _xr_ = _x_
   dopóki nie wystąpił warunek stop
3. Zwróć _xr_

# [Algorytm (Mi + La)](https://github.com/WorkingFen/PSZTProject/issues/4)

```
Nasze parametry:
- n -> wymiar X
- Mi -> wielkość populacji początkowej P
- La -> wielkość populacji reprodukującej
```

#### Kroki algorytmu:
1. Wygeneruj **P** - populację Mi osobników postaci <x1,...,xn,d1,...,dn>
   > Osobników _x_ jest Mi, _d_ są to czynniki szumu dla odpowiedniego osobnika.A więc osobnikiem będzie <x1,d1>, <x2,d2>, ..., <xn,dn>.
2. Wylosuj z **P** La-elementową tymczasową populację **T**
   > Losujemy z **P** La osobników za pomocą wielokrotnego losowania ze zwracaniem, a więc jeden osobnik może powtórzyć się kilkukrotnie.
3. Reprodukuj z **T** La-elementową populację potomną **R** stosując krzyżowanie i mutację.
   > Każdy osobnik z **T** przechodzi przez reprodukowanie, stąd populacja La-elementowa **R**
   - Krzyżowanie:
     - Pierwszy sposób to uśrednianie: <&x, &d> = <(x*f*+x*m*)/2, (d*f*+d*m*)/2>
     - Drugi sposób to interpolacja: <&x, &d> = <ax*f* + (1-a)x*m*, ad*f* + (1-a)d*m*>, dla a ~ U(0,1)
     > Gdzie <&x,&d> poprawnie powinny być przedstawione jako średnie x i d (Literki z kreskami nad nimi)
   - Mutacja:
     - Natężenie rozmywania:
       d*i*__R__ = &d*i* exp(T'N(0,1)+TN*i*(0,1))
       T' = 1/V2n, T = 1/V(2Vn), n = dim(x) 
       > V w tym przedstawieniu to pierwiastek, a dim(x) dla przykładu: x = <a,b,c> -> n = 3
     - Rozwiązanie:
       x*i*__R__ = &x*i* + d*i*__R__N*i*(0,1)
       > Są to rozwiązania dla kolejnych osobników
4. Utwórz **P** jako Mi osobników wybranych z sumy zbiorów **P** i **R**
   - Pierwszy sposób wyboru to wybranie Mi najlepszych
     > Powoduje, że znajdujemy tylko maksimum lokalne
   - Drugi sposób to metoda koła ruletki: Osobniki są losowane z prawdopodobieństwem proporcjonalnym do g(f(x)), np. g(y)=exp(y)
   - Trzeci sposób to selekcja rankingowa; prawdopodobieństwo wyboru _x_ proporcjonalne do Mi+La+1-pozycja(x)
5. Jeśli jest spełniony warunek stopu, zwróć najlepszy element z **P** jako wynik; w przeciwnym razie wróć do punktu 2.


## Presja selekcyjna, eksploracja, eksploatacja
##### Używany algorytm (Mi+La)
> Algorytm (1+1) potrafi jedynie znaleźć maksimum lokalne
Presja selekcyjna to uwzględnienie jakie mamy preferencje względem lepiej przystosowanych, czy słabe <eksploracja>, czy silne <eksploatacja>

Eksploracja polega na przeszukiwaniu obszaru w celu znalezienia maksimum globalnego, a eksploatacja ma na celu znalezienie maksimum lokalnego. 
> Najlepszym sposobem na wykrycie maksimów, jest początkowe ustawienie presji selekcyjnej na słabą, w celu odkrycia kilku maksimów, po czym zmianę na silną presję selekcyjną, co sprawi, że osobniki szybciej odkryją maksima, wokół których krążyły podczas słabej presji selekcyjnej.

## Skalowanie argumentów funkcji przystosowania
##### Używany algorytm (1+1)

```
Reakcja chemiczna
- temperatura [20,80]
- stężenie katalizatora [10^-5, 10^-4]
- tempo optymalizacji temperatury takie jak stężenia
```

Czasami zdarza się, że obszar przeszukiwany jest "szpilą" czyli bardzo wąskim obszarem, po którym nasz algorytm ciężko się porusza.
Rozwiązaniem takiego problemu jest skalowanie wymiarów:

- przeszukiwanie przestrzeni: [20,80]x[10,100]
- drugi wymiar to stężenie x10^6

##### Używany algorytm (Mi+La)

```
Problem:
- Zbiór P: f(x1)=100, f(x2)=0, f(x3)=-100
- Zbiór R: f(x1)=3, f(x2)=2, f(x3)=1
- Prawdopodobieństwo z sumy zbiorów P i R proporcjonalne do exp(f(x))
```

Rozwiązaniem tego przykładu jest 
- Wyliczenie dla sumy zbiorów P i R:
  - &f -> średnie f(x)
  - &d -> odchylenie standardowe f(x)
- Zamiast f(x) do obliczenia prawdopodobieństwa używać (f(x)-&f)(k/&d), gdzie k~= 1 które reguluje presję selekcyjną. 
  > Słaba presja gdy k>1, silna gdy k<1

## Dobór podobnych
##### Używany algorytm (Mi+La)

> Potomstwo punktów z okolic różnych maksimów lokalnych jest słabe

Rozwiązaniem takiego problemu jest krzyżowanie podobnych

> Prawdopodobieństwo, że _x_ oraz _y_ tworzą potomka proporcjonalne do wzoru 1/((1+||x-y||^2)/c^2), gdzie c - przypuszczalna odległość między sąsiednimi maksimami

## Strategia elitarna
##### Używany algorytm (Mi+La)

Strategia elitarna polega na zagwarantowaniu, że najlepszy osobnik ma miejsce w kolejnym pokoleniu. Chodzi o to, że nie warto tracić najlepszego osobnika, jako, że jest duże prawdopodobieństwo, że będzie reproduktorem kolejnych osobników wysokiej jakości.

## Nowoczesne algorytmy ewolucyjne

Nowi członkowie populacji są losowani z tego samego rozkładu o dostosowującej się macierzy kowariancji.

##### Algorytm (1+La) z estymacją macierzy kowariancji
- Estymowana jest cała macierz kowariancji, a nie tylko d
- La potomków zamiast jednego
- Reszta zbliżona do algorytmu (1+1)

##### [CMA-ES](https://github.com/WorkingFen/PSZTProject/issues/5)

CMA-ES - covariance matrix adaptation evolution strategy
- W każdym pokoleniu Mi nowych osobników z tego samego rozkładu normalnego
- Algorytm manipuluje parametrami tego rozkładu

##### [Ewolucja różnicowa](https://github.com/WorkingFen/PSZTProject/issues/6)

- Selekcja metodą Mi najlepszych lub zbliżoną
- Nowe osobniki uzyskiwane ze starych formułami typu:
  - nowy = x*i* + k(x*j*-x*k*), gdzie x*i*, x*j*, x*k* to osobniki, a k to współczynnik
