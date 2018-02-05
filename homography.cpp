/* Homography with opencv
 Sammy Hasan
 Feb 2018
*/

# include <opencv2/opencv.hpp>
# include "opencv2/xfeatures2d.hpp"
# include <iostream>
# include <vector>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int main(int argc,char** argv){

  // simple check of input
  if (argc != 3){
    std::cout << "Please input path to 2 images, Thanks!" << std::endl;
    return -1;
  }


  // loading images

  Mat img1 = imread(argv[1]);
  Mat img2 = imread(argv[2]);


  // using SURF to detect keypoints
  cout << "SURF-ing" << endl;

  int minHessian = 400;
  Ptr<SURF> detector = SURF::create(minHessian);

  vector<KeyPoint> keypoints1, keypoints2;
  Mat descriptors_img1, descriptors_img2;

  detector->detectAndCompute( img2, Mat(), keypoints2, descriptors_img2 );
  detector->detectAndCompute( img1, Mat(), keypoints1, descriptors_img1 );

  // Feature matching
  cout << "Matching Features" << endl;

  FlannBasedMatcher matcher;
  vector<DMatch> matches;
  matcher.match( descriptors_img2, descriptors_img1, matches );

  double max_dist = 0; double min_dist = 100;
  for( int i = 0; i < descriptors_img2.rows; i++ )
  { double dist = matches[i].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
  }

  vector< DMatch > good_matches;
  for( int i = 0; i < descriptors_img2.rows; i++ )
  { if( matches[i].distance <= 3*min_dist )
     { good_matches.push_back( matches[i]); }
  }

  vector<Point2f> P_img1,P_img2;
  for( size_t i = 0; i < good_matches.size(); i++ )
  {
    P_img2.push_back( keypoints2[ good_matches[i].queryIdx ].pt );
    P_img1.push_back( keypoints1[ good_matches[i].trainIdx ].pt );
  }

  // calculating Homography
  Mat H = findHomography( P_img2, P_img1, RANSAC );

  // displaying H values
  // cout << "H size: " << H.size() << endl;
  cout << " " << endl;
  cout << "Homography Matrix" << endl;

  for(int r=0; r<H.rows;r++){
    for(int c=0;c<H.cols;c++){
      cout << "H[" << r << "," << c << "]:  " << H.at<double>(r,c) << endl;
    }
  }
  cout << " " << endl;
  // type of img1
  //cout << "img type:" << img1.type() << endl;




  // Warp drives activated :)
  Mat warpped,warpped_full;

  int cols = img1.cols + img2.cols;
  int rows = img1.rows;
  Size si(cols,rows);

  warpPerspective(img2,warpped_full, H, si);
  imshow("Warppie",warpped_full);


  warpPerspective(img2,warpped, H, img2.size());


  namedWindow("Error",CV_WINDOW_AUTOSIZE);
  namedWindow("Output",CV_WINDOW_AUTOSIZE);


  // resizing for viewing convinience
  resize(img1,img1,Size(600,600));
  resize(img2,img2,Size(600,600));
  resize(warpped,warpped,Size(600,600));

  Mat sidebyside(600,1800,CV_8UC3);
  img1.copyTo(sidebyside(Rect(0,0,600,600)));
  warpped.copyTo(sidebyside(Rect(600,0,600,600)));
  img2.copyTo(sidebyside(Rect(1200,0,600,600)));

 // pixelwise error
  Mat error;
  // error = img1 - warpped;
  absdiff(img1,warpped,error);

  cout << "Displaying results .. Two windows are open!" << endl;

  imshow("Output",sidebyside);
  imshow("Error",error);

  waitKey(0);


  return 0;
}
