// Affiche les 16 premières lignes du triangle de Pascal.
//---------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
const int NBR = 15;
//---------------------------------------------------------------------------
int main(int argc, char* argv[]) {
	long** c = new long*[NBR + 1];
	c[0] = new long[1];
	c[0][0] = 1L;
	for (int n = 1; n <= NBR; n++) {
		c[n] = new long[n + 1];
		c[n][0] = 1L;
		for (int m = 1; m < n; m++) {
			c[n][m] = c[n - 1][m - 1] + c[n - 1][m];
		}
		c[n][n] = 1L;
	}

	cout << endl << "      ";
	for (int m = 0; m <= NBR; m++) {
		cout << setw(5) << left << m;
	}
	cout << endl;

	for (int n = 0; n <= NBR; n++) {
		cout << endl << setw(2) << left << n << " -> ";
		for (int m = 0; m <= n; m++) {
			cout << setw(5) << left << c[n][m];
		}
		cout << endl;
	}

	for (int n = 0; n <= NBR; n++)
		delete[] c[n];
	delete[] c;
}
