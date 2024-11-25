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

void remove_background(const string& video_name, const string& output_video_name, Ptr<BackgroundSubtractor> pBackSub) {
    // Abre o vídeo
    VideoCapture capture(video_name);
    if (!capture.isOpened()) {
        printf("\nNão foi possível abrir o vídeo: %s\n", video_name.c_str());
        return;
    }

    // Pega informações do vídeo
    int frameWidth = static_cast<int>(capture.get(CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(capture.get(CAP_PROP_FRAME_HEIGHT));
    double fps = capture.get(CAP_PROP_FPS);

    // Gravador para salvar o resultado
    VideoWriter writer(output_video_name, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, Size(frameWidth, frameHeight), false);
    if (!writer.isOpened()) {
        printf("\nNão foi possível abrir o arquivo para salvar o vídeo: %s\n", output_video_name.c_str());
        return;
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

        // Grava resultado
        writer.write(fgMask);

        // Input do teclado
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
    }

    capture.release();
    writer.release();
    destroyAllWindows();
}

int main(int argc, char* argv[])
{
    CommandLineParser parser(argc, argv, params);

    // Cria objeto BackgroundSubtractor
    Ptr<BackgroundSubtractor> pBackSub;
    if (parser.get<String>("algo") == "MOG2")
        pBackSub = createBackgroundSubtractorMOG2();
    else
        pBackSub = createBackgroundSubtractorKNN();

    remove_background("objeto_lento.avi", "objeto_lento_mask.avi", pBackSub);

    remove_background("objeto_rapido.avi", "objeto_rapido_mask.avi", pBackSub);

    return 0;
}
