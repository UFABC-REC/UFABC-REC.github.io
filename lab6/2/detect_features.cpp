#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/features2d.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        cout << "Não foi possível acessar a webcam!" << endl;
        return -1;
    }

    Ptr<ORB> detector = ORB::create();

    Mat frame, gray, img_keypoints;
    vector<KeyPoint> keypoints;

    while (true) {
        cap >> frame;

        if (frame.empty()) {
            cout << "Falha na captura do quadro!" << endl;
            break;
        }

        cvtColor(frame, gray, COLOR_BGR2GRAY);

        detector->detect(gray, keypoints);

        drawKeypoints(frame, keypoints, img_keypoints, Scalar(0, 255, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        imshow("Webcam - Keypoints Detectadas", img_keypoints);

        char key = (char)waitKey(1);
        if (key == 27 || key == 'q' || key == 'Q') {
            break;
        }
    }

    cap.release();
    destroyAllWindows();
    
    return 0;
}
