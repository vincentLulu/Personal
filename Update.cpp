#include "Update.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void WearCheck(vector <double> &WearDepth) {
	// cout << WearDepth.size() << endl;
	for (size_t i = 1; i < WearDepth.size()-1; ++i) {
		if (WearDepth[i - 1] == 0 && WearDepth[i] != 0 && WearDepth[i] > WearDepth[i + 1]) {
			WearDepth[i] = 0.5 * WearDepth[i + 1];
			// cout << "a";
		}
		else {
			if (WearDepth[i] != 0 && WearDepth[i + 1] == 0 && WearDepth[i] > WearDepth[i - 1]) {
				WearDepth[i] = 0.5 * WearDepth[i - 1];
				// cout << "b";
			}
		}
	}
}

bool iszero(Data item) {
	return (item.Coords[1] == 0);
}

void Update(vector <Data> &AbaInput, vector <Data> &GeoInput, const vector <Data> TempAbaInput, const vector <Data> TempGeoInput, const vector <CorreInfor> Correlation) {
	vector <double> WearDepth;
	for (size_t i = 0; i < Correlation.size(); ++i) {
		if (Correlation[i].Cri > 272.9) {
			int startID = Correlation[i].TempID[0];
			int endID = startID + 1;
			while (TempAbaInput[endID].Cri > 272.9) {
				cout << TempAbaInput[endID].Cri << " ";
				++endID;
			}
			/*
			// test
			cout << Correlation[i].Cri << " ";
			cout << AbaInput[TempAbaInput[startID].ID-1].Coords[1] << " ";
			cout << AbaInput[TempAbaInput[endID].ID-1].Coords[1] << " ";
			cout << Correlation[i].Cri << " ";
			cout << TempAbaInput[endID].Cri << endl;
			
			cout << (Correlation[i].Cri - 272.9)*
				(AbaInput[TempAbaInput[startID].ID-1].Coords[1] - AbaInput[TempAbaInput[endID].ID-1].Coords[1]) /
				(Correlation[i].Cri - TempAbaInput[endID].Cri) << endl;

			cout << "0--------------" << endl;
			*/
			
			WearDepth.push_back((Correlation[i].Cri -272.9)*
				(AbaInput[TempAbaInput[startID].ID-1].Coords[1] - AbaInput[TempAbaInput[endID].ID-1].Coords[1])/
				(Correlation[i].Cri - TempAbaInput[endID].Cri));
		}
		else
			WearDepth.push_back(0.0);
	}
	// cout << WearDepth.size() << " " << endl;

	WearCheck(WearDepth);

	/*
	int mycount = count_if(AbaInput.begin(), AbaInput.end(), iszero);
	cout << mycount << endl;
	cout << "------------------------------" << endl;
	*/

	const int VerticalNum = Correlation[2].TempID[0] - Correlation[1].TempID[0];
	// cout << VerticalNum;
	for (size_t i = 0; i < WearDepth.size(); ++i) {
		if (WearDepth[i] != 0) {
			// Update AbaInput
			//cout << AbaInput[TempAbaInput[Correlation[i].TempID[0]].ID - 1].Coords[1] << " ";
			//cout << setprecision(6) << AbaInput[TempAbaInput[Correlation[i + 1].TempID[0] - 1].ID - 1].Coords[1] << endl;
			double ratio = (WearDepth[i])/(AbaInput[TempAbaInput[Correlation[i].TempID[0]].ID - 1].Coords[1]);
			int StartIndex = Correlation[i].TempID[0];
			for (size_t ii = 0; ii < VerticalNum; ++ii) {
				//cout << AbaInput[TempAbaInput[StartIndex+ii].ID - 1].Coords[1] << endl;
				AbaInput[TempAbaInput[StartIndex + ii].ID - 1].Coords[1] -= ratio* AbaInput[TempAbaInput[StartIndex + ii].ID - 1].Coords[1];
				//cout << AbaInput[TempAbaInput[StartIndex + ii].ID - 1].Coords[1] << endl;
			}

			
			// Update GeoInput
			
			for (size_t iii = 1; iii < Correlation[i].TempID.size(); ++iii) {
				//cout << TempGeoInput[Correlation[i].TempID[iii]].Coords[1] << " ";
				//cout << GeoInput[TempGeoInput[Correlation[i].TempID[iii]].ID].Coords[1] << " ";
				GeoInput[TempGeoInput[Correlation[i].TempID[iii]].ID].Coords[1] -= WearDepth[i];
				//cout << GeoInput[TempGeoInput[Correlation[i].TempID[iii]].ID].Coords[1] << " ";
			}
			// cout << "---------------" << endl;
			

		}
	}
}