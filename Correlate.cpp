#include "Correlate.h"
#include <algorithm>
#include <iostream>

using namespace std;

bool operation(Data first, Data second) {
	return (first.Coords[0] < second.Coords[0]) ||
		((first.Coords[0] == second.Coords[0]) && (first.Coords[2] < second.Coords[2])) ||
		((first.Coords[0] == second.Coords[0]) && (first.Coords[2] == second.Coords[2]) && (first.Coords[1] > second.Coords[1]));
}

bool operation2(CorreInfor first, CorreInfor second) {
	return (first.Cri > second.Cri);
}

void Correlate(vector <Data> &TempInput, vector <Data> &TempGeoInput, vector <CorreInfor> &Correlation) {
	sort(TempInput.begin(), TempInput.end(), operation);
	sort(TempGeoInput.begin(), TempGeoInput.end(), operation);
	
	/*
	for (int i = 0; i < 1000; i++) {
		cout << TempInput[i].Coords[0] << " " << TempInput[i].Coords[1] << " " << TempInput[i].Coords[2] << endl;
	}
	cout << "-------------" << endl;
	
	for (int i = 0; i < 100; i++) {
		cout << TempGeoInput[i].Coords[0] << " " << TempGeoInput[i].Coords[1] << " " << TempGeoInput[i].Coords[2] << endl;
	}
	cout << TempInput.size() << endl;
	*/

	for (size_t i = 1; i < TempInput.size()-1; ++i) {
		if ((TempInput[i].Coords[0] == TempInput[i - 1].Coords[0] && TempInput[i].Coords[1] != TempInput[i - 1].Coords[1] && TempInput[i].Coords[2] != TempInput[i - 1].Coords[2]) ||
			(TempInput[i].Coords[0] != TempInput[i - 1].Coords[0] && TempInput[i].Coords[1] != TempInput[i - 1].Coords[1] && TempInput[i].Coords[2] != TempInput[i - 1].Coords[2])){
			CorreInfor temp;
			temp.Cri = TempInput[i].Cri;
			temp.TempID.push_back(i);
			Correlation.push_back(temp);
		}
	}
	/*
	for (vector <CorreInfor>::iterator MapIter2 = Correlation.begin(); MapIter2 != Correlation.end(); ++MapIter2) {
		cout << (*MapIter2).Cri << " ";
		for (vector <int>::iterator ii = (*MapIter2).TempID.begin(); ii < (*MapIter2).TempID.end(); ++ii) {
			cout << *ii << " ";
		}
		cout << endl;
	}
	cout << Correlation.size() << endl;
	*/

	bool continueflag = false;
	vector <CorreInfor>::iterator MapIter = Correlation.begin();
	for (size_t g = 1; g < TempGeoInput.size()-1; ++g) {
		if (continueflag == true) {
			if (TempGeoInput[g].Coords[0] == TempGeoInput[g - 1].Coords[0] && TempGeoInput[g].Coords[1] == TempGeoInput[g - 1].Coords[1] && TempGeoInput[g].Coords[2] == TempGeoInput[g - 1].Coords[2]) {
				(*MapIter).TempID.push_back(g);
			}
			else {
				continueflag = false;
				++MapIter;
			}
		}
		else {
			if ((TempGeoInput[g].Coords[0] != TempGeoInput[g - 1].Coords[0] && TempGeoInput[g].Coords[1] != TempGeoInput[g - 1].Coords[1] && TempGeoInput[g].Coords[2] != TempGeoInput[g - 1].Coords[2])||
				(TempGeoInput[g].Coords[0] == TempGeoInput[g - 1].Coords[0] && TempGeoInput[g].Coords[1] != TempGeoInput[g - 1].Coords[1] && TempGeoInput[g].Coords[2] != TempGeoInput[g - 1].Coords[2])) {
				(*MapIter).TempID.push_back(g);
				continueflag = true;
			}
		}
	}
	
	/*
	cout << "test------------------------" << endl;
	
	for (vector <CorreInfor>::iterator MapIter2 = Correlation.begin(); MapIter2 != Correlation.end(); ++MapIter2) {
		cout << (*MapIter2).Cri << " ";
		for (vector <int>::iterator ii = (*MapIter2).TempID.begin()+1; ii < (*MapIter2).TempID.end(); ++ii) {
			cout << TempGeoInput[*ii].Coords[1] << " ";
			// cout << *ii << " ";
		}
		cout << endl;
	}
	
	sort(Correlation.begin(), Correlation.end(), operation2);
	for (size_t i = 0; i < 5; ++i) {
		cout << Correlation[i].Cri << endl;
	}
	*/
}