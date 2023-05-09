//#include "Platform/Platform.hpp"
#include "./Include/Headers/AlgorithmVisualizerController.hpp"
using namespace std::literals::chrono_literals;

// This program uses the SFML library to visualize sorting algorithms at work.
// Controls-----------------------------------------------------
// SpaceBar: Starts the algorithm
// R: Generates a new set of bar values
// M: Mutes the sound of the algorithm
// Left/Right Arrow Keys: Changes the selected algorithm
// Up/Down Arrow Keys: Changes the amount of bars in the set by 10
// Period/Comma: Changes the speed of the algorithm by increasing or decreasing the delay


// Creates and runs The AlgorithmVisualizerController object.
int main() {
	AlgorithmVisualizerController algoVC(100, 10ms);
	algoVC.start();
	return 0;
}




