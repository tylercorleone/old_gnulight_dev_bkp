#ifndef CONSTAT_LIGHT_MODE_H
#define CONSTAT_LIGHT_MODE_H

#include "defines.h"
#include "GnulightMode.h"

class ConstantLightMode: public GnulightMode {
public:
	ConstantLightMode(const char*, Gnulight*);
	bool interpretUserInteraction(ButtonInteraction& interaction);
protected:
	bool onEnterMode(ButtonInteraction* interaction);
	void onExitMode();
};

#endif
