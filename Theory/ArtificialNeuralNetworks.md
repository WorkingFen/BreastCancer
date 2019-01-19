# Sieci neuronowe

## Uczenie - usprawnienia

- Minibatch-e: Estymator gradientu = średnia z kilku kolejnych próbek
- Inercja: _Y_ należy do (0,1) zmiana wag = - _-B_ * gradient + _Y_ * poprzednia\_zmiana 
- Normalizacja pochodnych: dzielenie przez ich odchylenia standardowe
- Algorytm uczenia siec ADAM: połączenie wyżej wymienionych

## K-krotna walidacja krzyżowa

1. Sortujemy zbiór **T** w losowym porządku
2. Dzielimy **T** na **k** równych części:  __T*1*__ u...u __T*k*__ = **T**
3. Dla **i**=1,...,**k**:
   1. Uczymy sieć na zbiorze **T**\T*i*
   2. Rejestrujemy średnią stratę J*i*
4. Uczymy sieć na zbiorze T
5. Przyjmujemy średnią stratę tej sieci **J**~= (1/k) * Suma(od i do k) J*i*

## Przeuczenie

Jest to sytuacja, w której występuje znacznie większy błąd na zbiorze testowym aniżeli treningowym.

### Metody walki z przeuczeniem

#### Wczesne zatrzymanie uczenia

> Dane: zbiór treningowy i walidacyjny

Uczymy sieć na zbiorze treningowym dopóki strata w zbiorze walidacyjnym (a nie treningowym) spada

#### Regularyzacja

Stosujemy ~q(y) = q(y) + Alfa||Theta||^2 lub ~q(y) = q(y) + Alfa||Theta||

#### Odrzucanie (drop-out)

> Celem jest elastyczność i odporność na braki

- Prawdopodobieństwo **p** ustalone dla warstwy
- W trakcie uczenia dla danej próbki odrzucamy z prawdopodobieństwem **p** dane wejście
- W teście używane są wszystkie wejścia warstwy, ale wagi są przemnożone przez **1-p**
