################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/adau1761.c \
C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/audioPlayer.c \
C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/audioRxTx.c \
C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/audioSample.c \
C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/bufferPool_d.c \
C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/chunk_d.c \
C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/main.c \
C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/snd_sample.c 

OBJS += \
./srcExt/adau1761.o \
./srcExt/audioPlayer.o \
./srcExt/audioRxTx.o \
./srcExt/audioSample.o \
./srcExt/bufferPool_d.o \
./srcExt/chunk_d.o \
./srcExt/main.o \
./srcExt/snd_sample.o 

C_DEPS += \
./srcExt/adau1761.d \
./srcExt/audioPlayer.d \
./srcExt/audioRxTx.d \
./srcExt/audioSample.d \
./srcExt/bufferPool_d.d \
./srcExt/chunk_d.d \
./srcExt/main.d \
./srcExt/snd_sample.d 


# Each subdirectory must supply rules for building sources it contributes
srcExt/adau1761.o: C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/adau1761.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../freertos_bsp_3_1_1/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

srcExt/audioPlayer.o: C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/audioPlayer.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../freertos_bsp_3_1_1/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

srcExt/audioRxTx.o: C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/audioRxTx.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../freertos_bsp_3_1_1/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

srcExt/audioSample.o: C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/audioSample.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../freertos_bsp_3_1_1/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

srcExt/bufferPool_d.o: C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/bufferPool_d.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../freertos_bsp_3_1_1/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

srcExt/chunk_d.o: C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/chunk_d.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../freertos_bsp_3_1_1/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

srcExt/main.o: C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../freertos_bsp_3_1_1/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

srcExt/snd_sample.o: C:/Users/Surya/Documents/surya/zedboard/lab5/audio_rx_tx/src/snd_sample.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../freertos_bsp_3_1_1/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


