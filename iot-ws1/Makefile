# compiler used for building
CXX = g++

# Compilation flags: -std=c++17 : Use the C++17 standard  ,-Wall :whichenables all compiler warnings
CXXFLAGS = -std=c++17 -Wall

# src code directory
SRC_DIR = src

# unit tests directory
TEST_DIR = tests

# build output directory
BUILD_DIR = build

# all :builds everything(both mains and tests
all: ebikeClient generateEBikeFile test_test_ebikeClient test_test_GPSSensor

# building main client program which read from gps and sends them
ebikeClient: $(SRC_DIR)/ebikeClient.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -o $@ $<
	chmod +x $@

# building generateeBike.cpp from util
generateEBikeFile: $(SRC_DIR)/util/generateEBikeFile.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -o $@ $<
	chmod +x $@

# builds test_ebikeClient.cpp from /tests
test_test_ebikeClient: $(TEST_DIR)/test_ebikeClient.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(TEST_DIR) -o $@ $<
	chmod +x $@

# builds test_GPSSensor.cpp from /tests
test_test_GPSSensor: $(TEST_DIR)/test_GPSSensor.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(TEST_DIR) -o $@ $<
	chmod +x $@

# cleans previously generated files
clean:
	rm -f ebikeClient generateEBikeFile test_test_ebikeClient test_test_GPSSensor

.PHONY: all clean

