# Algorytmy genetyczne

Algorytmy genetyczne różnią się od ewolucyjnych faktem, że to nie osobniki są krzyżowane, a ich kod tworzący. Algorytmy tego typu nie wykorzystywane są do znajdowania rozwiązań problemów optymalizacji tak jak ewolucyjne, tylko do modyfikacji działania programu [Na przykład do tworzenia muzyki]

## Algorytmy genetyczne założenia
1. Osobnik czyli _fenotyp_, kodowany jest przez pewien projekt czyli _genotyp_
2. Krzyżowane i mutowane są wyłącznie _genotypy_
3. Prawie wszystko da się zapisać przez sekwencję bitów, więc można je zmieniać

- Terminologia:
  - _fenotyp_ -> osobnik
  - _genotyp_ -> kod osobnika
  - _gen_ -> pojedynczy element kodu
  - _locus_ -> pozycja w genotypie
  - _chromosom_ -> zgrupowanie pozycji, na których geny kodują jakąś niezależną cechę fenotypu

## Ogólny algorytm genetyczny

1. Wygeneruj populację początkową genotypów **P**
   > Tak jak dla przykładu z muzyką, będą to stworzone przez człowieka utwory
2. Reprodukuj z par z **P** zbiór genotypów **R** przez zastosowanie krzyżowania a potem mutacji
3. Wybierz z sumy zbiorów **P** i **R** nową populację **P** tworząc z każdego genotypu osobnika i oceniając go
4. Jeśli nie jest spełniony warunek stopu, wróć do punktu 2, w przeciwnym razie zwróć najlepszy fenotyp dla osobnika

#### Krzyżowanie

1. Krzyżowanie jednopunktowe polega na zamianie tylko względem jednego _locus_ genotypu
2. Krzyżowanie kilkupunktowe polega na zamianie kilku _locus_ danego genotypu
3. Krzyżowanie równomierne polega na tym, że dane _locus_ zajmowane jest przez gen od losowego rodzica

#### Mutacja

1. Z zadanym prawdopodobieństwem p*m* podlega jej każdy gen w genotypie
2. p*m* powinno być małe; na przykłąd takie aby mutacji podlegał co 10-ty genotyp

### Jak rozróżnić algorytmy ewolucyjne od genetycznych?
> Problem komiwojażera

- Podejście ewolucyjne "klasyczne"
  - osobnikami są permutacje - na nich przeprowadzane są krzyżowania i mutacja
- Podejście genetyczne
  - permutacje są reprezentowane przez wektory binarne - na nich przeprowadzane są krzyżowanie i mutacja
