#ifndef UPDATE
#define UPDATE
#include "Readin.h"
#include "Correlate.h"
#include <vector>

using namespace std;

void WearCheck(vector <double> &WearDepth);


void Update(vector <Data> &AbaInput, vector <Data> &GeoInput, vector <Data> TempAbaInput, vector <Data> TempGeoInput, vector <CorreInfor> Correlation);
#endif // !UPDATE
#pragma once
