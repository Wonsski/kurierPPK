# Kurier - projekt PPK

Polecenie: <br>
Kurier ma za zadanie zawieść towar do klientów w różnych lokalizacjach i powrócić do miejsca, z którego wyjechał. Kurier musi odwiedzić każdego klienta raz i tylko raz. Należy znaleźć zamkniętą najkrótszą drogę, która umożliwia odwiedzenie wszystkich klientów. W pliku wejściowym zapisane są długości dróg pomiędzy miastami. Drogi zapisane są w następujący sposób:
<br>(\<klient A\> - \<klient B\> : <odległość>) </br>
Niektóre drogi nie są symetryczne, tzn. jest pewna różnica między drogą tam a z powrotem. Zapis (\<klient C\> -> \<klient D\> : \<odległość CD\>),
oznacza długość drogi jednokierunkowej od klienta C do klienta D. Poszczególne drogi są rozdzielone przecinkami. Nie jest podana liczba dróg.
<br>
Jeżeli nie jest możliwe wyznaczenie drogi, program zgłasza odpowiedni komunikat. Przykładowy plik wejściowy:
```
(1 - 2 : 4.5), 
(4 -> 3: 4.5),
(4 - 2: 0.4)
```
W pliku wynikowym należy zapisać drogę kuriera (kolejność odwiedzania klientów i długość drogi).
Program uruchamiany jest z linii poleceń z potrzebnymi przełącznikami, natomiast uruchomienie programu bez parametrów powoduje wypisanie krótkiej instrukcji.
<br><br>
Autor: Radosław Rajda
