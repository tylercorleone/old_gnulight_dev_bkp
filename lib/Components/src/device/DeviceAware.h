#ifndef DEVICEAWARE_H
#define DEVICEAWARE_H

template <class DeviceClass> class DeviceAware {
public:
	DeviceAware(DeviceClass *hostDevice) {
		this->hostDevice = hostDevice;
	}
	DeviceClass* Device() {
		return hostDevice;
	}
private:
	DeviceClass *hostDevice;
};

#endif
