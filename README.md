# Code_for_the_People
code that might be helpful for someone

## Contents
- threading.cpp: threading using c++ <thread> with a safe queue locked with mutex.
  this simple example demonstrates concurent access to a safe queue as seen by the print statements.

- video_pixel_threaded.cpp: openCV videocapture for live video pixelisation using threads.

- disparity.cpp: openCV StereoBM for find the disparity map from two stereo images.

- corner_detect.cpp: FAST (Features from Accelerated Segment Test) implementation from scratch with openCV.

     ![Alt text](https://github.com/OakLake/Code_for_the_People/blob/master/imgs/detected.png "Detected Corners")

- track.cpp: corner detection using goodFeaturesToTrack and tracking with calcOpticalFlowPyrLK in openCV. Tried with KITTI dataset (http://www.cvlibs.net/datasets/kitti/raw_data.php?type=city)

     ![](https://github.com/OakLake/Code_for_the_People/blob/master/imgs/QvO1J4.gif)

- file_IO.cpp: reading and writing to file in c++ using <fstream>

- prime_divisor.cpp: finding the prime divisors or prime factorials of a number (int)

- string_switch.cpp: switches "char"s of a string only once, run it !

- morse.cpp: converting text to morse,using C++ &lt;map&gt;,&lt;ifstream&gt; and &lt;string&gt;.

- genetic.cpp: simple genetic algorithm, crossover and mutation. fitness = number of 1's

- cell.cpp: animated cellular automata in terminal (squint your eyes for maximum efficiency).

- str_gen_sort.cpp: generate random string of predefined length range, save to file,load and sort.

- cv_colorCircDetection.cpp: detecting coloured circles with HoughCircles in opencv, with slider for adjusting parameters (colour and tuning).

- kalman.py: simple kalman filter.

![Alt text](https://github.com/OakLake/Code_for_the_People/blob/master/imgs/kalman.png)

- aruco.cpp: ArUco marker detection.

![Alt text](https://github.com/OakLake/Code_for_the_People/blob/master/imgs/aruco_detected.png)
