/**
 * NOME: Leandro Scarpi Granelli, RA: 11202022007
 * NOME: Willian Gambaro
 * NOME: Leonardo Lerio
 * DATA: 27/11/2024
 * PROGRAMA: detectar_carros.cpp
 * RUN: 'cmake . && make && ./detectar_carros'
 */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("./resources/cars.mp4");
    if (!cap.isOpened()) {
        cerr << "Erro: não foi possível abrir o vídeo." << endl;
        return -1;
    }

    Ptr<BackgroundSubtractorMOG2> pBackSub = createBackgroundSubtractorMOG2();
    pBackSub->setDetectShadows(true);

    Mat frame, dst, mask;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // Converter o vídeo para escala de cinza reduz o custo computacional e não atrapalha a eficiência ao detectar os carros
        cvtColor(frame, dst, COLOR_BGR2GRAY);

        // O filtro gaussiano ajuda a reduzir falsos positivos, diminuindo o impacto de ruídos ou pequenos detalhes
        GaussianBlur(dst, dst, Size(11, 11), 0, 0);

        // Aplica o subtrator de fundo para gerar a máscara de movimento
        pBackSub->apply(dst, mask);

        // Aplica um threshold na máscara, convertendo os pixels com valor acima de 230 para 255 (branco) e abaixo para 0 (preto), criando uma imagem binária
        threshold(mask, mask, 230, 255, THRESH_BINARY);

        // Realiza erosão na máscara para reduzir áreas pequenas e remover ruídos
        erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)), Point(-1, -1), 1);

        // Realiza dilatação na máscara para expandir os contornos dos objetos em movimento
        dilate(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(11, 11)), Point(-1, -1), 2);

        // Encontrar contornos
        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // Desenha quadrados vermelhos ao redor dos carros
        for (size_t i = 0; i < contours.size(); i++) {
            if (contourArea(contours[i]) > 500) {
                Rect bounding_box = boundingRect(contours[i]);
                rectangle(frame, bounding_box, Scalar(0, 0, 255), 2);
            }
        }

        imshow("Vídeo com máscara dilatada", mask);
        imshow("Vídeo original", frame);

        char key = waitKey(30);
        if (key == 'q' || key == 'Q') {
            cout << "Saindo..." << endl;
            break;
        }
    }

    return 0;
}
