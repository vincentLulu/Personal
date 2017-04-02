#include "Writing.h"
#include <fstream>
#include <sstream>

using namespace std;

bool GeoOperation(const string line, const Data Item) {
	istringstream in(line);
	string taken;
	in >> taken;
	in >> taken;
	in >> taken;
	if (stod(taken) == Item.Coords[1])
		return true;
	else
		return false;
}

bool AbaOperation(const string line, const Data Item) {
	istringstream in(line);
	string taken;
	vector <string> temp;
	while (getline(in, taken, ',')) {
		temp.push_back(taken);
	}
	if (stod(temp[2]) == Item.Coords[1])
		return true;
	else
		return false;
}

void Aba_Geo_Output(const vector <Data> AbaInput, const vector <Data> GeoInput) {
	ofstream AbaOut("regNew.inp");
	ofstream GeoOut("2-GPNew.stl");

	ifstream AbaIn("reg.inp");
	ifstream GeoIn("2-GP.stl");

	string line;
	int i = 0;
	while (getline(GeoIn, line)) {
		if (line.find("vertex") != string::npos) {
			if (GeoOperation(line, GeoInput[i]))
				GeoOut << line << endl;
			else
				GeoOut << "vertex " << GeoInput[i].Coords[0] << " " << GeoInput[i].Coords[1] << " " << GeoInput[i].Coords[2] << endl;
			++i;
		}
		else
			GeoOut << line << endl;
	}
	GeoIn.close();
	GeoOut.close();

	bool toWrite = false;
	int PartID = 0;
	i = 0;
	while (getline(AbaIn, line)) {
		if (line.find("Node")!=string::npos) {
			toWrite = true;
			++PartID;
			AbaOut << line << endl;
			continue;
		}
		if (line.find("Element") != string::npos) {
			toWrite = false;
			AbaOut << line << endl;
			continue;
		}
		if (toWrite && PartID == 1) {
			if (AbaOperation(line, AbaInput[i])) {
				AbaOut << line << endl;
				++i;
				continue;
			}
			else {
				AbaOut << AbaInput[i].ID << "," << AbaInput[i].Coords[0] << "," << AbaInput[i].Coords[1] << "," << AbaInput[i].Coords[2] << endl;
				++i;
				continue;
			}
		}
		AbaOut << line << endl;
	}
	AbaIn.close();
	AbaOut.close();
}