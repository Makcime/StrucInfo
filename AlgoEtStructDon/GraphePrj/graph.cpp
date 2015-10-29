//---------------------------------------------------------------------------
#include "graph.h"
//---------------------------------------------------------------------------
class TWork {
private:
	// TODO
	double bestLength;
	TWork(const TGraph& _graph, int& _begin, int& _end, TPath& _path, double& _length);
	~TWork();
	void DoWork();
	friend bool ComputeShortestPath(const TGraph& _graph, int _begin, int _end,
			TPath& _path, double& _length);
};
//---------------------------------------------------------------------------
// TODO definitions for TDest
TDest::TDest(){

}

TDest::~TDest(){

}

int& TDest::operator[](int _i){

}

const int& TDest::operator[](int _i) const{

}

//---------------------------------------------------------------------------
// TODO definitions for TGraph
TGraph::TGraph(){

}

TGraph::TGraph(int dim){

}

TGraph::~TGraph(){

}

int TGraph::Dim() const{

}

TDest& TGraph::operator[](int i){

}

const TDest& TGraph::operator[](int i) const{

}

//---------------------------------------------------------------------------
// TODO definitions for TPath
TPath::TPath(int _lengthMax){

}

TPath::TPath(const TPath& _path){ // constructeur de copie{

}

TPath::~TPath(){

}

TPath& TPath::TPath::operator=(const TPath& _path){

}

int TPath::LengthMax() const{

}

int TPath::Length() const{

}

void TPath::Erase(){

}

bool TPath::Add(int _s){

}

bool TPath::Remove(){

}

int TPath::Last() const{

}

int& TPath::operator[](int _i){

}

const int& TPath::operator[](int _i) const{

}

//---------------------------------------------------------------------------
// TODO definitions for TWork
TWork::TWork(const TGraph& _graph, int& _begin, int& _end, TPath& _path, double& _length){
	bestLength = _length;
}
TWork::~TWork(){

}

void TWork::DoWork(){

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
//---------------------------------------------------------------------------

