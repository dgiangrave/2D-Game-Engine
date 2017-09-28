// Author:  David Giangrave
// Date:    9/26/17
// Purpose: Manages the display
// File:    DisplayManager.cpp

#include "DisplayManager.h"
#include "LogManager.h"
#include "Color.h"

// Set default fields
df::DisplayManager::DisplayManager()
{
	setType("DisplayManager");
	
	

	// Set Window sizes to default
	m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
	m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;

	

}

// Get the singleton instance of GameManager
df::DisplayManager& df::DisplayManager::getInstance()
{
	static df::DisplayManager instance;

	return instance;
}

int df::DisplayManager::startUp() {

	if (m_p_window != NULL) {
		return 0;
	}


	// Create the SFML window
	m_p_window = new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_vertical_pixels), WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);
	m_p_window->setMouseCursorVisible(false);
	m_p_window->setVerticalSyncEnabled(true);

	// Set font
	if (m_font.loadFromFile("df-font.ttf") == false) {
		LM.writeLog("Failed to load font from file.");
	}

	df::Manager::startUp();
	return 0;
}

void df::DisplayManager::shutDown() {
	if (m_p_window != NULL) {
		m_p_window->close();
		delete m_p_window;
		m_p_window = NULL;
	}
}

int df::DisplayManager::drawCh(Vector world_pos, char ch, Color color) const {
	//make sure the window is allocated
	if (m_p_window == NULL) {
		return -1;
	}

	// Covert spaces (x,y) to pixels (x,y)
	Vector pixel_pos = spacesToPixels(world_pos);

	// Draw background rectangle since text is "see through" in sfml
	static sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
	rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	rectangle.setPosition(pixel_pos.getX() - charWidth()/10,
						  pixel_pos.getY() + charHeight() / 5);
	m_p_window->draw(rectangle);

	// Create character text to draw
	static sf::Text text("", m_font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold);

	// Scale to right size
	if (charWidth() < charHeight()) {
		text.setCharacterSize(charWidth() * 2);
	}
	else {
		text.setCharacterSize(charHeight() * 2);
	}

	// Set SFML color based on Dragonfly color
	switch (color) {
	case UNDEFINED_COLOR:
		text.setColor(sf::Color::Transparent);
		break;
	case BLACK:
		text.setColor(sf::Color::Black);
		break;
	case RED:
		text.setColor(sf::Color::Red);
		break;
	case GREEN:
		text.setColor(sf::Color::Green);
		break;
	case YELLOW:
		text.setColor(sf::Color::Yellow);
		break;
	case BLUE:
		text.setColor(sf::Color::Blue);
		break;
	case MAGENTA:
		text.setColor(sf::Color::Magenta);
		break;
	case CYAN:
		text.setColor(sf::Color::Cyan);
		break;
	case WHITE:
		text.setColor(sf::Color::White);
		break;
	case CUSTOM:
		text.setColor(sf::Color::Transparent);
		break;
	}

	// Set position in window (in pixels)
	text.setPosition(pixel_pos.getX(), pixel_pos.getY());

	// Draw character
	m_p_window->draw(text);

	return 0;
}

// Render current window buffer
// Return 0 if ok else -1
int df::DisplayManager::swapBuffers() {
	// Makw sure window is allocated 
	if (m_p_window == NULL) {
		return -1;
	}

	// Display current window
	m_p_window->display();

	// Clear window to get ready for next draw
	m_p_window->clear(m_window_background_color);
	//m_p_window->clear();


	return 0;
}

float df::charHeight(void) {
	// DisplayManager getVerticalPixels()) divided by the number 
	// of vertical characters(DisplayManager getVertical()
	return (DM.getVerticalPixels() / DM.getVertical());
}

float df::charWidth(void) {
	// (DisplayManager getHorizontalPixels()) divided by the number of
	// horizontal characters(DisplayManager getHorizontal()
	return (DM.getHorizontalPixels() / DM.getHorizontal());
}

int df::DisplayManager::getVerticalPixels() const {
	return m_window_vertical_pixels;
}

int df::DisplayManager::getHorizontalPixels() const {
	return m_window_horizontal_pixels;
}


df::Vector df::spacesToPixels(Vector spaces) {
	Vector pixelVector;

	pixelVector.setX(spaces.getX() * charWidth());
	pixelVector.setY(spaces.getY() * charHeight());

	return pixelVector;
}

df::Vector df::pixelsToSpaces(Vector pixels) {
	Vector spacesVector;

	spacesVector.setX(pixels.getX() / charWidth());
	spacesVector.setY(pixels.getY() / charHeight());

	return spacesVector;
}

int df::DisplayManager::getHorizontal() const {
	return m_window_horizontal_chars;
}

int df::DisplayManager::getVertical() const {
	return m_window_vertical_chars;
}

// Draw string at window location (x,y) with color
// Justified left center or right
// return 0 if ok -1 otherwise
int df::DisplayManager::drawString(Vector pos, std::string str, Justification just, Color color) const {
	// Get starting position
	Vector starting_pos = pos;
	switch (just)
	{
	case df::LEFT_JUSTIFIED:
		break;
	case df::CENTER_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size() / 2);
		break;
	case df::RIGHT_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size());
		break;
	default:
		break;
	}

	// Draw string character by character
	for (int i = 0; i < str.size(); i++) {
		Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(temp_pos, str[i], color);
	}

	return 0;
}


bool df::DisplayManager::setBackgroundColor(Color new_color) {
	// Set SFML color based on Dragonfly color
	switch (new_color) {
	case UNDEFINED_COLOR:
		m_window_background_color = sf::Color::Transparent;
		break;
	case BLACK:
		m_window_background_color = sf::Color::Black;
		break;
	case RED:
		m_window_background_color = sf::Color::Red;
		break;
	case GREEN:
		m_window_background_color = sf::Color::Green;
		break;
	case YELLOW:
		m_window_background_color = sf::Color::Yellow;
		break;
	case BLUE:
		m_window_background_color = sf::Color::Blue;;
		break;
	case MAGENTA:
		m_window_background_color = sf::Color::Magenta;
		break;
	case CYAN:
		m_window_background_color = sf::Color::Cyan;
		break;
	case WHITE:
		m_window_background_color = sf::Color::White;
		break;
	case CUSTOM:
		m_window_background_color = sf::Color::Transparent;
		break;
	}

	return true;
}


sf::RenderWindow *df::DisplayManager::getWindow() const {
	return m_p_window;
}