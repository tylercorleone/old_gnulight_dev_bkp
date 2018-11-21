#ifndef COMPONENTSUTILS_H
#define COMPONENTSUTILS_H

#include <Arduino.h>
#include <stdarg.h>

#include "Named.h"

// taken from https://gist.github.com/EleotleCram/eb586037e2976a8d9884
inline int aprintf(const char *str, va_list argv) {
	int i, j, count = 0;

	for (i = 0, j = 0; str[i] != '\0'; i++) {
		if (str[i] == '%') {
			count++;

			Serial.write(reinterpret_cast<const uint8_t*>(str + j), i - j);

			switch (str[++i]) {
				case 'i':
				case 'd': Serial.print(va_arg(argv, int));
					break;
				case 'u': Serial.print(va_arg(argv, unsigned));
					break;
				case 'l': Serial.print(va_arg(argv, long));
					break;
				case 'f': Serial.print(va_arg(argv, double));
					break;
				case 'c': Serial.print((char) va_arg(argv, int));
					break;
				case 's': Serial.print(va_arg(argv, const char *));
					break;
				case '%': Serial.print('%');
					break;
				default:;
			};

			j = i + 1;
		}
	};

	if (i > j) {
		Serial.write(reinterpret_cast<const uint8_t*>(str + j), i - j);
	}

	return count;
}

inline void log(const char *fmt, ...) {
	va_list argv;
	va_start(argv, fmt);

	aprintf(fmt, argv);

	va_end(argv);

	Serial.println();
	Serial.flush();
}

inline void logNamedInstance(Named *instance, const char *fmt, ...) {
	if (instance->getInstanceName() == nullptr) {
		return;
	}

	va_list argv;
	va_start(argv, fmt);

	Serial.print(instance->getInstanceName());
	Serial.print(": ");
	aprintf(fmt, argv);

	va_end(argv);

	Serial.println();
	Serial.flush();
}

#endif
