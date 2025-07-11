#ifndef LIDAR_READ_H
#define LIDAR_READ_H


#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "lidar_datasheet.h" // Includes your LiDARFrameTypeDef, LidarPointStructDef, CalCRC8, angle(), etc.
#include <string>
#include <iostream>

//#define SERIAL_PORT_PATH "/dev/ttyTHS0"
#define NUM_ANGLES 36000    // 360° in 0.01° increments
#define NUM_BINS 36         // every 10°: 0°, 10°, ... ,350°
#define POINT_PER_PACK 12   // as defined in your header
#define HEADER 0x54
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <cmath>

#include <filesystem>  // For directory scanning
#include <vector>

struct termios uart_tty;

int open_serial_port(std::string path)
{
    int fd = open(path.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd < 0)
    {
        printf("Could not open file %s...%d\n", path.c_str(), fd);
        exit(EXIT_FAILURE);
    }
    return fd;
}

void configure_serial_port(int fd)
{
    if (tcgetattr(fd, &uart_tty))
    {
        printf("Error getting port attributes.\n");
        exit(EXIT_FAILURE);
    }
    cfsetispeed(&uart_tty, B230400);
    cfmakeraw(&uart_tty);
    if (tcsetattr(fd, TCSANOW, &uart_tty))
    {
        printf("Error setting port attributes.\n");
        exit(EXIT_FAILURE);
    }
}

std::string findLidarPort()
{
    std::vector<std::string> possiblePorts = {"/dev/ttyTHS0", "/dev/ttyTHS1"};

    for (const auto &port : possiblePorts)
    {
        int fd = open(port.c_str(), O_RDONLY); // Open in blocking mode
        if (fd < 0)
        {
            printf("Failed to open %s\n", port.c_str());
            continue; // Try the next port
        }

        configure_serial_port(fd);

        // Try multiple reads to check for LiDAR data
        uint8_t buf[50];
        bool lidarFound = false;
        for (int attempts = 0; attempts < 10; attempts++) // Try 10 times
        {
            ssize_t recvd = read(fd, buf, sizeof(buf));
            if (recvd > 0)
            {
                for (ssize_t i = 0; i < recvd; i++)
                {
                    if (buf[i] == HEADER) // Found LiDAR header
                    {
                        lidarFound = true;
                        break;
                    }
                }
            }
            if (lidarFound) break;
            usleep(10000); // Wait 10ms before next attempt
        }

        close(fd);

        if (lidarFound)
        {
            printf("LiDAR found on %s\n", port.c_str());
            return port;
        }
    }

    printf("No valid LiDAR port found!\n");
    exit(EXIT_FAILURE);
}


// Adjustable parameters:
double time_adj = 0.1;  // Only use measurements updated within the last 0.1 seconds
double at_angle = 3.0;  // ±3° around the bin center


// Global buffers
LidarPointStructDef *distances = (LidarPointStructDef *)calloc(NUM_ANGLES, sizeof(LidarPointStructDef));
// Store the last update time (in seconds) for each angle index.
double *measurementTime = (double *)calloc(NUM_ANGLES, sizeof(double));
// Output array for the averaged distances for each 10° bin.
double angularDistances[NUM_BINS] = {0};

// Update function for a LiDAR frame; it updates both the distances and their timestamps.
void processLidarDataFrame(LiDARFrameTypeDef *frame, LidarPointStructDef *distances, double *measurementTime)
{
    if (frame->crc8 != CalCRC8((uint8_t *)frame, sizeof(LiDARFrameTypeDef) - 1))
    {
        printf("Wrong checksum: skipping frame\n");
        return;
    }
    if (frame->start_angle < frame->end_angle)
    {
        // Clear previous data in this angle range
        //memset(distances + frame->start_angle, 0, (frame->end_angle - frame->start_angle) * sizeof(LidarPointStructDef));
        
        // Get current time in seconds
        auto now = std::chrono::steady_clock::now();
        double now_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(now.time_since_epoch()).count();

        for (int i = 0; i < POINT_PER_PACK; i++)
        {
            if (frame->point[i].intensity > 10)
            {
                int idx = std::clamp(angle(frame->start_angle, frame->end_angle, i), 0, NUM_ANGLES-1);
                distances[idx] = frame->point[i];
                measurementTime[idx] = now_seconds;
            }
        }
    }
}

// Read data frames from the serial port.
void readLidarDataFrames(int fd, LidarPointStructDef *distances, double *measurementTime)
{
    const std::size_t buf_len = 4096;
    uint8_t buf[buf_len];
    ssize_t recvd = read(fd, buf, buf_len - 1);
    if (recvd >= 0)
        buf[recvd] = '\0';

    // For debugging:
    //printf("Received: %ld bytes\n", recvd);

    for (ssize_t i = 0; i < recvd-46; i++)
    {
        if (buf[i] == HEADER)
        {
            processLidarDataFrame((LiDARFrameTypeDef *)(buf + i), distances, measurementTime);
            i += 46; // Skip to next packet (adjust if needed)
        }
    }
}

// Compute the average distance for each 10° bin using only fresh data.
void updateAngularDistances(double* angularDistances, LidarPointStructDef *distances, double *measurementTime, double time_adj, double at_angle)
{
    auto now = std::chrono::steady_clock::now();
    double now_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(now.time_since_epoch()).count();
    // Convert at_angle (in degrees) to index range (since 1 index = 0.01°)
    int angle_range = static_cast<int>(at_angle * 100);

    // Loop over each 10° bin (0°, 10°, ..., 350°)
    for (int bin = 0; bin < NUM_BINS; bin++)
    {
        int bin_center = bin * 1000;  // 0°->0, 10°->1000, etc.
        double sum = 0.0;
        int count = 0;

        // Average measurements within [bin_center - angle_range, bin_center + angle_range]
        for (int offset = -angle_range; offset <= angle_range; offset++)
        {
            int index = bin_center + offset;
            // Wrap index around if it goes out of bounds
            if (index < 0)
                index += NUM_ANGLES;
            if (index >= NUM_ANGLES)
                index -= NUM_ANGLES;

            // Only consider fresh measurements
            if ((now_seconds - measurementTime[index]) <= time_adj)
            {
                sum += distances[index].distance;
                count++;
            }
        }

        angularDistances[bin] = (count > 0) ? (sum / count) : 0;
    }
}

#endif