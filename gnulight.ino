#include "Gnulight.h"

Gnulight* pGnulight;

void setup() {
#ifdef INFO
	Serial.begin(9600);
#endif
	debug("setup()");

//	setUnusedPinStatus(OUTPUT, LOW);
	pGnulight = new Gnulight;
	pGnulight->Setup();
}

void loop() {
	pGnulight->Loop(WDTO_X);
}

//#include "gnulight.h"
//#include "button.h"
//#include "system.h"
//
//void setup() {
//#ifdef DEBUG
//  Serial.begin(9600);
//#endif
//
//  debug1("SETUP");
//
//  pinMode(LED_PIN, OUTPUT);
//  pinMode(DEVICES_VCC_PIN, OUTPUT);
//  pinMode(CS_PIN, OUTPUT);
//  pinMode(BATTERY_SENSING_PIN, INPUT);
//  pinMode(CURRENT_SENSING_PIN, INPUT);
//  pinMode(TEMPERATURE_SENSING_PIN, INPUT);
//
//#ifndef DEBUG
//  power_usart0_disable(); // 0.1 mA (28.7 mA)
//#endif
//  //power_twi_disable(); // 0.4 mA
//  //power_timer0_disable(); // pin 5, 6
//  //power_timer1_disable(); // pin 9, 10
//  //power_timer2_disable(); // 0.4 mA pin 3, 11
//
//  // SPI.begin();
//
//  //  SPI.begin();
//  //  digitalWrite(CS, LOW);
//  //  delayMicroseconds(2000);
//  //  SPI.transfer16(0x21FF);
//  //  delayMicroseconds(500);
//  //  digitalWrite(CS, HIGH);
//  //  SPI.endTransaction();
//  //  SPI.end();
//
////  setUnusedPinStatus(OUTPUT, LOW);
//  setPwmFrequency(LED_PIN, 64); // 31250/divisor = x Hz
//  button.setup();
//  switchPower(OFF);
//}
//
void setUnusedPinStatus(int mode, int level) {
	/* Current mA */
	// INPUT LOW (0.429, 9.04)
	// INPUT HIGH (0.429, 5.12)
	// OUTPUT LOW (0.429, 5.55)
	// OUTPUT HIGH (0.429, 5.12)
	// INPUT_PULLUP LOW (0.429, 9.04)
	// INPUT_PULLUP HIGH (0.429, 5.15)
	pinMode(0, mode);
	pinMode(3, mode);
	pinMode(4, mode);
	pinMode(6, mode);
	pinMode(7, mode);
	pinMode(8, mode);
	pinMode(12, mode);

	digitalWrite(0, level);
	digitalWrite(3, level);
	digitalWrite(4, level);
	digitalWrite(6, level);
	digitalWrite(7, level);
	digitalWrite(8, level);
	digitalWrite(12, level);

	pinMode(A0, mode);
	pinMode(A1, mode);
	pinMode(A5, mode);
	pinMode(A6, mode);
	pinMode(A7, mode);

	digitalWrite(A0, level);
	digitalWrite(A1, level);
	digitalWrite(A5, level);
	digitalWrite(A6, level);
	digitalWrite(A7, level);
}
//
//unsigned long lastCycleBeginTime = 0;
//unsigned strobeDelayMultiplier = 1;
//
//void loop() {
//
//  unsigned long now = getNow();
//
//  if (button.isUserInteracting()) {
//    interpretUserInteraction();
//  }
//
//#ifdef DEBUG_VV
//  printLog();
//#endif
//
//  if (power_state == ON) {
//    if (function == STROBE) {
//
//      /* STROBES TIMING */
//
//      if (strobe_mode == SLOW_STROBE && now - last_strobe_time >= SLOW_STROBE_DELAY) {
//        last_strobe_time = now;
//        toggleLed();
//      }
//      else if (strobe_mode == BEACON_STROBE && now - last_strobe_time >= BEACON_STROBE_DELAY) {
//        if ( LED_state == ON ) {
//          last_strobe_time = now;
//          switchLed(OFF);
//        }
//        else if (now - last_strobe_time >= BEACON_STROBE_DELAY * 100 / BEACON_STROBE_DUTY_CYCLE) {
//          last_strobe_time = now;
//          switchLed(ON);
//        }
//      }
//      else if (strobe_mode == FAST_STROBE && now - last_strobe_time >= FAST_STROBE_DELAY * strobeDelayMultiplier) {
//        last_strobe_time = now;
//        toggleLed();
//        if (LED_state == OFF) {
//          strobeDelayMultiplier *= 2;
//        } else {
//          strobeDelayMultiplier = 1;
//        }
//      }
//      else if (strobe_mode == SINUSOIDAL_STROBE && now - last_strobe_time >= SINUSOIDAL_STROBE_DELAY) {
//        applyLevel(getMainLevel() * (sin((now / 1000.0f) * (PI)) + 1.0f) / 2.0f);
//        last_strobe_time = now;
//      }
//      else if (strobe_mode == RANDOM_STROBE && now - last_strobe_time >= random_strobe_delay * strobeDelayMultiplier) {
//        last_strobe_time = now;
//        toggleLed();
//        int x = random(0, 101);
//
//        if (x <= 95) {
//          random_strobe_delay = RANDOM_STROBE_MIN_DELAY;
//        } else if (x < 99) {
//          random_strobe_delay = random(RANDOM_STROBE_MIN_DELAY, RANDOM_STROBE_MIN_DELAY * 3);
//        } else if (LED_state == ON) {
//          random_strobe_delay = random(RANDOM_STROBE_MIN_DELAY * 3, RANDOM_STROBE_MIN_DELAY * 5);
//        } else {
//          random_strobe_delay = RANDOM_STROBE_MIN_DELAY;
//        }
//        if (LED_state == OFF) {
//          strobeDelayMultiplier *= 2;
//        } else {
//          strobeDelayMultiplier = 1;
//        }
//      }
//    }
//    else if (function == BATTERY_CHECK) {
//
//      /* BATTERY CHECK TIMING */
//
//      if (strobes_count == 0) {
//        if (now - last_strobe_time >= INFO_STROBE_DELAY / 5.0) {
//          strobes_count++; last_strobe_time = now + INFO_STROBE_DELAY * 0.8 ; switchLed(OFF);
//        }
//      }
//      else {
//        if (now - last_strobe_time >= INFO_STROBE_DELAY) { // cast needed because of negative values (last_strobe_time getting greater of now at previous step)
//          if (strobes_count < batteryVoltageToFlashNumber( battery_voltage / 2 )) {
//            if (LED_state == ON) {
//              strobes_count++;
//            }
//            last_strobe_time = now;
//            toggleLed();
//          }
//          else {
//            switchPower(OFF);
//          }
//        }
//      }
//    }
//    else if (function == TEMPERATURE_CHECK) {
//
//      /* TEMPERATURE CHECK TIMING */
//
//      if (now - last_strobe_time >= INFO_STROBE_DELAY) {
//        if (strobes_count < (unsigned)(temperature / 10.0)) {
//          if (LED_state == ON) strobes_count++;
//          last_strobe_time = now;
//          toggleLed();
//        }
//        else {
//          switchPower(OFF);
//        }
//      }
//    }
//    else if (function == BATTERY_PROTECTION && now - last_strobe_time >= INFO_STROBE_DELAY / 10.0) {
//
//      /* BATTERY PROTECTION TIMING */
//
//      if (strobes_count < 3) {
//        if (LED_state == ON) {
//          last_strobe_time = now;
//          strobes_count++;
//          switchLed(OFF);
//        }
//        else if (now - last_strobe_time >= INFO_STROBE_DELAY * 9.0 / 10.0) {
//          last_strobe_time = now;
//          switchLed(ON);
//        }
//      }
//      else {
//        switchPower(OFF);
//      }
//    }
//  }
//
//  if (power_state == ON || button.isUserInteracting()) {
//    LowPower.idle(SLEEP_15MS, ADC_ON, TIMER2_ON, TIMER1_ON, TIMER0_ON, SPI_ON, USART0_ON, TWI_ON);
//    timer.resetMillis();
//  } else {
//    debug1("Going to sleep forever");
//    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
//    debug1("Waked-up from forever sleep");
//    timer.resetMillis();
//  }
//}
//
//void interpretUserInteraction() {
//
//  unsigned int clicksCount = button.getClicksCount();
//
//  if (clicksCount > 0) {
//
//    /* SEQUENCE RECOGNIZING */
//
//    debug3("Detected a sequence of ", clicksCount, " clicks");
//
//    switch (clicksCount) {
//      case 1:
//        if (power_state == OFF) {
//          function = NONE;
//          main_level_index = LVL_MAX;
//          applyLevel(getMainLevel());
//        } else {
//          switchPower(OFF);
//        }
//        break;
//      case 2:
//        if (power_state == OFF) {
//          function = NONE;
//          main_level_index = LVL_MED;
//          applyLevel(getMainLevel());
//        }
//        else {
//          if (function == NONE) {
//            sublevel_indexes[main_level_index] = (sublevel_indexes[ main_level_index ] + 1) % SUBLEVELS_NUM;
//            applyLevel(getMainLevel());
//          }
//          else if (function == STROBE) {
//            strobe_mode = (strobe_mode + 1) % STROBES_NUM + 30;
//            applyLevel(getMainLevel()); // because some strobe modes can alter the level
//          }
//          else {
//            switchPower(OFF);
//          }
//        }
//        break;
//      case 3:
//        if (power_state == OFF) {
//          function = STROBE;
//          main_level_index = LVL_MAX;
//          applyLevel(getMainLevel());
//        }
//        else {
//          switchPower(OFF);
//        }
//        break;
//      case 4:
//        if (power_state == OFF) {
//          function = BATTERY_CHECK;
//          strobes_count = 0;
//          main_level_index = LVL_MED;
//          applyLevel(getMainLevel());
//        }
//        else {
//          switchPower(OFF);
//        }
//        break;
//      case 5:
//        if (power_state == OFF) {
//          function = TEMPERATURE_CHECK;
//          strobes_count = 0;
//          main_level_index = LVL_MED;
//          applyLevel(getMainLevel());
//        }
//        else {
//          switchPower(OFF);
//        }
//        break;
//      case 6 :
//        lightnessSimulationEnabled = !lightnessSimulationEnabled;
//        break;
//      default:
//        toggleLed();
//    }
//
//#ifdef DEBUG
//    printLog();
//#endif
//  } else {
//
//    /* no click received */
//
//    if (button.isHoldingFrom(nextCycleThreshold)) { // && (cycling || function == NONE || function == STROBE))
//      cycling = true;
//      nextCycleThreshold += CYCLE_DURATION;
//
//      debug1("CYCLING");
//
//      if (power_state == ON) {
//        main_level_index = (main_level_index + 1) % LEVELS_NUM;
//      }
//      else {
//        main_level_index = LVL_MIN;
//      }
//
//      applyLevel(getMainLevel());
//
//#ifdef DEBUG
//      printLog();
//#endif
//    } else if (cycling && !button.isPushed()) {
//      debug1("Exiting from cycling");
//      cycling = false;
//      nextCycleThreshold = CYCLE_ZERO_DURATION;
//    }
//  }
//}
//
