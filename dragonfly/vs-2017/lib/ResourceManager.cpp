// Author:  David Giangrave
// Date:    10/11/17
// Purpose: Loads and handles external resources for the
//			engine like spites and audio files
// File:    ResourceManager.cpp

#include "ResourceManager.h"
#include "LogManager.h"

#include <iostream>
#include <fstream>



// Read singleline ‘tag number’ ,return number ( e.g., ”frames 5”)
int readLineInt(std::ifstream *p_file, int *p_line_num, const char *tag);

// Read singleline ‘tag string’ ,return string ( e.g., ”color green”)
std::string readLineStr(std::ifstream *p_file, int *p_line_num, const char *tag);

// Read frame until 'eof' return Frame
df::Frame readFrame(std::ifstream *p_file, int *p_line_number, int width, int height);

df::ResourceManager::ResourceManager()
{
	setType("ResourceManager");

	//Sprite *p_sprite[MAX_SPRITES];
}

// Get the singleton instance of GameManager
df::ResourceManager& df::ResourceManager::getInstance()
{
	static df::ResourceManager instance;

	return instance;
}


int df::ResourceManager::startUp()
{
	m_sprite_count = 0;
	m_sound_count = 0;
	m_music_count = 0;

	for (int i = 0; i < MAX_SPRITES; i++) {
		p_sprite[i] = nullptr;
	}

	return Manager::startUp();
}

void df::ResourceManager::shutDown()
{
	delete[] p_sprite;

	Manager::shutDown();
}

int df::ResourceManager::loadSprite(std::string filename, std::string label) {
	//FILE *file = fopen(filename.c_str(), "r");

	//std::ifstream *file (filename.c_str(), std::ifstream::in);

	std::ifstream *file = new std::ifstream(filename.c_str(), std::ifstream::in);

	// ------------ Read Header ----------------------
	int frames, width, height;
	int lineNumber = 0;
	std::string color;

	// Read in frame count
	try {
		frames = readLineInt(file, &lineNumber, FRAMES_TOKEN.c_str());
		//lineNumber++;
	}
	catch (std::exception e) {
		LM.writeLog("Failed to read frame count on line : %d. Error message: %s", lineNumber, e.what());
		return -1;
	}
	// Read in width
	try {
		width = readLineInt(file, &lineNumber, WIDTH_TOKEN.c_str());
		lineNumber++;
	}
	catch (std::exception e) {
		LM.writeLog("Failed to read width on line : %d. Error message: %s", lineNumber, e.what());
		return -1;
	}
	// Read in height
	try {
		height = readLineInt(file, &lineNumber, HEIGHT_TOKEN.c_str());
		lineNumber++;
	}
	catch (std::exception e) {
		LM.writeLog("Failed to read height on line : %d. Error message: %s", lineNumber, e.what());
		return -1;
	}
	// Read in color
	try {
		color = readLineStr(file, &lineNumber, COLOR_TOKEN.c_str());
		lineNumber++;
	}
	catch (std::exception e) {
		LM.writeLog("Failed to read color on line : %d. Error message: %s", lineNumber, e.what());
		LM.writeLog("Defaulting to default color!");
		color = "white";
	}


	// ----- Make New sprite based on header ---------
	p_sprite[m_sprite_count] = new Sprite(frames);
	p_sprite[m_sprite_count]->setWidth(width);
	p_sprite[m_sprite_count]->setHeight(height);
	//Sprite *p_new_sprite = new Sprite(frames);
	//p_new_sprite->setHeight(height);
	//p_new_sprite->setWidth(width);

	if (color == "black") {
		p_sprite[m_sprite_count]->setColor(Color::BLACK);
	}
	else if (color == "red") {
		p_sprite[m_sprite_count]->setColor(Color::RED);
	}
	else if (color == "green") {
		p_sprite[m_sprite_count]->setColor(Color::GREEN);
	}
	else if (color == "yellow") {
		p_sprite[m_sprite_count]->setColor(Color::YELLOW);
	}
	else if (color == "blue") {
		p_sprite[m_sprite_count]->setColor(Color::BLUE);
	}
	else if (color == "magenta") {
		p_sprite[m_sprite_count]->setColor(Color::MAGENTA);
	}
	else if (color == "cyan") {
		p_sprite[m_sprite_count]->setColor(Color::CYAN);
	}
	else if (color == "white") {
		p_sprite[m_sprite_count]->setColor(Color::WHITE);
	}
	else {
		LM.writeLog("Color string not found setting to default");
		p_sprite[m_sprite_count]->setColor(COLOR_DEFAULT);
	}

	//sprite.setColor(color conversion)
	//p_sprite[m_sprite_count]->setColor(df::Color::WHITE);

	for (int i = 1; i <= frames; i++) {
		Frame next_frame = readFrame(file, &lineNumber, width, height);
		//LM.writeLog("Again: /n%s", next_frame.getString().c_str());
		p_sprite[m_sprite_count]->addFrame(next_frame);
	}
	p_sprite[m_sprite_count]->setLabel(label);
	//LM.writeLog("Frame 0: \n%s", p_sprite[m_sprite_count]->getFrame(0).getString().c_str());
	m_sprite_count++;
	//LM.writeLog("Frame 0 by label: \n%s", this->getSprite(label)->getFrame(0).getString().c_str());

	// Check that the file is still good
	if (!(*file).good()) {
		LM.writeLog("p_file marked as not good near EOF!");
	}

	// Read the eof token
	/*
	try {
		readLineStr(file, &lineNumber, END_FRAME_TOKEN.c_str());
		lineNumber++;
	}
	catch (std::exception e) {
		LM.writeLog("Failed to find eof on line: %d! Messege: %s", lineNumber, e.what());
		delete p_sprite[m_sprite_count];
		return -1;
	}
	*/
	
	// Close the file
	file->close();

	// Set the sprites label
	

	// Add the sprite to the list
	//if (m_sprite_count < MAX_SPRITES) {
	//	p_sprite[m_sprite_count] = p_new_sprite;
	//	m_sprite_count++;
	//}
	//else {
	//	LM.writeLog("Could not add sprite, already at max sprite count!");
	//}

	

	return 0;
}


