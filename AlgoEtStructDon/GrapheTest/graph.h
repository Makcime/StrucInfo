#ifndef GRAPH_H_
#define GRAPH_H_
//---------------------------------------------------------------------------
const double INFINITY = 10e100;
//---------------------------------------------------------------------------
class TGraph;
//---------------------------------------------------------------------------
class TDest { // ensembel des somments qu'on peu atteindre depuis un sommet, rangée dans la matrice associée au graph
	//TODO
public:
	TDest();
	~TDest();
	double& operator[](int _i);
	const double& operator[](int _i) const;

private:
	double* pValues;
	friend class TGraph;
};
//---------------------------------------------------------------------------
class TGraph {
public:
	// TODO
	TGraph(int dim);
	~TGraph();
	int Dim() const;
	TDest& operator[](int i); // nous renvoie une ref vers un "Dest" qu on peut modifier
	const TDest& operator[](int i) const; // nous renvoie une ref vers un "Dest" qu on peut modifier
    TGraph& operator=(const TGraph& g);

private:
	int dim;
	TDest* ppDest;
};
//---------------------------------------------------------------------------
class TPath { // un chemin est une liste de sommets
public:
	TPath(int _lengthMax);
	TPath(const TPath& _path); // constructeur de copie?
	~TPath();
	TPath& operator=(const TPath& _path);
	int LengthMax() const;
	int Length() const;
	void Erase();
	bool Add(int _s);
	bool Remove();
	int Last() 	const;
	int& operator[](int _i);
	const int& operator[](int _i) const;
private:
	int* pNodes;
	int lengthMax;
	int length;
};
//---------------------------------------------------------------------------
bool ComputeShortestPath(const TGraph& _graph, int _start, int _end, TPath& _path,
		double& _length);

bool DijkstraShortestPath(const TGraph& _graph, int _start, int _end, TPath& _path,
	double& _length);

//---------------------------------------------------------------------------
#endif /*GRAPH_H_*/
