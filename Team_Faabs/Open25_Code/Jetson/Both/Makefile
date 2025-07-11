.PHONY: run run_nogui run_noteensy all clean programm nogui noteensy Programm Programm_nogui Programm_noteensy

CXX = g++ -g 
CXXFLAGS = -Wall -std=c++17 -I/usr/include/libdwarf -I/usr/include/opencv4 -I/home/robotik/lgnurobotic_opencv/Jetson -I/home/robotik/backward-cpp
LDLIBS = -L/usr/lib -lpthread -lusb -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_flann -lopencv_videoio -ldl -ldw -lbfd -ldwarf -lunwind

default: all run
clean: 
	rm bin/Programm bin/Programm_nogui bin/Programm_noteensy bin/Programm_onlycam

Programm: bin/Programm
bin/Programm: Programm.cpp OpenCV_Proc/opencv_proc.h OpenCV_Camera/opencv_camera.h OpenCV_GUI/opencv_gui.h Teensy_Kommunikation/teensy_kommunikation.h ../rawhid/hid_LINUX.c
	$(CXX) $(CXXFLAGS) Programm.cpp /home/robotik/backward-cpp/backward.cpp ../rawhid/hid_LINUX.c $(LDLIBS) -o bin/Programm 
run: 
	bin/Programm
programm: Programm run



Programm_nogui: bin/Programm_nogui
bin/Programm_nogui: Programm.cpp OpenCV_Proc/opencv_proc.h OpenCV_Camera/opencv_camera.h OpenCV_GUI/opencv_gui.h Teensy_Kommunikation/teensy_kommunikation.h ../rawhid/hid_LINUX.c
	$(CXX) $(CXXFLAGS) -DNO_GUI Programm.cpp /home/robotik/backward-cpp/backward.cpp ../rawhid/hid_LINUX.c $(LDLIBS) -o bin/Programm_nogui
run_nogui: 
	bin/Programm_nogui
nogui: Programm_nogui run_nogui



Programm_noteensy: bin/Programm_noteensy
bin/Programm_noteensy: Programm.cpp OpenCV_Proc/opencv_proc.h OpenCV_Camera/opencv_camera.h OpenCV_GUI/opencv_gui.h Teensy_Kommunikation/teensy_kommunikation.h
	$(CXX) $(CXXFLAGS) -DNO_TEENSY Programm.cpp /home/robotik/backward-cpp/backward.cpp $(LDLIBS) -o bin/Programm_noteensy
run_noteensy: 
	bin/Programm_noteensy
noteensy: Programm_noteensy run_noteensy



Programm_onlycam: bin/Programm_onlycam
bin/Programm_onlycam: Programm.cpp OpenCV_Proc/opencv_proc.h OpenCV_Camera/opencv_camera.h OpenCV_GUI/opencv_gui.h Teensy_Kommunikation/teensy_kommunikation.h
	$(CXX) $(CXXFLAGS) -DNO_GUI -DNO_TEENSY Programm.cpp /home/robotik/backward-cpp/backward.cpp $(LDLIBS) -o bin/Programm_onlycam
run_onlycam: 
	bin/Programm_onlycam
onlycam: Programm_onlycam run_onlycam



all: Programm Programm_noteensy Programm_nogui Programm_onlycam
