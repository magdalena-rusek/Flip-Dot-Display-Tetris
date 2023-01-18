# Flip-Dot-Display-Tetris

**WPROWADZENIE**

Celem projektu było napisanie gry „Tetris” w języku C++ oraz uruchomienie jej na mikrokontrolerze ARM (STM32), z wykorzystaniem wyświetlacza elektromagnetycznego („flip-dot display”). Projekt ten był realizowany w ramach przedmiotu uniwersyteckiego "Technika Mikroprocesorowa" oraz został jedną z prac nagrodzonych w konkursie na najciekawszy projekt. Krótki film z omówieniem: https://drive.google.com/file/d/1UwqR071ZhoM5006fCu-O8h5sH24qAT7j/view?usp=sharing.

**WYKORZYSTANE CZĘŚCI ELEKTRONICZNE**
- _mikrokontroler STM32_ - moduł z 32-bitowym mikrokontrolerem STM32F103C8T6 wyposażony w rdzeń ARM Cortex M3 
- _wyświetlacz elektromagnetyczny ("flip-dot display")_ - składa się z 9 rzędów i 28 kolumn dysków magnetycznych ("pikseli"), które z jednej strony są czarne, a z drugiej żółte. Sterowanie nimi wspomagane jest przez rejestry przesuwne MC74HC595AN
- _płytka stykowa_
- _przyciski, rezystory, przewody_
- _zasilacz AC/DC 24V_

**ZASADY GRY**

Gra rozpoczyna się na prostokątnej planszy, początkowo pustej, która jest ułożona krótszym bokiem w poziomie. Plansza ma wymiary 28 wierszy na 9 kolumn. W trakcie gry, pośrodku górnej krawędzi planszy, pojawiają się pojedynczo klocki złożone z czterech kwadratów. Klocki te przemieszczają się w kierunku dolnej krawędzi. Kiedy klocek opadnie na sam dół, zostaje unieruchomiony i pojawia się kolejny klocek u góry planszy. Gra trwa do momentu, w którym klocek nie będzie mógł pojawić się na planszy. Zadaniem gracza jest układanie klocków na planszy (poprzez obracanie i przesuwanie ich w poziomie) w taki sposób, aby
kwadraty składające się na nie utworzyły wiersz na całej szerokości prostokąta. W tej sytuacji wiersz ten zostaje usunięty, a pozostałe klocki opadają w kierunku dna, zapewniając większą przestrzeń dla następnych elementów. Po usunięciu określonej liczby wierszy, prędkość gry wzrasta.

Siedem podstawowych kształtów klocków:<br>
![image](https://user-images.githubusercontent.com/114939939/213165322-1e5e4e1a-7919-452a-b695-87ee0be8ffff.png)

**SCHEMATY**

- schemat połączeń:<br>
![image](https://user-images.githubusercontent.com/114939939/213163504-d5744b6f-9df9-4027-a882-5387a0b7e14a.png)

- schemat przycisków:<br>
![image](https://user-images.githubusercontent.com/114939939/213163642-50604bd7-adfa-440b-9205-3d32f799bb4c.png)

- przy podłączaniu wyświetlacza do płytki należy pamiętać, że masa znajduje się po innej stronie niż
reszta pinów:<br>
![image](https://user-images.githubusercontent.com/114939939/213165206-0c5143db-c095-4ea8-94b6-1189317049b1.png)

**STEROWANIE**

Grą można sterować za pomocą terminala lub przycisków zewnętrznych.<br>
Kroki w przypadku wykorzystania monitora szeregowego:
- otwórz Putty,
- ustaw „connection type” = „serial”, zmień nazwę portu i prędkość,
- „category”: connection -> SSH -> serial -> "flow control" = "None".

Przy tych ustawieniach można używać klawiszy „w”, „s”, „a”, „d” do sterowania grą.

**TETRIS**
- ekran powitalny:<br>
![image](https://user-images.githubusercontent.com/114939939/213168105-65e65001-b230-453d-9e66-adabd5f87b20.png)

- gra w akcji:<br>
![image](https://user-images.githubusercontent.com/114939939/213168172-9369992d-ae62-4316-92e1-852803f07dd3.png)


**AUTORZY**
- Dominika Worek
- Magdalena Rusek
