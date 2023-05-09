#ifndef SRC_ALGORITHM_
#define SRC_ALGORITHM_
#include <chrono>

#include "Bar.hpp"
using namespace std::literals::chrono_literals;

class AlgorithmVisualizerController;

class Algorithm {
	// Protected Algorithm variables
	protected:
		std::string name;
		AlgorithmVisualizerController* algoVC;

	// Protected Algorithm functions
	protected:
		void swap(struct Bar *xp, struct Bar *yp);
		virtual void algorithmFinish(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay);

	// Public Algorithm functions
	public:
		Algorithm();
		Algorithm(std::string name, AlgorithmVisualizerController *VC) : name(name) { algoVC = VC; };
		virtual ~Algorithm() { };
		virtual void run(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay) = 0;
		std::string getName() { return name; };
};



class InsertionSort : public Algorithm {

	private:
		virtual void insertionSort(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay);

	public:
		InsertionSort(AlgorithmVisualizerController *algoVC) : Algorithm("Insertion Sort", algoVC) {};
		virtual void run(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay);
};


class SelectionSort: public Algorithm {

	private:
		virtual void selectionSort(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay);

	public:
		SelectionSort(AlgorithmVisualizerController *algoVC) : Algorithm("Selection Sort", algoVC) {};
		virtual void run(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay);
};




class QuickSort: public Algorithm {

	private:
		int partition(std::vector<Bar> &barVector, int low, int high, std::chrono::microseconds &delay);
		void quickSort(std::vector<Bar> &barVector, int low, int high, std::chrono::microseconds &delay);

	public:
		QuickSort(AlgorithmVisualizerController *algoVC) : Algorithm("Quick Sort", algoVC) {};
		virtual void run(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay);
};


class MergeSort: public Algorithm {

	private:
		void merge(std::vector<struct Bar> &barVector, int const left, int const mid, int const right, std::chrono::microseconds &delay);
		void mergeSort(std::vector<struct Bar> &barVector, int begin, int end, std::chrono::microseconds &delay);

	public:
		MergeSort(AlgorithmVisualizerController *algoVC) : Algorithm( "Merge Sort", algoVC) {};
		virtual void run(std::vector<struct Bar> &barVector, int sizeOfVector, std::chrono::microseconds &delay);

};

#endif