int df::ResourceManager::unloadSprite(std::string label) {
	for (int i = 0; i < m_sprite_count; i++) {
		if (label.compare(p_sprite[i]->getLabel()) == 0) {
			delete p_sprite[i];

			// Scoot over remaining sprites
			for (int j = i; j < m_sprite_count - 1; j++) {
				p_sprite[j] = p_sprite[j + 1];
			}

			m_sprite_count--;

			return 0;
		}
	}

	// Failed to find sprite: error
	LM.writeLog("FAILED to unload sprite with label '%s'! Could not be found in sprite array!", label.c_str());
	return -1;
}


df::Sprite *df::ResourceManager::getSprite(std::string label) const {
	for (int i = 0; i <= m_sprite_count - 1; i++) {
		if (label == p_sprite[i]->getLabel()) {
			return p_sprite[i];
		}
	}

	
	LM.writeLog("FAILED to get sprite with label '%s'! Could not be found in sprite array!", label.c_str());
	return NULL; 
}


int readLineInt(std::ifstream *p_file, int *p_line_number, const char *tag) {
	std::string line = "";

	if (!p_file->good()) {
		throw std::runtime_error("p_file marked as not good!");
	}

	try {
		std::getline(*p_file, line);
		//LM.writeLog("%s", line.c_str());
	}
	catch (std::exception e) {
		throw std::runtime_error("Failed getline from p_file!");
	}

	if (line.compare(0, strlen(tag), tag)) {
		throw std::runtime_error("tag not properly read from file!");
	}

	line.substr(strlen(tag) + 1);

	int number = atoi(line.substr(strlen(tag) + 1).c_str());

	if (number == NULL) {
		throw std::runtime_error("number could not be created from string!");
	}

	(*p_line_number)++;

	return number;
}


