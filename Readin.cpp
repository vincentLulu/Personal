#include "Readin.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

inline void ReadAba_RptLine(const string line, vector <Data> &Input, vector <Data> &TempInput) {
	istringstream in(line);
	string taken;
	in >> taken;
	in >> taken;
	for (int i = 0; i < Input.size(); i++) {
		in >> taken;
		Input[i].Cri = stod(taken);
		TempInput[i].Cri = stod(taken);
	}
}

inline void ReadAba_InpLine(const string line, vector <double> &Dis) {

	istringstream in(line);
	string taken;
	while (getline(in, taken, ',')) {
		Dis.push_back(stod(taken));
	}
}

inline void ReadAba_InpLine(const string line, vector <Data> &Input, vector <Data> &TempInput) {
	istringstream in(line);
	string taken;
	Data Temp;
	Data Temp2;
	getline(in, taken, ',');
	Temp.ID = stoi(taken);
	Temp2.ID = stoi(taken);
	while (getline(in, taken, ',')) {
		Temp.Coords.push_back(stod(taken));
		Temp2.Coords.push_back(round(stod(taken)*100.0) / 100.0);
	}
	Temp.Cri = 0.0;
	Temp.Cri = 0.0;
	Input.push_back(Temp);
	TempInput.push_back(Temp2);
}

void ReadAba(vector <Data> &Input, vector <Data> &TempInput, vector <double> Dis, const int i, const string file) {
	ifstream infile(file.c_str());
	string taken;
	string CoordStart("Node");
	string CoordEnd("Element");
	string DisStart("name=Up-1");
	bool CoordTriger = false;
	int PartID = 0;
	bool DisTriger = false;

	ifstream infile2("abaqus.rpt");
	string Cri;
	if (i % 2 == 0) {
		Cri = "MAX";
	}
	else
		Cri = "MIN";

	if (Input.empty()) {
		cout << "empty" << endl;
		while (getline(infile, taken)) {
			if (taken.find(CoordStart) != string::npos) {
				CoordTriger = true;
				++PartID;
				continue;
			}
			if (taken.find(CoordEnd) != string::npos) {
				CoordTriger = false;
			}
			if (taken.find(DisStart) != string::npos) {
				DisTriger = true;
				continue;
			}

			if (CoordTriger == true && PartID == 1) {
				ReadAba_InpLine(taken, Input, TempInput);
			}
			if (DisTriger == true) {
				ReadAba_InpLine(taken, Dis);
				DisTriger = false;
			}
		}
		while (getline(infile2, taken)) {
			if (taken.find(Cri) != string::npos) {
				ReadAba_RptLine(taken, Input, TempInput);
			}
		}
	}
	else {
		cout << "not empty" << endl;
		while (getline(infile, taken)) {
			if (taken.find(DisStart) != string::npos) {
				DisTriger = true;
				continue;
			}
			if (DisTriger == true) {
				Dis.clear();
				ReadAba_InpLine(taken, Dis);
				DisTriger = false;
			}
		}
		while (getline(infile2, taken)) {
			if (taken.find(Cri) != string::npos) {
				ReadAba_RptLine(taken, Input, TempInput);
			}
		}
	}
}


inline void ReadGeo_StlLine(const string line, const int i, vector <Data> &GeoInput, vector <Data> &TempGeoInput) {
	istringstream in(line);
	string taken;
	Data Temp;
	Data Temp2;
	in >> taken;
	Temp.ID = i;
	Temp2.ID = i;
	while (in >> taken) {
		Temp.Coords.push_back(stod(taken));
		Temp2.Coords.push_back(round(stod(taken)*100.0) / 100.0);
	}
	Temp.Cri = 0.0;
	Temp2.Cri = 0.0;
	GeoInput.push_back(Temp);
	TempGeoInput.push_back(Temp2);
}

void ReadGeo(vector <Data> &GeoInput, vector <Data> &TempGeoInput) {
	ifstream in("2-GP.stl");
	string taken;
	int i = 0;
	while (getline(in, taken)) {
		if (taken.find("vertex") != string::npos) {
			ReadGeo_StlLine(taken, i, GeoInput, TempGeoInput);
			++i;
		}
	}
}
