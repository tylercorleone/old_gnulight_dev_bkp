################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/paolo/Arduino/libraries/Task/MessageTask.cpp \
/home/paolo/Arduino/libraries/Task/TaskManager.cpp 

LINK_OBJ += \
./libraries/Task/MessageTask.cpp.o \
./libraries/Task/TaskManager.cpp.o 

CPP_DEPS += \
./libraries/Task/MessageTask.cpp.d \
./libraries/Task/TaskManager.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Task/MessageTask.cpp.o: /home/paolo/Arduino/libraries/Task/MessageTask.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/Task/TaskManager.cpp.o: /home/paolo/Arduino/libraries/Task/TaskManager.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/paolo/Arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/cores/arduino" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/variants/eightanaloginputs" -I"/home/paolo/Arduino/libraries/LowPower-master" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI" -I"/home/paolo/Arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.21/libraries/SPI/src" -I"/home/paolo/Arduino/libraries/Task" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