std::string readLineStr(std::ifstream *p_file, int *p_line_number, const char *tag) {
	std::string line;

	if (!p_file->good()) {
		throw std::runtime_error("p_file marked as not good!");
	}

	try {
		std::getline(*p_file, line);
	}
	catch (std::exception e) {
		throw std::runtime_error("Failed getline from p_file!");
	}

	if (line.compare(0, strlen(tag), tag)) {
		throw std::runtime_error("tag not properly read from file!");
	}

	(*p_line_number)++;
	
	std::string output;
	if (line.length() == strlen(tag)) {
		output = "";
	}
	else {
		output = line.substr(strlen(tag) + 1);
	}

	return output;
}


df::Frame readFrame(std::ifstream *p_file, int *p_line_number, int width, int height) {
	std::string line, frame_str;

	if (!p_file->good()) {
		LM.writeLog("Error line %d. p_file no good!", *p_line_number);
		LM.writeLog("Defaulting to empty frame!");
		return df::Frame();
	}

	for (int i = 1; i <= height; i++) {
		try {
			std::getline(*p_file, line);
		}
		catch (std::exception e) {
			LM.writeLog("Error line %d. Failed getline from p_file!");
			LM.writeLog("Defaulting to empty frame!");
			return df::Frame();
		}
		(*p_line_number)++;

		if (line.length() != width) {
			LM.writeLog("Error line %d. Line width %d, expected %d.", *p_line_number, line.length(), width);
			LM.writeLog("Defaulting to empty frame!");
			return df::Frame();
		}

		frame_str += line;
		
	}

	if (!p_file->good()) {
		LM.writeLog("Error line %d. p_file no good!", *p_line_number);
		LM.writeLog("Defaulting to empty frame!");
		return df::Frame();
	}

	try {
		std::getline(*p_file, line);
	}
	catch (std::exception e) {
		LM.writeLog("Error line %d. Failed getline from p_file!");
		LM.writeLog("Defaulting to empty frame!");
		return df::Frame();
	}

	//if (line.compare(0, df::END_FRAME_TOKEN.length(), df::END_FRAME_TOKEN)) {
	if (line != df::END_FRAME_TOKEN) {
		LM.writeLog("Error line %d. Failed to find end of frame token!");
		LM.writeLog("Defaulting to empty frame!");
		return df::Frame();
	}

	df::Frame frame = df::Frame(width, height, frame_str);
	//LM.writeLog("Added Frame: \n%s", frame.getString().c_str());
	return frame;
}




int df::ResourceManager::loadSound(std::string filename, std::string label) {
	if (m_sound_count == MAX_SOUNDS) {
		LM.writeLog("Sound array full, failed to load sound!");
		return -1;
	}

	if (m_sound[m_sound_count].loadSound(filename) == -1) {
		LM.writeLog("Failed to load sound from file!");
		return -1;
	}

	m_sound[m_sound_count].setLabel(label);
	m_sound_count++;
	return 0;
}

int df::ResourceManager::unloadSound(std::string label) {
	for (int i = 0; i <= m_sound_count; i++) {
		if (label == m_sound[i].getLabel()) {
			for (int j = 0; j < m_sound_count - 2; j++) {
				m_sound[j] = m_sound[j + 1];
			}
			m_sound_count--;
			return 0;
		}
	}
	return -1;
}

df::Sound *df::ResourceManager::getSound(std::string label) {
	for (int i = 0; i <= m_sound_count; i++) {
		if (label == m_sound[i].getLabel())
			return(&m_sound[i]);
	}
	return NULL; //sound not found
}

int df::ResourceManager::loadMusic(std::string filename, std::string label) {
	if (m_music_count == MAX_MUSICS) {
		LM.writeLog("Music array full, failed to load music!");
		return -1;
	}

	if (m_music[m_music_count].loadMusic(filename) == -1) {
		LM.writeLog("Failed to load music from file!");
		return -1;
	}

	m_music[m_music_count].setLabel(label);
	m_music_count++;
	return 0;
}

int df::ResourceManager::unloadMusic(std::string label) {
	for (int i = 0; i <= m_music_count; i++) {
		if (label == m_music[i].getLabel()) {
			m_music[i].setLabel("");
			return 0;
		}
	}
	return -1;
}

df::Music *df::ResourceManager::getMusic(std::string label) {
	for (int i = 0; i <= m_music_count; i++) {
		if (label == m_music[i].getLabel())
			return(&m_music[i]);
	}
	return NULL; // Music not found
}