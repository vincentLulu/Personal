#ifndef CORRELATE
#define CORRELATE

#include "Readin.h"

struct CorreInfor {
	double Cri;
	vector <int> TempID;
};

bool operation(Data first, Data second);

void Correlate(vector <Data> &TempInput, vector <Data> &TempGeoInput, vector <CorreInfor> &Correlation);
#endif // !CORRELATE
#pragma once
