// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Header file for clock class
// File:    Clock.h

#ifndef __CLOCK_H__
#define __CLOCK_H__

namespace df {

	class Clock {

	private:
		long int previous_time; // Previous time delta() called (in microsecs)

	public:
		// Sets previous_time to current time
		Clock();

		// Return time elapsed since delta() was last called, -1 if error
		// Units are microseconds
		long int delta();

		// Return time elapsed since delta() was called, -1 if error
		// Units are microseconds
		long int split() const;
	};

} // End df namespace
#endif // __CLOCK_H__