#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
 
using namespace cv;
 
Mat src, src_gray;
Mat dst, detected_edges;
 
int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";
 
static void CannyThreshold(int, void*)
{
	blur( src_gray, detected_edges, Size(3,3) );

	Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

	dst = Scalar::all(0);

	src.copyTo( dst, detected_edges);

	imshow( window_name, dst );
}
 
 
int main( int argc, char** argv )
{
	const char* filename = argc >= 2 ? argv[1] : "image.jpg";
	
	src = imread(samples::findFile(filename), IMREAD_COLOR);

	if( src.empty() )
	{
	std::cout << "Could not open or find the image!\n" << std::endl;
	std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
	return -1;
	}

	dst.create( src.size(), src.type() );

	cvtColor( src, src_gray, COLOR_BGR2GRAY );

	namedWindow( window_name, WINDOW_AUTOSIZE );

	createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
	
	std::cout << "\nPressione 's' para salvar uma imagem.\n";
	std::cout << "\nPressione 'k' para iniciar uma gravação e 'h' para encerrar.\n";
	std::cout << "\nPressione 'ESC' para sair.\n";
  
	VideoWriter videoWriter;
	bool isRecording = false;
	char key;
	while (true) {
		CannyThreshold(0, 0);
		
		key = waitKey(30);
		
		if (key == 's' || key == 'S') {
			imwrite("imagem_filtrada.png", dst);
			std::cout << "Imagem salva como 'imagem_filtrada.png'\n";
		} else if (key == 'k' || key == 'K') {
			if (!isRecording) {
				videoWriter.open("video.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), 10, dst.size());
				isRecording = true;
				std::cout << "\nIniciada gravação de vídeo...\n";
			}
		} else if (key == 'h' || key == 'H') {
			if (isRecording) {
				videoWriter.release();
				isRecording = false;
				std::cout << "\nGravação de vídeo finalizada, vídeo salvo como 'video.mp4'\n";
			}
		} else if (key == 27) {
			break;
		}
		
		if (isRecording) {
			videoWriter.write(dst);
		}
	}
	
	if (isRecording) {
		videoWriter.release();
	}

	return 0;
}
