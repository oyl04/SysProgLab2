# SysProgLab2
Теорія автоматів.

Скінчений автомат без виходів: A = <A, S, s0, F, f>, де

А = {a, b, c, …} – вхідний алфавіт,

S = {0, 1, 2, …} – множина станів,

s0 є S – початковий стан,

F є S – множина фінальних (заключних) станів,

f: S×A→S – функція переходів (автомат, знаходячись у певному стані та читаючи черговий символ зі вхідного слова переходить в інший стан згідно цієї функції доти, поки не закінчилось слово та поки існують відповідні переходи).

Функція переходів може бути не всюди визначеною та може бути багатозначною (у випадку недетермінованого автомату).

Слово e – слово нульової довжини (зарезервоване, ε). Таким чином, для будь-якого символу або слова w справедливо: we=ew=w. Якщо автомат допускає e-переходи, то використовується функція переходів вигляду S×(A∪{e})→S замість звичайної для задання такого автомату.

Автомат A сприймає (допускає, розпізнає) слово w, якщо, читаючи по одному символу з цього слова (за кожен такт роботи – зліва направо) і виконуючи переходи відповідно до функції переходів f, починаючи з стану s0, він потрапляє через |w| кроків у стан f∈F.

|w| = довжина слова w,

||Set|| = потужність множини Set, для скінчених – кількість її (унікальних) елементів.

 —
Автомат A на вході програми (та на виході, де потрібно) подається у вигляді текстового файлу наступної структури:

||A||

||S||

s0

||F||     fs1 є F 	…     fs||F|| є F    	// перелічені через проміжок кількість та всі стани з множини F

s   a   s’                            	  // всі такі трійки, що (s, a, s’) є f, через проміжок, по одній на рядок – до кінця файлу.

Розробити та реалізувати представлення скінченого автомата в пам`яті ЕОМ та виконати наступну задачу:

Реалізувати алгоритм мінімізації детермінованого скінченого автомата.
