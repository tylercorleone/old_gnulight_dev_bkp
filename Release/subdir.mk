################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../gnulight.ino 

CPP_SRCS += \
../AdvancedLightDriver.cpp \
../Button.cpp \
../ConstantLightMode.cpp \
../FunctionsSequenceTask.cpp \
../Gnulight.cpp \
../GnulightMode.cpp \
../LightDriver.cpp \
../LightMonitorTask.cpp \
../LithiumBattery.cpp \
../LithiumBatteryMonitor.cpp \
../ParameterCheckMode.cpp \
../PowerOffMode.cpp \
../StrobeMode.cpp \
../UserInteractionMonitorTask.cpp \
../sloeber.ino.cpp \
../utils.cpp 

LINK_OBJ += \
./AdvancedLightDriver.cpp.o \
./Button.cpp.o \
./ConstantLightMode.cpp.o \
./FunctionsSequenceTask.cpp.o \
./Gnulight.cpp.o \
./GnulightMode.cpp.o \
./LightDriver.cpp.o \
./LightMonitorTask.cpp.o \
./LithiumBattery.cpp.o \
./LithiumBatteryMonitor.cpp.o \
./ParameterCheckMode.cpp.o \
./PowerOffMode.cpp.o \
./StrobeMode.cpp.o \
./UserInteractionMonitorTask.cpp.o \
./sloeber.ino.cpp.o \
./utils.cpp.o 

INO_DEPS += \
./gnulight.ino.d 

CPP_DEPS += \
./AdvancedLightDriver.cpp.d \
./Button.cpp.d \
./ConstantLightMode.cpp.d \
./FunctionsSequenceTask.cpp.d \
./Gnulight.cpp.d \
./GnulightMode.cpp.d \
./LightDriver.cpp.d \
./LightMonitorTask.cpp.d \
./LithiumBattery.cpp.d \
./LithiumBatteryMonitor.cpp.d \
./ParameterCheckMode.cpp.d \
./PowerOffMode.cpp.d \
./StrobeMode.cpp.d \
./UserInteractionMonitorTask.cpp.d \
./sloeber.ino.cpp.d \
./utils.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
AdvancedLightDriver.cpp.o: ../AdvancedLightDriver.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Button.cpp.o: ../Button.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

ConstantLightMode.cpp.o: ../ConstantLightMode.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

FunctionsSequenceTask.cpp.o: ../FunctionsSequenceTask.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Gnulight.cpp.o: ../Gnulight.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

GnulightMode.cpp.o: ../GnulightMode.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

LightDriver.cpp.o: ../LightDriver.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

LightMonitorTask.cpp.o: ../LightMonitorTask.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

LithiumBattery.cpp.o: ../LithiumBattery.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

LithiumBatteryMonitor.cpp.o: ../LithiumBatteryMonitor.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

ParameterCheckMode.cpp.o: ../ParameterCheckMode.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

PowerOffMode.cpp.o: ../PowerOffMode.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

StrobeMode.cpp.o: ../StrobeMode.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

UserInteractionMonitorTask.cpp.o: ../UserInteractionMonitorTask.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

gnulight.o: ../gnulight.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

sloeber.ino.cpp.o: ../sloeber.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

utils.cpp.o: ../utils.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


