#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat src = imread("resources/FotoGrupo.jpg", IMREAD_COLOR);
    if (src.empty()) {
        cout << "Não foi possível carregar a imagem!" << endl;
        return -1;
    }

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    Ptr<ORB> detector = ORB::create();
    vector<KeyPoint> keypoints;
    detector->detect(gray, keypoints);

    Mat img_keypoints;
    drawKeypoints(src, keypoints, img_keypoints, Scalar(0, 255, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    imshow("Keypoints Detectadas", img_keypoints);

    imwrite("resources/image_with_features.jpg", img_keypoints);

    waitKey();
    return 0;
}
