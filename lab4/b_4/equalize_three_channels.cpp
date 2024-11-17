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

    Mat frame, equalizedImage;
    vector<Mat> channels;

    while (true) {
        cap >> frame;

        if (frame.empty()) {
            cerr << "Erro ao capturar o quadro!" << endl;
            break;
        }

        split(frame, channels);

        for (auto& channel : channels) {
            equalizeHist(channel, channel);
        }

        merge(channels, equalizedImage);

        imshow("Imagem Original", frame);
        imshow("Imagem Equalizada", equalizedImage);

        char key = (char) waitKey(1);
        if (key == 'q') {
            break;
        }
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
