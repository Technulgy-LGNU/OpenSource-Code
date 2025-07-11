#ifndef TEENSY_KOMMUNIKATION_H
#define TEENSY_KOMMUNIKATION_H

#ifdef TEENSY
#include "rawhid/hid.h"
#endif

class Teensy{
public:
	void connect(){
		#ifdef TEENSY
			printf("connecting\n");
			int r = 0;
			do {
				r = rawhid_open(1, 0x16C0, 0x0486, 0xFFAB, 0x0200);
			} while (r <= 0);
			printf("opened rawhid device\n");
		#endif
	}
	
	void reconnect(){
		connect();
	}
	
	bool send(char *buf, int len){
		#ifdef TEENSY
			bool ok = rawhid_send(0, buf, len, 100)>=0;
			#if VERBOSE
				if(!ok){
					std::cout << "error while senden" << std::endl;
				}
			#endif
			return ok;
		#else
			return false;
		#endif
	}
	
	bool transmit(std::optional<cv::Rect>ball,std::optional<cv::Rect>goalY,std::optional<cv::Rect>goalB, double angularDistances[NUM_BINS]  ){
		#if defined(TEENSY) | VERBOSE
			bool ob = ball.has_value();
			int16_t ox = ob?ball->x + (ball->width / 2):0;
			int16_t oy = ob?ball->y + (ball->height / 2):0;
			int16_t oh = ob?ball->height:0;
			int16_t ow = ob?ball->width:0;
			
			bool yb = goalY.has_value();
			int16_t yx = yb?goalY->x + (goalY->width / 2):0;
			int16_t yy = yb?goalY->y + (goalY->height / 2):0;
			int16_t yh = yb?goalY->height:0;
			int16_t yw = yb?goalY->width:0;

			bool bb = goalB.has_value();
			int16_t bx = bb?goalB->x + (goalB->width / 2):0;
			int16_t by = bb?goalB->y + (goalB->height / 2):0;
			int16_t bh = bb?goalB->height:0;
			int16_t bw = bb?goalB->width:0;

			//int bx_r = 308- by;
			//int by_r = 408- bx;
			

			char msg[54];
			for(int i=0;i<54;i++){
				msg[i]=0;
			}

			msg[0] = ((ob >> 0) & ((1<<1)-1)) << 0 | ((ox >> 0) & ((1<<6)-1)) << 1;
			msg[1] = ((ox >> 6) & ((1<<4)-1)) << 0 | ((oy >> 0) & ((1<<3)-1)) << 4;
			msg[2] = ((oy >> 3) & ((1<<7)-1)) << 0;
			msg[3] = ((ow >> 0) & ((1<<7)-1)) << 0;
			msg[4] = ((ow >> 7) & ((1<<3)-1)) << 0 | ((oh >> 0) & ((1<<4)-1)) << 3;
			msg[5] = ((oh >> 4) & ((1<<6)-1)) << 0 | ((yb >> 0) & ((1<<1)-1)) << 6;
			msg[6] = ((yx >> 0) & ((1<<7)-1)) << 0;
			msg[7] = ((yx >> 7) & ((1<<3)-1)) << 0 | ((yy >> 0) & ((1<<4)-1)) << 3;
			msg[8] = ((yy >> 4) & ((1<<6)-1)) << 0 | ((yw >> 0) & ((1<<1)-1)) << 6;
			msg[9] = ((yw >> 1) & ((1<<7)-1)) << 0;
			msg[10] = ((yw >> 8) & ((1<<2)-1)) << 0 | ((yh >> 0) & ((1<<5)-1)) << 2;
			msg[11] = ((yh >> 5) & ((1<<5)-1)) << 0 | ((bb >> 0) & ((1<<1)-1)) << 5 | ((bx >> 0) & ((1<<1)-1)) << 6;
			msg[12] = ((bx >> 1) & ((1<<7)-1)) << 0;
			msg[13] = ((bx >> 8) & ((1<<2)-1)) << 0 | ((by >> 0) & ((1<<5)-1)) << 2;
			msg[14] = ((by >> 5) & ((1<<5)-1)) << 0 | ((bw >> 0) & ((1<<2)-1)) << 5;
			msg[15] = ((bw >> 2) & ((1<<7)-1)) << 0;
			msg[16] = ((bw >> 9) & ((1<<1)-1)) << 0 | ((bh >> 0) & ((1<<6)-1)) << 1;
			msg[17] = ((bh >> 6) & ((1<<4)-1)) << 0 | (1<<7);

			for(int i =0; i<NUM_BINS; i++)
			{
				msg[18+i] = std::clamp((int)angularDistances[i]/10,0,255); 
			}
			printf("%u\n",ob);

			#if VERBOSE
				//printf("%u,%u,%u\n", msg[0], msg[1], msg[2]);
				//printf("%d,%d,%d\n", bb, bx_r, by_r);
			#endif
			return send(msg, 54);
		#else
			return false;
		#endif
	}

	void close(){
		#ifdef TEENSY
			rawhid_close(0);
		#endif
	}
};

#endif // TEENSY_KOMMUNIKATION_H
