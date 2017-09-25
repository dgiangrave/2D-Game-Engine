// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Hold a list of object * to all objects in the game world
// File:    ObjectList.cpp

#include "ObjectList.h"
#include "Object.h"

// Default constructor
df::ObjectList::ObjectList()
{
	count = 0;
}

// Insert object pointer in list
// return 0 if ok, else -1
int df::ObjectList::insert(Object *p_o)
{
	// Check for room
	if (count == MAX_OBJECTS)
		return -1;

	p_obj[count] = p_o;
	count++;
	return 0;
}

// Remove object pointer from list
// return 0 if found, else -1
int df::ObjectList::remove(Object *p_o)
{
	for (int i = 0; i < count; i++)
	{
		if (p_obj[i] == p_o) // Found ...
		{
			for (int j = i; j < (count - 1); j++) // Move everything over
			{
				p_obj[j] = p_obj[j + 1];
			}
			count--;
			return 0;
		}
	}
	return -1; // Failed to find
}

// clear list (setting count to 0)
void df::ObjectList::clear() {
	count = 0;
}

// Return count of number of objects in list
int df::ObjectList::getCount() const {
	return count;
}

// return true if list is empty, else false
bool df::ObjectList::isEmpty() const {
	if (count == 0)
		return true;

	return false;
}

// return true if list is Full, else false
bool df::ObjectList::isFull() const {
	if (count == MAX_OBJECTS)
		return true;

	return false;
}