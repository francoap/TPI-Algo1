################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Flor.cpp \
../Juego.cpp \
../Nivel.cpp \
../Vampiro.cpp \
../main.cpp 

OBJS += \
./Flor.o \
./Juego.o \
./Nivel.o \
./Vampiro.o \
./main.o 

CPP_DEPS += \
./Flor.d \
./Juego.d \
./Nivel.d \
./Vampiro.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -std=c++11 -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


