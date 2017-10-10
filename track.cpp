/*

finding features and tracking in video sequence
by Sammy Hasan
2017
*/

# include <opencv2/opencv.hpp>
# include <iostream>
# include <vector>

using namespace std;
using namespace cv;


void cronerDetect(Mat,Mat,vector<Point2f>*,int,double,int);
void placeCorners(Mat,vector<Point2f>*,int);
int track_KLT(Mat,Mat,vector<Point2f>*,vector<Point2f>*,vector<uchar>,vector<float>);
void drawOpticalFlowLines(Mat,vector<Point2f>*,vector<Point2f>*);

int x,x1,x2,y,yy,y2;

int main(void){

  Mat frame,gray_frame;
  VideoCapture cap;
  int maxCorner = 10;
  vector<Point2f>* corners = new vector<Point2f>(maxCorner);
  vector<Point2f>* corners2 = new vector<Point2f>(maxCorner);
  vector<uchar> status(maxCorner);
  vector<float> err(maxCorner);

  int rSize_by2 = 6;

  double quality = 0.01;
  int euc_dist = 14;
  int matched;

  namedWindow("Video Feed",WINDOW_AUTOSIZE);


  cap.open(0);
  if(!cap.isOpened()){
    cerr << "Failure to open cap";
    return -1;
  }

  // get started with an initial frame_pre
  Mat frame_pre;
  cap.read(frame_pre);
  frame_pre.convertTo(frame_pre,CV_8UC1);
  cvtColor(frame_pre,frame_pre,CV_BGR2GRAY);

  if(frame_pre.empty()){
    cerr << "empty frame received!";
    return -1;
  }




  for(;;){
    cap.read(frame);
    if(frame.empty()){
      cerr << "empty frame received!";
      break;
    }
    frame.convertTo(frame,CV_8UC1);
    cvtColor(frame,gray_frame,CV_BGR2GRAY);

    cronerDetect(frame,gray_frame,corners,maxCorner,quality,euc_dist); // could use FAST instead
    placeCorners(frame,corners,rSize_by2);
    matched = track_KLT(frame_pre,gray_frame,corners,corners2,status,err);
    drawOpticalFlowLines(frame,corners,corners2);

    imshow("Video Feed",frame);

    frame_pre = gray_frame.clone();
    corners = corners2; // backpropagate corners
    corners2->clear();

    if(waitKey(5) >= 0){
      break;
    }

  }
  return 0;
}



// // // //

void cronerDetect(Mat frame,Mat gray_frame,vector<Point2f>* corners,int maxCorner,double quality,int euc_dist){

  goodFeaturesToTrack(gray_frame,*corners,maxCorner,quality,euc_dist);

}

////

void placeCorners(Mat frame,vector<Point2f>* corners,int rSize_by2){
  for(int c=0;c<corners->size();c++){
    x = corners->at(c).x;
    y = corners->at(c).y;
    x1 = x-rSize_by2;
    yy = y-rSize_by2; // y1 naming causing error ??
    x2 = x+rSize_by2;
    y2 = y+rSize_by2;

    rectangle(frame,Point(x1,yy),Point(x2,y2),Scalar(255,0,0));
  }

}

int track_KLT(Mat frame_pre,Mat frame_next,vector<Point2f>* corners1,vector<Point2f>* corners2, vector<uchar> status,vector<float> err){

  calcOpticalFlowPyrLK(frame_pre,frame_next, *corners1,*corners2,status,err);

  // remove unmatched corners, vector status indicates 0/1 unmatched/matched.
  int shift = 0;
  for(int s=0;s<status.size();s++){
    if(status.at(s) == 0){
      corners1->erase(corners1->begin() + s - shift);
      corners2->erase(corners2->begin() + s - shift);
      shift++;
    }
  }
  return corners2->size(); // number of matched corners
}

void drawOpticalFlowLines(Mat frame,vector<Point2f>* corners1,vector<Point2f>* corners2){
  for(int c=0; c<corners1->size();c++){
    line(frame,corners1->at(c),corners2->at(c),Scalar(0,255,0));
  }

}
