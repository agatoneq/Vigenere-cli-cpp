#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "vigenere.h"

using namespace::std;

bool czytajUstawienia(int argc, char** argv, Ustawienia& ustawienia)
{
	for (int i = 1; i < argc - 1; ++i)
	{
		string parametr = argv[i];

		if (parametr == "--en")
			ustawienia.tryb = Flaga::kodowanie;

		if (parametr == "--de")
			ustawienia.tryb = Flaga::dekodowanie;

		if (parametr == "--br")
			ustawienia.tryb = Flaga::lamanie;

		if (parametr == "-i")
			ustawienia.sciezkaPlikuWejsciowego = argv[++i];

		else if (parametr == "-o")
			ustawienia.sciezkaPlikuWyjsciowego = argv[++i];

		else if (parametr == "-k")
			ustawienia.sciezkaPlikuZKluczem = argv[++i];
	}
	return ustawienia.sciezkaPlikuWejsciowego != "" && ustawienia.sciezkaPlikuWyjsciowego != "";
}

void pomoc(const string& nazwaProgramu)
{
	cerr << "Programu uzywa sie nastepujaco: " << endl;
	cerr << nazwaProgramu << " --en(lub inna flaga z listy) -i <plik_wejsciowy> -o <plik_wyjsciowy> -k <plik_z_kluczem>(prosze podawac jedynie w sytuacji wybrania trybu szyfrowania lub deszyfrowania, w innym przypadku zalaczony klucz bedzie ignorowany)" << endl << endl;
	cerr << "Lista flag: " << endl << "Dla szyfrowania: --en" << endl << "Dla deszyfrowania: --de" << endl << "Dla lamania: --br" << endl;
}

string pobierzZKlucza(const Ustawienia& ustawienia)
{
	string klucz = "";
	string linia;
	ifstream plik(ustawienia.sciezkaPlikuZKluczem);
	if (!plik)
	{
		cerr << "Wystapil blad. Nie mozna otworzyc pliku z kluczem " << ustawienia.sciezkaPlikuZKluczem << "\n";
		cerr << "Sprawdz czy podales przelacznik -k <plik_z_kluczem>"<<"\n";
	}
	while (getline(plik, linia))
		if (linia != "")
			klucz += linia;
	return klucz;
}

bool przerobPlik(const Ustawienia& ustawienia, string& klucz)
{
	ifstream plik1(ustawienia.sciezkaPlikuWejsciowego);
	if (!plik1)
	{
		cerr << "Wystapil blad. Nie mozna otworzyc pliku " << ustawienia.sciezkaPlikuWejsciowego << "\n";
		return false;
	}

	ofstream plik2(ustawienia.sciezkaPlikuWyjsciowego);
	if (!plik2)
	{
		cerr << "Wystapil blad. Nie mozna otworzyc pliku " << ustawienia.sciezkaPlikuWyjsciowego << endl;
		return false;
	}

	int licznik = 0;
	char znak;
	char znakKlucza = ' ';
	char zaszyfrowany_znak = ' ';

	while (plik1.get(znak))
	{
		for (int i = 0; i < klucz.length(); i++)
		{
			if (licznik % klucz.length() == i)
				znakKlucza = klucz[i];
		}

		if (isalpha(znak))
		{
			if(ustawienia.tryb == Flaga::kodowanie)
			zaszyfrowany_znak = szyfruj(znak, znakKlucza);
			else if (ustawienia.tryb == Flaga::dekodowanie|| ustawienia.tryb == Flaga::lamanie)
				zaszyfrowany_znak = deszyfruj(znak, znakKlucza);

			plik2 << zaszyfrowany_znak;
			licznik++;
		}
		else
			plik2 << znak;
	}
	cout << "Operacja przebiegla pomyslnie. Twoj tekst znajduje sie w pliku \"" << ustawienia.sciezkaPlikuWyjsciowego << "\"." << endl;
	return true;
}

int pozycja_w_alfabecie(char znak)
{
	int licznik = 0;
	string alfabet = "abcdefghijklmnopqrstuvwxyz";
	string ALFABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < alfabet.size(); i++)
	{
		if (alfabet[i] == znak|| ALFABET[i] == znak)
			licznik = i + 1;
	}
	return licznik;
}

char szyfruj(char znak, char znak_klucza)
{
	string alfabet = "abcdefghijklmnopqrstuvwxyz";
	string ALFABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int pozycja_znaku_tekstu, pozycja_znaku_klucza, pozycja_znaku_zaszyfrowanego;
	char zaszyfrowany_znak;

	pozycja_znaku_tekstu = pozycja_w_alfabecie(znak);
	pozycja_znaku_klucza = pozycja_w_alfabecie(znak_klucza);
	pozycja_znaku_zaszyfrowanego = pozycja_znaku_tekstu + pozycja_znaku_klucza - 1;
	if (isupper(znak))
		zaszyfrowany_znak = ALFABET[(pozycja_znaku_zaszyfrowanego - 1) % ALFABET.length()];
	else
		zaszyfrowany_znak = alfabet[(pozycja_znaku_zaszyfrowanego - 1) % alfabet.length()];

	return zaszyfrowany_znak;
}

