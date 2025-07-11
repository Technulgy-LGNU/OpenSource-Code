#ifndef NO_GUI
#define GUI
#endif

#ifndef NO_TEENSY
#define TEENSY
#endif

#define VERBOSE 1

#include <opencv2/opencv.hpp>
#include <iostream>
#include <optional>
#include <fcntl.h>
#include <unistd.h>

#include "lidar/lidar_read.h"
#include "Teensy_Kommunikation/teensy_kommunikation.h"
#include "OpenCV_GUI/opencv_gui.h"
#include "OpenCV_Camera/opencv_camera.h"
#include "OpenCV_Proc/opencv_proc.h"

Teensy teensy;
OpenCV_GUI gui;
OpenCV_Camera cam;
OpenCV_Proc proc1, proc2, proc3;

pthread_t proc1_thread, proc2_thread, proc3_thread, lidar_thread;
pthread_barrier_t barrier1, barrier2;
pthread_mutex_t l_mutex;
cv::Mat frame;
std::tuple<cv::Mat, std::optional<cv::Rect>> result1, result2, result3; 


void* proc1_func(void* args){
	for(;;){
		pthread_barrier_wait(&barrier1);
		result1 = proc1.process(frame);
		pthread_barrier_wait(&barrier2);
	}
}
void* proc2_func(void* args){
	for(;;){
		pthread_barrier_wait(&barrier1);
		result2 = proc2.process(frame);
		pthread_barrier_wait(&barrier2);
	}
}
void* proc3_func(void* args){
	for(;;){
		pthread_barrier_wait(&barrier1);
		result3 = proc3.process(frame);
		pthread_barrier_wait(&barrier2);
	}
}
void* lidar_func(void* args){
	std::string foundPort = findLidarPort();
	
	int uart_fd = open_serial_port(foundPort);
    configure_serial_port(uart_fd);

	for(;;){
		
	    // Update the distances and measurementTime arrays with new LiDAR data.
        readLidarDataFrames(uart_fd, distances, measurementTime);
		pthread_mutex_lock(&l_mutex);
        // Calculate the averaged distances for each 10° bin using only fresh measurements.
        updateAngularDistances(angularDistances, distances, measurementTime, time_adj, at_angle);
        pthread_mutex_unlock(&l_mutex);
	    usleep(100000); 
    }
    close(uart_fd);
    return 0;
}

int main()
{
	teensy.connect();
	gui.init();
	cam.init();

	pthread_barrier_init(&barrier1, NULL, 4);
	pthread_barrier_init(&barrier2, NULL, 4);
	pthread_mutex_init(&l_mutex, NULL);

	pthread_create(&proc1_thread, NULL, proc1_func, NULL);
	pthread_create(&proc2_thread, NULL, proc2_func, NULL);
	pthread_create(&proc3_thread, NULL, proc3_func, NULL);

	//lidar thread
	pthread_create(&lidar_thread, NULL, lidar_func, NULL);

	for (;;) {
		proc1.setLower(gui.getLower(0));
		proc1.setUpper(gui.getUpper(0));
		proc2.setLower(gui.getLower(1));
		proc2.setUpper(gui.getUpper(1));
		proc3.setLower(gui.getLower(2));
		proc3.setUpper(gui.getUpper(2));
		
		frame = cam.read();

		pthread_barrier_wait(&barrier1);
		pthread_barrier_wait(&barrier2);

		switch(gui.getIndex()){
			case 0:
				gui.show(frame, result1);
			break;
			case 1:
				gui.show(frame, result2);
			break;
			case 2:
				gui.show(frame, result3);
			break;
			default:
				gui.show(frame, result1);
			break;
		} 
		pthread_mutex_lock(&l_mutex);
		if (!teensy.transmit(std::get<1>(result1),std::get<1>(result2),std::get<1>(result3),angularDistances)) {
			teensy.reconnect();
		}
		pthread_mutex_unlock(&l_mutex);

		if(gui.waitKey())break;
	}
	cam.release();
	teensy.close();
}
