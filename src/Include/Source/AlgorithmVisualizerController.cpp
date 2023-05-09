#include "../Headers/AlgorithmVisualizerController.hpp"
#include "../Headers/Bar.hpp"


//Constructor.
AlgorithmVisualizerController::AlgorithmVisualizerController(int sizeOfVector, std::chrono::microseconds delay)
: mainWindow(sf::VideoMode(800.0f,800.0f), "Sorting Algorithm Visualizer")
, sizeofVector(sizeOfVector), delay(delay) {

	// Initializes the algorithm pointer to an Insertion Sort object.
	algorithm = new InsertionSort(this);

	// Pre-loads all sound files into Buffers which is stored in the SoundBuffers map,
	// the Map uses the  AlgorithmVisualizerController Sound enums as its identifier.
	std::string filenames[] = {"content/xylophoneSounds/D.wav"
							  ,"content/xylophoneSounds/E.wav"
							  ,"content/xylophoneSounds/F.wav"
							  ,"content/xylophoneSounds/G.wav"
							  ,"content/xylophoneSounds/A.wav"
							  ,"content/xylophoneSounds/B.wav"
							  ,"content/xylophoneSounds/C.wav"
							  ,"content/xylophoneSounds/Dhigh.wav"
							  ,"content/xylophoneSounds/Ehigh.wav"};
	for(int i = Sounds::D; i != Sounds::LAST; i++){
		sf::SoundBuffer *tempBuffer = new sf::SoundBuffer;
		if(!tempBuffer->loadFromFile(filenames[i])) {
			throw std::runtime_error("TextureHolder::load - Failed to load " + filenames[i]);
		} else {
			soundBuffers.insert(std::make_pair(static_cast<Sounds>(i), std::move(tempBuffer)));
		}
	}
}


// Starts the Program loop
void AlgorithmVisualizerController::start() {
	generateVector();
	while(mainWindow.isOpen()) {
		handleInput();
		draw();
	}
}

void AlgorithmVisualizerController::handleInput() {
	while(mainWindow.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				mainWindow.close();
				break;

			case sf::Event::KeyPressed:

				// Starts the Thread which runs the selected Algorithm.
				if(event.key.code == sf::Keyboard::Space && !isRunning) {
					algorithmThread = std::thread(&Algorithm::run, algorithm, std::ref(barVector), sizeofVector, std::ref(delay));
					algorithmThread.detach();
					isRunning = true;
				}

				// Generates a new set of Values for the vector.
				if(event.key.code == sf::Keyboard::R && !isRunning) {
					generateVector();
				}

				// Closes the window.
				if(event.key.code == sf::Keyboard::Escape) {
					mainWindow.close();
				}

				// Mutes the horrid noise this beast makes.
				if(event.key.code == sf::Keyboard::M) {
					isMuted = !isMuted;
				}


				// Listens to the left and right arrow keys and handles the selection of the algorithm.
				if((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) && !isRunning) {
					chosenAlgorithm = (event.key.code == sf::Keyboard::Left) ? chosenAlgorithm - 1 : chosenAlgorithm + 1;
					switch (chosenAlgorithm){
						case 0:
							algorithm = new InsertionSort(this);
							break;

						case 1:
							algorithm = new SelectionSort(this);
							break;

						case 2:
							algorithm = new QuickSort(this);
							break;

						case 3:
							algorithm = new MergeSort(this);
							break;

						default:
							algorithm = new InsertionSort(this);
							chosenAlgorithm = 0;
							break;
					}
				}

				// Listens to the up and down arrow keys, increases the size of the bar vector and generates a new bar vector.
				if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) && !isRunning) {
					sizeofVector = (event.key.code == sf::Keyboard::Up) ? sizeofVector + 10 : sizeofVector - 10;
					generateVector();
				}

				// Listens to the Period and Comma buttons and changes amount of delay in each algorithm.
				if(event.key.code == sf::Keyboard::Period || (event.key.code == sf::Keyboard::Comma && delay > 0ms)) {
					delay = (event.key.code == sf::Keyboard::Comma) ? delay - 1ms : delay + 1ms;
				}
					break;



			default:
				break;
		}
	}

}

