#ifndef OPENCV_GUI_H
#define OPENCV_GUI_H
#include <fstream>
constexpr int centerX = 408;
constexpr int centerY = 308;

cv::Point p1(centerX + 12, centerY);
cv::Point p2(centerX - 12, centerY);
cv::Point p3(centerX, centerY + 12);
cv::Point p4(centerX, centerY - 12);
cv::Point center(centerX, centerY);

int lower[3] = {0, 197, 62};
int upper[3] = {18, 255, 171};
int id = 0;	
int save = 0;
std::string calibConfigPath = "/home/robotik/lgnurobotic_opencv/Jetson/Both/calib.config";

class OpenCV_GUI{
	#ifdef GUI
		std::string windowNameCam = "Cam";
		std::string windowNameCamorigin = "CamOrigin";
		std::string windowNameBars = "Calib";
	#endif
	struct config { 
		int lowers[3][3] = {{0, 197, 62}, {20, 220, 50}, {32, 95, 43}};   // y: 23, 140, 58 ########## b:90, 67, 33
		int uppers[3][3] = {{18, 255, 171}, {32, 255, 159}, {55, 145, 55}}; // y: 63, 255, 255 ######### b:179, 255, 130
		int indexs = 0;
		int *lower_temp = lower;
		int *upper_temp = upper;
		int *id_temp = &id;
	} config;	
public:
	static void lowerupper_Callback(int pos, void *userdata){
		struct config* config = (struct config*) userdata;
		config->lowers[config->indexs][0] = config->lower_temp[0];
		config->lowers[config->indexs][1] = config->lower_temp[1];
		config->lowers[config->indexs][2] = config->lower_temp[2];
		config->uppers[config->indexs][0] = config->upper_temp[0];
		config->uppers[config->indexs][1] = config->upper_temp[1];
		config->uppers[config->indexs][2] = config->upper_temp[2];
	} 
	static void index_Callback(int pos, void *userdata){
		std::string windowNameBars = "Calib";
		struct config* config = (struct config*) userdata;
		config->indexs = *config->id_temp;

		config->lower_temp[0] = config->lowers[config->indexs][0];
		config->lower_temp[1] = config->lowers[config->indexs][1];
		config->lower_temp[2] = config->lowers[config->indexs][2];
		config->upper_temp[0] = config->uppers[config->indexs][0];
		config->upper_temp[1] = config->uppers[config->indexs][1];
		config->upper_temp[2] = config->uppers[config->indexs][2];

		cv::setTrackbarPos("[0] Lower", windowNameBars, config->lowers[config->indexs][0]);
		cv::setTrackbarPos("[1] Lower", windowNameBars, config->lowers[config->indexs][1]);
		cv::setTrackbarPos("[2] Lower", windowNameBars, config->lowers[config->indexs][2]);
		cv::setTrackbarPos("[0] Upper", windowNameBars, config->uppers[config->indexs][0]);
		cv::setTrackbarPos("[1] Upper", windowNameBars, config->uppers[config->indexs][1]);
		cv::setTrackbarPos("[2] Upper", windowNameBars, config->uppers[config->indexs][2]);
	} 
	static void save_Callback(int pos, void *userdata){
		struct config* config = (struct config*) userdata;
		std::ofstream file(calibConfigPath);
		file << config->indexs;
		file << std::endl;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				file << config->lowers[i][j];
				file << " ";
			} 
			file << std::endl;
		} 
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				file << config->uppers[i][j];
				file << " ";
			} 
			file << std::endl;
		} 
	}	
	void init(){
		std::ifstream file(calibConfigPath);
		if(file.is_open()){
			file >> config.indexs;
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					file >> config.lowers[i][j];
				} 
			} 
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					file >> config.uppers[i][j];
				} 
			} 
		} 
		#ifdef GUI
			cv::namedWindow(windowNameCam, cv::WINDOW_NORMAL);
			cv::namedWindow(windowNameBars, cv::WINDOW_NORMAL);
			cv::namedWindow(windowNameCamorigin, cv::WINDOW_NORMAL);

			cv::createTrackbar("[0] Lower", windowNameBars, lower + 0, 179, lowerupper_Callback, &config);
			cv::createTrackbar("[1] Lower", windowNameBars, lower + 1, 255, lowerupper_Callback, &config);
			cv::createTrackbar("[2] Lower", windowNameBars, lower + 2, 255, lowerupper_Callback, &config);
			cv::createTrackbar("[0] Upper", windowNameBars, upper + 0, 179, lowerupper_Callback, &config);
			cv::createTrackbar("[1] Upper", windowNameBars, upper + 1, 255, lowerupper_Callback, &config);
			cv::createTrackbar("[2] Upper", windowNameBars, upper + 2, 255, lowerupper_Callback, &config);
			cv::createTrackbar("index", windowNameBars, &id, 2, index_Callback, &config);
			cv::createTrackbar("save", windowNameBars, &save, 1, save_Callback, &config);
		
			cv::setTrackbarPos("index", windowNameBars, config.indexs);
		#endif
	}
	cv::Scalar getLower(int index){
		return cv::Scalar_<int>{config.lowers[index][0], config.lowers[index][1], config.lowers[index][2]};
	}
	cv::Scalar getUpper(int index){
		return cv::Scalar_<int>{config.uppers[index][0], config.uppers[index][1], config.uppers[index][2]};
	}	
	int getIndex(){
		return config.indexs;
	}	
	void show(cv::Mat original, std::tuple<cv::Mat, std::optional<cv::Rect>> result){
		#ifdef GUI
			std::optional<cv::Rect> second = std::get<1>(result);
			if(second.has_value()){
				cv::Rect ball = second.value();
				cv::rectangle(original, ball, cv::Scalar(0, 165, 255), 2);
				int centerBallX = ball.x + (ball.width / 2);
				int centerBallY = ball.y + (ball.height / 2);
				cv::Point pBall(centerBallX, centerBallY);
				cv::line(original, center, pBall, cv::Scalar(255, 255, 255), 1);
			}

			cv::line(original,p1,p2,cv::Scalar(255,0,0),2);
			cv::line(original,p3,p4,cv::Scalar(255,0,0),2);
			cv::imshow(windowNameCam, std::get<0>(result));
			cv::imshow(windowNameCamorigin, original);
		#endif
	}
	bool waitKey(){
		return cv::waitKey(1)=='q';
	}
};

#endif // OPENCV_GUI_H
