#ifndef GNULIGHT_MODE_H
#define GNULIGHT_MODE_H

#include "Button.h"
#include "system/HostSystemAware.h"

class Gnulight;

class GnulightMode: public HostSystemAware<Gnulight> {
	friend class Gnulight;
public:
	GnulightMode(const char*, Gnulight* gnulight);
	const char* getClassName();
	virtual bool interpretUserInteraction(ButtonInteraction& interaction) {return false;}
protected:
	char* className;
	virtual bool onEnterMode(ButtonInteraction* interaction = nullptr) {return false;}
	virtual bool onEnterMode(const char* msg) {return false;}
	virtual void onExitMode() {}
	virtual ~GnulightMode() {};
};

#endif
