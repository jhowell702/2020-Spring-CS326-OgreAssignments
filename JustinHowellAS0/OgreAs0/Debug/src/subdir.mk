################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BaseApplication.cpp \
../src/TutorialApplication.cpp 

OBJS += \
./src/BaseApplication.o \
./src/TutorialApplication.o 

CPP_DEPS += \
./src/BaseApplication.d \
./src/TutorialApplication.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/OGRE -I/usr/local/include/OGRE/Overlay -I/usr/include/ois -I"/home/zeroxgen/eclipse/eclipse-workspace/OgreAs0/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


