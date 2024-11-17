#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
 
using namespace std;
using namespace cv;

Mat src; Mat dst;

void calculateAndDrawHistogram(const Mat& img, const string& windowName, const string& filename) {
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange[] = {range};
    bool uniform = true, accumulate = false;

    Mat hist;
    calcHist(&img, 1, 0, Mat(), hist, 1, &histSize, histRange, uniform, accumulate);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++) {
        line(histImage, 
             Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(hist.at<float>(i))),
             Scalar(255), 2, 8, 0);
    }
    imshow(windowName, histImage);
    imwrite(filename, histImage);
    printf("\nAperte qualquer tecla para continuar!\n");
    waitKey();
    destroyAllWindows();
}

int main(int argc, char** argv) {	
	const char* filename = argc >= 2 ? argv[1] : "image.jpg";
	src = imread(samples::findFile(filename), IMREAD_COLOR);
	if (src.empty()) {
		printf("Error opening image\n");
		printf("Usage: \n %s [image_name-- default image.jpg] \n", argv[0]);
		return EXIT_FAILURE;
	}

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    imwrite("before_eq_image.jpg", gray);

    imshow("Gray Image - Before Equalization", gray);
    calculateAndDrawHistogram(gray, "Histogram - Before Equalization", "before_eq_hist.jpg");

    Mat eq;
    equalizeHist(gray, eq);
    imwrite("after_eq_image.jpg", eq);

    imshow("Gray Image - After Equalization", eq);
    calculateAndDrawHistogram(eq, "Histogram - After Equalization", "after_eq_hist.jpg");

    return 0;
}