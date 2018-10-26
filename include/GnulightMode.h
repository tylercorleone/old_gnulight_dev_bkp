#ifndef GNULIGHT_MODE_H
#define GNULIGHT_MODE_H

#include "Button.h"
#include "system/HostSystemAware.h"

class Gnulight;

class GnulightMode: public HostSystemAware<Gnulight> {
	friend class Gnulight;
public:
	GnulightMode(Gnulight* gnulight, const char* modeName);
	const char* getModeName();
	virtual bool interpretUserInteraction(ButtonInteraction& interaction) {return false;}
protected:
	const char* modeName;
	virtual bool onEnterMode() {return false;}
	virtual bool onEnterMode(ButtonInteraction* interaction) {return false;}
	virtual bool onEnterMode(const char* msg) {return false;}
	virtual void onExitMode() {}
	virtual ~GnulightMode() {};
};

#endif
