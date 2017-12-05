// Aruco Markers - OpenCV C++
// Sammy Hasan
// 2017


# include <opencv2/aruco.hpp>
# include <opencv2/opencv.hpp>
# include <iostream>
# include <vector>

using namespace std;
using namespace cv;


void generate_aruco(int);
Mat detect_aruco(Mat);

int main(int argc, char const *argv[]) {

  /* Generate markers from defined dict
  for(int m=0;m<10;m++){
    generate_aruco(m);
  }*/

  cout << "\nAruco Dictionary: 6X6_50\n" << endl;

  // Detection of markers

  Mat frame,outputImg;
  VideoCapture cap;
  cap.open(0);
  if(!cap.isOpened()){
    cout << "Could not open VideoCapture device!" << endl;
    return -1;
  }

  cap.set(CV_CAP_PROP_FRAME_WIDTH,1280);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT,960);

  for(;;){
    cap.read(frame);
    outputImg = detect_aruco(frame);

    namedWindow("detection",WINDOW_AUTOSIZE);
    imshow("detection",outputImg);
    if(waitKey(1)>0){break;}
  }


  return 0;
}


void generate_aruco(int id){
  cout << "generating ArUco markers" << endl;
  Mat markerImage;
  cv::Ptr<aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);
  cv::aruco::drawMarker(dict,id,200,markerImage,1);

  imwrite("./markers/arUco_marker_id_"+to_string(id)+".png",markerImage);
  imshow("Marker",markerImage);
  waitKey(1000);

}


Mat detect_aruco(Mat img){

  vector<int> markerIDs;
  vector<vector<Point2f>> markerCorners,rejected;

  // cv::Ptr<cv::aruco::DetectorParameters> parameters;
  // Ptr<aruco::DetectorParameters> params = new aruco::DetectorParameters;

  Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
  cv::aruco::detectMarkers(img,dict,markerCorners,markerIDs);

  Mat outputImg = img.clone();
  cout << "\r::Detected " <<  markerIDs.size() << " markers" << flush;
  cv::aruco::drawDetectedMarkers(outputImg,markerCorners,markerIDs);

  return outputImg;

}