char deszyfruj(char znak, char znak_klucza)
{
	string alfabet = "abcdefghijklmnopqrstuvwxyz";
	string ALFABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int pozycja_znaku_odszyfrowanego, pozycja_znaku_klucza, pozycja_znaku_zaszyfrowanego, pozycja_bez_bledu;
	char odszyfrowany_znak;
	
	pozycja_znaku_zaszyfrowanego = pozycja_w_alfabecie(znak);
	pozycja_znaku_klucza = pozycja_w_alfabecie(znak_klucza);
	pozycja_znaku_odszyfrowanego = pozycja_znaku_zaszyfrowanego - pozycja_znaku_klucza + 1;
	pozycja_bez_bledu = alfabet.length() + pozycja_znaku_odszyfrowanego;
	if (isupper(znak))
		odszyfrowany_znak = ALFABET[(pozycja_bez_bledu - 1) % ALFABET.length()];
	else
		odszyfrowany_znak = alfabet[(pozycja_bez_bledu - 1) % alfabet.length()];
	
	return odszyfrowany_znak;
}

string pobierzZPliku(const Ustawienia& ustawienia)
{
	string zaszyfrowany = "";
	char znak;
	ifstream plik(ustawienia.sciezkaPlikuWejsciowego);
	if (!plik)
		cerr << "Wystapil blad. Nie mozna otworzyc pliku " << ustawienia.sciezkaPlikuWejsciowego << "\n";
	else
	{
		while (plik >> znak)
		{
			if (isalpha(znak))
				zaszyfrowany.push_back(tolower(znak));
		}
	}
	return zaszyfrowany;
}

int rozmiarKlucza(string& zaszyfrowany)
{
	vector<int>koincydencje;
	int licz_koincydencje = 0;
	for (int przesuniecie = 1; przesuniecie < zaszyfrowany.length(); przesuniecie++)
	{
		licz_koincydencje = 0;
		for (int j = 0; j < zaszyfrowany.length(); j++)
		{
			if ((j - przesuniecie) >= 0)
			{
				if (zaszyfrowany[j] == zaszyfrowany[(j - przesuniecie)])
					licz_koincydencje++;
			}
		}
		koincydencje.push_back(licz_koincydencje);
	}

	int maxym = 0;
	int licz_maxym = 0;
	int suma_maxym = 0;
	for (int i = 0; i < koincydencje.size() - 1; i++)
	{
		if (koincydencje[i] > maxym)
		{
			maxym = koincydencje[i];
			licz_maxym++;
			suma_maxym += maxym;
		}
	}

	vector<int> najwieksze;
	int x = suma_maxym / licz_maxym;
	for (int i = 0; i < koincydencje.size() - 1; i++)
	{
		if (koincydencje[i] > x)
			najwieksze.push_back(koincydencje[i]);
	}
	
	vector<int>indexy;
	for (int i = 0; i < koincydencje.size() - 1; i++)
	{
		for (int j = 0; j < najwieksze.size(); j++)
		{
			if (koincydencje[i] == najwieksze[j])
			{
				indexy.push_back(i);
				break;
			}
		}
	}

	int minim;
	int dlugosc_klucza = 0;
	for (int i = indexy.size() - 1; i > 0; i--)
	{
		if (i == indexy.size() - 1)
			dlugosc_klucza = indexy[i];

		minim = indexy[i] - indexy[i - 1];
		if (minim < dlugosc_klucza)
			dlugosc_klucza = minim;
	}

	return dlugosc_klucza;
}

string odgadnijKlucz(string& zaszyfrowany, int dlugosc_klucza)
{
	string alfabet = "abcdefghijklmnopqrstuvwxyz";
	string klucz = "";
	string grupa;
	
	int licznik, licz, maxym, pozycja;
	char znak_klucza;

	for (int j = 0; j < dlugosc_klucza; j++)
	{
		grupa = "";
		for (int i = 0; i < zaszyfrowany.length(); i++)
		{
			if (i % dlugosc_klucza == j)
				grupa.push_back(zaszyfrowany[i]);
		}

		vector <double> czestosci_w_tekscie;
		for (char i = 'a'; i <= 'z'; i++)
		{
			licznik = 0;
			for (auto znak : grupa)
				if (znak == i)
					licznik++;
			czestosci_w_tekscie.push_back(licznik);
		}

		licz = 0;
		maxym = 0;
		for (int i = 0; i < czestosci_w_tekscie.size(); i++)
		{
			if (czestosci_w_tekscie[i] > maxym)
				maxym = czestosci_w_tekscie[i];

			if (maxym == czestosci_w_tekscie[i])
				licz = i;
		}

		pozycja = licz - 3;
		znak_klucza = alfabet[(pozycja + alfabet.length() - 1) % alfabet.length()];
		klucz.push_back(znak_klucza);
	}

	return klucz;
}