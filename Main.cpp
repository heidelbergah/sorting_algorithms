#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

const int windowWidth = 1200;
const int windowHeight = 800;
const int blockMaxHeight = windowHeight - 200;
int numOfBlocks = 80;
int timeToSort = 0;
bool hasBeenRun = false;
bool hasBeenSorted = false;

class Block {
public:
	RectangleShape block;
	Block(int identifier) {
		ID = identifier;
		block.setFillColor(Color::Yellow);
		//block.setOutlineThickness(1);
		//block.setOutlineColor(Color::Black);
		block.setSize(Vector2f(windowWidth / numOfBlocks, blockHeight));
		block.setOrigin(0, blockHeight);
	}
	void setStartingPosition(float multiplier) {
		float currentPos = (windowWidth / numOfBlocks) * multiplier;
		block.setPosition(Vector2f(currentPos, windowHeight));
	}
	void setRanHeight() {
		blockHeight = rand() % blockMaxHeight + 1;
		block.setSize(Vector2f(windowWidth / numOfBlocks, blockHeight));
		block.setOrigin(0, blockHeight);
	}
	void setHeight(int newHeight) {
		blockHeight = newHeight;
	}
	//Allows blocks values to change accordingly without floating
	void reset() {
		block.setSize(Vector2f(windowWidth / numOfBlocks, blockHeight));
		block.setOrigin(0, blockHeight);
		block.setPosition(block.getPosition().x, windowHeight);
	}
	int getHeight() {
		return blockHeight;
	}
private:
	int ID = 0;
	float blockWidth = 0;
	float blockHeight = 300;
};

class Slider {
public:
	RectangleShape sliderBox;
	CircleShape sliderPoint;
	Slider() {
		//Create sliderBox and set values
		sliderBox.setSize(Vector2f(sliderWidth, sliderHeight));
		sliderBox.setFillColor(Color::White);
		sliderBox.setOrigin(0, sliderHeight / 2);
		sliderBox.setPosition(Vector2f(sliderXPos, 25));
		//Create sliderPoint and set values
		sliderPoint.setRadius(sliderPointRadius);
		sliderPoint.setFillColor(Color::Yellow);
		sliderPoint.setOrigin(10, 6);
		sliderPoint.setPosition(Vector2f(sliderXPos, 20));
	}

	void keepInRange() {
		if (sliderPoint.getPosition().x < 20) {
			sliderPoint.setPosition(sliderXPos, 20);
		}
		else if (sliderPoint.getPosition().x > sliderWidth + 20) {
			sliderPoint.setPosition(sliderWidth + 20, 20);
		}
	}

	void setBlockAmount() {
		value = (sliderPoint.getPosition().x + sliderXPos) * 2;
		numOfBlocks = value;
	}
private:
	int value = 0;
	int sliderWidth = 560;
	int sliderHeight = 2;
	int sliderPointRadius = 10;
	int sliderXPos = 20;
};

class Button {
public:
	RectangleShape buttonBox;
	Text buttonText;
	Font buttonFont;
	Button(String text, Font& font) {
		buttonBox.setSize(Vector2f(buttonWidth, buttonHeight));
		buttonBox.setFillColor(Color::Black);
		buttonBox.setOutlineThickness(1);
		buttonBox.setOutlineColor(Color::Yellow);
		buttonBox.setPosition(0, 0);
		buttonText.setFont(font);
		buttonText.setFillColor(Color::White);
		buttonText.setString(text);
	}

	void setButtonAsSelected() {
		buttonBox.setOutlineColor(Color::Red);
	}

	void setButtonAsHovered() {
		buttonBox.setOutlineColor(Color::Yellow);
		buttonBox.setOutlineThickness(2);
	}

	void setButtonAsNeutral() {
		buttonBox.setOutlineThickness(1);
		buttonBox.setOutlineColor(Color::Yellow);
	}

	void setButtonPosition(int x, int y) {
		buttonBox.setPosition(x, y);
		buttonText.setPosition(x, y + 5);
	}
private:
	int buttonWidth = 150;
	int buttonHeight = 50;
	String displayText;
};

//Completed. D.N.T
void insertionSort(vector<Block>& blocks) {
	Clock clock;
	int i, j;

	for (i = 0; i < blocks.size(); i++) {
		for (j = 0; j < blocks.size(); j++) {
			if (blocks[i].getHeight() > blocks[j].getHeight()) {
				int iBlock = blocks[i].getHeight();
				int jBlock = blocks[j].getHeight();
				blocks[j].setHeight(iBlock);
				blocks[i].setHeight(jBlock);
			}
		}
	}
	for (int i = 0; i < blocks.size(); i++) {
		blocks[i].reset();
	}

	timeToSort = clock.getElapsedTime().asMilliseconds();
}

//Completed. D.N.T
void selectionSort(vector<Block>& blocks) {
	Clock clock;
	int i, j, minIndex;
	int time;
	bool isSorted = false;
	bool sortingRequired = false;
	while (!isSorted) {
		for (i = 0; i < blocks.size() - 1; i++) {
			minIndex = i;
			for (j = i + 1; j < blocks.size(); j++) {
				if (blocks[j].getHeight() > blocks[minIndex].getHeight()) {
					minIndex = j;

					int iBlock = blocks[i].getHeight();
					int minIndexBlock = blocks[minIndex].getHeight();
					blocks[i].setHeight(minIndexBlock);
					blocks[minIndex].setHeight(iBlock);

					/*Bottom line is there to show that there has been at least one change in the vector
					/In that case, we would need to run a loop for every element until no changes have been made*/
					sortingRequired = true;
				}
			}
		}
		//If no changes were made, the vector has been sorted successfully and the loop can stop
		if (!sortingRequired) {
			isSorted = true;
		}
		sortingRequired = false;
	}
	for (i = 0; i < blocks.size(); i++) {
		blocks[i].reset();
	}

	timeToSort = clock.getElapsedTime().asMilliseconds();
}

