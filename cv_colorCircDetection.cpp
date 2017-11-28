// Coloured Circle detection
// by Sammy Hasan
// 2017

# include <opencv2/opencv.hpp>
# include <opencv2/imgproc/imgproc.hpp>
# include "opencv2/highgui/highgui.hpp"
# include <iostream>
# include <vector>

/*
https://docs.opencv.org/trunk/da/d97/tutorial_threshold_inRange.html
https://docs.opencv.org/3.1.0/df/d0d/tutorial_find_contours.html
*/
using namespace cv;
using namespace std;


int blur_slider,param1,param2,blur_slider_H,Hue_low,Hue_high;


void blur_callback(int b,void *data){
    blur_slider = (b%2==1)? b:b+1;
    cout << "Moved Slider, Val= " << blur_slider << endl;
}

void HL_callback(int hue, void *data){
  Hue_low = hue;
}
void HH_callback(int hue, void *data){
  Hue_high = hue;
}

void blurH_callback(int b, void* data){
  blur_slider_H = (b%2==1)? b:b+1;
}

void p1_callback(int p,void* data){
  param1 = p;
}
void p2_callback(int p,void* data){
  param2 = p;
}

int main(int argc, char const *argv[]) {
  Mat frame;
  Mat HSV,hsv_frame,frame_cap;
  VideoCapture cap(0);

  blur_slider = 13;
  blur_slider_H = 9;
  Hue_low = 20;
  Hue_high = 30;
  param1 = 100;
  param2 = 40;
  namedWindow("Vid Feed",1);
  namedWindow("HSV Thr",1);
  createTrackbar("BlurTrack","Vid Feed",&blur_slider,21,blur_callback);
  createTrackbar("Hue Low","Vid Feed",&Hue_low,179,HL_callback);
  createTrackbar("Hue high","Vid Feed",&Hue_high,179,HH_callback);
  createTrackbar("Blur","HSV Thr",&blur_slider_H,21,blurH_callback);
  createTrackbar("P1","HSV Thr",&param1,200,p1_callback);
  createTrackbar("P2","HSV Thr",&param2,200,p2_callback);

  // cap.open(0);

  if(!cap.isOpened()){
    cout << "[Error!] Could not open videocapture device!" << endl;
    return -1;
  }

  cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);

  Scalar low_hsv;
  Scalar high_hsv;

  for(;;){

    vector<Vec3f> circles;
    low_hsv = Scalar(Hue_low,100,100);
    high_hsv = Scalar(Hue_high,255,255);

    cap.read(frame_cap);
    // GaussianBlur(frame,frame,Size(5,5),5,5);
    medianBlur(frame_cap,frame,blur_slider);
    cvtColor(frame,frame,CV_BGR2GRAY);

    cvtColor(frame_cap,HSV,CV_BGR2HSV);
    inRange(HSV,low_hsv,high_hsv,hsv_frame);
    medianBlur(hsv_frame,hsv_frame,blur_slider_H);
    GaussianBlur(hsv_frame, hsv_frame, Size(9, 9), 2, 2);
    // Canny(hsv_frame,canny_output,threshold,threshold*2,3);
    HoughCircles(hsv_frame,circles, HOUGH_GRADIENT, 1,frame.rows/16,param1, param2, 30, 230);

    for(int c=0;c<circles.size();c++){
      Vec3i circ = circles[c];
      circle( frame_cap, Point(circ[0], circ[1]), circ[2], Scalar(0,255,0), 3, LINE_AA);
    }


    imshow("Vid Feed",frame_cap);
    imshow("HSV Raw",HSV);
    imshow("HSV Thr",hsv_frame);
    // if(waitKey(30) >= 0) break;
    waitKey(5);
  }

  return 0;
}
