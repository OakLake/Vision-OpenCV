/*
FAST corner detection from scratch
by Sammy Hasan
2017
*/

# include <opencv2/opencv.hpp>
# include <iostream>
# include <vector>
# include <string>

using namespace std;
using namespace cv;


bool isCorner(Mat,int,int );


void debug(String text){
  cerr << text << endl;
}

/* MAIN ()*/
int main(int argc,char** argv){

  int window_size = 7;
  int intensity_thr = atoi(argv[2]);
  cout << "intensity_thr: " << intensity_thr << endl;
  int contig = 12; // min number of required contigous pixels for a corner


  Mat image,grey_image,roi;
  grey_image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE); // also converts to grey scale
  image = grey_image.clone();
  cvtColor(grey_image,image,CV_GRAY2BGR);


  // slide over the input image
  for(int x=0;x<grey_image.cols-window_size;x++){
    for(int y=0;y<grey_image.rows-window_size;y++){
      roi = grey_image(Rect(x,y,window_size,window_size));

      // check if corner exists:
      if (isCorner(roi,intensity_thr,contig)){
        circle(image,Point(x+window_size/2-1,y+window_size/2-1),3,Scalar(255,0,0),-1);
      }

    }
  }


  namedWindow("Original",WINDOW_AUTOSIZE);
  imshow("Original",image);
  imwrite("detected.png",image);


  waitKey(0);

  return 0;
}


bool isCorner(const Mat window,int thr,int cont_N){

  // check if pixel intenisties are larger than thr from centre intenisty
  int cntr_pix_I = window.at<uchar>(window.rows/2,window.cols/2);
  int pix_I = 0;
  int pos;

  vector<int> thr_test;
  /*
  0 - same
  1 - darker
  2 - brighter
  */

  int x_arr[16] = {0,0,1,2,3,4,5,6,6,6,5,4,3,2,1,0};
  int y_arr[16] = {3,4,5,6,6,6,5,4,3,2,1,0,0,0,1,2};

  for (int v=0;v<16;v++){

    pix_I = (int)window.at<uchar>(x_arr[v],y_arr[v]);

    if (abs(pix_I-cntr_pix_I) < thr){
      thr_test.push_back(0);
    }else{
      pos = (pix_I-cntr_pix_I) > 0 ? 2:1;
      thr_test.push_back(pos);
    }
  }

  // thr_test now populated using threshold test

  // quick check (1,9,5,13) points
  int chk[4] = {1,9,5,13};
  int c = 0;
  for(int z=0;z<4;z++){
    if(thr_test.at(chk[z]-1) != 0)
      c++;
  }
  if(c>=3){
      // perform full check with contingency
      // looping over thr_test
      int cached = thr_test.at(0);
      int cont_count = 0;

      for(int l=1;l<thr_test.size();l++){
        if(thr_test.at(l) == cached && thr_test.at(l) != 0){
          cont_count++;
        }else{
          cont_count = 0;
        }
        cached = thr_test.at(l);
      }
      return cont_count >= cont_N;

  }else{
    return false;
  }
  return false;

}
