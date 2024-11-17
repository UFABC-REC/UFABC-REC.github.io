#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
 
using namespace std;
using namespace cv;

int main(int argc, char** argv) {	
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Erro ao abrir a webcam!" << endl;
        return -1;
    }   

    printf("\nAperte 'q' para sair!\n");

    Mat frame, gray, equalized, binary_no_eq, binary_eq;
    
    while (true) {
        cap >> frame;

        if (frame.empty()) {
            cerr << "Erro ao capturar o quadro!" << endl;
            break;
        }

        cvtColor(frame, gray, COLOR_BGR2GRAY);

        equalizeHist(gray, equalized);

        threshold(gray, binary_no_eq, 128, 255, THRESH_BINARY);

        threshold(equalized, binary_eq, 128, 255, THRESH_BINARY);

        imshow("Original (Cinza)", gray);
        imshow("Equalizado", equalized);
        imshow("Binário (Sem Equalização)", binary_no_eq);
        imshow("Binário (Com Equalização)", binary_eq);

        char key = (char)waitKey(1);
        if (key == 'q') {
            break;
        }
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
