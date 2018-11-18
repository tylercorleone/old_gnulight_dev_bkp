#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ComponentsUtils.h"

enum class OnOffState {
	ON, OFF
};

#define INFO
#define DEBUG
#define TRACE

#define LOG_BUFFER_SIZE 128

#ifdef INFO
#define info(fmt, ...) log(fmt, ##__VA_ARGS__)
#define infoNamedInstance(fmt, ...) logNamedInstance(this, fmt, ##__VA_ARGS__)
#define WDTO_X 6 // -> WDTO_1S
#ifdef DEBUG
#define debug(fmt, ...) log(fmt, ##__VA_ARGS__)
#define debugNamedInstance(fmt, ...) logNamedInstance(this, fmt, ##__VA_ARGS__)
#ifdef TRACE
#define trace(fmt, ...) log(fmt, ##__VA_ARGS__)
#define traceNamedInstance(fmt, ...) logNamedInstance(this, fmt, ##__VA_ARGS__)
#else
#define trace(fmt, ...)
#define traceNamedInstance(fmt, ...)
#endif
#else
#define debug(fmt, ...)
#define debugNamedInstance(fmt, ...)
#define trace(fmt, ...)
#define traceNamedInstance(fmt, ...)
#endif
#else
#define WDTO_X
#define info(fmt, ...)
#define infoNamedInstance(fmt, ...)
#define trace(fmt, ...)
#define traceNamedInstance(fmt, ...)
#define debug(fmt, ...)
#define debugNamedInstance(fmt, ...)
#endif

#endif
