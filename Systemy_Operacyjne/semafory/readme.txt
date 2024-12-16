Wzajemne Wykluczanie dla Procesów: Semafory
-------------------------------------------

Zadanie wzajemnego wykluczania dla procesów zaimplementowane przy pomocy semaforów systemu UNIX. Czas operacji na wspólnym zasobie symulowany jest za pomocą funkcji sleep. W trakcie i po sekcji krytycznej program wypisuje komunikat. Podaje stan semafora i liczbę procesów pod nim czekających.
Po utworzeniu semofar jest inizjalizowany odpowiednią wartością.

Biblioteka prostych w użyciu funkcji do: tworzenia, uzyskiwania dostępu, inicjowania, sterowania, operowania i usuwania semaforów.

Program do powielania procesów realizuje wzajemne wykluczanie – w oparciu o funkcje fork i exec (nazwa programu do inicjowania procesów oraz liczba procesów przekazywana przez argumenty programu ,,powielacza”). Program ten tworzy i inicjuje semafor, a na ko´ncu go usuwa (kiedy wszystkie jego procesy potomne zakończą swoje działanie).