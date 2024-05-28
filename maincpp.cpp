#include <iostream>
#include <string>
#include <fstream>
#include "funkcje.h"

using namespace::std;

int main(int argc, char** argv)
{
	Ustawienia ustawienia;
	if (!czytajUstawienia(argc, argv, ustawienia))
	{
		pomoc(argv[0]);
		return 1;
	}

	string tekst = wezZPliku(ustawienia, ustawienia.sciezkaDoPliku);
	string klucz = wezZPliku(ustawienia, ustawienia.sciezkaZKluczem);

	//szyfruj
	zapiszDoPliku(ustawienia, szyfruj(tekst, klucz));

	//deszyfruj
	//zapiszDoPliku(ustawienia, deszyfruj(tekst, klucz));

	//lam
	//lam(napis);
}