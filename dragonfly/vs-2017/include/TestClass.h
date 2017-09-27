// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Header file for TestClass class
// File:    TestClass.h

#ifndef __TEST_CLASS_H__
#define __TEST_CLASS_H__

#include "Manager.h"
#include "Object.h"

namespace df {

	class TestClass : df::Object {

	private:

	public:
		TestClass();
		~TestClass();
		void draw();

	};

} // End df namespace
#endif // __TEST_CLASS_H__
