#ifndef OPENCV_PROC_H
#define OPENCV_PROC_H

constexpr int NOF_ERODE_DILATE = 1;

class OpenCV_Proc{
	cv::Scalar lower;
	cv::Scalar upper;
public:
	void setLower(cv::Scalar lower){
		this->lower = lower;
	}
	void setUpper(cv::Scalar upper){
		this->upper = upper;
	}
	std::tuple<cv::Mat, std::optional<cv::Rect>> process(cv::Mat frame_input){
		cv::Mat frame;
		cv::GaussianBlur(frame_input, frame, cv::Size(3, 3), 0);
		cv::cvtColor(frame, frame, cv::COLOR_BGR2HSV);
		cv::inRange(frame, lower, upper, frame);
		for (int i = 0; i < NOF_ERODE_DILATE; i++) {
			cv::erode(frame, frame, cv::Mat());
			cv::dilate(frame, frame, cv::Mat());
		}
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(frame, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
		int bigestBallArea = 0;
		int BNbBall;
		if (contours.size() > 0) {
			for (uint i = 0; i < contours.size(); i++) {
				cv::Rect r = cv::boundingRect(contours[i]);
				if (bigestBallArea < (r.height * r.width)) {
					bigestBallArea = r.height * r.width;
					BNbBall = i;
				}
			}
			return std::make_tuple(frame, cv::boundingRect(contours[BNbBall]));
		}
		return std::make_tuple(frame, std::nullopt);
	}
};

#endif // OPENCV_PROC_H
