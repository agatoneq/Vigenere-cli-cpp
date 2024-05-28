#include <iostream>
#include <string>
#include <fstream>
#include "funkcje.h"

using namespace::std;

bool czytajUstawienia(int argc, char** argv, Ustawienia& ustawienia)
{
	for (int i = 1; i < argc - 1; ++i)
	{
		string parametr = argv[i];

		if (parametr == "--en")
			ustawienia.kodowanie = argv[i];

		if (parametr == "--de")
			ustawienia.dekodowanie = argv[i];

		if (parametr == "--br")
			ustawienia.lamanie = argv[i];

		if (parametr == "-i")
			ustawienia.sciezkaDoPliku = argv[++i];

		else if (parametr == "-o")
			ustawienia.sciezkaZPliku = argv[++i];

		else if (parametr == "-k")
			ustawienia.sciezkaZKluczem = argv[++i];
	}
	return ustawienia.sciezkaDoPliku != "";
	return ustawienia.sciezkaZPliku != "";
	return ustawienia.sciezkaZKluczem != "";
}

void pomoc(const string& nazwaProgramu)
{
	cerr << "Programu uzywa sie nastepujaco: " << endl;
	cerr << nazwaProgramu << "--en(lub inna flaga z listy) -i <sciezka_do_pliku> -o <sciezka_z_pliku> -k <sciezka_z_kluczem>" << endl;
	cerr << "Lista flag: " << endl << "Dla szyfrowania: --en" << endl << "Dla deszyfrowania: --de" << endl << "Dla lamania: --br" << endl;
}

//bool czytajFlagi(const Ustawienia& ustawienia, string napis, string klucz)
//{
//	string szyfruj(napis, klucz);
//
//}

string wezZPliku(const Ustawienia& ustawienia, string sciezka)
{
	string rezultat = "";
	ifstream plik(sciezka);
	if (!plik)
	{
		cerr << "Wystapil blad. Nie mozna otworzyc pliku " << sciezka << "\n";
		//return "";
	}
	string linia;
	while (getline(plik, linia))
		if (linia != "")
		{
			rezultat += linia;
			cout << linia << "\n";
		}
	return rezultat;
}

bool zapiszDoPliku(const Ustawienia& ustawienia, string rezultat)
{
	ofstream plik(ustawienia.sciezkaZPliku);
	if (!plik)
	{
		cerr << "Wystapil blad." << endl;
		return false;
	}
	else
		plik << rezultat << " ";
	return true;
}

int pozycja_w_alfabecie(char znak)
{
	int licznik = 0;
	string alfabet = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < alfabet.size(); i++)
	{
		if (alfabet[i] == znak)
			licznik = i + 1;
	}
	return licznik;
}

string szyfruj(string napis, string klucz)
{
	string alfabet = "abcdefghijklmnopqrstuvwxyz";
	int wynik, wynik1, wynik2;
	string rezultat;

	for (int i = 0; i < napis.length(); i++)
	{
		wynik1 = pozycja_w_alfabecie(napis[i]);

		wynik2 = pozycja_w_alfabecie(klucz[i % klucz.length()]);

		wynik = wynik1 + wynik2 - 1;

		rezultat += alfabet[(wynik - 1) % alfabet.length()];

		//cout << endl << rezultat << endl;
	}
	return rezultat;
}

string deszyfruj(string napis, string klucz)
{
	string alfabet = "abcdefghijklmnopqrstuvwxyz";
	int wynik, wynik1, wynik2, wynik3;
	string rezultat;

	for (int i = 0; i < napis.length(); i++)
	{
		wynik = pozycja_w_alfabecie(napis[i]);

		wynik2 = pozycja_w_alfabecie(klucz[i % klucz.length()]);

		wynik1 = wynik - wynik2 + 1;

		wynik3 = alfabet.length() + wynik1;

		rezultat += alfabet[(wynik3 - 1) % alfabet.length()];
	}
	cout << endl << endl;
	return rezultat;
}

//int dlugosc_klucza(string napis)
//{
//	int x, rezultat;
//	for (int i = 0; i < napis.length(); i++)
//	{
//		if (napis[i]);
//	}
//	
//	string alfabet = "abcdefghijklmnopqrstuvwxyz";
//	return rezultat;
//}

//string lam(string napis)
//{
//	string alfabet = "abcdefghijklmnopqrstuvwxyz";
//	int wynik, wynik1, wynik2, wynik3;
//	string rezultat;
//
//	for (int i = 0; i < napis.length(); i++)
//	{
//		wynik = pozycja_w_alfabecie(napis[i]);
//
//		wynik2 = pozycja_w_alfabecie(klucz[i % klucz.length()]);
//
//		wynik1 = wynik - wynik2 + 1;
//
//		wynik3 = alfabet.length() + wynik1;
//
//		rezultat += alfabet[(wynik3 - 1) % alfabet.length()];
//	}
//	cout << endl << endl;
//	return rezultat;
//}