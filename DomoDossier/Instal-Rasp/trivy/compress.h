#ifndef COMPRESS_H
#define COMPRESS_H
#include <vector>
#include <stdio.h>
//#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv/cv.h>

using namespace std;

class compress {
private:
    string nomfichier_dest;
    cv::Mat image; //objet image
    vector<int> compression_param; //tableau pour les paramètres de compressions
    int taille_compression;
public:
    void compression(string, string, int);
    compress();
};

#endif /* COMPRESS_H */

