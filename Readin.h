#ifndef READIN
#define READIN

#include <string>
#include <vector>
using namespace std;

struct Data {
	int ID;
	vector <double> Coords;
	double Cri;
};

inline void ReadAba_RptLine(const string line, vector <Data> &Input, vector <Data> &TempInput);

inline void ReadAba_InpLine(const string line, vector <double> &Dis);

inline void ReadAba_InpLine(const string line, vector <Data> &Input, vector <Data> &TempInput);

void ReadAba(vector <Data> &Input, vector <Data> &TempInput, vector <double> Dis, const int i, const string file);

inline void ReadGeo_StlLine(const string line, const int i, vector <Data> &GeoInput, vector <Data> &TempGeoInput);

void ReadGeo(vector <Data> &GeoInput, vector <Data> &TempGeoInput);

#endif // !READIN
#pragma once
