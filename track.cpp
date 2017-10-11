/*

finding features and tracking in video sequence
by Sammy Hasan
2017
*/

# include <opencv2/opencv.hpp>
# include <iostream>
# include <vector>
# include <string>

using namespace std;
using namespace cv;


void cronerDetect(Mat,Mat,vector<Point2f>*,int,double,int);
void placeCorners(Mat,vector<Point2f>*,int,vector<uchar>*);
int track_KLT(Mat,Mat,vector<Point2f>*,vector<Point2f>*,vector<uchar>*,vector<float>);
void drawOpticalFlowLines(Mat,vector<Point2f>*,vector<Point2f>*);

int x,x1,x2,y,yy,y2;

int main(void){

  Mat frame,gray_frame;
  int maxCorner = 200;
  vector<Point2f>* corners = new vector<Point2f>(maxCorner);
  vector<Point2f>* corners2 = new vector<Point2f>(maxCorner);
  vector<uchar>* status = new vector<uchar>(maxCorner);
  vector<float> err(maxCorner);

  int rSize_by2 = 6;

  double quality = 0.01;
  int euc_dist = 14;
  int matched = 0;

  namedWindow("Image Sequence",WINDOW_AUTOSIZE);


  // get started with an initial frame_pre

  // Using the KITTI DataBase -> 2011_09_26_drive_0048
  string PATH = "./2011_09_26/2011_09_26_drive_0048_extract/image_00/data/";
  Mat frame_pre = imread(PATH+to_string(0)+".png");
  frame_pre.convertTo(frame_pre,CV_8UC1);
  cvtColor(frame_pre,frame_pre,CV_BGR2GRAY);





  for(int i=1;i<27;i++){
    frame = imread(PATH+to_string(i)+".png");
    frame.convertTo(frame,CV_8UC1);
    cvtColor(frame,gray_frame,CV_BGR2GRAY);
    cout << "Loaded: " << i << endl;
    // check the number of matched corners between pre and next frames, update list if insufficinet
    if (matched < 5){
      cout << "Detecting Corners" << endl;
      cronerDetect(frame,gray_frame,corners,maxCorner,quality,euc_dist);
    }

    // cout << "status: " << status.size() << endl;
    // cout << "corners: " << corners->size() << endl;

    placeCorners(frame,corners,rSize_by2,status);
    // cout << "Placing Corners" << endl;
    matched = track_KLT(frame_pre,gray_frame,corners,corners2,status,err);
    drawOpticalFlowLines(frame,corners,corners2);

    cout << "Matched corners count: " << matched << endl;
    imshow("Image Sequence",frame);

    frame_pre = gray_frame.clone();
    *corners = *corners2; // backpropagate corners
    corners2->clear();

    waitKey(0);
    // if(waitKey(10) >= 0){
    //   break;
    // }

  }
  return 0;
}



// // // //

void cronerDetect(Mat frame,Mat gray_frame,vector<Point2f>* corners,int maxCorner,double quality,int euc_dist){
  // could use FAST instead
  goodFeaturesToTrack(gray_frame,*corners,maxCorner,quality,euc_dist);

}

void placeCorners(Mat frame,vector<Point2f>* corners,int rSize_by2,vector<uchar>* status){

  // cout << "placeCorners Status Vec: ";

  for(int c=0;c<status->size();c++){
    Scalar color;
    int corner_status = status->at(c);
    // cout << corner_status;

    if (corner_status == 1){
      color = Scalar(0,255,0);
    }else{
      color = Scalar(255,0,0);
    }

    x = corners->at(c).x;
    y = corners->at(c).y;
    x1 = x-rSize_by2;
    yy = y-rSize_by2; // y1 naming causing error ??
    x2 = x+rSize_by2;
    y2 = y+rSize_by2;

    rectangle(frame,Point(x1,yy),Point(x2,y2),color);
  }

  // cout << " " << endl;

}

int track_KLT(Mat frame_pre,Mat frame_next,vector<Point2f>* corners1,vector<Point2f>* corners2, vector<uchar>* status,vector<float> err){

  calcOpticalFlowPyrLK(frame_pre,frame_next, *corners1,*corners2,*status,err);

  // check number of matched corners
  // cout << "track_KLT Status Vec: ";

  int matched = 0;
  for(int m=0;m<status->size();m++){
    int corner_status = status->at(m);
    // cout << corner_status;

    if( corner_status == 1){
      matched++;
    }
  }

  // cout << " " << endl;
  return matched; // number of matched corners
}

void drawOpticalFlowLines(Mat frame,vector<Point2f>* corners1,vector<Point2f>* corners2){
  for(int c=0; c<corners1->size();c++){
    line(frame,corners1->at(c),corners2->at(c),Scalar(0,255,0));
  }

}
