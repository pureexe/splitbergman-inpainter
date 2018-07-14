#pragma once
#include "stdafx.h"

double Clamper(Mat data,int row,int col) {
	int height = data.rows;
	int width = data.cols;
	if (row < 0) {
		row = 0;
	}
	else if (row >= height) {
		row = height - 1;
	}
	if (col < 0) {
		col = 0;
	}
	else if (col >= width) {
		col = width - 1;
	}
	return data.at<double>(row, col);
}