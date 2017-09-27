//
// Star.h
//

#include "Object.h"

#define STAR_CHAR '.'

class Star : public df::Object {

private:

public:
	Star();
	void draw(void);
	int eventHandler(const df::Event *p_e);
};
