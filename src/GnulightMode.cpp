#include "GnulightMode.h"
#include "Gnulight.h"

GnulightMode::GnulightMode(const char* className, Gnulight* gnulight) :
		className(className), HostSystemAware(gnulight) {
}

const char* GnulightMode::getClassName() {
	return className;
}
