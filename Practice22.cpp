#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

#include <iomanip> // accuracy
#include <algorithm>

#include "Readin.h"
#include "Correlate.h"
#include "Update.h"
#include "Writing.h"

using namespace std;

int main() {
	int NumCyc;
	string NameFile;
	cout << "Please enter a number of cycles and the name of simulation file: ";
	cin >> NumCyc >> NameFile;
	string FullFile = NameFile + ".inp";

	ifstream infile(FullFile.c_str());
	if (!infile) {
		cout << "Please save your simulation file first" << endl;
		return -1;
	}

	vector <Data> AbaInput;
	vector <Data> TempAbaInput;
	vector <double> Dis;
	vector <Data> GeoInput;
	vector <Data> TempGeoInput;
	vector <CorreInfor> Correlation;

	for (int i = 0; i < NumCyc; i++) {
		cout << "AbaQus Readin in Progress" << endl;
		ReadAba(AbaInput, TempAbaInput,Dis, i,FullFile);
		cout << "GeoInfor Readin in Progress" << endl;
		ReadGeo(GeoInput, TempGeoInput);

		cout << "Correlation in Progress" << endl;
		Correlate(TempAbaInput, TempGeoInput, Correlation);

		cout << "Update in Progress" << endl;
		Update(AbaInput, GeoInput, TempAbaInput, TempGeoInput, Correlation);

		cout << "Output in Progress" << endl;
		Aba_Geo_Output(AbaInput, GeoInput);
	}
	/*
	for (int i = 0; i < 5; i++) {
		cout << setprecision(6) << AbaInput[i].ID << " " << AbaInput[i].Coords[0] << " " << AbaInput[i].Coords[1]
			<< " " << AbaInput[i].Coords[2] << " " << AbaInput[i].Cri << endl;
		cout << TempAbaInput[i].ID << " " << TempAbaInput[i].Coords[0] << " " << TempAbaInput[i].Coords[1]
			<< " " << TempAbaInput[i].Coords[2] << " " << TempAbaInput[i].Cri << endl;
	}
	
	for (int i = 0; i < 5; i++) {
		cout << setprecision(10) << GeoInput[i].ID << " " << GeoInput[i].Coords[0] << " " << GeoInput[i].Coords[1]
			<< " " << GeoInput[i].Coords[2] << " " << GeoInput[i].Cri << endl;
		cout << TempGeoInput[i].ID << " " << TempGeoInput[i].Coords[0] << " " << TempGeoInput[i].Coords[1]
			<< " " << TempGeoInput[i].Coords[2] << " " << TempGeoInput[i].Cri << endl;
	}
	*/
}
