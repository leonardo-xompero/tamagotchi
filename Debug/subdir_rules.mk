################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/energia_tool_arm-none-eabi-gcc_6.3.1-20170620/bin/arm-none-eabi-gcc-6.3.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_target_name__=M4F -Dxdc_cfg__xheader__=\"configPkg/package/cfg/energia_pm4fg.h\" -DBOARD_MSP_EXP432P401R -Dxdc__nolocalstring=1 -D__MSP432P401R__ -DCORE_VERSION=5252 -DF_CPU=48000000L -DENERGIA_MSP_EXP432P401R -DENERGIA_ARCH_MSP432R -D_DEFAULT_SOURCE -DENERGIA=23 -DARDUINO=10610 -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/cores/msp432r/ti/runtime/wiring/" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/cores/msp432r/ti/runtime/wiring/msp432" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/kernel/tirtos/packages/ti/sysbios/posix" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/kernel/tirtos/packages" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/source" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/energia" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/source/ti/devices/msp432p4xx/driverlib" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/source/ti/devices/msp432p4xx/inc" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/source/ti/devices/msp432p4xx/" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/source/third_party/CMSIS/Include" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/cores/msp432r" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/variants/MSP_EXP432P401R" -I"C:/ti/workspace/tamagotchi" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/libraries/EduBPMKII_Screen" -I"C:/ti/energia_tool_arm-none-eabi-gcc_6.3.1-20170620/arm-none-eabi/include" -Os -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -w -Wall -mabi=aapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

pet_menu_x.null: ../pet_menu_x.ino
	@echo 'Building file: "$<"'
	@echo 'Invoking: Resource Custom Build Step'
	
	@echo 'Finished building: "$<"'
	@echo ' '

pet_menu_y.null: ../pet_menu_y.ino
	@echo 'Building file: "$<"'
	@echo 'Invoking: Resource Custom Build Step'
	
	@echo 'Finished building: "$<"'
	@echo ' '

build-272851377:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-272851377-inproc

build-272851377-inproc: ../tamagotchi.ino
	@echo 'Building file: "$<"'
	@echo 'Invoking: Resource Custom Build Step'
	
	@echo 'Finished building: "$<"'
	@echo ' '

tamagotchi.cpp: build-272851377 ../tamagotchi.ino
main.cpp: build-272851377

%.o: ./%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/energia_tool_arm-none-eabi-gcc_6.3.1-20170620/bin/arm-none-eabi-gcc-6.3.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_target_name__=M4F -Dxdc_cfg__xheader__=\"configPkg/package/cfg/energia_pm4fg.h\" -DBOARD_MSP_EXP432P401R -Dxdc__nolocalstring=1 -D__MSP432P401R__ -DCORE_VERSION=5252 -DF_CPU=48000000L -DENERGIA_MSP_EXP432P401R -DENERGIA_ARCH_MSP432R -D_DEFAULT_SOURCE -DENERGIA=23 -DARDUINO=10610 -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/cores/msp432r/ti/runtime/wiring/" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/cores/msp432r/ti/runtime/wiring/msp432" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/kernel/tirtos/packages/ti/sysbios/posix" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/kernel/tirtos/packages" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/source" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/energia" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/source/ti/devices/msp432p4xx/driverlib" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/source/ti/devices/msp432p4xx/inc" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/source/ti/devices/msp432p4xx/" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/system/source/third_party/CMSIS/Include" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/cores/msp432r" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/variants/MSP_EXP432P401R" -I"C:/ti/workspace/tamagotchi" -I"C:/Users/inca/AppData/Local/Energia15/packages/energia/hardware/msp432r/5.29.0/libraries/EduBPMKII_Screen" -I"C:/ti/energia_tool_arm-none-eabi-gcc_6.3.1-20170620/arm-none-eabi/include" -Os -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -w -Wall -mabi=aapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"  -fno-rtti -fno-threadsafe-statics -fno-exceptions $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


