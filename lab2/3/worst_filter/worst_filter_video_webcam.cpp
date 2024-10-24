#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

int KERNEL_SIZE = 3;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Erro ao abrir a webcam" << endl;
        return -1;
    }

    Mat frame, dst;
    char window_name[] = "Webcam Filter";

    namedWindow(window_name, WINDOW_AUTOSIZE);

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            cout << "Erro ao capturar imagem da webcam" << endl;
            break;
        }

        bilateralFilter(frame, dst, KERNEL_SIZE, KERNEL_SIZE * 2, KERNEL_SIZE / 2);

        imshow(window_name, dst);

        char key = (char)waitKey(30);
        if (key == 's') {
            imwrite("worst_filter_image.jpg", dst);
            cout << "Imagem salva como worst_filter_image.jpg" << endl;
        } else if (key == 27) {
            break;
        }
    }

    cap.release();
    destroyAllWindows();
    return 0;
}