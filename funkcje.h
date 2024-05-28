#ifndef NAGLOWEK_H
#define NAGLOWEK_H

enum class Flaga {};

struct Ustawienia
{
	std::string sciezkaDoPliku;
	std::string sciezkaZPliku;
	std::string sciezkaZKluczem;
	std::string kodowanie;
	std::string dekodowanie;
	std::string lamanie;
};

bool czytajUstawienia(int argc, char** argv, Ustawienia& ustawienia);
void pomoc(const std::string& nazwaProgramu);
std::string wezZPliku(const Ustawienia& ustawienia, std::string sciezka);
bool zapiszDoPliku(const Ustawienia& ustawienia, std::string tekst);
int pozycja_w_alfabecie(char znak);
std::string szyfruj(std::string napis, std::string klucz);
std::string deszyfruj(std::string napis, std::string klucz);
int dlugosc_klucza(std::string napis);
std::string lam(std::string napis);

#endif