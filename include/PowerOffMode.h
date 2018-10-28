#ifndef POWER_OFF_TASK_H
#define POWER_OFF_TASK_H

#include "GnulightMode.h"

class PowerOffMode: public GnulightMode {
	friend class Gnulight;
public:
	PowerOffMode(Gnulight* gnulight, const char* modeName) :
			GnulightMode(gnulight, modeName) {
	}
	virtual bool interpretUserInteraction(ButtonInteraction& interaction);
protected:
	bool onEnterMode() override;
	void onExitMode() override;
};

#endif
