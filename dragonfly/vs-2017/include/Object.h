// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Header file for object class
// File:    Object.h

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>

#include "Vector.h"
#include "Event.h"

namespace df {

	class Object {

	private:
		int id;             // Unique object identifier
		std::string type;   // user-defined identifier
		Vector position;    // position in game world

	public:
		// Construct object. Set default params and
		// add to game world (WorldManager)
		Object();

		// Destroy object
		// remove from game world (WorldManager)
		virtual ~Object();

		// set Object id
		void setId(int new_id);

		// get object id
		int getId() const;

		// set type identifier of object
		void setType(std::string new_type);

		// Get type identifier of object
		std::string getType() const;

		// set position of object
		void setPosition(Vector new_pos);

		// get position of object
		Vector getPosition() const;

		// Handle event by default ignoring everything
		// return 0 if ignored
		virtual int eventHandler(const Event *p_e);
	};

} // end namespace df
#endif // __OBJECT_H__