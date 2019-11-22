################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ConsoleIO.c" \
"../Sources/Systick.c" \
"../Sources/data.c" \
"../Sources/main.c" \
"../Sources/mcg.c" \
"../Sources/memory.c" \
"../Sources/sa_mtb.c" \
"../Sources/uartBuffer.c" \
"../Sources/uartHandler.c" \

C_SRCS += \
../Sources/ConsoleIO.c \
../Sources/Systick.c \
../Sources/data.c \
../Sources/main.c \
../Sources/mcg.c \
../Sources/memory.c \
../Sources/sa_mtb.c \
../Sources/uartBuffer.c \
../Sources/uartHandler.c \

OBJS += \
./Sources/ConsoleIO.o \
./Sources/Systick.o \
./Sources/data.o \
./Sources/main.o \
./Sources/mcg.o \
./Sources/memory.o \
./Sources/sa_mtb.o \
./Sources/uartBuffer.o \
./Sources/uartHandler.o \

C_DEPS += \
./Sources/ConsoleIO.d \
./Sources/Systick.d \
./Sources/data.d \
./Sources/main.d \
./Sources/mcg.d \
./Sources/memory.d \
./Sources/sa_mtb.d \
./Sources/uartBuffer.d \
./Sources/uartHandler.d \

OBJS_QUOTED += \
"./Sources/ConsoleIO.o" \
"./Sources/Systick.o" \
"./Sources/data.o" \
"./Sources/main.o" \
"./Sources/mcg.o" \
"./Sources/memory.o" \
"./Sources/sa_mtb.o" \
"./Sources/uartBuffer.o" \
"./Sources/uartHandler.o" \

C_DEPS_QUOTED += \
"./Sources/ConsoleIO.d" \
"./Sources/Systick.d" \
"./Sources/data.d" \
"./Sources/main.d" \
"./Sources/mcg.d" \
"./Sources/memory.d" \
"./Sources/sa_mtb.d" \
"./Sources/uartBuffer.d" \
"./Sources/uartHandler.d" \

OBJS_OS_FORMAT += \
./Sources/ConsoleIO.o \
./Sources/Systick.o \
./Sources/data.o \
./Sources/main.o \
./Sources/mcg.o \
./Sources/memory.o \
./Sources/sa_mtb.o \
./Sources/uartBuffer.o \
./Sources/uartHandler.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ConsoleIO.o: ../Sources/ConsoleIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ConsoleIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ConsoleIO.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Systick.o: ../Sources/Systick.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Systick.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Systick.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/data.o: ../Sources/data.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/data.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/data.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcg.o: ../Sources/mcg.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcg.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcg.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/memory.o: ../Sources/memory.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/memory.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/memory.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/uartBuffer.o: ../Sources/uartBuffer.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/uartBuffer.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/uartBuffer.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/uartHandler.o: ../Sources/uartHandler.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/uartHandler.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/uartHandler.o"
	@echo 'Finished building: $<'
	@echo ' '


