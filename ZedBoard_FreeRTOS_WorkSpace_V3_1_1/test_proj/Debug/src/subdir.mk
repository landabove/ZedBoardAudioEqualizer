################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/adau1761.c \
../src/audioPlayer.c \
../src/kiss_fft.c \
../src/main.c \
../src/snd_sample.c 

OBJS += \
./src/adau1761.o \
./src/audioPlayer.o \
./src/kiss_fft.o \
./src/main.o \
./src/snd_sample.o 

C_DEPS += \
./src/adau1761.d \
./src/audioPlayer.d \
./src/kiss_fft.d \
./src/main.d \
./src/snd_sample.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../freertos_bsp_3_1_1/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


