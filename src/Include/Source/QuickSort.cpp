#include "../Headers/Algorithm.hpp"
#include "../Headers/AlgorithmVisualizerController.hpp"

using namespace std::literals::chrono_literals;


// A function which selects a pivot point and is used to seperate the vector into 2 sub-vectors based on
// if the values are higher or lower than the pivot point.
int QuickSort::partition (std::vector<Bar> &barVector, int low, int high, std::chrono::microseconds &delay)
{
    int pivot = barVector[high].value;

    int i = (low - 1);

    sf::Color sectionColor = sf::Color(rand() % 100, rand() % 100, rand() % 255); // generates a random near blue color for each partition section.

    for (int j = low; j <= high - 1; j++)
    {
		barVector[j].color = sectionColor;
        if (barVector[j].value < pivot)
        {
            i++;
            swap(&barVector[i], &barVector[j]);
            algoVC->playSound(barVector[j].value);
			std::this_thread::sleep_for(delay);
            algoVC->playSound(barVector[i].value);
		}
    }

    swap(&barVector[i + 1], &barVector[high]);
	barVector[i+1].color = sf::Color::Red;

    algoVC->playSound(barVector[high].value);
	std::this_thread::sleep_for(delay);


    return (i + 1);
}


// Function which recursively performs a Quick sort algorithm on the provided struct Bar vector
void QuickSort::quickSort(std::vector<Bar> &barVector, int low, int high, std::chrono::microseconds &delay) {
	    if (low < high)
    {
        int partitionIndex = partition(barVector, low, high, delay);
        quickSort(barVector, low, partitionIndex - 1, delay);
        quickSort(barVector, partitionIndex + 1, high, delay);
    }
}


// Overridden run() function which calls all necessary functions to sort a given struct Bar vector using
// the Quick Sort functions.
void QuickSort::run(std::vector<Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay)
{
	quickSort(barVector, 0, sizeOfVector-1, delay);
	algorithmFinish(barVector, sizeOfVector, delay);
}
