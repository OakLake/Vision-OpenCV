/*
OpenCV C++ Disparity map
by Sammy Hasan
2017
*/

# include <opencv2/opencv.hpp>
# include <iostream>
#include "calib3d.hpp"

using namespace std;
using namespace cv;

int main(){

  Mat img_l,img_r;

  // importing images from local directory, images have been copied from source.
  img_l = imread("./tsukuba_l.png",CV_8UC1);
  img_r = imread("./tsukuba_r.png",CV_8UC1);
  Mat img_disparity(img_l.rows,img_l.cols,CV_8UC1);

  // creating stereoBM object
  Ptr<StereoBM> stereo = StereoBM::create(16*5,21);
  stereo->compute(img_l,img_r,img_disparity);

  namedWindow("Left",WINDOW_AUTOSIZE);
  namedWindow("Right",WINDOW_AUTOSIZE);
  namedWindow("Disparity", WINDOW_AUTOSIZE);


  // normalise disparity image
  normalize(img_disparity,img_disparity,0,255,NORM_MINMAX,CV_8UC1);


  // display
  imshow("Left",img_l);
  imshow("Right",img_r);
  imshow("Disparity",img_disparity);

  waitKey(0);

  return 0;

}
