#include "../Headers/Algorithm.hpp"
#include "../Headers/AlgorithmVisualizerController.hpp"

// Function which performs an Selection sort algorithm on the provided struct Bar vector
void SelectionSort::selectionSort(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay) {
	int lowest = 0;
	int counter = 0;
	int current = 0;

    for (counter = 0; counter < sizeOfVector; counter++)
    {
        lowest = counter;
        for (current = counter+1; current < sizeOfVector; current++) {
			barVector[current].color = sf::Color::Red;
			algoVC->playSound(barVector[current].value);
			std::this_thread::sleep_for(delay);
        	if (barVector[current].value < barVector[lowest].value) {
				barVector[lowest].color = sf::Color::White;
            	lowest = current;
				algoVC->playSound(barVector[lowest].value);

			}
			barVector[current].color = sf::Color::White;
			barVector[lowest].color = sf::Color::Blue;
		}


        swap(&barVector[lowest], &barVector[counter]);
		barVector[lowest].color = sf::Color::Blue;
    }
}


// Overridden run() function which calls all necessary functions to sort a given struct Bar vector using
// the Selection Sort functions.
void SelectionSort::run(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay) {
	selectionSort(barVector, sizeOfVector, delay);
	algorithmFinish(barVector, sizeOfVector, delay);
}
