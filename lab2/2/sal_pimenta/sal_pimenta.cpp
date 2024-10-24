#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

void add_salt_pepper_noise(Mat &srcArr, float pa, float pb )
{    
	RNG rng; // rand number generator
    int amount1=srcArr.rows*srcArr.cols*pa;
    int amount2=srcArr.rows*srcArr.cols*pb;
    for(int counter=0; counter<amount1; ++counter)
    {
     srcArr.at<uchar>(rng.uniform( 0,srcArr.rows), rng.uniform(0, srcArr.cols)) =0;

    }
     for (int counter=0; counter<amount2; ++counter)
     {
     srcArr.at<uchar>(rng.uniform(0,srcArr.rows), rng.uniform(0,srcArr.cols)) = 255;
     }
}

int main(int argc, char* argv[]) {
	Mat srcArr;
		
	if (argc <= 1) {
		srcArr = imread("image.jpg");
	} else if (argc >= 2) {
		srcArr = imread(argv[1]);
	}
	
	cvtColor(srcArr, srcArr, COLOR_RGB2GRAY, 1);
	
	float pa = 0.02;
	float pb = 0.02;
	
	add_salt_pepper_noise(srcArr, pa, pb);
	
	imwrite("salt_pepper_noise_image.jpg", srcArr);
	
	printf("\nFiltro sal e pimenta aplicado na imagem!");
	printf("\nImagem salva\n\n");
}
