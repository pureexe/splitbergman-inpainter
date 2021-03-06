// splitbergman-inpainter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SplitbergmanSolver.h"
#include "PeakSignalToNoiseRatio.h"
#include "RootMeanSquareError.h"
#include "string"


int main()
{
	//Variable Configuration
	double lambda_value = 250;
	double theta = 5;
	double tolerant = 1e-6;
	int max_iteration = 10000;

	std::string prefix = "../images/256x256/case";
	std::string result_prefix = "case";
	std::string case_number = "4";
	Mat to_inpaint_uint8 = imread(prefix+ case_number+"_toinpaint.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat inpaint_domain_uint8 = imread(prefix + case_number + "_inpaintdomain.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat original_uint8 = imread(prefix + case_number + "_original.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat toinpaint_image;
	Mat inpaint_domain;
	Mat original;
	Mat lambda;
	Mat inpaint_domain_reverse = inpaint_domain_uint8 < 1;
	to_inpaint_uint8.convertTo(toinpaint_image, CV_64F);
	inpaint_domain_reverse.convertTo(inpaint_domain, CV_64F);
	original_uint8.convertTo(original, CV_64F);
	original = original / 255;
	inpaint_domain = inpaint_domain / 255;
	lambda = inpaint_domain * lambda_value;
	toinpaint_image = toinpaint_image / 255;
	/* OpenCV_TELEA*/
	Mat inpainted_image_uint8, inpainted_image;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	inpaint(to_inpaint_uint8, inpaint_domain_uint8, inpainted_image_uint8, 3, cv::INPAINT_TELEA);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	inpainted_image_uint8.convertTo(inpainted_image,CV_64F);
	inpainted_image = inpainted_image / 255;
	printf("OpenCV_TELEA inpainted time: %.6f\n", (duration / 1000000.0));
	imshow("TELEA RESULT", inpainted_image);
	printf("RMSE: %.8f\n", RootMeanSquareError(inpainted_image, original));
	printf("PNSR: %.4f\n", PeakSignalToNoiseRatio(inpainted_image, original));
	imwrite(result_prefix + case_number + "_OpenCV_TELEA.png", inpainted_image_uint8);
	/*SplitBergman*/
	/*
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	Mat inpainted_splitbergman_image = SplitBergmanSolver(toinpaint_image, lambda, theta, tolerant, max_iteration);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	printf("Split bergman inpainted time: %.6f\n", (duration / 1000000.0));
	imshow("TO_INPAINT", toinpaint_image);
	imshow("Split-bergman Result", inpainted_splitbergman_image);
	printf("RMSE: %.8f\n",RootMeanSquareError(inpainted_splitbergman_image, original));
	printf("PNSR: %.4f\n", PeakSignalToNoiseRatio(inpainted_splitbergman_image, original));
	*/
	waitKey(0);
    return 0;
}

