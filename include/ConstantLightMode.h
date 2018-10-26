#ifndef CONSTAT_LIGHT_MODE_H
#define CONSTAT_LIGHT_MODE_H

#include "defines.h"
#include "GnulightMode.h"

#define CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS 300UL

class ConstantLightMode: public GnulightMode {
public:
	ConstantLightMode(Gnulight* gnulight, const char* modeName) :
			GnulightMode(gnulight, modeName) {
	}
	bool interpretUserInteraction(ButtonInteraction& interaction);
protected:
	bool onEnterMode(ButtonInteraction* interaction);
	void onExitMode();
};

#endif
