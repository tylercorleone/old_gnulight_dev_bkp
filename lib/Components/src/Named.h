#ifndef NAMED_H
#define NAMED_H

class Named {
public:

	const char* getInstanceName() {
		return instanceName;
	}

	void setInstanceName(const char *instanceName) {
		this->instanceName = instanceName;
	}

private:
	const char *instanceName = nullptr;
};

#endif
