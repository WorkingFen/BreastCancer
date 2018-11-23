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

# [Algorytm (1+1)](issues/3) 

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

# [Algorytm (Mi + La)](issues/4)

