// Author:  David Giangrave
// Date:    10/11/17
// Purpose: A single frame of an animation clip for sprites
// File:    Frame.cpp

#include "Frame.h"

df::Frame::Frame() {
	m_width = 0;
	m_height = 0;
	m_frame_str = "";
}

df::Frame::Frame(int new_width, int new_height, std::string frame_str) {
	m_width = new_width;
	m_height = new_height;
	m_frame_str = frame_str;
}

void df::Frame::setWidth(int new_width) {
	m_width = new_width;
}

int df::Frame::getWidth() const {
	return m_width;
}

void df::Frame::setHeight(int new_height) {
	m_height = new_height;
}

int df::Frame::getHeight() const {
	return m_height;
}

void df::Frame::setString(std::string new_frame_string) {
	m_frame_str = new_frame_string;
}

std::string df::Frame::getString() const {
	return m_frame_str;
}