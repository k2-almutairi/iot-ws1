#ifndef GPSSENSOR_H
#define GPSSENSOR_H

#include <cstdint>
#include "hal/ISensor.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <cstdlib>

 /*GPS sensor which reads latitdue ang longitude
 it implement the Isensor inteface from HAL files*/
class GPSSensor : public ISensor {
private:
    int id;             //Sensor id
    int dimension;      // dimension(usually 2)
    std::ifstream file; // Input file stream 

public:

     // this constructor initialize the sensor with given ID and set dimension to 2
    GPSSensor(int sensorId) : id(sensorId), dimension(2) {}

     //this constructor open provided csv file for testing in stanalone
    GPSSensor(const std::string& filepath) : id(0), dimension(2) {
        file.open(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open GPS CSV file: " + filepath);
        }
    }

     //getter function for the sensor ID
    int getId() const override {
        return id;
    }

    // getter for the dimension
    int getDimension() const override {
        return dimension;
    }


     /* this fucntion remove whitespaces ,parses values in the csv file and return the formatted string in a form like : "latitude; longitude"
     and takes into consideration the fails or exception handling*/
    std::string format(std::vector<uint8_t> reading) override {
        if (reading.empty()) return "";

        // convert the byte into string
        std::string rawLine(reading.begin(), reading.end());

        // removing whitspaces
        rawLine.erase(std::remove_if(rawLine.begin(), rawLine.end(),
            [](unsigned char c) { return std::isspace(c); }), rawLine.end());

        try {
            std::size_t pos = 0;
            // parse the latitude
            double lat = std::stod(rawLine, &pos);
            // the remain part is the longitude
            std::string rest = rawLine.substr(pos);

            // for removing leading commas
            rest.erase(0, rest.find_first_not_of(","));

            // parses the longitude
            double lon = std::stod(rest);

            // make it in form latitude; longitude" and return it
            std::ostringstream oss;
            oss << lat << "; " << lon;
            return oss.str();
        } catch (const std::exception& e) {
            // if fail , exception return original string
            return rawLine;
        }
    }

   
     /*reads one line from file,expects it to contain comma-separation,
     returns the formatted string in theform:"latitude; longitude".*/
    
    std::string readValue() {
        std::string line;
        if (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string lat, lon;
            if (!std::getline(ss, lat, ',')) return "";
            if (!std::getline(ss, lon, ',')) return "";
            return lat + "; " + lon;
        }
        return "";
    }

    //Destructor
    ~GPSSensor() {
        if (file.is_open()) {
            file.close();
        }
    }
};

#endif

