/* 
 * File:   compress.cpp
 */
#include "compress.h"

using namespace cv;

compress::compress() {
}

void compress::compression(string imageSrc, string imageDst, int taille) {
    //string nomNoExt;
    //nomNoExt = imageSrc;
    //nomNoExt.erase(nomNoExt.end() - 4, nomNoExt.end());
    //nomfichier_dest = nomNoExt + "_conv.jpg";

    image = imread(imageSrc, CV_LOAD_IMAGE_COLOR);
    taille_compression = taille;
    if (!image.data) {
        fprintf(stderr, " No image data \n ");
    }
    compression_param.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_param.push_back(taille_compression);

    try {
        imwrite(imageDst, image, compression_param);
    } catch (runtime_error& ex) {
        fprintf(stderr, "Veillez convertir votre image au format JPG : %s\n", ex.what());
    }
}
