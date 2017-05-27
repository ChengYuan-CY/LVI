################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../CMSIS/EFM32PG1B/startup_gcc_efm32pg1b.s 

C_SRCS += \
../CMSIS/EFM32PG1B/system_efm32pg1b.c 

OBJS += \
./CMSIS/EFM32PG1B/startup_gcc_efm32pg1b.o \
./CMSIS/EFM32PG1B/system_efm32pg1b.o 

C_DEPS += \
./CMSIS/EFM32PG1B/system_efm32pg1b.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/EFM32PG1B/%.o: ../CMSIS/EFM32PG1B/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -c -x assembler-with-cpp -I"C:\Users\yucheng\SimplicityStudio\v4_workspace\SLSTK3401A_cryotimer\inc" -I"C:/Users/yucheng/SimplicityStudio/v4_workspace/SLSTK3401A_cryotimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//hardware/kit/SLSTK3401A_EFM32PG/config" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//platform/Device/SiliconLabs/EFM32PG1B/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//platform/emlib/inc" '-DEFM32PG1B200F256GM48=1' -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/EFM32PG1B/system_efm32pg1b.o: ../CMSIS/EFM32PG1B/system_efm32pg1b.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32PG1B200F256GM48=1' -I"C:\Users\yucheng\SimplicityStudio\v4_workspace\SLSTK3401A_cryotimer\inc" -I"C:/Users/yucheng/SimplicityStudio/v4_workspace/SLSTK3401A_cryotimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//hardware/kit/SLSTK3401A_EFM32PG/config" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//platform/Device/SiliconLabs/EFM32PG1B/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.0//platform/emlib/inc" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"CMSIS/EFM32PG1B/system_efm32pg1b.d" -MT"CMSIS/EFM32PG1B/system_efm32pg1b.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


