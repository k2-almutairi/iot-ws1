#include "GPSSensor.h"
#include "hal/CSVHALManager.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#include <memory>


 //prints current timestamp to std::cout in a format [YYYY-MM-DD HH:MM:SS].
void printTimestamp() 
{
    auto now = std::chrono::system_clock::now();
    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[" << std::put_time(std::localtime(&t_c), "%Y-%m-%d %H:%M:%S") << "] ";
}


 /* main function , initializes HAL manager, atach to GPSSensor, reads data from int and print them with timestamps*/
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./ebikeClient <csv_path> <sensor_id>" << std::endl;
        return 1;
    }

    // getting thearguments from command line and assining them
    std::string csvPath = argv[1];
    int sensorId = std::stoi(argv[2]) - 1; // decrementing the id since it have dimension 2 in csv

    // initializing HAL with 1 port
    CSVHALManager hal(1);
    hal.initialise(csvPath);

    // declaring GPS sensor for the HAL usinf the given id.
    std::shared_ptr<GPSSensor> gps = std::make_shared<GPSSensor>(sensorId);
    hal.attachDevice(0, gps);

    // main loop:read gps data and print them every 5 seconds
    while (true) 
      {
        try {
            // reading data from sensor using HAL manager
            auto data = hal.read(0);
            // format the reading into readble format
            std::string reading = gps->format(data);
            // print the current time
            printTimestamp();
            std::cout << "GPS: " << reading << std::endl;
        } catch (const std::out_of_range& e) {
            // break when no more rows available
            break;
        }
        // 5 seconds delay
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    // releasing drom port
    hal.releaseDevice(0);
    return 0;
}

