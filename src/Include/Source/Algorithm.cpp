#include "../Headers/Algorithm.hpp"
#include "../Headers/AlgorithmVisualizerController.hpp"

using namespace std::literals::chrono_literals;


// Default constructor
Algorithm::Algorithm() {
	name = "none";
}

//Swaps the value of 2 Bar objects
void Algorithm::swap(struct Bar *xp, struct Bar *yp) {
    struct Bar temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// turns each rectangle green from lowest to highest value
// to signify the algorithm is finished
void Algorithm::algorithmFinish(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay) {
	for(int i = 0; i < sizeOfVector; i++) {
		barVector[i].color = sf::Color::Green;
        algoVC->playSound(barVector[i].value);
		std::this_thread::sleep_for(delay);
	}
    algoVC->setRunning(false);
}