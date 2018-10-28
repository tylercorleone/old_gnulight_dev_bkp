#ifndef DIMMABLE_H_
#define DIMMABLE_H_

template <class DimmableValueType> class Dimmable {
public:
	virtual void dim(DimmableValueType value) = 0;
	virtual ~Dimmable() {}
};

#endif
