#ifndef COMPONENTS_H
#define COMPONENTS_H

#define _constrain(value,low,high) ((value)<(low)?(low):((value)>(high)?(high):(value)))

#include "common/Enums.h"
#include "common/FunctionsSequenceTask.h"
#include "common/Named.h"

#include "utils/print_utils.h"
#include "utils/fixed_trigonometry.h"

#include "system/System.h"

#include "Battery.h"
#include "Button.h"
#include "CappablePotentiometer.h"
#include "DelayedCappablePotentiometerActuator.h"
#include "DelayedLevelSetter.h"
#include "DelayedPotentiometerActuator.h"
#include "LightDimmer.h"
#include "LithiumBattery.h"
#include "Potentiometer.h"

#endif
