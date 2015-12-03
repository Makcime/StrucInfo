//---------------------------------------------------------------------------
#include "graph.h"
#include <iostream>
#include <iomanip>

//---------------------------------------------------------------------------
class TWork {
private:
	// TODO
	const TGraph& graph;
	const int begin;
	const int end;
	TPath tmpPath;
	TPath& bestPath;
	double bestLength;
	double& length;
	bool* visitedNodes;

	TWork(const TGraph& _graph, int& _begin, int& _end, TPath& _path, double& _length);
	~TWork();
	void DoWork();
	friend bool ComputeShortestPath(const TGraph& _graph, int _begin, int _end,
			TPath& _path, double& _length);
};
//---------------------------------------------------------------------------
// TODO definitions for TWork
TWork::TWork(const TGraph& _graph, int& _begin, int& _end, TPath& _path, double& _length):
	begin(_begin), graph(_graph), end(_end), bestPath(_path), length(_length), tmpPath(_path.LengthMax()){

	bestLength = INFINITY;
	tmpPath.Add(begin);
	visitedNodes = new bool [graph.Dim()];
	for (int i = 0; i < graph.Dim(); ++i)
		visitedNodes[i] = false;
	visitedNodes[begin] = true;

}

TWork::~TWork(){
}

void TWork::DoWork(){
	if (tmpPath.Last() == end){
		length = 0;
		for (int i = 0; i < tmpPath.Length() -1; ++i)
			length += graph[tmpPath[i]][tmpPath[i + 1]];
		if(length < bestLength){
			bestLength = length;
			bestPath = tmpPath;
		}
	}else {
		for (int i = 0; i < graph.Dim(); ++i){
			if((!visitedNodes[i]) && (graph[tmpPath.Last()][i] < INFINITY ) 
				&& graph[tmpPath.Last()][i] > 0){
				tmpPath.Add(i);
				visitedNodes[i] = true;
				DoWork();
				tmpPath.Remove();
				visitedNodes[i] = false;
			}
		}
	}
}
//---------------------------------------------------------------------------
// TODO definitions for TDest
TDest::TDest():
	pValues(0){
}

TDest::~TDest(){
	delete[] pValues;
}

double& TDest::operator[](int i){
	return pValues[i];
}

const double& TDest::operator[](int i) const{
	return pValues[i];
}

//---------------------------------------------------------------------------
// TODO definitions for TGraph
TGraph::TGraph(int dim) :
	dim(dim){
	ppDest = new TDest[dim];

	for (int i = 0; i < dim; ++i){
		ppDest[i].pValues = new double[dim];
		for (int j = 0; j < dim; ++j)
			ppDest[i].pValues[j] = (i!=j) ? INFINITY : 0;
	}
}

TGraph::~TGraph(){
	delete[] ppDest;
}

int TGraph::Dim() const{
	return dim;
}

TDest& TGraph::operator[](int i){
	return ppDest[i];
}

const TDest& TGraph::operator[](int i) const{
	return ppDest[i];
}

TGraph& TGraph::operator=(const TGraph& g){    
    if (this != &g){
        for (int i = 0; i < dim; ++i)
          for (int j = 0; j < dim; ++j)
            ppDest[i].pValues[j] = g.ppDest[i].pValues[j];
    }
		
	return *this;
}

//---------------------------------------------------------------------------
// TODO definitions for TPath
TPath::TPath(int _lengthMax):
length(0), lengthMax(_lengthMax){
	pNodes = new int[lengthMax];
}

TPath::TPath(const TPath& _path){ // constructeur de copie?
	lengthMax = _path.lengthMax;
	length = _path.length;
	pNodes = new int[lengthMax];

	for(int i = 0; i <lengthMax; i++)
		pNodes [i] = _path[i];
}

TPath::~TPath(){
	delete[] pNodes;
}

TPath& TPath::operator=(const TPath& _path){
    
    if( (this != &_path) ){
	    (*this).length = _path.length;
	    (*this).lengthMax = _path.lengthMax;
        if(_path.lengthMax != (*this).lengthMax){
            delete [] pNodes;
            pNodes = new int[_path.lengthMax];            
        }    
        for(int i=0; i<_path.length; i++)
            pNodes[i] = _path[i];
    }
	return *this;
}

int TPath::LengthMax() const{
	return this->lengthMax;
}

int TPath::Length() const{
	return this->length;
}

void TPath::Erase(){
	length = 0;
}

bool TPath::Add(int _s){
	if(length == lengthMax)
		return false;

	pNodes[length++] = _s;
	return true;
}

bool TPath::Remove(){
	if (length > 0){
		length--;
		return true;
	}
	return false;
}

int TPath::Last() const{
	return pNodes[length-1];
}

int& TPath::operator[](int _i){
	return this->pNodes[_i];
}

const int& TPath::operator[](int _i) const{
	return this->pNodes[_i];
}

//---------------------------------------------------------------------------
bool ComputeShortestPath(const TGraph& _graph, int _begin, int _end, TPath& _path,
                         double& _length) {
	if (_begin >= _graph.Dim() || _end >= _graph.Dim() || _path.LengthMax()
	        < _graph.Dim())
		return false;
	TWork t(_graph, _begin, _end, _path, _length);
	t.DoWork();
	_length = t.bestLength;
	if (_length < INFINITY)
		return true;
	else
		return false;
}

bool DijkstraShortestPath(const TGraph& _graph, int _start, int _end, TPath& _path,
	double& _length){

	bool* visitedNodes = new bool [_graph.Dim()];

	// pour chaque noeud, stocker la distance minimum pour l'atteindre (default = INFINITY)
	double*lengths	= new double [_graph.Dim()];

	// de quel noeud a t il été atteint par la pllus petite distance? (default = -1)
	int* froms	= new int [_graph.Dim()];

	for (int i = 0; i < _graph.Dim(); ++i){
		visitedNodes[i] = false;
		lengths[i] = INFINITY;
		froms[i] = -1;
	}

	//demarrer du start
	int currentNode = _start;
	int nextNode = _start;
	lengths[currentNode] = 0;
	
	while (!visitedNodes[_end]){
	// while (nextNode != _end){

		currentNode = nextNode;
		visitedNodes[currentNode] = true;

		int bestLength = INFINITY;

		// toucher tous les noeuds non visités dupuis le noeuds courant 
		for (int i = 0; i < _graph.Dim(); ++i)
			if (i != currentNode && !visitedNodes[i])
				if((_graph[currentNode][i] + lengths[currentNode]) < lengths[i]){
					froms[i] = currentNode;
					lengths[i] = _graph[currentNode][i] + lengths[currentNode];
				}

		// trouver le prochain noeuds 
		for (int i = 0; i < _graph.Dim(); ++i)
			if(!visitedNodes[i] && bestLength > lengths[i]){
				nextNode = i;
				bestLength = _graph[currentNode][i];
		}

		if (nextNode == currentNode) // break loop if no next node possible
			break;
	}

	_path.Erase();
	int i = _end;
	_length = lengths[i];
	TPath p(_graph.Dim());
	p.Add(i);

	if (_length < INFINITY){
		while(i != _start){
			i = froms[i];
			p.Add(i);
		}
		for (int j = p.Length(); j > 0; j--)
			_path.Add(p[j-1]);
	}

}
//---------------------------------------------------------------------------