// Draws all the bars within the BarVector vector, also calls the draw value function
void AlgorithmVisualizerController::draw() {
		mainWindow.clear();
		float width = mainWindow.getSize().x;
		float outLine = (width/sizeofVector < 4) ? 0 : 1.0f;
		for(int i = 0; i < sizeofVector; i++) {
			sf::RectangleShape rectangle;
			rectangle.setOrigin(0.f, barVector[i].value);
			rectangle.setSize(sf::Vector2f(width/float(sizeofVector), barVector[i].value));
			rectangle.setOutlineColor(sf::Color::Black);
			rectangle.setFillColor(barVector[i].color);
			rectangle.setOutlineThickness(outLine);
			rectangle.setPosition((width/float(sizeofVector))*i, mainWindow.getSize().y);
			mainWindow.draw(rectangle);
		}
		drawInfo();
		mainWindow.display();
}


// Handles displaying the algorithm values.
// Current Algorithm
// Delay time
// Number of Bars
// is Muted
void AlgorithmVisualizerController::drawInfo() {
	sf::Font font;
	font.loadFromFile("content/Roboto-Black.ttf");

	sf::Text nameText(algorithm->getName(), font);
	nameText.setCharacterSize(15);
	nameText.setStyle(sf::Text::Bold);
	nameText.setFillColor(sf::Color::White);
	mainWindow.draw(nameText);

	sf::Text delayText("Delay: " + std::to_string((delay.count() / 1000)) + "ms", font);
	delayText.setCharacterSize(15);
	delayText.setStyle(sf::Text::Bold);
	delayText.setFillColor(sf::Color::White);
	delayText.setPosition(150, 0);
	mainWindow.draw(delayText);

	sf::Text vecSizeText("Vector Size: " + std::to_string(sizeofVector), font);
	vecSizeText.setCharacterSize(15);
	vecSizeText.setStyle(sf::Text::Bold);
	vecSizeText.setFillColor(sf::Color::White);
	vecSizeText.setPosition(275, 0);
	mainWindow.draw(vecSizeText);

	std::string mutedString = (isMuted) ? "On" : "Off";
	sf::Text muteText("Mute: " + mutedString, font);
	muteText.setCharacterSize(15);
	muteText.setStyle(sf::Text::Bold);
	muteText.setFillColor(sf::Color::White);
	muteText.setPosition(700, 0);
	mainWindow.draw(muteText);
}




//Generates a new vector
void AlgorithmVisualizerController::generateVector() {
		barVector.clear();
		for(int i = 0; i < sizeofVector; i++) {
			struct Bar bar;
			bar.color = sf::Color::White;
			bar.value = (rand() % 700) + 10;
			barVector.push_back(bar);
		}
}



// Takes in the a value from a bar and integer divides it by 100 to get a 1 digit number.
// then uses a switch statment to decide which sound to load from the soundBuffer Map and finally plays the sound.
void AlgorithmVisualizerController::playSound(int value) {
	if(delay != 0ms && !isMuted) {
	int noteValue = value / 100;
	switch(noteValue){
		case 0:
			sound.setBuffer(*soundBuffers.find(Sounds::D)->second);
			break;
		case 1:
			sound.setBuffer(*soundBuffers.find(Sounds::E)->second);
			break;
		case 2:
			sound.setBuffer(*soundBuffers.find(Sounds::F)->second);
			break;
		case 3:
			sound.setBuffer(*soundBuffers.find(Sounds::G)->second);
			break;
		case 4:
			sound.setBuffer(*soundBuffers.find(Sounds::A)->second);
			break;
		case 5:
			sound.setBuffer(*soundBuffers.find(Sounds::B)->second);
			break;
		case 6:
			sound.setBuffer(*soundBuffers.find(Sounds::C)->second);
			break;
		case 7:
			sound.setBuffer(*soundBuffers.find(Sounds::DHIGH)->second);
			break;
		case 8:
			sound.setBuffer(*soundBuffers.find(Sounds::EHIGH)->second);
			break;
		default:
			break;

	}
		sound.play();

	}

}

// Sets the is running boolean value, used to tell if the algorithm is still in
// progress and locks out player input if it is.
void AlgorithmVisualizerController::setRunning(bool running) {
	isRunning = running;
}