# include <iostream>
# include <stdio.h>
# include <opencv2/opencv.hpp>
# include <thread>

using namespace std;
using namespace cv;

int mask = 24;

void process(Mat region){

  for(int x=0; x<region.cols; x+=mask){
    for(int y=0; y<region.rows; y+=mask){
      region(Rect(x,y,mask,mask)) = mean(region(Rect(x,y,mask,mask)));
    }
  }
}

int main(){

  VideoCapture cap;
  cap.open(0);
  if(!cap.isOpened()){
    cerr << "Failed to open VideoCapture cap(0)";
  }

  int cap_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int cap_hegiht = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  // to crop image to multiples of mask
  // 24x24 mask, defined before main()
  int w24multiples = (int)(cap_width/mask);
  w24multiples = (w24multiples % 2 == 0) ? w24multiples:(w24multiples-1);
  int h24multiples = (int)(cap_hegiht/mask);
  h24multiples = (h24multiples % 2 == 0) ? h24multiples:(h24multiples-1);

  int width24 = w24multiples*mask;
  int height24 = h24multiples*mask;

  cout << "Cap WxH: " << cap_width <<"x"<< cap_hegiht << endl;
  cout << "Crop 24 WxH: " << width24 <<"x"<< height24 << endl;

  Mat frame;

  Mat region_1,region_2,region_3,region_4;

  while(true){

    cap.read(frame);
    if(frame.empty()){
      cerr << "Empty frame failure!";
      break;
    }

    // cropping the frame to fit 'mask' multiples
    frame = frame(Rect(0,0,width24,height24));

    // Break down frame into 4 rects to be processed by threading
    region_1 = frame(Rect(0,0,width24/2,height24/2));
    region_2 = frame(Rect(width24/2,0,width24/2,height24/2));
    region_3 = frame(Rect(0,height24/2,width24/2,height24/2));
    region_4 = frame(Rect(width24/2,height24/2,width24/2,height24/2));

    thread pross1(process,region_1);
    thread pross2(process,region_2);
    thread pross3(process,region_3);
    thread pross4(process,region_4);

    pross1.join();
    pross2.join();
    pross3.join();
    pross4.join();

    frame(Rect(0,0,width24/2,height24/2)) = region_1;
    frame(Rect(width24/2,0,width24/2,height24/2)) = region_2;
    frame(Rect(0,height24/2,width24/2,height24/2)) = region_3;
    frame(Rect(width24/2,height24/2,width24/2,height24/2)) = region_4;

    // cvtColor(frame,frame_grey,CV_RGB2GRAY);
    // frame_grey(Rect(100,100,100,100)) = mean(frame_grey(Rect(100,100,100,100)));

    flip(frame,frame,1);
    imshow("Frame",frame);

    if(waitKey(5) >= 0){
      break;
    }


  }
}
