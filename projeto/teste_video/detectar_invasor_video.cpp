/**
 * NOME: Leandro Scarpi Granelli, RA: 11202022007
 * NOME: William
 * NOME: Leonardo
 * DATA: 27/11/2024
 * PROGRAMA: detectar_invasor_video.cpp
 * RUN: 'cmake . && make && ./detectar_invasor_video'
 */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("../resources/boneco_amarelo.mp4");
    if (!cap.isOpened()) {
        cerr << "Erro: não foi possível abrir o vídeo." << endl;
        return -1;
    }

    Ptr<BackgroundSubtractorMOG2> pBackSub = createBackgroundSubtractorMOG2();
    pBackSub->setVarThreshold(75);

    int erosion_size = 5;
    Mat erosion_element = getStructuringElement(0, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));

    int dilation_size = 11;
    Mat dilation_element = getStructuringElement(0, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));

    Mat frame, gray, gaussian, equalized, mask, dilated, eroded;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // Converter o vídeo para escala de cinza reduz o custo computacional e não atrapalha a eficiência ao detectar o invasor, já que o importante é a forma e não as cores
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // O filtro gaussiano ajuda a reduzir falsos positivos, diminuindo o impacto de ruídos ou pequenos detalhes
        GaussianBlur(gray, gaussian, Size(11, 11), 0, 0);

        equalizeHist(gaussian, equalized);

        pBackSub->apply(equalized, mask);

        erode(mask, eroded, erosion_element);
        dilate(eroded, dilated, dilation_element);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(dilated, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (int i = 0; i < contours.size(); i++) {
            if (contourArea(contours[i]) > 500) {
                Rect bounding_box = boundingRect(contours[i]);
                rectangle(frame, bounding_box, Scalar(0, 0, 255), 2);
            }
        }

        imshow("Vídeo original", frame);
        // imshow("Vídeo em escala de cinza", gray);
        // imshow("Vídeo com filtro gaussiano", gaussian);
        // imshow("Vídeo com histograma equalizado", equalized);
        // imshow("Vídeo com subtração de fundo", mask);
        // imshow("Vídeo com imagem erode", eroded);
        imshow("Vídeo com máscara dilatada", dilated);

        char key = waitKey(30);
        if (key == 'q' || key == 'Q') {
            cout << "Saindo..." << endl;
            break;
        }
    }

    return 0;
}
