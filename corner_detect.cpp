/*
FAST corner detection from scratch
by Sammy Hasan
2017
*/

# include <opencv2/opencv.hpp>
# include <iostream>
# include <vector>

using namespace std;
using namespace cv;

bool isCorner(Mat window,int thr,vector* pixels);
vector<int[]> circle_vals(int radius); // takes in radius and returns list of [x,y] correspoding to pixels on the edge of the circle, raster of circle

int main(){

  int window_size = 7; // 7x7
  int intensity_thr = ;
  int contig = 9; // number of required contigous pixels for a corner

  vector<int>* ixX_s = new vector<int>();
  vector<int>* ixY_s = new vector<int>();

  circle_vals(window_size);
  // vectors are now populated

  Mat image,grey_image,roi;
  image = imread("./image",CV_U8C1);

  // convert to greyscale
  cvColor(image,grey_image,CV_BGR2GRAY);

  // slide over the input image
  for(int x=0;x<grey_image.rows-window_size;x++){
    for(int y=0;y<grey_image.cols-window_size;y++){
      roi = grey_image(Rect(x,y,window_size,window_size))
      if (isCorner(roi,intensity_thr,pixels,contig)){
        circle(image,Point(x+window_size/2-1,y+window_size/2-1),4,Scalar(136,50,203),2);
      }
    }
  }


  namedWindow("Original",WIDOW_AUTOSIZE);
  imshow("Original",image);


  waitKey(0);

  return 0;
}


bool isCorner(Mat window,int thr,vector<int>* pix_x,ector<int>* pix_y,int cont_N){

  // check if pixel intenisties are larger than thr from centre intenisty
  int cntr_pix_I = window.at<int>(window/2,window/2);
  int pix_I = 0;
  int x,y;

  vector<bool> thr_test = new vector<bool>();

  for (int v=0;v<pix_x->size()<v++){
    x = pix_x(v);
    y = pix_y(v);

    pix_I = window.at<int>(x,y);
    thr_test.push_back(abs(pix_I-cntr_pix_I) >= thr);
  }

  // thr_test now populated using threshold test

  // quick check 4 points on ver and hor axis

  int num_true = 0;
  for(int s=0;s<4;s++){
    if (thr_test(s*skip+1)){
      num_true++;
    }
  }
  if (num_true == 1 or num_true == 3){
    return true; // is corner based on quick check
  }else{
    // perform full check with contingency
    // looping over thr_test
    bool cached = thr_test(0);
    int cont_count = 0;
    for(int l=1;l<thr_test.size();l++){
      if(thr_test(l) == cached){
        cont_count++;
      }else{
        cont_count = 0;
        cached = thr_test(l);
      }
    }
  }
  return false;

}


void circle_vals(int mask_dim,vector<int>* ixX_s,vector<int>* ixY_s; ){


  Mat mask = Mat::zeros(mask_dim+2,mask_dim+2,CV_8UC1); // +2: padding on each side
  int midPt = mask_dim/2;
  circle(mask,Point(midPt,midPt),midPt,Scalar(255),1);
  mask.at<int>(1,midPt-1) = 0; // directs the search
  // starting at mid of top row, pixel 1:
  // indeces start from 0,
  int x_row = 1;
  int y_col = midPt;

  int brk_flag = 0;
  int inc = 0;
  while(inc<(mask_dim+1)*2) // while white pixels havent been all counted
  {

    mask.at<int>(x_row,y_col) = 0; // done with element
    ixX_s->push_back(x_row-1);
    ixY_s->push_back(y_col-1);

    brk_flag = 0;
    for(int xp = -1;xp<2;xp++){
      for(int yp = -1;yp<2;yp++){
        if(mask.at<int>(x_row+xp,y_col+yp) == 255){
          x_row += xp;
          y_col += yp;
          brk_flag = 1;
          break;

        }
      }
      // break from second for loop
      if (brk_flag == 1)
        break;
    }

    inc++;
  }

  ixX_s->push_back(0);
  ixY_s->push_back(midPt-2); // -2 =  for padding (-1) + last pixel in loop (-1)

}
