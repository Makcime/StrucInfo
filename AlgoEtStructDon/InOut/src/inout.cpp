#include <iostream>
#include <ctype.h>
#include <sstream>
#include <string.h>
#include <string>
#include <limits>
#include "inout.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
void Purge(void) {
	//  if (!cin) cin.clear();
	//  for (int i=cin.rdbuf()->in_avail();i>0;i--) cin.get();

	if (!cin)
		cin.clear();
	cin.putback(';');
	cin.ignore(std::numeric_limits<std::streamsize>::max(), ';');
}
//---------------------------------------------------------------------------
int Stop(void) {
	char stop;
	do {
		Purge();
		cout << endl << "Voulez-vous arrêter (<O>ui/<N>on) ? ";
		cin >> stop;
		stop = (char) toupper(stop);
	} while ((stop != 'O') && (stop != 'N'));
	return (stop == 'O');
}
//---------------------------------------------------------------------------
void Pause(void) {
	cout << endl << "Appuyer sur <Entrée> pour continuer ";
	Purge();
	cin.get();
}
//---------------------------------------------------------------------------
void ShowTitle(const char* title, char s, int lineLength) {
	int l = strlen(title);
	int nb = (lineLength - l) / 2;
	for (int i = 0; i < nb; ++i)
		cout << " ";
	cout << title << endl;
	for (int i = 0; i < nb; ++i)
		cout << " ";
	for (; l > 0; --l)
		cout << s;
	cout << endl;
}
//---------------------------------------------------------------------------
void Center(const char* message, int lineLength) {
	int l = strlen(message);
	int nb = (lineLength - l) / 2;
	for (int i = 0; i < nb; ++i)
		cout << " ";
	cout << message << endl;
}
//---------------------------------------------------------------------------
int ReadInt(const char* message, int min, int max) {
	int i;
	string buf;
	bool good;
	cout << message;
	do {
		good = false;
		Purge();
		cin >> buf;
		buf.append("\n");
		istringstream iss(buf);
		iss >> i;
		if (iss.get() == '\n')
			good = iss.good();
	} while (!good || i < min || i > max);
	return (i);
}
//---------------------------------------------------------------------------
double ReadDouble(const char* message, double min, double max) {
	double d;
	string buf;
	bool good;
	cout << message;
	do {
		good = false;
		Purge();
		cin >> buf;
		buf.append("\n");
		istringstream iss(buf);
		iss >> d;
		if (iss.get() == '\n')
			good = iss.good();
	} while (!good || d < min || d > max);
	return (d);
}
//---------------------------------------------------------------------------
char ReadChar(const char* message, const char* chars) {
	const char* p;
	char c;
	cout << message;
	do {
		Purge();
		cin.get(c);
		c = (char) toupper(c);
		for (p = chars; *p != '\0' && toupper(*p) != c; ++p)
			;
	} while (*p == '\0');
	return c;
}
//---------------------------------------------------------------------------
void Suspend(unsigned long d) {
	for (unsigned long i = 0; i < d; ++i)
		;
}
//---------------------------------------------------------------------------
char* ReadString(const char* message, int longMax) {
	char* tampon = new char[longMax + 1];
	Purge();
	cout << message;
	cin >> ws;
	cin.get(tampon, longMax + 1);
	int l = strlen(tampon);
	char* pStr = 0;
	try {
		pStr = new char[l + 1];
		strcpy(pStr, tampon);

	} catch (bad_alloc e) {
	}
	delete[] tampon;
	return pStr;
}
//---------------------------------------------------------------------------
char* ReadStringUp(const char* message, int longMax) {
	char* tampon = new char[longMax + 1];
	Purge();
	cout << message;
	cin >> ws;
	cin.get(tampon, longMax + 1);
	int l = strlen(tampon);
	char* pStr = 0;
	try {
		pStr = new char[l + 1];
		char *p1, *p2;
		for (p1 = pStr, p2 = tampon; *p2 != '\0'; ++p1, ++p2)
			*p1 = (char) toupper(*p2);
		*p1 = '\0';

	} catch(bad_alloc e) {
	}
	delete[] tampon;
	return pStr;
}
//---------------------------------------------------------------------------
