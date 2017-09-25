// Author:  David Giangrave
// Date:    9/13/17
// Purpose: A base class for a typical manager to serve general purposes
// File:    Manager.cpp

#include "Manager.h"

// Basic constructor sets general type of manager
df::Manager::Manager()
{
	setType("Manager");
}

df::Manager::~Manager()
{

}

// Allows user to set the type of class, mainly used by child objects
void df::Manager::setType(std::string type)
{
	this->type = type;
}

// Allows access to the type field
std::string df::Manager::getType() const
{
	return type;
}

// child objects do alot of work here, for general purpose
// set the started flag to true
int df::Manager::startUp()
{
	is_started = true;
	return 0;
}

// Again children do work here, just set flag for now
void df::Manager::shutDown()
{
	is_started = false;
}

// Allows access to see if the class has been started
bool df::Manager::isStarted() const
{
	return is_started;
}