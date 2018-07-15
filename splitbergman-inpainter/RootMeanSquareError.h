#pragma once
#include "stdafx.h"
#include "MeanSquareError.h"
#include <cmath>

double RootMeanSquareError(Mat input, Mat refererence) {
	return sqrt(MeanSquareError(input, refererence));
}