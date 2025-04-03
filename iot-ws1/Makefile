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
all: $(BUILD_DIR)/ebikeClient $(BUILD_DIR)/generateEBikeFile $(BUILD_DIR)/test_ebikeClient $(BUILD_DIR)/test_GPSSensor

# building main client program which read from gps and sends them
$(BUILD_DIR)/ebikeClient: $(SRC_DIR)/ebikeClient.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -o $@ $<

# building generateeBike.cpp from util
$(BUILD_DIR)/generateEBikeFile: $(SRC_DIR)/util/generateEBikeFile.cpp
	mkdir -p $(BUILD_DIR)/util
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -o $@ $<

# builds test_ebikeClient.cpp from /tests
$(BUILD_DIR)/test_ebikeClient: $(TEST_DIR)/test_ebikeClient.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(TEST_DIR) -o $@ $<

# builds test_GPSSensor.cpp from /tests
$(BUILD_DIR)/test_GPSSensor: $(TEST_DIR)/test_GPSSensor.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(TEST_DIR) -o $@ $<

# cleans previously generated files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

