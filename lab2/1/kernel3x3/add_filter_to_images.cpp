#include<iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int KERNEL_SIZE = 3;

Mat src; Mat dst;
char window_name[] = "Add filter to image";

int main(int argc, char** argv) {
	namedWindow(window_name, WINDOW_AUTOSIZE);
	
	const char* filename = argc >= 2 ? argv[1] : "image.jpg";
	
	src = imread(samples::findFile(filename), IMREAD_COLOR);
	
	if (src.empty()) {
		printf("Error opening image\n");
		printf("Usage: \n %s [image_name-- default image.jpg] \n", argv[0]);
		return EXIT_FAILURE;
	}
	
	// Clonando imagem para dst
	dst = src.clone();
	
	// Filtro de média
	blur(src, dst, Size(KERNEL_SIZE, KERNEL_SIZE), Point(-1, -1));
	string filter_name = "blur";
	string image_out_name = filter_name + "_image_kernel" + to_string(KERNEL_SIZE) + "x" + to_string(KERNEL_SIZE) + ".jpg";
	imwrite(image_out_name, dst);
	
	// Filtro gaussiano
	GaussianBlur(src, dst, Size(KERNEL_SIZE, KERNEL_SIZE), 0, 0);
	filter_name = "gaussian_blur";
	image_out_name = filter_name + "_image_kernel" + to_string(KERNEL_SIZE) + "x" + to_string(KERNEL_SIZE) + ".jpg";
	imwrite(image_out_name, dst);
	
	// Filtro de mediana
	medianBlur(src, dst, KERNEL_SIZE);
	filter_name = "median_blur";
	image_out_name = filter_name + "_image_kernel" + to_string(KERNEL_SIZE) + "x" + to_string(KERNEL_SIZE) + ".jpg";
	imwrite(image_out_name, dst);
	
	// Filtro bilateral
	bilateralFilter(src, dst, KERNEL_SIZE, KERNEL_SIZE * 2, KERNEL_SIZE / 2);
	filter_name = "bilateral_blur";
	image_out_name = filter_name + "_image_kernel" + to_string(KERNEL_SIZE) + "x" + to_string(KERNEL_SIZE) + ".jpg";
	imwrite(image_out_name, dst);

	printf("\nFiltros aplicados nas imagens");
	printf("\nImagens salvas!\n\n");

	return 0;
}
