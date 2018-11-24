#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ComponentsUtils.h"

enum class OnOffState {
	ON, OFF
};

//#define INFO
//#define DEBUG
//#define TRACE

#define GET_MACRO(_1, _2, NAME, ...) NAME

#ifdef INFO
#define info(fmt, ...) log(fmt, ##__VA_ARGS__)
#define infoIfNamed(fmt, ...) logNamedInstance(this, fmt, ##__VA_ARGS__)
#define infoIfOtherNamed(other, fmt, ...) logNamedInstance(other, fmt, ##__VA_ARGS__)
#ifdef DEBUG
#define debug(fmt, ...) log(fmt, ##__VA_ARGS__)
#define debugIfNamed(fmt, ...) logNamedInstance(this, fmt, ##__VA_ARGS__)
#define debugIfOtherNamed(other, fmt, ...) logNamedInstance(other, fmt, ##__VA_ARGS__)
#ifdef TRACE
#define trace(fmt, ...) log(fmt, ##__VA_ARGS__)
#define traceIfNamed(fmt, ...) logNamedInstance(this, fmt, ##__VA_ARGS__)
#define traceIfOtherNamed(other, fmt, ...) logNamedInstance(other, fmt, ##__VA_ARGS__)
#else
#define trace(fmt, ...)
#define traceIfNamed(fmt, ...)
#define traceIfOtherNamed(other, fmt, ...)
#endif
#else
#define debug(fmt, ...)
#define debugIfNamed(fmt, ...)
#define debugIfOtherNamed(other, fmt, ...)
#define trace(fmt, ...)
#define traceIfNamed(fmt, ...)
#define traceIfOtherNamed(other, fmt, ...)
#endif
#else
#define info(fmt, ...)
#define infoIfNamed(fmt, ...)
#define infoIfOtherNamed(other, fmt, ...)
#define trace(fmt, ...)
#define traceIfNamed(fmt, ...)
#define traceIfOtherNamed(other, fmt, ...)
#define debug(fmt, ...)
#define debugIfNamed(fmt, ...)
#define debugIfOtherNamed(other, fmt, ...)
#endif

#define _constrain(value,low,high) ((value)<(low)?(low):((value)>(high)?(high):(value)))

#endif
