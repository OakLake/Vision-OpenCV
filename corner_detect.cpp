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


bool isCorner(Mat,int,vector<int>* ,vector<int>* ,int );
// void circle_vals(int,vector<int>*,vector<int>*);
void populate_vecs(vector<int>*,vector<int>*);


void debug(String text){
  cerr << text << endl;
}

/* MAIN ()*/
int main(int argc,char** argv){

  int window_size = 7; // 7x7
  int intensity_thr = atoi(argv[2]);
  cout << "intensity_thr: " << intensity_thr << endl;
  int contig = 14; // min number of required contigous pixels for a corner

  vector<int>* ixX_s = new vector<int>();
  vector<int>* ixY_s = new vector<int>();

  // circle_vals(window_size,ixX_s,ixY_s);
  populate_vecs(ixX_s,ixY_s);
  // vectors are now populated

  Mat image,grey_image,roi;
  grey_image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE); // also converts to grey scale
  image = grey_image.clone();
  cvtColor(grey_image,image,CV_GRAY2BGR);


  // slide over the input image
  for(int x=0;x<grey_image.cols-window_size;x++){
    for(int y=0;y<grey_image.rows-window_size;y++){
      roi = grey_image(Rect(x,y,window_size,window_size));

      // check if corner exists:
      if (isCorner(roi,intensity_thr,ixX_s,ixY_s,contig)){
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


bool isCorner(const Mat window,int thr,vector<int>* pix_x,vector<int>* pix_y,int cont_N){

  // check if pixel intenisties are larger than thr from centre intenisty
  int cntr_pix_I = window.at<uchar>(window.rows/2,window.cols/2);
  int pix_I = 0;
  int x,y;

  vector<bool> thr_test;

  for (int v=0;v<pix_x->size();v++){
    x = pix_x->at(v);
    y = pix_y->at(v);

    pix_I = (int)window.at<uchar>(x,y);
    thr_test.push_back(abs(pix_I-cntr_pix_I) >= thr);
  }

  // thr_test now populated using threshold test

  // quick check (1,9,5,13) points
  int chk[4] = {1,9,5,13};
  int c = 0;
  for(int z=0;z<4;z++){
    if(thr_test.at(chk[z]-1))
      c++;
  }
  if(c>=3){
      // perform full check with contingency
      // looping over thr_test
      bool cached = thr_test.at(0);
      int cont_count = 0;
      for(int l=1;l<thr_test.size();l++){
        if(thr_test.at(l) == cached){
          cont_count++;
        }else{
          cont_count = 0;
          cached = thr_test.at(l);
        }
      }
      return cont_count >= cont_N;

  }else{
    return false;
  }
  return false;

}



// remedy measure, introduce code redundecy for still using vectors
void populate_vecs(vector<int>* pix_x,vector<int>* pix_y){
  int x[16] = {0,0,1,2,3,4,5,6,6,6,5,4,3,2,1,0};
  int y[16] = {3,4,5,6,6,6,5,4,3,2,1,0,0,0,1,2};
  for(int i=0;i<16;i++){
    pix_x->push_back(x[i]);
    pix_y->push_back(y[i]);
  }
  cout << "populated" << endl;
}
/*
void circle_vals(int mask_dim,vector<int>* ixX_s,vector<int>* ixY_s){


  Mat mask = Mat::zeros(mask_dim+2,mask_dim+2,CV_8UC1); // +2: padding on each side
  int midPt = mask_dim/2;
  circle(mask,Point(midPt+1,midPt+1),midPt,Scalar(255),1);
  mask.at<uchar>(1,midPt-1) = 0; // directs the search
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
        if((int)mask.at<uchar>(x_row+xp,y_col+yp) == 255){
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
*/
