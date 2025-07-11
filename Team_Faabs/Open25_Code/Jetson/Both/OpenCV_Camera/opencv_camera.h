#ifndef OPENCV_CAMERA_H
#define OPENCV_CAMERA_H

class OpenCV_Camera{
	cv::VideoCapture cam;
	std::string camSet = "nvarguscamerasrc sensor_id=1 awblock=true aelock=true wbmode=0 !  video/x-raw(memory:NVMM), width=3264, height=2464, format=NV12, framerate=21/1 ! nvvidconv flip-method=0 ! video/x-raw, width=816, height=616, format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink";

public:
	void init(){
		cam = cv::VideoCapture(camSet);
	}
	cv::Mat read(){
		cv::Mat frame;
		cam.read(frame);
		return frame;	
	}
	void release(){
		cam.release();
	}
};

#endif // OPENCV_CAMERA_H
