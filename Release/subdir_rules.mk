################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
gpio_if.obj: ../gpio_if.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -Ooff --opt_for_speed=1 --include_path="D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/example/common" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/driverlib/" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/inc/" --define=ccs --define=cc3200 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="gpio_if.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

kiss_fft.obj: ../kiss_fft.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -Ooff --opt_for_speed=1 --include_path="D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/example/common" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/driverlib/" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/inc/" --define=ccs --define=cc3200 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="kiss_fft.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

kiss_fftr.obj: ../kiss_fftr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -Ooff --opt_for_speed=1 --include_path="D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/example/common" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/driverlib/" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/inc/" --define=ccs --define=cc3200 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="kiss_fftr.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -Ooff --opt_for_speed=1 --include_path="D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/example/common" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/driverlib/" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/inc/" --define=ccs --define=cc3200 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pinmux.obj: ../pinmux.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -Ooff --opt_for_speed=1 --include_path="D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/example/common" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/driverlib/" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/inc/" --define=ccs --define=cc3200 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="pinmux.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: D:/TI/CC3200SDK_1.3.0/cc3200-sdk/example/common/startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -Ooff --opt_for_speed=1 --include_path="D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/example/common" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/driverlib/" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/inc/" --define=ccs --define=cc3200 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer_if.obj: ../timer_if.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -Ooff --opt_for_speed=1 --include_path="D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/example/common" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/driverlib/" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/inc/" --define=ccs --define=cc3200 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="timer_if.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart_if.obj: D:/TI/CC3200SDK_1.3.0/cc3200-sdk/example/common/uart_if.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -Ooff --opt_for_speed=1 --include_path="D:/TI/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/example/common" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/driverlib/" --include_path="D:/TI/CC3200SDK_1.3.0/cc3200-sdk/inc/" --define=ccs --define=cc3200 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uart_if.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


