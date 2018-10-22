#include "GnulightMode.h"
#include "Gnulight.h"

GnulightMode::GnulightMode(Gnulight* gnulight, const char* modeName) :
		HostSystemAware(gnulight), modeName(modeName) {
	trace("Inst. " + modeName);
}

const char* GnulightMode::getModeName() {
	return modeName;
}
