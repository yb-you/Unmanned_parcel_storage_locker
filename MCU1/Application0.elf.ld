
/*
!!! Primary linker script file generated automatically !!!
This file contains the input and output files names
It also includes the secondary/main linker script that is specified in the Ride options (default or custom)
*/

SEARCH_DIR(".")
SEARCH_DIR("C:\cortex_m3\microprocessorEX\project_MCU1\obj")
SEARCH_DIR("C:\Program Files (x86)\Raisonance\Ride\Lib\ARM")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\delay.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\main.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\RCC_config.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\GPIO_config.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\NVIC_config.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\EXTI_config.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\TIM_config.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\USART_config.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\Keypad.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\door_lock.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\lcd.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\stm32f10x_it.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\system_stm32f10x.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\startup_stm32f10x_md.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\misc.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\stm32f10x_spi.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\stm32f10x_exti.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\stm32f10x_flash.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\stm32f10x_tim.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\stm32f10x_gpio.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\stm32f10x_usart.o")
INPUT("C:\cortex_m3\microprocessorEX\project_MCU1\obj\stm32f10x_rcc.o")
EXTERN( __io_putchar )
EXTERN( _write )
GROUP(
"STM32x_io_putchar_thumb.a"
"std_sbrk_thumb.lib"
"smallprintf_thumb.a"
"libc.a"
"libm.a"

)
INCLUDE "C:\cortex_m3\microprocessorEX\project_MCU1\obj\STM32F103_128K_20K_FLASH.ld"
OUTPUT("C:\cortex_m3\microprocessorEX\project_MCU1\Application0.elf")
