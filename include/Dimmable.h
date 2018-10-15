#ifndef DIMMABLE_H_
#define DIMMABLE_H_

template <class DimmableValueType> class Dimmable {
public:
	Dimmable(DimmableValueType initialDimmableValueMax) {
		this->dimmableValueMax = dimmableValueMax;
	}
	void setDimmableMaxValue(DimmableValueType dimmableValueMax) {
		this->dimmableValueMax = dimmableValueMax;
	}
	DimmableValueType getDimmableMaxValue() {
		return dimmableValueMax;
	}
private:
	DimmableValueType dimmableValueMax;
};

#endif
