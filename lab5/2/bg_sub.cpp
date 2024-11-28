#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

const char* params
    = "{ algo           | MOG2      | Método de subtração de fundo (KNN, MOG2) }";

int main(int argc, char* argv[])
{
    CommandLineParser parser(argc, argv, params);

    // Cria objeto BackgroundSubtractor
    Ptr<BackgroundSubtractor> pBackSub;
    if (parser.get<String>("algo") == "MOG2")
        pBackSub = createBackgroundSubtractorMOG2();
    else
        pBackSub = createBackgroundSubtractorKNN();

    // Abre webcam 
    VideoCapture capture(0);
    if (!capture.isOpened()) {
        printf("\nNão foi possível acessar a webcam!\n");
        return 0;
    }

    Mat frame, fgMask;
    while (true) {
        capture >> frame;
        if (frame.empty())
            break;

        // Atualiza modelo de fundo
        pBackSub->apply(frame, fgMask);

        // Exibe o número do frame
        rectangle(frame, Point(10, 2), Point(100, 20), Scalar(255, 255, 255), -1);
        stringstream ss;
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), Point(15, 15),
                FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));

        // Exibe frame atual e fg masks
        imshow("Frame", frame);
        imshow("FG Mask", fgMask);


        // Input do teclado
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
    }

    return 0;
}
