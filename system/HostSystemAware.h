#ifndef HOST_SYSTEM_AWARE_H
#define HOST_SYSTEM_AWARE_H

template <class HostSystemClass> class HostSystemAware {
public:
	HostSystemAware(HostSystemClass* pSystem) {
		this->pSystem = pSystem;
	}
protected:
	HostSystemClass* pSystem;
};

#endif
