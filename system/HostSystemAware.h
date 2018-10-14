#ifndef HOST_SYSTEM_AWARE_H
#define HOST_SYSTEM_AWARE_H

template <class HostSystemClass> class HostSystemAware {
public:
	HostSystemAware(HostSystemClass* pHostSystem) {
		this->pHostSystem = pHostSystem;
	}
protected:
	HostSystemClass* pHostSystem;
};

#endif
