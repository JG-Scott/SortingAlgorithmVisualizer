#ifndef SRC_ALGORITHM_CONTROLLER_
#define SRC_ALGORITHM_CONTROLLER_
#include "Algorithm.hpp"
#include "Bar.hpp"
class AlgorithmVisualizerController {
	private: // SFML Display Sound Variables
	sf::RenderWindow mainWindow;
	sf::Event event;


	private: // SFML Sound Variables
	enum Sounds {
		D,
		E,
		F,
		G,
		A,
		B,
		C,
		DHIGH,
		EHIGH,
		LAST,
	};
	std::map<Sounds, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
	sf::SoundBuffer buffer;
	sf::Sound sound;

	private: // Algorithm Variables
	Algorithm *algorithm;
	std::vector<struct Bar> barVector;
	int sizeofVector;
	std::chrono::microseconds delay;

	private: //GUI control Variables
	std::thread algorithmThread;
	int chosenAlgorithm = 0;
	bool isMuted = false;
	bool isRunning = false;



	public: // Public Algorithm controller Functions
	AlgorithmVisualizerController(int sizeOfVector, std::chrono::microseconds delay);
	void start();
	void handleInput();
	void draw();
	void drawInfo();
	void playSound(int value);
	void generateVector();
	void setRunning(bool running);
};


#endif