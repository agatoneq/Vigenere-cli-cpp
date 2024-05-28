#include <iostream>
#include <string>
#include "vigenere.h"

using namespace::std;

int main(int argc, char** argv)
{
	Ustawienia ustawienia;
	if (!czytajUstawienia(argc, argv, ustawienia))
	{
		pomoc(argv[0]);
		return 1;
	}
	
	if (ustawienia.tryb == Flaga::kodowanie || ustawienia.tryb == Flaga::dekodowanie)
	{
		string klucz1 = pobierzZKlucza(ustawienia);
		przerobPlik(ustawienia, klucz1);
	}

	else if (ustawienia.tryb == Flaga::lamanie)
	{
		string zaszyfrowany = pobierzZPliku(ustawienia);
		string klucz2 = odgadnijKlucz(zaszyfrowany, rozmiarKlucza(zaszyfrowany));
		cout << "Tekst zostal odszyfrowany kluczem: " << klucz2 << endl;
		przerobPlik(ustawienia, klucz2);
	}

	else
	{
		cerr << "Nie podano trybu lub dany tryb nie jest obslugiwany. Nalezy podac jeden z ponizszych: " << endl;
		cerr << "Dla szyfrowania: --en" << endl << "Dla deszyfrowania: --de" << endl << "Dla lamania: --br" << endl;
	}
}