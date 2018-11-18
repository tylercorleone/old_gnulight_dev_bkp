#ifndef HOST_SYSTEM_AWARE_H
#define HOST_SYSTEM_AWARE_H

template <class HostSystemClass> class HostSystemAware {
public:
	HostSystemAware(HostSystemClass *hostSystem) {
		this->hostSystem = hostSystem;
	}
	HostSystemClass* getHostSystem() {
		return hostSystem;
	}
private:
	HostSystemClass *hostSystem;
};

#endif
