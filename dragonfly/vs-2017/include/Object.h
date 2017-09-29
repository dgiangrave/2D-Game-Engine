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

	// Types of solidness of Object
	enum Solidness {
		HARD,       // Object causes collisions and impedes
		SOFT,       // Object causes collision, but doesn't impede
		SPECTRAL,   // Object doesn't cause collisions
	};

	class Object {


	private:
		int id;             // Unique object identifier
		std::string type;   // user-defined identifier
		Vector position;    // position in game world
		int m_altitude;

		Vector direction;	// Direction vector
		float speed;	// Object speed in direction

		Solidness m_solidness; // Solidness of object

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

		virtual void draw();

		// Set altitutde of Object with checks for range 0 - Max Alt
		// Return 0 if ok and -1 otherwise
		int setAltitude(int new_altitude);

		// Return altitude of object
		int getAltitude() const;

		// Set speed of Object
		void setSpeed(float speed);

		// Get speed pf Object
		float getSpeed() const;

		// Set direction of Object
		void setDirection(Vector newDirection);

		// Get direction of Object
		Vector getDirection() const;

		// Set direction and speed of Object
		void setVelocity(Vector new_Velocity);

		// Get velocity of Object based on the directiona and speed
		Vector getVelocity() const;

		// predict object position based on speed and direction
		// return predicted position
		Vector predictPosition();

		bool isSolid() const; // True if HARD or SOFT else false

		// Set object solidness with checks for consistency
		// Return 0 if okay and -1 if not
		int setSolidness(Solidness new_solid);

		// Return object solidness
		Solidness getSolidness() const;
	};

} // end namespace df
#endif // __OBJECT_H__