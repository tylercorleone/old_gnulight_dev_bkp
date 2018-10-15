#ifndef POWER_OFF_TASK_H
#define POWER_OFF_TASK_H

#include "defines.h"
#include "GnulightMode.h"

class PowerOffMode: public GnulightMode {
	friend class Gnulight;
public:
	PowerOffMode(const char*, Gnulight*);
	virtual bool interpretUserInteraction(ButtonInteraction& interaction);
protected:
	bool onEnterMode(ButtonInteraction* interaction = nullptr) override ;
	bool onEnterMode(const char* msg) override {return onEnterMode();};
	void onExitMode();
};

#endif
