#include <iostream>
#include <iomanip>
#include "graph.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
TGraph* CreateGraph();
void ShowGraph(const TGraph& graph);
void ShowPath(const TGraph& graph, const TPath& path, double length);
bool FindNewPath(void);
//---------------------------------------------------------------------------
int main(int argc, char* argv[]) {
	//*
	TGraph* pGraph = CreateGraph();
	TPath path(pGraph->Dim());
	int start, end;
	double length;
	cout << endl;
	ShowGraph(*pGraph);
	
	do {
		cout << endl << "Sommet de départ et d'arrivée: ";
		cin >> start >> end;
		ComputeShortestPath(*pGraph, start, end, path, length);
		ShowPath(*pGraph, path, length);
	} while (FindNewPath());
	delete pGraph;
	//*/

	return 0;
}
//---------------------------------------------------------------------------
TGraph* CreateGraph() {
	int dim;
	cout << "Nombre de sommets dans le graphe? ";
	cin >> dim;
	TGraph* pGraph = new TGraph(dim);
	int n1, n2;
	double d;
	do {
		cout
				<< "Sommet de départ, sommet d'arrivée et longueur (<-1> pour finir): ";
		cin >> n1;
		if (n1 == -1)
			break;
		cin >> n2;
		if (n2 == -1)
			break;
		cin >> d;
		(*pGraph)[n1][n2] = d;
	} while (true);
	return pGraph;
}
//---------------------------------------------------------------------------
void ShowGraph(const TGraph& graph) {

	cout << "   |";
	for (int i = 0; i < graph.Dim(); ++i) {
		cout << "    " << "s" << i;
	}

	cout << endl << "---+";
	for (int i = 0; i < graph.Dim(); ++i) {
		cout << "------";
	}
	cout << endl;

	for (int i = 0; i < graph.Dim(); ++i) {
		cout << "s" << setw(1) << i << " |";
		for (int j = 0; j < graph.Dim(); ++j)
			if (graph[i][j] < INFINITY)
				cout << setw(6) << graph[i][j];
			else
				cout << setw(6) << ".";
		cout << endl;
	}
}
//---------------------------------------------------------------------------
void ShowPath(const TGraph& graph, const TPath& path, double length) {
	if (length == INFINITY)
		cout << "Aucun chemin n'a été trouvé!" << endl;
	else {
		cout << "Un chemin de longueur " << length << " a été trouvé: ";

			int s = 0;
		double len = 0.0;
		for (int i = 0, sPrec = path[0]; i < path.Length(); ++i) {
			s = path[i];
			len += graph[sPrec][s];
			if (i != 0)
				cout << " ,";
			cout << " " << s << " (" << len << ")";
			sPrec = s;
		}
		cout << endl;
	}
}
//---------------------------------------------------------------------------
bool FindNewPath(void) {
	char findAnother;
	do {
		cout << endl
				<< "Voulez-vous rechercher un autre chemin (<O>ui/<N>on) ? ";
		cin >> findAnother;
		findAnother = (char) toupper(findAnother);
	} while ((findAnother != 'O') && (findAnother != 'N'));
	return (findAnother == 'O');
}
//---------------------------------------------------------------------------


