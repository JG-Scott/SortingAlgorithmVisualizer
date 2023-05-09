#include "../Headers/Algorithm.hpp"
#include "../Headers/AlgorithmVisualizerController.hpp"
using namespace std::literals::chrono_literals;


// Function which performs an Insertion sort algorithm on the provided struct Bar vector
void InsertionSort::insertionSort(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay){
	int current = 0;
	int key = 0;
    for (int i = 1; i < sizeOfVector; i++)
    {
        key = barVector[i].value;
        current = i - 1;

        while (current >= 0 && barVector[current].value > key)
        {
			swap(&barVector[current + 1], &barVector[current]);
			algoVC->playSound(barVector[current+1].value);
			barVector[current+1].color = sf::Color::Blue;
            current = current - 1;

			std::this_thread::sleep_for(delay);
        }

        barVector[current + 1].color = sf::Color::Blue;
        barVector[current + 1].value = key;
    }
}

// Overridden run() function which calls all necessary functions to sort a given struct Bar vector using
// the Insertion Sort functions.
void InsertionSort::run(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay) {
	insertionSort(barVector, sizeOfVector, delay);
	algorithmFinish(barVector, sizeOfVector, delay);
}