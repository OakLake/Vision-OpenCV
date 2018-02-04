# Vision-OpenCV
Miscellaneous OpenCV code 

## Contents

- video_pixel_threaded.cpp: openCV videocapture for live video pixelisation using threads.

- disparity.cpp: openCV StereoBM for find the disparity map from two stereo images.

- corner_detect.cpp: FAST (Features from Accelerated Segment Test) implementation from scratch with openCV.

     ![Alt text](https://github.com/OakLake/Code_for_the_People/blob/master/imgs/detected.png "Detected Corners")

- track.cpp: corner detection using goodFeaturesToTrack and tracking with calcOpticalFlowPyrLK in openCV. Tried with KITTI dataset (http://www.cvlibs.net/datasets/kitti/raw_data.php?type=city)

     ![](https://github.com/OakLake/Code_for_the_People/blob/master/imgs/QvO1J4.gif)

- cv_colorCircDetection.cpp: detecting coloured circles with HoughCircles in opencv, with slider for adjusting parameters (colour and tuning).

- aruco.cpp: ArUco marker detection.

     ![Alt text](https://github.com/OakLake/Code_for_the_People/blob/master/imgs/aruco_detected.png)

- homography.cpp: opencv homography and image warpping.

     ![Alt text](https://github.com/OakLake/Vision-OpenCV/blob/master/imgs/homography.png)
