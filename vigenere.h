/** vigenere.h @file*/
#ifndef VIGENERE_H
#define VIGENERE_H

/** 
* @brief Unia, ktora przechowuje mozliwe do wybrania tryby.
* Trybami, jakie mozna wybrac, sa: tryb szyfrowania, dekodowania lub lamania, istnieje takze jeden dodatkowy tryb inne.
*/
enum class Flaga
{ kodowanie, dekodowanie, lamanie, inne};

/** 
* @brief Struktura zawiera nazwy plikow: wejsciowego, wyjsciowego i pliku z kluczem oraz wybrany tryb.
* Automatycznie ustawiany jest dodaktowy tryb inne, przypisywany, gdy zaden inny nie zostanie wybrany.
*/
struct Ustawienia
{
	std::string sciezkaPlikuWejsciowego;
	std::string sciezkaPlikuWyjsciowego;
	std::string sciezkaPlikuZKluczem;
	Flaga tryb=Flaga::inne;
};

/**
* @brief Funkcja czyta parametry podane przez uzytkownika.
* 
* @param argc - liczba podanych wyrazow w wierszu polecen
* @param argv - tablica wpisanych wyrazow w wierszu polecen
* @param ustawienia - zmienna typu Ustawienia, gdzie wpisywane sa podawane nazwy plikow
* @return bool
*/
bool czytajUstawienia(int argc, char** argv, Ustawienia& ustawienia);

/**
* @brief Funkcja wypisuje komunikat o braku lub niepoprawnosci wpisanych parametrow.
*/
void pomoc(const std::string& nazwaProgramu);

/**
* @brief Funkcja wczytuje tekst z podanego pliku wejsciowego z kluczem.
* 
* @param ustawienia - zmienna przechowuje nazwe pliku wejsciowego z kluczem
* @return std::string
*/
std::string pobierzZKlucza(const Ustawienia& ustawienia);

/**
* @brief Funkcja odpowiada za wyslanie odpowiednich znakow do odpowiednich funkcji.
* Funkcja otwiera plik wejsciowy i pobiera z niego jeden znak, jesli nie jest on litera, zostaje od razu wczytany do pliku wyjsciowego. 
* W przeciwnym przypadku znak zostaje wyslany, razem z odpowiednim znakiem klucza do odpowiedniej funkcji: szyfrowania lub deszyfrowania, w zaleznosci od wybranego trybu. 
* 
* @param ustawienia - zmienna przechowuje nazwy plikow wejsciowego oraz wyjsciowego
* @param klucz - zmienna przechowuje napis sluzacy za klucz do szyfrowania lub deszyfrowania tekstu
* @return bool
*/
bool przerobPlik(const Ustawienia& ustawienia, std::string& klucz);


/** 
* @brief Funkcja znajduje pozycje w alfabecie przekazanego znaku, jest wykorzystywana w funkcji: szyfruj oraz deszyfruj.
*
* @param znak - przekazana litera
* @return int
*/
int pozycja_w_alfabecie(char znak);

/**
* @brief Funkcja znajduje wartosci liczbowe danych liter i szyfruje przekazany znak.
* 
* @param znak - przekazana litera tekstu jawnego
* @param znak_klucza - przekazana litera klucza
* @return char
*/
char szyfruj(char znak, char znak_klucza);

/** 
* @brief Funkcja znajduje wartosci liczbowe danych liter i deszyfruje przekazany znak.
*
* @param znak - przekazana litera tekstu zaszyfrowanego
* @param znak_klucza - przekazana litera klucza
* @return char
*/
char deszyfruj(char znak, char znak_klucza);


/** 
* @brief Funkcja wczytuje tekst z pliku wejsciowego i przygotowuje go do uzycia w funkcjach potrzebnych do zlamania zaszyfrowanego tekstu.
* Funkcja usuwa z wczytanego tekstu wszystkie znaki, ktore nie sa literami i wczytuje je do jednego napisu.
*
* @param ustawienia - zmienna przechowuje nazwe pliku wejsciowego
* @return std::string
*/
std::string pobierzZPliku(const Ustawienia& ustawienia);

/** 
* @brief Funkcja znajduje jaka dlugosc ma klucz wykorzystany do zaszyfrowania tekstu.
* Funkcja wykorzystuje metode Friedmana, sprawdzajac przy jakim przesunieciu tekstu liczba koincydencji jest najwieksza.
*
* @param zaszyfrowany - zaszyfrowany tekst, skladajacy sie jedynie z liter
* @return int
*/
int rozmiarKlucza(std::string& zaszyfrowany);

/** 
* @brief Funkcja odgaduje jakie slowo zostale uzyte jako klucz do zaszyfrowania tekstu.
* Funkcja wykorzystuje metode czestosci pojawiania sie liter w jezyku angielskim - zaklada, ze najczesciej powtarzajaca sie litera w tekscie to "e".
*
* @param zaszyfrowany - zaszyfrowany tekst, skladajacy sie jedynie z liter
* @param dlugosc_klucza - znaleziona dlugosc klucza szyfrujacego tekst
* @return std::string
*/
std::string odgadnijKlucz(std::string& zaszyfrowany, int dlugosc_klucza);

#endif