//Completed. D.N.T
void bubbleSort(vector<Block>& blocks) {
	Clock clock;
	int i, j;
	int time;
	for (i = 0; i < blocks.size() - 1; i++) {
		// Last i elements are already in place 
		for (j = 0; j < blocks.size() - i - 1; j++) {
			if (blocks[j].getHeight() < blocks[j + 1].getHeight()) {
				int jBlock = blocks[j].getHeight();
				int jOneIndexBlock = blocks[j + 1].getHeight();
				blocks[j].setHeight(jOneIndexBlock);
				blocks[j + 1].setHeight(jBlock);
			}
		}
	}
	for (i = 0; i < blocks.size(); i++) {
		blocks[i].reset();
	}

	timeToSort = clock.getElapsedTime().asMilliseconds();
}

void createRandomizedBlocks(vector<Block>& blocks) {
	for (int i = 0; i < numOfBlocks; i++) {
		blocks.push_back(i);
		blocks[i].setRanHeight();
		blocks[i].setStartingPosition(i);
	}
}

int main() {
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Sorting Algorithm");
	window.setFramerateLimit(30);

	Event event;
	Slider slider;
	Font font;
	font.loadFromFile("Font/AGENCYR.ttf");
	Text text;
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setPosition(20, 50);

	Text textTimeToComplete;
	textTimeToComplete.setFont(font);
	textTimeToComplete.setFillColor(Color::White);
	textTimeToComplete.setPosition(20, 80);

	Button selectionSortButton("Selection Sort", font);
	selectionSortButton.setButtonPosition(700, 5);
	Button insertionSortButton("Insertion Sort", font);
	insertionSortButton.setButtonPosition(855, 5);
	Button bubbleSortButton("Bubble Sort", font);
	bubbleSortButton.setButtonPosition(1010, 5);

	vector<Block> blocks = {};
	srand(time(NULL));
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
		}
		//Bottom function creates first initial set of randomIzed blocks
		if (!hasBeenRun) {
			createRandomizedBlocks(blocks);
			hasBeenRun = true;
		}

		//Controller for slider
		auto mousePosition = Mouse::getPosition(window); // Mouse position relative to the window
		auto translatedPosition = window.mapPixelToCoords(mousePosition); // Mouse position translated into window coordinates
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (slider.sliderPoint.getGlobalBounds().contains(translatedPosition)) { // Rectangle-contains-point check
				slider.sliderPoint.setPosition(Mouse::getPosition(window).x, 20);
				slider.keepInRange();
				slider.setBlockAmount();
				blocks.clear();
				createRandomizedBlocks(blocks);
				hasBeenSorted = false;
				timeToSort = 0;
			}
		}

		textTimeToComplete.setString(to_string(timeToSort) + " Milliseconds To Sort");
		text.setString(to_string(numOfBlocks) + " Blocks");

		if (insertionSortButton.buttonBox.getGlobalBounds().contains(translatedPosition)) {
			insertionSortButton.setButtonAsHovered();
			if (Mouse::isButtonPressed(Mouse::Left)) {
				insertionSortButton.setButtonAsSelected();
				if (!hasBeenSorted) {
					insertionSort(blocks);
					hasBeenSorted = true;
					textTimeToComplete.setString(to_string(timeToSort) + " Milliseconds To Sort");
				}
			}
			else {
				insertionSortButton.setButtonAsHovered();
			}
		}
		else {
			insertionSortButton.setButtonAsNeutral();
		}

		if (selectionSortButton.buttonBox.getGlobalBounds().contains(translatedPosition)) {
			selectionSortButton.setButtonAsHovered();
			if (Mouse::isButtonPressed(Mouse::Left)) {
				selectionSortButton.setButtonAsSelected();
				if (!hasBeenSorted) {
					selectionSort(blocks);
					hasBeenSorted = true;
					textTimeToComplete.setString(to_string(timeToSort) + " Milliseconds To Sort");
				}
			}
			else {
				selectionSortButton.setButtonAsHovered();
			}
		}
		else {
			selectionSortButton.setButtonAsNeutral();
		}

		if (bubbleSortButton.buttonBox.getGlobalBounds().contains(translatedPosition)) {
			bubbleSortButton.setButtonAsHovered();
			if (Mouse::isButtonPressed(Mouse::Left)) {
				bubbleSortButton.setButtonAsSelected();
				if (!hasBeenSorted) {
					bubbleSort(blocks);
					hasBeenSorted = true;
					textTimeToComplete.setString(to_string(timeToSort) + " Milliseconds To Sort");
				}
			}
			else {
				bubbleSortButton.setButtonAsHovered();
			}
		}
		else {
			bubbleSortButton.setButtonAsNeutral();
		}

		window.clear(Color::Black);
		for (int i = 0; i < numOfBlocks; i++) {
			window.draw(blocks[i].block);
		}
		window.draw(slider.sliderBox);
		window.draw(slider.sliderPoint);
		window.draw(text);
		window.draw(textTimeToComplete);

		window.draw(selectionSortButton.buttonBox);
		window.draw(selectionSortButton.buttonText);
		window.draw(insertionSortButton.buttonBox);
		window.draw(insertionSortButton.buttonText);
		window.draw(bubbleSortButton.buttonBox);
		window.draw(bubbleSortButton.buttonText);

		window.display();
	}
}