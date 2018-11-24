#ifndef HOSTSYSTEMAWARE_H
#define HOSTSYSTEMAWARE_H

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
