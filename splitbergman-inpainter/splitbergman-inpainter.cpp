// splitbergman-inpainter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SplitbergmanSolver.h"


int main()
{
	//Variable Configuration
	double lambda_value = 750;
	double theta = 20;
	double tolerant = 1e-3;
	int max_iteration = 10000;	

	Mat to_inpaint_uint8 = imread("../images/256x256/case2_toinpaint.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat inpaint_domain_uint8 = imread("../images/256x256/case2_inpaintdomain.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat toinpaint_image;
	Mat inpaint_domain;
	Mat lambda;
	inpaint_domain_uint8 = inpaint_domain_uint8 < 1;
	to_inpaint_uint8.convertTo(toinpaint_image, CV_64F);
	inpaint_domain_uint8.convertTo(inpaint_domain, CV_64F);
	inpaint_domain = inpaint_domain / 255;
	lambda = inpaint_domain * lambda_value;
	toinpaint_image = toinpaint_image / 255;
	//cv::Mat inpaintedImage;
	//cv::inpaint(to_inpaint, inpaint_domain, inpaintedImage, 3, cv::INPAINT_TELEA);
	Mat inpainted_splitbergman_image = SplitBergmanSolver(toinpaint_image, lambda, theta, tolerant, max_iteration);
	imshow("TO_INPAINT", toinpaint_image);
	imshow("Inpainted Result", inpainted_splitbergman_image);
	waitKey(0);
    return 0;
}

