#include "../Headers/Algorithm.hpp"
#include "../Headers/AlgorithmVisualizerController.hpp"


// Creates and merges 2 sub-vectors
void MergeSort::merge(std::vector<struct Bar> &barVector, int const left, int const mid, int const right, std::chrono::microseconds &delay)
{

    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;


    auto *leftArray = new struct Bar[subArrayOne],
         *rightArray = new struct Bar[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++) {


        leftArray[i] = barVector[left + i];
		barVector[left+i].color = sf::Color::Blue;
		std::this_thread::sleep_for(delay);
	}
    for (auto j = 0; j < subArrayTwo; j++) {
        rightArray[j] = barVector[mid + 1 + j];
		barVector[mid+1+j].color = sf::Color::Blue;
		std::this_thread::sleep_for(delay);
	}

    auto indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;



    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].value <= rightArray[indexOfSubArrayTwo].value) {
            barVector[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
			barVector[indexOfMergedArray].color = sf::Color::Blue;
		std::this_thread::sleep_for(delay);
        }
        else {
            barVector[indexOfMergedArray].value = rightArray[indexOfSubArrayTwo].value;
            indexOfSubArrayTwo++;
            		std::this_thread::sleep_for(delay);

        }
        algoVC->playSound(barVector[indexOfMergedArray].value);
        indexOfMergedArray++;
    }


    while (indexOfSubArrayOne < subArrayOne) {
        barVector[indexOfMergedArray].value = leftArray[indexOfSubArrayOne].value;
        indexOfSubArrayOne++;
        indexOfMergedArray++;
		std::this_thread::sleep_for(delay);
    }


    while (indexOfSubArrayTwo < subArrayTwo) {
        barVector[indexOfMergedArray].value = rightArray[indexOfSubArrayTwo].value;
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
		std::this_thread::sleep_for(delay);
    }

}


// Function which recursively performs a Merge sort algorithm on the provided struct Bar vector
void MergeSort::mergeSort(std::vector<struct Bar> &barVector, int begin, int end, std::chrono::microseconds &delay)
{
    if (begin >= end) return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(barVector, begin, mid, delay);
    mergeSort(barVector, mid + 1, end, delay);
    merge(barVector, begin, mid, end, delay);
}



// Overridden run() function which calls all necessary functions to sort a given struct Bar vector using
// the Merge Sort functions.
void MergeSort::run(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay)
{
	mergeSort(barVector, 0, sizeOfVector-1, delay);
	algorithmFinish(barVector, sizeOfVector, delay);
}
