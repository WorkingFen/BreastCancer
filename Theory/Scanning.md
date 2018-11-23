# Przeszukiwanie

Do czego zastosować przeszukiwanie?
Na przykład do rozwiazywanie problemów takich jak poszukiwanie sekwencji operacji prowadzącej do celu, albo poszukiwanie układu stanowiącego rozwiązanie.

### Planowanie

Jest to optymalizacja sekwencji działań. W dzisiejszych czasach często poszukujemy jakichkolwiek sekwencji, lub najkrótszych/najmniej kosztownych.

## Model 

```
Ogólny model <S, P, s0, T, c> gdzie:
- S -> przestrzeń stanów
- P -> zbiór operatorów, które dają wyniki w przestrzeni stanów
- s0 -> stan początkowy, gdzie s0 należy do S
- T -> zbiór stanów terminalnych, gdzie T jest podzbiorem S
- c -> funkcja kosztu, która daje wynik w przestrzeni liczb rzeczywistych
```

Interesuje nas:
- Znalezienie jakiejkolwiek sekwencji P0,...,P*t-1*, takiej, że s*i+1*=P*i*(s*i*) oraz s*t* należy do **T**
- Znalezienie najkrótszej takiej sekwencji
- Znalezienie najmniej kosztownej takiej sekwencji, to jest minimalizującej. (t-1)E(i=0) c(s*i*, s*i+1*), gdzie E to znak sumy, (t-1) jest nad sumą, a (i=0) pod nią

### Problemy przykładowe

- Układanie kostki
- 3 misjonarzy + 3 ludożerców przeprawiających się przez rzekę 2-osobową łódką. W żadnej chwili na brzegu nie może być więcej ludożerców niż misjonarzy
- Problem n hetmanów: jak ustawić n hetmanów na szachownicy n/n aby żaden nie był atakowany przez żadnego innego
- Dwa pojemniki mają 5 oraz 7 litrów pojemności. Jak, zapełniając je do pełna, opróżniając i przelewając wodę między nimi odmierzyć 4 litry?
- Problem komiwojażera

## Grafy stanów

- Graf skierowany
- Węzły to stany -> _s_ należące do **S**
- Krawędzie to operatory -> _p_ należące do **P**
- i-ta warstwa grafu -> takie stany, że aby do nich dotrzeć z początkowego potrzeba i wystarcza _i_ operatorów
- Rozwijanie stanu -> znalezienie wszystkich stanów, które da się otrzymać z danego przez zastosowanie różnych operatorów

## Strategie nieinformowane

### Przeszukiwanie wszerz
0. Utwórz listę **A** stanów otwartych, pustą listę **Z** stanów zbadanych oraz wpisz _s0_ do **A**
1. Rozwiń pierwszy stan z **A** w sekwencję stanów; przesuń ten stan do **Z**; stany z sekwencji nieobecne w sumie zbiorów **A** i **Z** wpisz na _**koniec**_ **A**
2. Jeśli w **A** pojawił się stan terminalny - zakończ, w przeciwnym razie skocz do punktu 1.

### Przeszukiwanie w głąb
0. Utwórz listę **A** stanów otwartych, wpisz _s0_ do **A**
1. Rozwiń pierwszy stan z **A** w sekwencję stanów; stany z sekwencji nieobecne w **A** wpisz na _**Początek**_ **A**
2. Jeśli w **A** pojawił się stan terminalny - zakończ, w przeciwnym razie skocz do punktu 1

#### Wszerz vs w głąb - własności

- Wszerz znajduje najkrótsze rozwiązanie zużywając najmniej czasu, ale potrzebuje dużo pamięci
- W głąb potrzebuje mało pamięci, ale nie znajduje najlepszego rozwiązania jako pierwszego

### Przeszukiwanie w głąb z iteracyjnym pogłębianiem
0. Przypisz m=1
1. Przeszukaj w głąb do głębokości m
2. Przypisz m=m+1
3. Jeśli został znaleziony stan terminalny, zwróć rozwiązanie; w przeciwnym razie wróć do punktu 1.

#### Wszerz vs w głąb z iteracyjnym pogłębianiem

- Przeszukiwanie w głąb z iteracyjnym pogłębianiem nie potrzebuje tyle pamięci co przeszukiwanie wszerz
- Im częściej zdarzają się stany, do których można dotrzeć różnymi drogami, tym większą przewagę ma przeszukiwanie wszerz

### Przeszukiwanie dwukierunkowe

- Przeszukujemy wszerz od strony _s0_ oraz, poprzez operatory odwrotne, od strony **T**
- Szczęśliwy koniec: pojawienie się stanu, który jest na liście **A** procedry działającej w drugą stronę.

Cechy: Działa bardzo dobrze w przypadkach, w których **T** jest znane i małe, w innych przypadkach działa słabo

## Strategie minimalizujące koszt

### Pierwszy najtańszy
0. i=0, G*0*={_s0_}
1. Rozwiń z s*i* zbiór stanów P*i*
2. G*i+1* = suma zbiorów G*i* i P*i*-{_si_}
3. i=i+1
4. Wybierz s*i* jako najtańszy stan z G*i*
5. Jeśli s*i* jest terminalny - zakończ, w przeciwnym przypadku idź do punktu 1

## Strategie heurystyczne

### Pierwszy najlepszy
> h(s) - oszacowanie kosztu od stanu s do końca
0. i=0
1. Rozwiń stan s*i* w stany s*i,1*, s*i,2* itd.
2. Wybierz jako s*i+1* stan s*i,j* minimalizujący c(s*i*, s*i,j*)+h(s*i,j*)
3. i=i+1
4. Jeśli s*i* jest terminalny - zakończ, w przeciwnym razie przejdź do punktu 1

### A\*
> C(s) - koszt dotarcia do s, h(s) - dolne ograniczenie kosztu od stanu s do końca
0. i=0, G0={s0}
1. Rozwiń z s*i* zbiór stanów P*i*
2. G*i+1* = suma zbiorów G*i* i P*i* - {s*i*}
3. i=i+1
4. Wybierz s*i* jako stan z G*i* minimalizujący f(s) = C(s)+h(s)
5. Jeśli s*i* jest terminalny - zakończ, w przeciwnym przypadku idź do punktu 1.
> Własność: pierwsze znalezione rozwiązanie jest optymalne

##### Funkcja _h_

- Względnie łatwa do wyznaczenia
- Może stanowić rozwiązanie problemu uproszczonego
  - Przez zignorowanie pewnych ograniczeń
  - Świetnie, gdy problem uproszczony ma rozwiązanie analityczne
  - Może być wyznaczana poprzez rozwiązanie na bieżąco problemu uproszczonego

### IDA* (Iterative Deepening A\*)
> h(s) - dolne ograniczenie kosztu od stanu _s_ do końca; f(s) = C(s)+h(s)
0. Zainicjuj f*max*
1. Dokonaj przeszukania wgłąb bez rozwijania stanów dla których f(s) > f*max*
2. Jeśli znalazł się stan terminalny - zwróć go jako rozwiązanie
3. Powiększ f*max* i idź do punktu 1

#### Porównanie i rekomendacje

- Pierwszy najlepszy -> optymalność nie jest krytyczna a heurystyka oceniająca jest dobra
- A\* -> optymalność jest istotna a wymagania pamięciowe nie są ostre
- IDA\* -> przestrzeń stanów nie zmieści się w pamięci a heurystyka oceniająca jest kiepska
