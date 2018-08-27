ARM Linker, 5.03 [Build 76] [MDK-ARM Standard]

==============================================================================

Section Cross References

    main.o(.text) refers to system_stm32f4xx.o(.text) for SystemInit
    main.o(.text) refers to misc.o(.text) for NVIC_PriorityGroupConfig
    main.o(.text) refers to ili9325.o(.text) for ili9320_Initializtion
    main.o(.text) refers to led.o(.text) for led_configuration
    main.o(.text) refers to can1.o(.text) for Can1_Configuration
    main.o(.text) refers to stm32f4xx_gpio.o(.text) for GPIO_ToggleBits
    main.o(.text) refers to delay.o(.text) for delay_ms
    main.o(.text) refers to ov7725.o(.text) for OV_Init
    main.o(.text) refers to usart.o(.text) for USART_GPIO_Config
    main.o(.text) refers to ili9320_api.o(.text) for GUI_Text
    main.o(.text) refers to image.o(.text) for Transfer2Gray
    main.o(.text) refers to pid.o(.text) for CameraPid
    main.o(.text) refers to image.o(.data) for beep_send_flag
    main.o(.text) refers to main.o(.data) for button1
    main.o(.text) refers to ps2.o(.data) for send_picture_flag
    main.o(.text) refers to ov7725.o(.data) for Gray_Image_Buffer
    main.o(.text) refers to ov7725.o(.bss) for image
    main.o(.text) refers to dmul.o(.text) for __aeabi_dmul
    main.o(.text) refers to dfixi.o(.text) for __aeabi_d2iz
    main.o(.text) refers to visual_scope.o(.text) for VS4Channal_Send
    main.o(.text) refers to stm32f4xx_dma.o(.text) for DMA_GetITStatus
    main.o(.text) refers to stm32f4xx_dcmi.o(.text) for DCMI_CaptureCmd
    main.o(.text) refers to pid.o(.data) for XpScTime
    main.o(.text) refers to can1.o(.data) for HuorDistance
    led.o(.text) refers to stm32f4xx_rcc.o(.text) for RCC_AHB1PeriphClockCmd
    led.o(.text) refers to stm32f4xx_gpio.o(.text) for GPIO_Init
    ov7725.o(.text) refers to stm32f4xx_rcc.o(.text) for RCC_AHB1PeriphClockCmd
    ov7725.o(.text) refers to stm32f4xx_gpio.o(.text) for GPIO_PinAFConfig
    ov7725.o(.text) refers to sccb.o(.text) for SCCB_GPIO_Config
    ov7725.o(.text) refers to stm32f4xx_dcmi.o(.text) for DCMI_Init
    ov7725.o(.text) refers to misc.o(.text) for NVIC_Init
    ov7725.o(.text) refers to stm32f4xx_dma.o(.text) for DMA_DeInit
    ov7725.o(.text) refers to delay.o(.text) for delay_ms
    ov7725.o(.text) refers to ov7725.o(.constdata) for OV7725YUV_reg
    ov7725.o(.text) refers to ov7725.o(.bss) for image
    sccb.o(.text) refers to stm32f4xx_rcc.o(.text) for RCC_AHB1PeriphClockCmd
    sccb.o(.text) refers to stm32f4xx_gpio.o(.text) for GPIO_Init
    image.o(.text) refers to memseta.o(.text) for __aeabi_memclr4
    image.o(.text) refers to dflti.o(.text) for __aeabi_i2d
    image.o(.text) refers to fabs.o(i.__hardfp_fabs) for __hardfp_fabs
    image.o(.text) refers to cdcmple.o(.text) for __aeabi_cdcmple
    image.o(.text) refers to f2d.o(.text) for __aeabi_f2d
    image.o(.text) refers to cdrcmple.o(.text) for __aeabi_cdrcmple
    image.o(.text) refers to image.o(.data) for start_row
    image.o(.text) refers to ddiv.o(.text) for __aeabi_ddiv
    image.o(.text) refers to image.o(.bss) for center
    image.o(.text) refers to dadd.o(.text) for __aeabi_dsub
    image.o(.text) refers to led_show.o(.text) for number_show
    image.o(.text) refers to d2f.o(.text) for __aeabi_d2f
    image.o(.text) refers to can1.o(.data) for HuorDistance
    image.o(.text) refers to ov7725.o(.data) for Gray_Image_Buffer
    image.o(.text) refers to dmul.o(.text) for __aeabi_dmul
    image.o(.text) refers to dfixi.o(.text) for __aeabi_d2iz
    usart.o(.text) refers to stm32f4xx_rcc.o(.text) for RCC_AHB1PeriphClockCmd
    usart.o(.text) refers to stm32f4xx_gpio.o(.text) for GPIO_PinAFConfig
    usart.o(.text) refers to stm32f4xx_usart.o(.text) for USART_Init
    usart.o(.text) refers to misc.o(.text) for NVIC_Init
    usart.o(.text) refers to stm32f4xx_dma.o(.text) for DMA_DeInit
    usart.o(.text) refers to queue.o(.text) for GetQueueLength
    usart.o(.text) refers to usart.o(.bss) for aTxBuffer_UART2
    usart.o(.text) refers to usart.o(.data) for USART2_RX_STA
    can1.o(.text) refers to stm32f4xx_rcc.o(.text) for RCC_APB1PeriphClockCmd
    can1.o(.text) refers to stm32f4xx_gpio.o(.text) for GPIO_PinAFConfig
    can1.o(.text) refers to misc.o(.text) for NVIC_Init
    can1.o(.text) refers to stm32f4xx_can.o(.text) for CAN_DeInit
    can1.o(.text) refers to mydataprocess.o(.text) for EncodeS32Data
    can1.o(.text) refers to can1.o(.data) for ID_Electromagnet
    pid.o(.text) refers to f2d.o(.text) for __aeabi_f2d
    pid.o(.text) refers to dadd.o(.text) for __aeabi_dadd
    pid.o(.text) refers to d2f.o(.text) for __aeabi_d2f
    pid.o(.text) refers to fabs.o(i.__hardfp_fabs) for __hardfp_fabs
    pid.o(.text) refers to cdcmple.o(.text) for __aeabi_cdcmple
    pid.o(.text) refers to cdrcmple.o(.text) for __aeabi_cdrcmple
    pid.o(.text) refers to ddiv.o(.text) for __aeabi_ddiv
    pid.o(.text) refers to dmul.o(.text) for __aeabi_dmul
    pid.o(.text) refers to dfixi.o(.text) for __aeabi_d2iz
    pid.o(.text) refers to main.o(.data) for message
    pid.o(.text) refers to pid.o(.data) for Ek1
    pid.o(.text) refers to image.o(.data) for sp_flag
    pid.o(.text) refers to can1.o(.data) for HuorDistance
    pid.o(.text) refers to can1.o(.text) for SendPulse
    ili9320_api.o(.text) refers to ili9325.o(.text) for ili9320_PutChar
    led_show.o(.text) refers to printfa.o(i.__0sprintf) for __2sprintf
    led_show.o(.text) refers to ili9320_api.o(.text) for GUI_Text
    led_show.o(.text) refers to f2d.o(.text) for __aeabi_f2d
    led_show.o(.text) refers to led_show.o(.constdata) for .constdata
    ili9325.o(.text) refers to stm32f4xx_rcc.o(.text) for RCC_AHB3PeriphClockCmd
    ili9325.o(.text) refers to stm32f4xx_gpio.o(.text) for GPIO_PinAFConfig
    ili9325.o(.text) refers to stm32f4xx_fsmc.o(.text) for FSMC_NORSRAMInit
    ili9325.o(.text) refers to delay.o(.text) for delay_ms
    ili9325.o(.text) refers to ili9325.o(.data) for DeviceCode
    ili9325.o(.text) refers to ili9325.o(.constdata) for ascii_8x16
    visual_scope.o(.text) refers to usart.o(.text) for USART2_sendData
    kalman.o(.text) refers to dfltui.o(.text) for __aeabi_ui2d
    kalman.o(.text) refers to dmul.o(.text) for __aeabi_dmul
    kalman.o(.text) refers to dadd.o(.text) for __aeabi_dadd
    kalman.o(.text) refers to d2f.o(.text) for __aeabi_d2f
    kalman.o(.text) refers to f2d.o(.text) for __aeabi_f2d
    kalman.o(.text) refers to ddiv.o(.text) for __aeabi_ddiv
    ps2.o(.text) refers to usart.o(.data) for HandKey_Receive
    ps2.o(.text) refers to ps2.o(.data) for HandKey
    stm32f4xx_gpio.o(.text) refers to stm32f4xx_rcc.o(.text) for RCC_AHB1PeriphResetCmd
    stm32f4xx_rcc.o(.text) refers to stm32f4xx_rcc.o(.data) for APBAHBPrescTable
    stm32f4xx_tim.o(.text) refers to stm32f4xx_rcc.o(.text) for RCC_APB2PeriphResetCmd
    stm32f4xx_usart.o(.text) refers to stm32f4xx_rcc.o(.text) for RCC_APB2PeriphResetCmd
    stm32f4xx_can.o(.text) refers to stm32f4xx_rcc.o(.text) for RCC_APB1PeriphResetCmd
    system_stm32f4xx.o(.text) refers to system_stm32f4xx.o(.data) for SystemCoreClock
    startup_stm32f4xx.o(RESET) refers to startup_stm32f4xx.o(STACK) for __initial_sp
    startup_stm32f4xx.o(RESET) refers to startup_stm32f4xx.o(.text) for Reset_Handler
    startup_stm32f4xx.o(RESET) refers to stm32f4xx_it.o(.text) for NMI_Handler
    startup_stm32f4xx.o(RESET) refers to main.o(.text) for SysTick_Handler
    startup_stm32f4xx.o(RESET) refers to usart.o(.text) for DMA1_Stream6_IRQHandler
    startup_stm32f4xx.o(RESET) refers to can1.o(.text) for CAN1_RX0_IRQHandler
    startup_stm32f4xx.o(.text) refers to system_stm32f4xx.o(.text) for SystemInit
    startup_stm32f4xx.o(.text) refers to entry.o(.ARM.Collect$$$$00000000) for __main
    fabs.o(i.__hardfp_fabs) refers (Special) to iusefp.o(.text) for __I$use$fp
    fabs.o(i.__softfp_fabs) refers (Special) to iusefp.o(.text) for __I$use$fp
    fabs.o(i.fabs) refers (Special) to iusefp.o(.text) for __I$use$fp
    entry.o(.ARM.Collect$$$$00000000) refers (Special) to entry10a.o(.ARM.Collect$$$$0000000D) for __rt_final_cpp
    entry.o(.ARM.Collect$$$$00000000) refers (Special) to entry11a.o(.ARM.Collect$$$$0000000F) for __rt_final_exit
    entry.o(.ARM.Collect$$$$00000000) refers (Special) to entry7b.o(.ARM.Collect$$$$00000008) for _main_clock
    entry.o(.ARM.Collect$$$$00000000) refers (Special) to entry8b.o(.ARM.Collect$$$$0000000A) for _main_cpp_init
    entry.o(.ARM.Collect$$$$00000000) refers (Special) to entry9a.o(.ARM.Collect$$$$0000000B) for _main_init
    entry.o(.ARM.Collect$$$$00000000) refers (Special) to entry5.o(.ARM.Collect$$$$00000004) for _main_scatterload
    entry.o(.ARM.Collect$$$$00000000) refers (Special) to entry2.o(.ARM.Collect$$$$00000001) for _main_stk
    printfb.o(i.__0fprintf$bare) refers to printfb.o(i._printf_core) for _printf_core
    printfb.o(i.__0fprintf$bare) refers to fputc.o(i.fputc) for fputc
    printfb.o(i.__0printf$bare) refers to printfb.o(i._printf_core) for _printf_core
    printfb.o(i.__0printf$bare) refers to fputc.o(i.fputc) for fputc
    printfb.o(i.__0printf$bare) refers to stdout.o(.data) for __stdout
    printfb.o(i.__0snprintf$bare) refers to printfb.o(i._printf_core) for _printf_core
    printfb.o(i.__0snprintf$bare) refers to printfb.o(i._snputc) for _snputc
    printfb.o(i.__0sprintf$bare) refers to printfb.o(i._printf_core) for _printf_core
    printfb.o(i.__0sprintf$bare) refers to printfb.o(i._sputc) for _sputc
    printfb.o(i.__0vfprintf$bare) refers to printfb.o(i._printf_core) for _printf_core
    printfb.o(i.__0vfprintf$bare) refers to fputc.o(i.fputc) for fputc
    printfb.o(i.__0vprintf$bare) refers to printfb.o(i._printf_core) for _printf_core
    printfb.o(i.__0vprintf$bare) refers to fputc.o(i.fputc) for fputc
    printfb.o(i.__0vprintf$bare) refers to stdout.o(.data) for __stdout
    printfb.o(i.__0vsnprintf$bare) refers to printfb.o(i._printf_core) for _printf_core
    printfb.o(i.__0vsnprintf$bare) refers to printfb.o(i._snputc) for _snputc
    printfb.o(i.__0vsprintf$bare) refers to printfb.o(i._printf_core) for _printf_core
    printfb.o(i.__0vsprintf$bare) refers to printfb.o(i._sputc) for _sputc
    printf0.o(i.__0fprintf$0) refers to printf0.o(i._printf_core) for _printf_core
    printf0.o(i.__0fprintf$0) refers to fputc.o(i.fputc) for fputc
    printf0.o(i.__0printf$0) refers to printf0.o(i._printf_core) for _printf_core
    printf0.o(i.__0printf$0) refers to fputc.o(i.fputc) for fputc
    printf0.o(i.__0printf$0) refers to stdout.o(.data) for __stdout
    printf0.o(i.__0snprintf$0) refers to printf0.o(i._printf_core) for _printf_core
    printf0.o(i.__0snprintf$0) refers to printf0.o(i._snputc) for _snputc
    printf0.o(i.__0sprintf$0) refers to printf0.o(i._printf_core) for _printf_core
    printf0.o(i.__0sprintf$0) refers to printf0.o(i._sputc) for _sputc
    printf0.o(i.__0vfprintf$0) refers to printf0.o(i._printf_core) for _printf_core
    printf0.o(i.__0vfprintf$0) refers to fputc.o(i.fputc) for fputc
    printf0.o(i.__0vprintf$0) refers to printf0.o(i._printf_core) for _printf_core
    printf0.o(i.__0vprintf$0) refers to fputc.o(i.fputc) for fputc
    printf0.o(i.__0vprintf$0) refers to stdout.o(.data) for __stdout
    printf0.o(i.__0vsnprintf$0) refers to printf0.o(i._printf_core) for _printf_core
    printf0.o(i.__0vsnprintf$0) refers to printf0.o(i._snputc) for _snputc
    printf0.o(i.__0vsprintf$0) refers to printf0.o(i._printf_core) for _printf_core
    printf0.o(i.__0vsprintf$0) refers to printf0.o(i._sputc) for _sputc
    printf1.o(i.__0fprintf$1) refers to printf1.o(i._printf_core) for _printf_core
    printf1.o(i.__0fprintf$1) refers to fputc.o(i.fputc) for fputc
    printf1.o(i.__0printf$1) refers to printf1.o(i._printf_core) for _printf_core
    printf1.o(i.__0printf$1) refers to fputc.o(i.fputc) for fputc
    printf1.o(i.__0printf$1) refers to stdout.o(.data) for __stdout
    printf1.o(i.__0snprintf$1) refers to printf1.o(i._printf_core) for _printf_core
    printf1.o(i.__0snprintf$1) refers to printf1.o(i._snputc) for _snputc
    printf1.o(i.__0sprintf$1) refers to printf1.o(i._printf_core) for _printf_core
    printf1.o(i.__0sprintf$1) refers to printf1.o(i._sputc) for _sputc
    printf1.o(i.__0vfprintf$1) refers to printf1.o(i._printf_core) for _printf_core
    printf1.o(i.__0vfprintf$1) refers to fputc.o(i.fputc) for fputc
    printf1.o(i.__0vprintf$1) refers to printf1.o(i._printf_core) for _printf_core
    printf1.o(i.__0vprintf$1) refers to fputc.o(i.fputc) for fputc
    printf1.o(i.__0vprintf$1) refers to stdout.o(.data) for __stdout
    printf1.o(i.__0vsnprintf$1) refers to printf1.o(i._printf_core) for _printf_core
    printf1.o(i.__0vsnprintf$1) refers to printf1.o(i._snputc) for _snputc
    printf1.o(i.__0vsprintf$1) refers to printf1.o(i._printf_core) for _printf_core
    printf1.o(i.__0vsprintf$1) refers to printf1.o(i._sputc) for _sputc
    printf1.o(i._printf_core) refers to uidiv.o(.text) for __aeabi_uidivmod
    printf2.o(i.__0fprintf$2) refers to printf2.o(i._printf_core) for _printf_core
    printf2.o(i.__0fprintf$2) refers to fputc.o(i.fputc) for fputc
    printf2.o(i.__0printf$2) refers to printf2.o(i._printf_core) for _printf_core
    printf2.o(i.__0printf$2) refers to fputc.o(i.fputc) for fputc
    printf2.o(i.__0printf$2) refers to stdout.o(.data) for __stdout
    printf2.o(i.__0snprintf$2) refers to printf2.o(i._printf_core) for _printf_core
    printf2.o(i.__0snprintf$2) refers to printf2.o(i._snputc) for _snputc
    printf2.o(i.__0sprintf$2) refers to printf2.o(i._printf_core) for _printf_core
    printf2.o(i.__0sprintf$2) refers to printf2.o(i._sputc) for _sputc
    printf2.o(i.__0vfprintf$2) refers to printf2.o(i._printf_core) for _printf_core
    printf2.o(i.__0vfprintf$2) refers to fputc.o(i.fputc) for fputc
    printf2.o(i.__0vprintf$2) refers to printf2.o(i._printf_core) for _printf_core
    printf2.o(i.__0vprintf$2) refers to fputc.o(i.fputc) for fputc
    printf2.o(i.__0vprintf$2) refers to stdout.o(.data) for __stdout
    printf2.o(i.__0vsnprintf$2) refers to printf2.o(i._printf_core) for _printf_core
    printf2.o(i.__0vsnprintf$2) refers to printf2.o(i._snputc) for _snputc
    printf2.o(i.__0vsprintf$2) refers to printf2.o(i._printf_core) for _printf_core
    printf2.o(i.__0vsprintf$2) refers to printf2.o(i._sputc) for _sputc
    printf3.o(i.__0fprintf$3) refers to printf3.o(i._printf_core) for _printf_core
    printf3.o(i.__0fprintf$3) refers to fputc.o(i.fputc) for fputc
    printf3.o(i.__0printf$3) refers to printf3.o(i._printf_core) for _printf_core
    printf3.o(i.__0printf$3) refers to fputc.o(i.fputc) for fputc
    printf3.o(i.__0printf$3) refers to stdout.o(.data) for __stdout
    printf3.o(i.__0snprintf$3) refers to printf3.o(i._printf_core) for _printf_core
    printf3.o(i.__0snprintf$3) refers to printf3.o(i._snputc) for _snputc
    printf3.o(i.__0sprintf$3) refers to printf3.o(i._printf_core) for _printf_core
    printf3.o(i.__0sprintf$3) refers to printf3.o(i._sputc) for _sputc
    printf3.o(i.__0vfprintf$3) refers to printf3.o(i._printf_core) for _printf_core
    printf3.o(i.__0vfprintf$3) refers to fputc.o(i.fputc) for fputc
    printf3.o(i.__0vprintf$3) refers to printf3.o(i._printf_core) for _printf_core
    printf3.o(i.__0vprintf$3) refers to fputc.o(i.fputc) for fputc
    printf3.o(i.__0vprintf$3) refers to stdout.o(.data) for __stdout
    printf3.o(i.__0vsnprintf$3) refers to printf3.o(i._printf_core) for _printf_core
    printf3.o(i.__0vsnprintf$3) refers to printf3.o(i._snputc) for _snputc
    printf3.o(i.__0vsprintf$3) refers to printf3.o(i._printf_core) for _printf_core
    printf3.o(i.__0vsprintf$3) refers to printf3.o(i._sputc) for _sputc
    printf3.o(i._printf_core) refers to uidiv.o(.text) for __aeabi_uidivmod
    printf4.o(i.__0fprintf$4) refers to printf4.o(i._printf_core) for _printf_core
    printf4.o(i.__0fprintf$4) refers to fputc.o(i.fputc) for fputc
    printf4.o(i.__0printf$4) refers to printf4.o(i._printf_core) for _printf_core
    printf4.o(i.__0printf$4) refers to fputc.o(i.fputc) for fputc
    printf4.o(i.__0printf$4) refers to stdout.o(.data) for __stdout
    printf4.o(i.__0snprintf$4) refers to printf4.o(i._printf_core) for _printf_core
    printf4.o(i.__0snprintf$4) refers to printf4.o(i._snputc) for _snputc
    printf4.o(i.__0sprintf$4) refers to printf4.o(i._printf_core) for _printf_core
    printf4.o(i.__0sprintf$4) refers to printf4.o(i._sputc) for _sputc
    printf4.o(i.__0vfprintf$4) refers to printf4.o(i._printf_core) for _printf_core
    printf4.o(i.__0vfprintf$4) refers to fputc.o(i.fputc) for fputc
    printf4.o(i.__0vprintf$4) refers to printf4.o(i._printf_core) for _printf_core
    printf4.o(i.__0vprintf$4) refers to fputc.o(i.fputc) for fputc
    printf4.o(i.__0vprintf$4) refers to stdout.o(.data) for __stdout
    printf4.o(i.__0vsnprintf$4) refers to printf4.o(i._printf_core) for _printf_core
    printf4.o(i.__0vsnprintf$4) refers to printf4.o(i._snputc) for _snputc
    printf4.o(i.__0vsprintf$4) refers to printf4.o(i._printf_core) for _printf_core
    printf4.o(i.__0vsprintf$4) refers to printf4.o(i._sputc) for _sputc
    printf4.o(i._printf_core) refers to uldiv.o(.text) for __aeabi_uldivmod
    printf5.o(i.__0fprintf$5) refers to printf5.o(i._printf_core) for _printf_core
    printf5.o(i.__0fprintf$5) refers to fputc.o(i.fputc) for fputc
    printf5.o(i.__0printf$5) refers to printf5.o(i._printf_core) for _printf_core
    printf5.o(i.__0printf$5) refers to fputc.o(i.fputc) for fputc
    printf5.o(i.__0printf$5) refers to stdout.o(.data) for __stdout
    printf5.o(i.__0snprintf$5) refers to printf5.o(i._printf_core) for _printf_core
    printf5.o(i.__0snprintf$5) refers to printf5.o(i._snputc) for _snputc
    printf5.o(i.__0sprintf$5) refers to printf5.o(i._printf_core) for _printf_core
    printf5.o(i.__0sprintf$5) refers to printf5.o(i._sputc) for _sputc
    printf5.o(i.__0vfprintf$5) refers to printf5.o(i._printf_core) for _printf_core
    printf5.o(i.__0vfprintf$5) refers to fputc.o(i.fputc) for fputc
    printf5.o(i.__0vprintf$5) refers to printf5.o(i._printf_core) for _printf_core
    printf5.o(i.__0vprintf$5) refers to fputc.o(i.fputc) for fputc
    printf5.o(i.__0vprintf$5) refers to stdout.o(.data) for __stdout
    printf5.o(i.__0vsnprintf$5) refers to printf5.o(i._printf_core) for _printf_core
    printf5.o(i.__0vsnprintf$5) refers to printf5.o(i._snputc) for _snputc
    printf5.o(i.__0vsprintf$5) refers to printf5.o(i._printf_core) for _printf_core
    printf5.o(i.__0vsprintf$5) refers to printf5.o(i._sputc) for _sputc
    printf5.o(i._printf_core) refers to uldiv.o(.text) for __aeabi_uldivmod
    printf6.o(i.__0fprintf$6) refers to printf6.o(i._printf_core) for _printf_core
    printf6.o(i.__0fprintf$6) refers to fputc.o(i.fputc) for fputc
    printf6.o(i.__0printf$6) refers to printf6.o(i._printf_core) for _printf_core
    printf6.o(i.__0printf$6) refers to fputc.o(i.fputc) for fputc
    printf6.o(i.__0printf$6) refers to stdout.o(.data) for __stdout
    printf6.o(i.__0snprintf$6) refers to printf6.o(i._printf_core) for _printf_core
    printf6.o(i.__0snprintf$6) refers to printf6.o(i._snputc) for _snputc
    printf6.o(i.__0sprintf$6) refers to printf6.o(i._printf_core) for _printf_core
    printf6.o(i.__0sprintf$6) refers to printf6.o(i._sputc) for _sputc
    printf6.o(i.__0vfprintf$6) refers to printf6.o(i._printf_core) for _printf_core
    printf6.o(i.__0vfprintf$6) refers to fputc.o(i.fputc) for fputc
    printf6.o(i.__0vprintf$6) refers to printf6.o(i._printf_core) for _printf_core
    printf6.o(i.__0vprintf$6) refers to fputc.o(i.fputc) for fputc
    printf6.o(i.__0vprintf$6) refers to stdout.o(.data) for __stdout
    printf6.o(i.__0vsnprintf$6) refers to printf6.o(i._printf_core) for _printf_core
    printf6.o(i.__0vsnprintf$6) refers to printf6.o(i._snputc) for _snputc
    printf6.o(i.__0vsprintf$6) refers to printf6.o(i._printf_core) for _printf_core
    printf6.o(i.__0vsprintf$6) refers to printf6.o(i._sputc) for _sputc
    printf6.o(i._printf_core) refers to printf6.o(i._printf_pre_padding) for _printf_pre_padding
    printf6.o(i._printf_core) refers to uidiv.o(.text) for __aeabi_uidivmod
    printf6.o(i._printf_core) refers to printf6.o(i._printf_post_padding) for _printf_post_padding
    printf7.o(i.__0fprintf$7) refers to printf7.o(i._printf_core) for _printf_core
    printf7.o(i.__0fprintf$7) refers to fputc.o(i.fputc) for fputc
    printf7.o(i.__0printf$7) refers to printf7.o(i._printf_core) for _printf_core
    printf7.o(i.__0printf$7) refers to fputc.o(i.fputc) for fputc
    printf7.o(i.__0printf$7) refers to stdout.o(.data) for __stdout
    printf7.o(i.__0snprintf$7) refers to printf7.o(i._printf_core) for _printf_core
    printf7.o(i.__0snprintf$7) refers to printf7.o(i._snputc) for _snputc
    printf7.o(i.__0sprintf$7) refers to printf7.o(i._printf_core) for _printf_core
    printf7.o(i.__0sprintf$7) refers to printf7.o(i._sputc) for _sputc
    printf7.o(i.__0vfprintf$7) refers to printf7.o(i._printf_core) for _printf_core
    printf7.o(i.__0vfprintf$7) refers to fputc.o(i.fputc) for fputc
    printf7.o(i.__0vprintf$7) refers to printf7.o(i._printf_core) for _printf_core
    printf7.o(i.__0vprintf$7) refers to fputc.o(i.fputc) for fputc
    printf7.o(i.__0vprintf$7) refers to stdout.o(.data) for __stdout
    printf7.o(i.__0vsnprintf$7) refers to printf7.o(i._printf_core) for _printf_core
    printf7.o(i.__0vsnprintf$7) refers to printf7.o(i._snputc) for _snputc
    printf7.o(i.__0vsprintf$7) refers to printf7.o(i._printf_core) for _printf_core
    printf7.o(i.__0vsprintf$7) refers to printf7.o(i._sputc) for _sputc
    printf7.o(i._printf_core) refers to printf7.o(i._printf_pre_padding) for _printf_pre_padding
    printf7.o(i._printf_core) refers to uldiv.o(.text) for __aeabi_uldivmod
    printf7.o(i._printf_core) refers to printf7.o(i._printf_post_padding) for _printf_post_padding
    printf8.o(i.__0fprintf$8) refers to printf8.o(i._printf_core) for _printf_core
    printf8.o(i.__0fprintf$8) refers to fputc.o(i.fputc) for fputc
    printf8.o(i.__0printf$8) refers to printf8.o(i._printf_core) for _printf_core
    printf8.o(i.__0printf$8) refers to fputc.o(i.fputc) for fputc
    printf8.o(i.__0printf$8) refers to stdout.o(.data) for __stdout
    printf8.o(i.__0snprintf$8) refers to printf8.o(i._printf_core) for _printf_core
    printf8.o(i.__0snprintf$8) refers to printf8.o(i._snputc) for _snputc
    printf8.o(i.__0sprintf$8) refers to printf8.o(i._printf_core) for _printf_core
    printf8.o(i.__0sprintf$8) refers to printf8.o(i._sputc) for _sputc
    printf8.o(i.__0vfprintf$8) refers to printf8.o(i._printf_core) for _printf_core
    printf8.o(i.__0vfprintf$8) refers to fputc.o(i.fputc) for fputc
    printf8.o(i.__0vprintf$8) refers to printf8.o(i._printf_core) for _printf_core
    printf8.o(i.__0vprintf$8) refers to fputc.o(i.fputc) for fputc
    printf8.o(i.__0vprintf$8) refers to stdout.o(.data) for __stdout
    printf8.o(i.__0vsnprintf$8) refers to printf8.o(i._printf_core) for _printf_core
    printf8.o(i.__0vsnprintf$8) refers to printf8.o(i._snputc) for _snputc
    printf8.o(i.__0vsprintf$8) refers to printf8.o(i._printf_core) for _printf_core
    printf8.o(i.__0vsprintf$8) refers to printf8.o(i._sputc) for _sputc
    printf8.o(i._printf_core) refers to printf8.o(i._printf_pre_padding) for _printf_pre_padding
    printf8.o(i._printf_core) refers to uldiv.o(.text) for __aeabi_uldivmod
    printf8.o(i._printf_core) refers to printf8.o(i._printf_post_padding) for _printf_post_padding
    printfa.o(i.__0fprintf) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i.__0fprintf) refers to printfa.o(i._printf_core) for _printf_core
    printfa.o(i.__0fprintf) refers to fputc.o(i.fputc) for fputc
    printfa.o(i.__0printf) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i.__0printf) refers to printfa.o(i._printf_core) for _printf_core
    printfa.o(i.__0printf) refers to fputc.o(i.fputc) for fputc
    printfa.o(i.__0printf) refers to stdout.o(.data) for __stdout
    printfa.o(i.__0snprintf) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i.__0snprintf) refers to printfa.o(i._printf_core) for _printf_core
    printfa.o(i.__0snprintf) refers to printfa.o(i._snputc) for _snputc
    printfa.o(i.__0sprintf) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i.__0sprintf) refers to printfa.o(i._printf_core) for _printf_core
    printfa.o(i.__0sprintf) refers to printfa.o(i._sputc) for _sputc
    printfa.o(i.__0vfprintf) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i.__0vfprintf) refers to printfa.o(i._printf_core) for _printf_core
    printfa.o(i.__0vfprintf) refers to fputc.o(i.fputc) for fputc
    printfa.o(i.__0vprintf) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i.__0vprintf) refers to printfa.o(i._printf_core) for _printf_core
    printfa.o(i.__0vprintf) refers to fputc.o(i.fputc) for fputc
    printfa.o(i.__0vprintf) refers to stdout.o(.data) for __stdout
    printfa.o(i.__0vsnprintf) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i.__0vsnprintf) refers to printfa.o(i._printf_core) for _printf_core
    printfa.o(i.__0vsnprintf) refers to printfa.o(i._snputc) for _snputc
    printfa.o(i.__0vsprintf) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i.__0vsprintf) refers to printfa.o(i._printf_core) for _printf_core
    printfa.o(i.__0vsprintf) refers to printfa.o(i._sputc) for _sputc
    printfa.o(i._fp_digits) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i._fp_digits) refers to dmul.o(.text) for __aeabi_dmul
    printfa.o(i._fp_digits) refers to ddiv.o(.text) for __aeabi_ddiv
    printfa.o(i._fp_digits) refers to cdrcmple.o(.text) for __aeabi_cdrcmple
    printfa.o(i._fp_digits) refers to dadd.o(.text) for __aeabi_dadd
    printfa.o(i._fp_digits) refers to dfixul.o(.text) for __aeabi_d2ulz
    printfa.o(i._fp_digits) refers to uldiv.o(.text) for __aeabi_uldivmod
    printfa.o(i._printf_core) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i._printf_core) refers to printfa.o(i._printf_pre_padding) for _printf_pre_padding
    printfa.o(i._printf_core) refers to uldiv.o(.text) for __aeabi_uldivmod
    printfa.o(i._printf_core) refers to printfa.o(i._printf_post_padding) for _printf_post_padding
    printfa.o(i._printf_core) refers to printfa.o(i._fp_digits) for _fp_digits
    printfa.o(i._printf_core) refers to uidiv.o(.text) for __aeabi_uidivmod
    printfa.o(i._printf_post_padding) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i._printf_pre_padding) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i._snputc) refers (Special) to iusefp.o(.text) for __I$use$fp
    printfa.o(i._sputc) refers (Special) to iusefp.o(.text) for __I$use$fp
    dadd.o(.text) refers (Special) to iusefp.o(.text) for __I$use$fp
    dadd.o(.text) refers to llshl.o(.text) for __aeabi_llsl
    dadd.o(.text) refers to llsshr.o(.text) for __aeabi_lasr
    dadd.o(.text) refers to depilogue.o(.text) for _double_epilogue
    dmul.o(.text) refers (Special) to iusefp.o(.text) for __I$use$fp
    dmul.o(.text) refers to depilogue.o(.text) for _double_epilogue
    ddiv.o(.text) refers (Special) to iusefp.o(.text) for __I$use$fp
    ddiv.o(.text) refers to depilogue.o(.text) for _double_round
    dflti.o(.text) refers (Special) to iusefp.o(.text) for __I$use$fp
    dflti.o(.text) refers to depilogue.o(.text) for _double_epilogue
    dfltui.o(.text) refers (Special) to iusefp.o(.text) for __I$use$fp
    dfltui.o(.text) refers to depilogue.o(.text) for _double_epilogue
    dfixi.o(.text) refers (Special) to iusefp.o(.text) for __I$use$fp
    dfixi.o(.text) refers to llushr.o(.text) for __aeabi_llsr
    f2d.o(.text) refers (Special) to iusefp.o(.text) for __I$use$fp
    cdcmple.o(.text) refers (Special) to iusefp.o(.text) for __I$use$fp
    cdrcmple.o(.text) refers (Special) to iusefp.o(.text) for __I$use$fp
    d2f.o(.text) refers (Special) to iusefp.o(.text) for __I$use$fp
    d2f.o(.text) refers to fepilogue.o(.text) for _float_round
    entry2.o(.ARM.Collect$$$$00000001) refers to entry2.o(.ARM.Collect$$$$00002712) for __lit__00000000
    entry2.o(.ARM.Collect$$$$00002712) refers to startup_stm32f4xx.o(STACK) for __initial_sp
    entry2.o(__vectab_stack_and_reset_area) refers to startup_stm32f4xx.o(STACK) for __initial_sp
    entry2.o(__vectab_stack_and_reset_area) refers to entry.o(.ARM.Collect$$$$00000000) for __main
    entry5.o(.ARM.Collect$$$$00000004) refers to init.o(.text) for __scatterload
    entry9a.o(.ARM.Collect$$$$0000000B) refers to main.o(.text) for main
    entry9b.o(.ARM.Collect$$$$0000000C) refers to main.o(.text) for main
    fputc.o(i.fputc) refers (Special) to iusesemip.o(.text) for __I$use$semihosting$fputc
    fputc.o(i.fputc) refers (Special) to semi.o(.text) for __semihosting_library_function
    uldiv.o(.text) refers to llushr.o(.text) for __aeabi_llsr
    uldiv.o(.text) refers to llshl.o(.text) for __aeabi_llsl
    depilogue.o(.text) refers to llshl.o(.text) for __aeabi_llsl
    depilogue.o(.text) refers to llushr.o(.text) for __aeabi_llsr
    dfixul.o(.text) refers to llushr.o(.text) for __aeabi_llsr
    dfixul.o(.text) refers to llshl.o(.text) for __aeabi_llsl
    init.o(.text) refers to entry5.o(.ARM.Collect$$$$00000004) for __main_after_scatterload


==============================================================================

Removing Unused input sections from the image.

    Removing main.o(.rev16_text), (4 bytes).
    Removing main.o(.revsh_text), (4 bytes).
    Removing main.o(.constdata), (296 bytes).
    Removing stm32f4xx_it.o(.rev16_text), (4 bytes).
    Removing stm32f4xx_it.o(.revsh_text), (4 bytes).
    Removing led.o(.rev16_text), (4 bytes).
    Removing led.o(.revsh_text), (4 bytes).
    Removing delay.o(.rev16_text), (4 bytes).
    Removing delay.o(.revsh_text), (4 bytes).
    Removing ov7725.o(.rev16_text), (4 bytes).
    Removing ov7725.o(.revsh_text), (4 bytes).
    Removing sccb.o(.rev16_text), (4 bytes).
    Removing sccb.o(.revsh_text), (4 bytes).
    Removing image.o(.rev16_text), (4 bytes).
    Removing image.o(.revsh_text), (4 bytes).
    Removing image.o(.constdata), (296 bytes).
    Removing usart.o(.rev16_text), (4 bytes).
    Removing usart.o(.revsh_text), (4 bytes).
    Removing can1.o(.rev16_text), (4 bytes).
    Removing can1.o(.revsh_text), (4 bytes).
    Removing mydataprocess.o(.rev16_text), (4 bytes).
    Removing mydataprocess.o(.revsh_text), (4 bytes).
    Removing pid.o(.rev16_text), (4 bytes).
    Removing pid.o(.revsh_text), (4 bytes).
    Removing ili9320_api.o(.rev16_text), (4 bytes).
    Removing ili9320_api.o(.revsh_text), (4 bytes).
    Removing led_show.o(.rev16_text), (4 bytes).
    Removing led_show.o(.revsh_text), (4 bytes).
    Removing ili9325.o(.rev16_text), (4 bytes).
    Removing ili9325.o(.revsh_text), (4 bytes).
    Removing visual_scope.o(.rev16_text), (4 bytes).
    Removing visual_scope.o(.revsh_text), (4 bytes).
    Removing kalman.o(.rev16_text), (4 bytes).
    Removing kalman.o(.revsh_text), (4 bytes).
    Removing kalman.o(.text), (1102 bytes).
    Removing kalman.o(.bss), (116 bytes).
    Removing ps2.o(.rev16_text), (4 bytes).
    Removing ps2.o(.revsh_text), (4 bytes).
    Removing ps2.o(.text), (132 bytes).
    Removing misc.o(.rev16_text), (4 bytes).
    Removing misc.o(.revsh_text), (4 bytes).
    Removing stm32f4xx_exti.o(.rev16_text), (4 bytes).
    Removing stm32f4xx_exti.o(.revsh_text), (4 bytes).
    Removing stm32f4xx_exti.o(.text), (284 bytes).
    Removing stm32f4xx_gpio.o(.rev16_text), (4 bytes).
    Removing stm32f4xx_gpio.o(.revsh_text), (4 bytes).
    Removing stm32f4xx_rcc.o(.rev16_text), (4 bytes).
    Removing stm32f4xx_rcc.o(.revsh_text), (4 bytes).
    Removing stm32f4xx_tim.o(.rev16_text), (4 bytes).
    Removing stm32f4xx_tim.o(.revsh_text), (4 bytes).
    Removing stm32f4xx_tim.o(.text), (3234 bytes).
    Removing stm32f4xx_usart.o(.rev16_text), (4 bytes).
    Removing stm32f4xx_usart.o(.revsh_text), (4 bytes).
    Removing stm32f4xx_fsmc.o(.rev16_text), (4 bytes).
    Removing stm32f4xx_fsmc.o(.revsh_text), (4 bytes).
    Removing stm32f4xx_dma.o(.rev16_text), (4 bytes).
    Removing stm32f4xx_dma.o(.revsh_text), (4 bytes).
    Removing stm32f4xx_dcmi.o(.rev16_text), (4 bytes).
    Removing stm32f4xx_dcmi.o(.revsh_text), (4 bytes).
    Removing stm32f4xx_can.o(.rev16_text), (4 bytes).
    Removing stm32f4xx_can.o(.revsh_text), (4 bytes).
    Removing system_stm32f4xx.o(.rev16_text), (4 bytes).
    Removing system_stm32f4xx.o(.revsh_text), (4 bytes).
    Removing startup_stm32f4xx.o(HEAP), (512 bytes).
    Removing dfltui.o(.text), (26 bytes).

65 unused section(s) (total 6222 bytes) removed from the image.

==============================================================================

Image Symbol Table

    Local Symbols

    Symbol Name                              Value     Ov Type        Size  Object(Section)

    ../clib/../cmprslib/zerorunl2.c          0x00000000   Number         0  __dczerorl2.o ABSOLUTE
    ../clib/microlib/division.c              0x00000000   Number         0  uldiv.o ABSOLUTE
    ../clib/microlib/division.c              0x00000000   Number         0  uidiv.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry5.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry8a.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry7b.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry7a.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry2.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry9b.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry10a.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry11b.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry11a.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry8b.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry10b.o ABSOLUTE
    ../clib/microlib/init/entry.s            0x00000000   Number         0  entry9a.o ABSOLUTE
    ../clib/microlib/longlong.c              0x00000000   Number         0  llushr.o ABSOLUTE
    ../clib/microlib/longlong.c              0x00000000   Number         0  llshl.o ABSOLUTE
    ../clib/microlib/longlong.c              0x00000000   Number         0  llsshr.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printf1.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printfb.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printf4.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printf5.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printfa.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printf6.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printf0.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printf7.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printf3.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printf2.o ABSOLUTE
    ../clib/microlib/printf/printf.c         0x00000000   Number         0  printf8.o ABSOLUTE
    ../clib/microlib/printf/stubs.s          0x00000000   Number         0  stubs.o ABSOLUTE
    ../clib/microlib/stdio/fputc.c           0x00000000   Number         0  fputc.o ABSOLUTE
    ../clib/microlib/stdio/semi.s            0x00000000   Number         0  semi.o ABSOLUTE
    ../clib/microlib/stdio/streams.c         0x00000000   Number         0  stdout.o ABSOLUTE
    ../clib/microlib/string/memset.c         0x00000000   Number         0  memseta.o ABSOLUTE
    ../clib/microlib/stubs.s                 0x00000000   Number         0  iusesemip.o ABSOLUTE
    ../clib/microlib/stubs.s                 0x00000000   Number         0  iusefp.o ABSOLUTE
    ../fplib/microlib/d2f.c                  0x00000000   Number         0  d2f.o ABSOLUTE
    ../fplib/microlib/f2d.c                  0x00000000   Number         0  f2d.o ABSOLUTE
    ../fplib/microlib/fpadd.c                0x00000000   Number         0  dadd.o ABSOLUTE
    ../fplib/microlib/fpdiv.c                0x00000000   Number         0  ddiv.o ABSOLUTE
    ../fplib/microlib/fpepilogue.c           0x00000000   Number         0  fepilogue.o ABSOLUTE
    ../fplib/microlib/fpepilogue.c           0x00000000   Number         0  depilogue.o ABSOLUTE
    ../fplib/microlib/fpfix.c                0x00000000   Number         0  dfixi.o ABSOLUTE
    ../fplib/microlib/fpfix.c                0x00000000   Number         0  dfixul.o ABSOLUTE
    ../fplib/microlib/fpflt.c                0x00000000   Number         0  dflti.o ABSOLUTE
    ../fplib/microlib/fpflt.c                0x00000000   Number         0  dfltui.o ABSOLUTE
    ../fplib/microlib/fpmul.c                0x00000000   Number         0  dmul.o ABSOLUTE
    ../mathlib/fabs.c                        0x00000000   Number         0  fabs.o ABSOLUTE
    ..\Libraries\CMSIS\system_stm32f4xx.c    0x00000000   Number         0  system_stm32f4xx.o ABSOLUTE
    ..\Libraries\STM32F4xx_StdPeriph_Driver\src\misc.c 0x00000000   Number         0  misc.o ABSOLUTE
    ..\Libraries\STM32F4xx_StdPeriph_Driver\src\stm32f4xx_can.c 0x00000000   Number         0  stm32f4xx_can.o ABSOLUTE
    ..\Libraries\STM32F4xx_StdPeriph_Driver\src\stm32f4xx_exti.c 0x00000000   Number         0  stm32f4xx_exti.o ABSOLUTE
    ..\Libraries\STM32F4xx_StdPeriph_Driver\src\stm32f4xx_fsmc.c 0x00000000   Number         0  stm32f4xx_fsmc.o ABSOLUTE
    ..\Libraries\STM32F4xx_StdPeriph_Driver\src\stm32f4xx_gpio.c 0x00000000   Number         0  stm32f4xx_gpio.o ABSOLUTE
    ..\Libraries\STM32F4xx_StdPeriph_Driver\src\stm32f4xx_rcc.c 0x00000000   Number         0  stm32f4xx_rcc.o ABSOLUTE
    ..\Libraries\STM32F4xx_StdPeriph_Driver\src\stm32f4xx_tim.c 0x00000000   Number         0  stm32f4xx_tim.o ABSOLUTE
    ..\Libraries\STM32F4xx_StdPeriph_Driver\src\stm32f4xx_usart.c 0x00000000   Number         0  stm32f4xx_usart.o ABSOLUTE
    ..\Libraries\Startup\startup_stm32f4xx.s 0x00000000   Number         0  startup_stm32f4xx.o ABSOLUTE
    ..\User\src\Kalman.c                     0x00000000   Number         0  kalman.o ABSOLUTE
    ..\User\src\MyDataProcess.c              0x00000000   Number         0  mydataprocess.o ABSOLUTE
    ..\User\src\OV7725.c                     0x00000000   Number         0  ov7725.o ABSOLUTE
    ..\User\src\PS2.c                        0x00000000   Number         0  ps2.o ABSOLUTE
    ..\User\src\can1.c                       0x00000000   Number         0  can1.o ABSOLUTE
    ..\User\src\delay.c                      0x00000000   Number         0  delay.o ABSOLUTE
    ..\User\src\ili9320_api.c                0x00000000   Number         0  ili9320_api.o ABSOLUTE
    ..\User\src\ili9325.c                    0x00000000   Number         0  ili9325.o ABSOLUTE
    ..\User\src\led.c                        0x00000000   Number         0  led.o ABSOLUTE
    ..\User\src\led_show.c                   0x00000000   Number         0  led_show.o ABSOLUTE
    ..\User\src\main.c                       0x00000000   Number         0  main.o ABSOLUTE
    ..\User\src\pid.c                        0x00000000   Number         0  pid.o ABSOLUTE
    ..\User\src\queue.c                      0x00000000   Number         0  queue.o ABSOLUTE
    ..\User\src\sccb.c                       0x00000000   Number         0  sccb.o ABSOLUTE
    ..\User\src\stm32f4xx_dcmi.c             0x00000000   Number         0  stm32f4xx_dcmi.o ABSOLUTE
    ..\User\src\stm32f4xx_dma.c              0x00000000   Number         0  stm32f4xx_dma.o ABSOLUTE
    ..\User\src\stm32f4xx_it.c               0x00000000   Number         0  stm32f4xx_it.o ABSOLUTE
    ..\User\src\usart.c                      0x00000000   Number         0  usart.o ABSOLUTE
    ..\User\src\visual_scope.c               0x00000000   Number         0  visual_scope.o ABSOLUTE
    ..\\Libraries\\CMSIS\\system_stm32f4xx.c 0x00000000   Number         0  system_stm32f4xx.o ABSOLUTE
    ..\\Libraries\\STM32F4xx_StdPeriph_Driver\\src\\misc.c 0x00000000   Number         0  misc.o ABSOLUTE
    ..\\Libraries\\STM32F4xx_StdPeriph_Driver\\src\\stm32f4xx_can.c 0x00000000   Number         0  stm32f4xx_can.o ABSOLUTE
    ..\\Libraries\\STM32F4xx_StdPeriph_Driver\\src\\stm32f4xx_exti.c 0x00000000   Number         0  stm32f4xx_exti.o ABSOLUTE
    ..\\Libraries\\STM32F4xx_StdPeriph_Driver\\src\\stm32f4xx_fsmc.c 0x00000000   Number         0  stm32f4xx_fsmc.o ABSOLUTE
    ..\\Libraries\\STM32F4xx_StdPeriph_Driver\\src\\stm32f4xx_gpio.c 0x00000000   Number         0  stm32f4xx_gpio.o ABSOLUTE
    ..\\Libraries\\STM32F4xx_StdPeriph_Driver\\src\\stm32f4xx_rcc.c 0x00000000   Number         0  stm32f4xx_rcc.o ABSOLUTE
    ..\\Libraries\\STM32F4xx_StdPeriph_Driver\\src\\stm32f4xx_tim.c 0x00000000   Number         0  stm32f4xx_tim.o ABSOLUTE
    ..\\Libraries\\STM32F4xx_StdPeriph_Driver\\src\\stm32f4xx_usart.c 0x00000000   Number         0  stm32f4xx_usart.o ABSOLUTE
    ..\\User\\src\\Kalman.c                  0x00000000   Number         0  kalman.o ABSOLUTE
    ..\\User\\src\\MyDataProcess.c           0x00000000   Number         0  mydataprocess.o ABSOLUTE
    ..\\User\\src\\OV7725.c                  0x00000000   Number         0  ov7725.o ABSOLUTE
    ..\\User\\src\\PS2.c                     0x00000000   Number         0  ps2.o ABSOLUTE
    ..\\User\\src\\can1.c                    0x00000000   Number         0  can1.o ABSOLUTE
    ..\\User\\src\\delay.c                   0x00000000   Number         0  delay.o ABSOLUTE
    ..\\User\\src\\ili9320_api.c             0x00000000   Number         0  ili9320_api.o ABSOLUTE
    ..\\User\\src\\ili9325.c                 0x00000000   Number         0  ili9325.o ABSOLUTE
    ..\\User\\src\\led.c                     0x00000000   Number         0  led.o ABSOLUTE
    ..\\User\\src\\led_show.c                0x00000000   Number         0  led_show.o ABSOLUTE
    ..\\User\\src\\main.c                    0x00000000   Number         0  main.o ABSOLUTE
    ..\\User\\src\\pid.c                     0x00000000   Number         0  pid.o ABSOLUTE
    ..\\User\\src\\sccb.c                    0x00000000   Number         0  sccb.o ABSOLUTE
    ..\\User\\src\\stm32f4xx_dcmi.c          0x00000000   Number         0  stm32f4xx_dcmi.o ABSOLUTE
    ..\\User\\src\\stm32f4xx_dma.c           0x00000000   Number         0  stm32f4xx_dma.o ABSOLUTE
    ..\\User\\src\\stm32f4xx_it.c            0x00000000   Number         0  stm32f4xx_it.o ABSOLUTE
    ..\\User\\src\\usart.c                   0x00000000   Number         0  usart.o ABSOLUTE
    ..\\User\\src\\visual_scope.c            0x00000000   Number         0  visual_scope.o ABSOLUTE
    cdcmple.s                                0x00000000   Number         0  cdcmple.o ABSOLUTE
    cdrcmple.s                               0x00000000   Number         0  cdrcmple.o ABSOLUTE
    dc.s                                     0x00000000   Number         0  dc.o ABSOLUTE
    handlers.s                               0x00000000   Number         0  handlers.o ABSOLUTE
    image.c                                  0x00000000   Number         0  image.o ABSOLUTE
    image.c                                  0x00000000   Number         0  image.o ABSOLUTE
    init.s                                   0x00000000   Number         0  init.o ABSOLUTE
    RESET                                    0x08000000   Section      392  startup_stm32f4xx.o(RESET)
    .ARM.Collect$$$$00000000                 0x08000188   Section        0  entry.o(.ARM.Collect$$$$00000000)
    .ARM.Collect$$$$00000001                 0x08000188   Section        4  entry2.o(.ARM.Collect$$$$00000001)
    .ARM.Collect$$$$00000004                 0x0800018c   Section        4  entry5.o(.ARM.Collect$$$$00000004)
    .ARM.Collect$$$$00000008                 0x08000190   Section        0  entry7b.o(.ARM.Collect$$$$00000008)
    .ARM.Collect$$$$0000000A                 0x08000190   Section        0  entry8b.o(.ARM.Collect$$$$0000000A)
    .ARM.Collect$$$$0000000B                 0x08000190   Section        8  entry9a.o(.ARM.Collect$$$$0000000B)
    .ARM.Collect$$$$0000000D                 0x08000198   Section        0  entry10a.o(.ARM.Collect$$$$0000000D)
    .ARM.Collect$$$$0000000F                 0x08000198   Section        0  entry11a.o(.ARM.Collect$$$$0000000F)
    .ARM.Collect$$$$00002712                 0x08000198   Section        4  entry2.o(.ARM.Collect$$$$00002712)
    __lit__00000000                          0x08000198   Data           4  entry2.o(.ARM.Collect$$$$00002712)
    .text                                    0x0800019c   Section        0  main.o(.text)
    .text                                    0x08000920   Section        0  stm32f4xx_it.o(.text)
    .text                                    0x08000938   Section        0  led.o(.text)
    .text                                    0x080009e8   Section        0  delay.o(.text)
    .text                                    0x08000a20   Section        0  ov7725.o(.text)
    .text                                    0x08000db4   Section        0  sccb.o(.text)
    .text                                    0x080010e4   Section        0  image.o(.text)
    .text                                    0x08003b24   Section        0  usart.o(.text)
    .text                                    0x08004070   Section        0  can1.o(.text)
    .text                                    0x080042a0   Section        0  mydataprocess.o(.text)
    .text                                    0x080043c4   Section        0  pid.o(.text)
    .text                                    0x08004be4   Section        0  ili9320_api.o(.text)
    .text                                    0x0800504c   Section        0  led_show.o(.text)
    .text                                    0x080050e8   Section        0  ili9325.o(.text)
    .text                                    0x080061a0   Section        0  queue.o(.text)
    .text                                    0x08006234   Section        0  visual_scope.o(.text)
    CRC_CHECK                                0x08006235   Thumb Code    58  visual_scope.o(.text)
    .text                                    0x080062e4   Section        0  misc.o(.text)
    .text                                    0x080063c8   Section        0  stm32f4xx_gpio.o(.text)
    .text                                    0x08006624   Section        0  stm32f4xx_rcc.o(.text)
    .text                                    0x08006bac   Section        0  stm32f4xx_usart.o(.text)
    .text                                    0x08006fc8   Section        0  stm32f4xx_fsmc.o(.text)
    .text                                    0x080075e4   Section        0  stm32f4xx_dma.o(.text)
    .text                                    0x08007988   Section        0  stm32f4xx_dcmi.o(.text)
    .text                                    0x08007b14   Section        0  stm32f4xx_can.o(.text)
    CheckITStatus                            0x08008317   Thumb Code    16  stm32f4xx_can.o(.text)
    .text                                    0x08008500   Section        0  system_stm32f4xx.o(.text)
    SetSysClock                              0x08008501   Thumb Code   218  system_stm32f4xx.o(.text)
    .text                                    0x0800870c   Section       36  startup_stm32f4xx.o(.text)
    $v0                                      0x0800870c   Number         0  startup_stm32f4xx.o(.text)
    .text                                    0x08008730   Section        0  memseta.o(.text)
    .text                                    0x08008754   Section        0  dadd.o(.text)
    .text                                    0x080088a2   Section        0  dmul.o(.text)
    .text                                    0x08008986   Section        0  ddiv.o(.text)
    .text                                    0x08008a64   Section        0  dflti.o(.text)
    .text                                    0x08008a86   Section        0  dfixi.o(.text)
    .text                                    0x08008ac4   Section        0  f2d.o(.text)
    .text                                    0x08008aec   Section       40  cdcmple.o(.text)
    .text                                    0x08008b14   Section       40  cdrcmple.o(.text)
    .text                                    0x08008b3c   Section        0  d2f.o(.text)
    .text                                    0x08008b74   Section        0  uidiv.o(.text)
    .text                                    0x08008ba0   Section        0  uldiv.o(.text)
    .text                                    0x08008c02   Section        0  llshl.o(.text)
    .text                                    0x08008c20   Section        0  llushr.o(.text)
    .text                                    0x08008c40   Section        0  llsshr.o(.text)
    .text                                    0x08008c64   Section        0  fepilogue.o(.text)
    .text                                    0x08008c64   Section        0  iusefp.o(.text)
    .text                                    0x08008cd0   Section        0  depilogue.o(.text)
    .text                                    0x08008d8e   Section        0  dfixul.o(.text)
    .text                                    0x08008dc0   Section       36  init.o(.text)
    .text                                    0x08008de4   Section        0  __dczerorl2.o(.text)
    i.__0sprintf                             0x08008e40   Section        0  printfa.o(i.__0sprintf)
    i.__hardfp_fabs                          0x08008e68   Section        0  fabs.o(i.__hardfp_fabs)
    i.__scatterload_copy                     0x08008e7c   Section       14  handlers.o(i.__scatterload_copy)
    i.__scatterload_null                     0x08008e8a   Section        2  handlers.o(i.__scatterload_null)
    i.__scatterload_zeroinit                 0x08008e8c   Section       14  handlers.o(i.__scatterload_zeroinit)
    i._fp_digits                             0x08008e9c   Section        0  printfa.o(i._fp_digits)
    _fp_digits                               0x08008e9d   Thumb Code   326  printfa.o(i._fp_digits)
    i._printf_core                           0x08008ff8   Section        0  printfa.o(i._printf_core)
    _printf_core                             0x08008ff9   Thumb Code  1762  printfa.o(i._printf_core)
    i._printf_post_padding                   0x080096e8   Section        0  printfa.o(i._printf_post_padding)
    _printf_post_padding                     0x080096e9   Thumb Code    38  printfa.o(i._printf_post_padding)
    i._printf_pre_padding                    0x0800970e   Section        0  printfa.o(i._printf_pre_padding)
    _printf_pre_padding                      0x0800970f   Thumb Code    48  printfa.o(i._printf_pre_padding)
    i._sputc                                 0x0800973e   Section        0  printfa.o(i._sputc)
    _sputc                                   0x0800973f   Thumb Code    10  printfa.o(i._sputc)
    .constdata                               0x08009748   Section      296  ov7725.o(.constdata)
    OV7725RGB_reg                            0x08009748   Data         148  ov7725.o(.constdata)
    OV7725YUV_reg                            0x080097dc   Data         148  ov7725.o(.constdata)
    .constdata                               0x08009870   Section       12  led_show.o(.constdata)
    .constdata                               0x0800987c   Section     6096  ili9325.o(.constdata)
    .data                                    0x20000000   Section       55  main.o(.data)
    .data                                    0x20000038   Section        4  ov7725.o(.data)
    .data                                    0x20000040   Section      372  image.o(.data)
    .data                                    0x200001b4   Section       10  usart.o(.data)
    .data                                    0x200001c0   Section       36  can1.o(.data)
    .data                                    0x200001e4   Section      100  pid.o(.data)
    .data                                    0x20000248   Section        2  ili9325.o(.data)
    .data                                    0x2000024c   Section       17  ps2.o(.data)
    .data                                    0x2000025d   Section       16  stm32f4xx_rcc.o(.data)
    APBAHBPrescTable                         0x2000025d   Data          16  stm32f4xx_rcc.o(.data)
    .data                                    0x20000270   Section       20  system_stm32f4xx.o(.data)
    .bss                                     0x20000284   Section    128000  ov7725.o(.bss)
    .bss                                     0x2001f684   Section      496  image.o(.bss)
    .bss                                     0x2001f874   Section      296  usart.o(.bss)
    STACK                                    0x2001f9a0   Section     1024  startup_stm32f4xx.o(STACK)

    Global Symbols

    Symbol Name                              Value     Ov Type        Size  Object(Section)

    BuildAttributes$$THM_ISAv4$E$P$D$K$B$S$7EM$VFPi3$EXTD16$VFPS$VFMA$PE$A:L22UL41UL21$X:L11$S22US41US21$IEEE1$IW$USESV6$~STKCKD$USESV7$~SHL$OTIME$ROPI$IEEEJ$EBA8$MICROLIB$REQ8$PRES8$EABIv2 0x00000000   Number         0  anon$$obj.o ABSOLUTE
    __ARM_use_no_argv                        0x00000000   Number         0  main.o ABSOLUTE
    _printf_a                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_c                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_charcount                        0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_d                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_e                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_f                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_flags                            0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_fp_dec                           0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_fp_hex                           0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_g                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_i                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_int_dec                          0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_l                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_lc                               0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_ll                               0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_lld                              0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_lli                              0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_llo                              0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_llu                              0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_llx                              0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_longlong_dec                     0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_longlong_hex                     0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_longlong_oct                     0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_ls                               0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_mbtowc                           0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_n                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_o                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_p                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_percent                          0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_pre_padding                      0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_return_value                     0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_s                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_sizespec                         0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_str                              0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_truncate_signed                  0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_truncate_unsigned                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_u                                0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_wc                               0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_wctomb                           0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_widthprec                        0x00000000   Number         0  stubs.o ABSOLUTE
    _printf_x                                0x00000000   Number         0  stubs.o ABSOLUTE
    __cpp_initialize__aeabi_                  - Undefined Weak Reference
    __cxa_finalize                            - Undefined Weak Reference
    _clock_init                               - Undefined Weak Reference
    _microlib_exit                            - Undefined Weak Reference
    __Vectors_Size                           0x00000188   Number         0  startup_stm32f4xx.o ABSOLUTE
    __Vectors                                0x08000000   Data           4  startup_stm32f4xx.o(RESET)
    __Vectors_End                            0x08000188   Data           0  startup_stm32f4xx.o(RESET)
    __main                                   0x08000189   Thumb Code     0  entry.o(.ARM.Collect$$$$00000000)
    _main_stk                                0x08000189   Thumb Code     0  entry2.o(.ARM.Collect$$$$00000001)
    _main_scatterload                        0x0800018d   Thumb Code     0  entry5.o(.ARM.Collect$$$$00000004)
    __main_after_scatterload                 0x08000191   Thumb Code     0  entry5.o(.ARM.Collect$$$$00000004)
    _main_clock                              0x08000191   Thumb Code     0  entry7b.o(.ARM.Collect$$$$00000008)
    _main_cpp_init                           0x08000191   Thumb Code     0  entry8b.o(.ARM.Collect$$$$0000000A)
    _main_init                               0x08000191   Thumb Code     0  entry9a.o(.ARM.Collect$$$$0000000B)
    __rt_final_cpp                           0x08000199   Thumb Code     0  entry10a.o(.ARM.Collect$$$$0000000D)
    __rt_final_exit                          0x08000199   Thumb Code     0  entry11a.o(.ARM.Collect$$$$0000000F)
    main                                     0x0800019d   Thumb Code  1406  main.o(.text)
    DMA2_Stream1_IRQHandler                  0x0800071b   Thumb Code    46  main.o(.text)
    SysTick_Handler                          0x08000749   Thumb Code   334  main.o(.text)
    NMI_Handler                              0x08000921   Thumb Code     2  stm32f4xx_it.o(.text)
    HardFault_Handler                        0x08000923   Thumb Code     4  stm32f4xx_it.o(.text)
    MemManage_Handler                        0x08000927   Thumb Code     4  stm32f4xx_it.o(.text)
    BusFault_Handler                         0x0800092b   Thumb Code     4  stm32f4xx_it.o(.text)
    UsageFault_Handler                       0x0800092f   Thumb Code     4  stm32f4xx_it.o(.text)
    SVC_Handler                              0x08000933   Thumb Code     2  stm32f4xx_it.o(.text)
    DebugMon_Handler                         0x08000935   Thumb Code     2  stm32f4xx_it.o(.text)
    PendSV_Handler                           0x08000937   Thumb Code     2  stm32f4xx_it.o(.text)
    led_configuration                        0x08000939   Thumb Code   128  led.o(.text)
    Systic_Configuration                     0x080009b9   Thumb Code    32  led.o(.text)
    delay_ms                                 0x080009e9   Thumb Code    28  delay.o(.text)
    delay_us                                 0x08000a05   Thumb Code    26  delay.o(.text)
    OV_GPIO_Init                             0x08000a21   Thumb Code   322  ov7725.o(.text)
    OV_DCMI_Init                             0x08000b63   Thumb Code    54  ov7725.o(.text)
    OV_DCMI_DMA_Init                         0x08000b99   Thumb Code   128  ov7725.o(.text)
    OV_Window_Set                            0x08000c19   Thumb Code    94  ov7725.o(.text)
    OV_QVGAConfig                            0x08000c77   Thumb Code    46  ov7725.o(.text)
    OV_QVGAConfig2                           0x08000ca5   Thumb Code    40  ov7725.o(.text)
    OV_Start                                 0x08000ccd   Thumb Code    24  ov7725.o(.text)
    OV_Stop                                  0x08000ce5   Thumb Code    24  ov7725.o(.text)
    OV_Init                                  0x08000cfd   Thumb Code   104  ov7725.o(.text)
    OV_Init2                                 0x08000d65   Thumb Code    44  ov7725.o(.text)
    SCCB_GPIO_Config                         0x08000db5   Thumb Code    48  sccb.o(.text)
    I2C_delay                                0x08000de5   Thumb Code    14  sccb.o(.text)
    I2C_Stop                                 0x08000df3   Thumb Code    60  sccb.o(.text)
    I2C_Start                                0x08000e2f   Thumb Code    92  sccb.o(.text)
    I2C_Ack                                  0x08000e8b   Thumb Code    60  sccb.o(.text)
    I2C_NoAck                                0x08000ec7   Thumb Code    60  sccb.o(.text)
    I2C_WaitAck                              0x08000f03   Thumb Code    92  sccb.o(.text)
    I2C_SendByte                             0x08000f5f   Thumb Code    94  sccb.o(.text)
    I2C_ReadByte                             0x08000fbd   Thumb Code    88  sccb.o(.text)
    WR_SENSOR_Reg                            0x08001015   Thumb Code    86  sccb.o(.text)
    RD_SENSOR_Reg                            0x0800106b   Thumb Code   118  sccb.o(.text)
    Transfer2Gray                            0x080010e5   Thumb Code    84  image.o(.text)
    Transfer2Gray_UV                         0x08001139   Thumb Code    84  image.o(.text)
    image_threshold_sp                       0x0800118d   Thumb Code  1024  image.o(.text)
    image_threshold_hd                       0x0800158d   Thumb Code  1142  image.o(.text)
    image_threshold_xp                       0x08001a03   Thumb Code  1488  image.o(.text)
    midline_draw                             0x08001fd3   Thumb Code  1066  image.o(.text)
    midline_draw_hd                          0x080023fd   Thumb Code   976  image.o(.text)
    race_identity                            0x080027cd   Thumb Code   814  image.o(.text)
    Screen                                   0x08002afb   Thumb Code   378  image.o(.text)
    error_ca                                 0x08002c75   Thumb Code  3630  image.o(.text)
    max                                      0x08003aa3   Thumb Code    32  image.o(.text)
    restart_judge                            0x08003ac3   Thumb Code    80  image.o(.text)
    USART_GPIO_Config                        0x08003b25   Thumb Code   334  usart.o(.text)
    usart_txhander                           0x08003c73   Thumb Code    80  usart.o(.text)
    USART2_sendData                          0x08003cc3   Thumb Code    98  usart.o(.text)
    DMA1_Stream6_IRQHandler                  0x08003d25   Thumb Code    36  usart.o(.text)
    send_picture                             0x08003d49   Thumb Code    42  usart.o(.text)
    delay                                    0x08003d73   Thumb Code    28  usart.o(.text)
    USART2_IRQHandler                        0x08003d8f   Thumb Code   296  usart.o(.text)
    send_big_data                            0x08003eb7   Thumb Code   438  usart.o(.text)
    Can1_Configuration                       0x08004071   Thumb Code   238  can1.o(.text)
    SendPulse                                0x0800415f   Thumb Code    58  can1.o(.text)
    SendPulseBeep                            0x08004199   Thumb Code    48  can1.o(.text)
    SendHandKey_3                            0x080041c9   Thumb Code    54  can1.o(.text)
    SendElectromagnet                        0x080041ff   Thumb Code    44  can1.o(.text)
    CAN1_RX0_IRQHandler                      0x0800422b   Thumb Code    92  can1.o(.text)
    EncodeS32Data                            0x080042a1   Thumb Code    40  mydataprocess.o(.text)
    DecodeS32Data                            0x080042c9   Thumb Code    36  mydataprocess.o(.text)
    EncodeFloatData                          0x080042ed   Thumb Code    44  mydataprocess.o(.text)
    DecodeFloatData                          0x08004319   Thumb Code    40  mydataprocess.o(.text)
    EncodeS16Data                            0x08004341   Thumb Code    12  mydataprocess.o(.text)
    DecodeS16Data                            0x0800434d   Thumb Code    14  mydataprocess.o(.text)
    EncodeU16Data                            0x0800435b   Thumb Code    12  mydataprocess.o(.text)
    DecodeU16Data                            0x08004367   Thumb Code    12  mydataprocess.o(.text)
    EncodeU12Data                            0x08004373   Thumb Code    22  mydataprocess.o(.text)
    DecodeU12Data                            0x08004389   Thumb Code    16  mydataprocess.o(.text)
    EncodeU16to5Dec                          0x08004399   Thumb Code    42  mydataprocess.o(.text)
    CameraPid                                0x080043c5   Thumb Code  1974  pid.o(.text)
    GUI_Color565                             0x08004be5   Thumb Code    28  ili9320_api.o(.text)
    GUI_Text                                 0x08004c01   Thumb Code    56  ili9320_api.o(.text)
    GUI_Line                                 0x08004c39   Thumb Code   508  ili9320_api.o(.text)
    GUI_Circle                               0x08004e35   Thumb Code   372  ili9320_api.o(.text)
    GUI_Rectangle                            0x08004fa9   Thumb Code   122  ili9320_api.o(.text)
    GUI_Square                               0x08005023   Thumb Code    40  ili9320_api.o(.text)
    number_show                              0x0800504d   Thumb Code    50  led_show.o(.text)
    float_number_show                        0x0800507f   Thumb Code    88  led_show.o(.text)
    LCD_CtrlLinesConfig                      0x080050e9   Thumb Code   338  ili9325.o(.text)
    LCD_FSMCConfig                           0x0800523b   Thumb Code    88  ili9325.o(.text)
    LCD_X_Init                               0x08005293   Thumb Code    12  ili9325.o(.text)
    LCD_WriteReg                             0x0800529f   Thumb Code    10  ili9325.o(.text)
    LCD_ReadReg                              0x080052a9   Thumb Code    10  ili9325.o(.text)
    LCD_ReadSta                              0x080052b3   Thumb Code     6  ili9325.o(.text)
    LCD_WriteCommand                         0x080052b9   Thumb Code     6  ili9325.o(.text)
    LCD_WriteRAM_Prepare                     0x080052bf   Thumb Code     8  ili9325.o(.text)
    LCD_WriteRAM                             0x080052c7   Thumb Code     8  ili9325.o(.text)
    LCD_ReadRAM                              0x080052cf   Thumb Code    20  ili9325.o(.text)
    LCD_SetCursor                            0x080052e3   Thumb Code    40  ili9325.o(.text)
    Delay_nms                                0x0800530b   Thumb Code    24  ili9325.o(.text)
    ili9320_SetCursor                        0x08005323   Thumb Code    96  ili9325.o(.text)
    ili9320_SetWindows                       0x08005383   Thumb Code    52  ili9325.o(.text)
    ili9320_Clear                            0x080053b7   Thumb Code    38  ili9325.o(.text)
    ili9320_Delay                            0x080053dd   Thumb Code    10  ili9325.o(.text)
    ili9320_Initializtion                    0x080053e7   Thumb Code  3018  ili9325.o(.text)
    ili9320_BGR2RGB                          0x08005fb1   Thumb Code    26  ili9325.o(.text)
    ili9320_GetPoint                         0x08005fcb   Thumb Code    26  ili9325.o(.text)
    ili9320_SetPoint                         0x08005fe5   Thumb Code    42  ili9325.o(.text)
    ili9320_DrawPicture                      0x0800600f   Thumb Code   184  ili9325.o(.text)
    ili9320_PutChar                          0x080060c7   Thumb Code   182  ili9325.o(.text)
    ili9320_BackLight                        0x0800617d   Thumb Code    28  ili9325.o(.text)
    SetEmpty                                 0x080061a1   Thumb Code     8  queue.o(.text)
    EnQueue                                  0x080061a9   Thumb Code    52  queue.o(.text)
    DeQueue                                  0x080061dd   Thumb Code    42  queue.o(.text)
    GetQueueLength                           0x08006207   Thumb Code    46  queue.o(.text)
    VS4Channal_Send                          0x0800626f   Thumb Code   118  visual_scope.o(.text)
    NVIC_PriorityGroupConfig                 0x080062e5   Thumb Code    10  misc.o(.text)
    NVIC_Init                                0x080062ef   Thumb Code   108  misc.o(.text)
    NVIC_SetVectorTable                      0x0800635b   Thumb Code    14  misc.o(.text)
    NVIC_SystemLPConfig                      0x08006369   Thumb Code    34  misc.o(.text)
    SysTick_CLKSourceConfig                  0x0800638b   Thumb Code    40  misc.o(.text)
    GPIO_DeInit                              0x080063c9   Thumb Code   220  stm32f4xx_gpio.o(.text)
    GPIO_Init                                0x080064a5   Thumb Code   144  stm32f4xx_gpio.o(.text)
    GPIO_StructInit                          0x08006535   Thumb Code    18  stm32f4xx_gpio.o(.text)
    GPIO_PinLockConfig                       0x08006547   Thumb Code    34  stm32f4xx_gpio.o(.text)
    GPIO_ReadInputDataBit                    0x08006569   Thumb Code    18  stm32f4xx_gpio.o(.text)
    GPIO_ReadInputData                       0x0800657b   Thumb Code     8  stm32f4xx_gpio.o(.text)
    GPIO_ReadOutputDataBit                   0x08006583   Thumb Code    18  stm32f4xx_gpio.o(.text)
    GPIO_ReadOutputData                      0x08006595   Thumb Code     8  stm32f4xx_gpio.o(.text)
    GPIO_SetBits                             0x0800659d   Thumb Code     4  stm32f4xx_gpio.o(.text)
    GPIO_ResetBits                           0x080065a1   Thumb Code     4  stm32f4xx_gpio.o(.text)
    GPIO_WriteBit                            0x080065a5   Thumb Code    10  stm32f4xx_gpio.o(.text)
    GPIO_Write                               0x080065af   Thumb Code     4  stm32f4xx_gpio.o(.text)
    GPIO_ToggleBits                          0x080065b3   Thumb Code     8  stm32f4xx_gpio.o(.text)
    GPIO_PinAFConfig                         0x080065bb   Thumb Code    70  stm32f4xx_gpio.o(.text)
    RCC_DeInit                               0x08006625   Thumb Code    60  stm32f4xx_rcc.o(.text)
    RCC_HSEConfig                            0x08006661   Thumb Code    14  stm32f4xx_rcc.o(.text)
    RCC_GetFlagStatus                        0x0800666f   Thumb Code    60  stm32f4xx_rcc.o(.text)
    RCC_WaitForHSEStartUp                    0x080066ab   Thumb Code    56  stm32f4xx_rcc.o(.text)
    RCC_AdjustHSICalibrationValue            0x080066e3   Thumb Code    20  stm32f4xx_rcc.o(.text)
    RCC_HSICmd                               0x080066f7   Thumb Code     6  stm32f4xx_rcc.o(.text)
    RCC_LSEConfig                            0x080066fd   Thumb Code    46  stm32f4xx_rcc.o(.text)
    RCC_LSICmd                               0x0800672b   Thumb Code     6  stm32f4xx_rcc.o(.text)
    RCC_PLLConfig                            0x08006731   Thumb Code    32  stm32f4xx_rcc.o(.text)
    RCC_PLLCmd                               0x08006751   Thumb Code     6  stm32f4xx_rcc.o(.text)
    RCC_PLLI2SConfig                         0x08006757   Thumb Code    14  stm32f4xx_rcc.o(.text)
    RCC_PLLI2SCmd                            0x08006765   Thumb Code     6  stm32f4xx_rcc.o(.text)
    RCC_ClockSecuritySystemCmd               0x0800676b   Thumb Code     6  stm32f4xx_rcc.o(.text)
    RCC_MCO1Config                           0x08006771   Thumb Code    28  stm32f4xx_rcc.o(.text)
    RCC_MCO2Config                           0x0800678d   Thumb Code    28  stm32f4xx_rcc.o(.text)
    RCC_SYSCLKConfig                         0x080067a9   Thumb Code    20  stm32f4xx_rcc.o(.text)
    RCC_GetSYSCLKSource                      0x080067bd   Thumb Code    12  stm32f4xx_rcc.o(.text)
    RCC_HCLKConfig                           0x080067c9   Thumb Code    20  stm32f4xx_rcc.o(.text)
    RCC_PCLK1Config                          0x080067dd   Thumb Code    20  stm32f4xx_rcc.o(.text)
    RCC_PCLK2Config                          0x080067f1   Thumb Code    22  stm32f4xx_rcc.o(.text)
    RCC_GetClocksFreq                        0x08006807   Thumb Code   222  stm32f4xx_rcc.o(.text)
    RCC_RTCCLKConfig                         0x080068e5   Thumb Code    54  stm32f4xx_rcc.o(.text)
    RCC_RTCCLKCmd                            0x0800691b   Thumb Code     8  stm32f4xx_rcc.o(.text)
    RCC_BackupResetCmd                       0x08006923   Thumb Code     8  stm32f4xx_rcc.o(.text)
    RCC_I2SCLKConfig                         0x0800692b   Thumb Code     6  stm32f4xx_rcc.o(.text)
    RCC_AHB1PeriphClockCmd                   0x08006931   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_AHB2PeriphClockCmd                   0x08006953   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_AHB3PeriphClockCmd                   0x08006975   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_APB1PeriphClockCmd                   0x08006997   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_APB2PeriphClockCmd                   0x080069b9   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_AHB1PeriphResetCmd                   0x080069db   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_AHB2PeriphResetCmd                   0x080069fd   Thumb Code    72  stm32f4xx_rcc.o(.text)
    RCC_AHB3PeriphResetCmd                   0x08006a45   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_APB1PeriphResetCmd                   0x08006a67   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_APB2PeriphResetCmd                   0x08006a89   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_AHB1PeriphClockLPModeCmd             0x08006aab   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_AHB2PeriphClockLPModeCmd             0x08006acd   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_AHB3PeriphClockLPModeCmd             0x08006aef   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_APB1PeriphClockLPModeCmd             0x08006b11   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_APB2PeriphClockLPModeCmd             0x08006b33   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_ITConfig                             0x08006b55   Thumb Code    34  stm32f4xx_rcc.o(.text)
    RCC_ClearFlag                            0x08006b77   Thumb Code    18  stm32f4xx_rcc.o(.text)
    RCC_GetITStatus                          0x08006b89   Thumb Code    22  stm32f4xx_rcc.o(.text)
    RCC_ClearITPendingBit                    0x08006b9f   Thumb Code     8  stm32f4xx_rcc.o(.text)
    USART_DeInit                             0x08006bad   Thumb Code   156  stm32f4xx_usart.o(.text)
    USART_Init                               0x08006c49   Thumb Code   204  stm32f4xx_usart.o(.text)
    USART_StructInit                         0x08006d15   Thumb Code    24  stm32f4xx_usart.o(.text)
    USART_ClockInit                          0x08006d2d   Thumb Code    32  stm32f4xx_usart.o(.text)
    USART_ClockStructInit                    0x08006d4d   Thumb Code    12  stm32f4xx_usart.o(.text)
    USART_Cmd                                0x08006d59   Thumb Code    24  stm32f4xx_usart.o(.text)
    USART_SetPrescaler                       0x08006d71   Thumb Code    16  stm32f4xx_usart.o(.text)
    USART_OverSampling8Cmd                   0x08006d81   Thumb Code    22  stm32f4xx_usart.o(.text)
    USART_OneBitMethodCmd                    0x08006d97   Thumb Code    24  stm32f4xx_usart.o(.text)
    USART_SendData                           0x08006daf   Thumb Code     8  stm32f4xx_usart.o(.text)
    USART_ReceiveData                        0x08006db7   Thumb Code    10  stm32f4xx_usart.o(.text)
    USART_SetAddress                         0x08006dc1   Thumb Code    18  stm32f4xx_usart.o(.text)
    USART_ReceiverWakeUpCmd                  0x08006dd3   Thumb Code    24  stm32f4xx_usart.o(.text)
    USART_WakeUpConfig                       0x08006deb   Thumb Code    18  stm32f4xx_usart.o(.text)
    USART_LINBreakDetectLengthConfig         0x08006dfd   Thumb Code    18  stm32f4xx_usart.o(.text)
    USART_LINCmd                             0x08006e0f   Thumb Code    24  stm32f4xx_usart.o(.text)
    USART_SendBreak                          0x08006e27   Thumb Code    10  stm32f4xx_usart.o(.text)
    USART_HalfDuplexCmd                      0x08006e31   Thumb Code    24  stm32f4xx_usart.o(.text)
    USART_SetGuardTime                       0x08006e49   Thumb Code    16  stm32f4xx_usart.o(.text)
    USART_SmartCardCmd                       0x08006e59   Thumb Code    24  stm32f4xx_usart.o(.text)
    USART_SmartCardNACKCmd                   0x08006e71   Thumb Code    24  stm32f4xx_usart.o(.text)
    USART_IrDAConfig                         0x08006e89   Thumb Code    18  stm32f4xx_usart.o(.text)
    USART_IrDACmd                            0x08006e9b   Thumb Code    24  stm32f4xx_usart.o(.text)
    USART_DMACmd                             0x08006eb3   Thumb Code    18  stm32f4xx_usart.o(.text)
    USART_ITConfig                           0x08006ec5   Thumb Code    74  stm32f4xx_usart.o(.text)
    USART_GetFlagStatus                      0x08006f0f   Thumb Code    26  stm32f4xx_usart.o(.text)
    USART_ClearFlag                          0x08006f29   Thumb Code    18  stm32f4xx_usart.o(.text)
    USART_GetITStatus                        0x08006f3b   Thumb Code   110  stm32f4xx_usart.o(.text)
    USART_ClearITPendingBit                  0x08006fa9   Thumb Code    30  stm32f4xx_usart.o(.text)
    FSMC_NORSRAMDeInit                       0x08006fc9   Thumb Code    56  stm32f4xx_fsmc.o(.text)
    FSMC_NORSRAMInit                         0x08007001   Thumb Code   224  stm32f4xx_fsmc.o(.text)
    FSMC_NORSRAMStructInit                   0x080070e1   Thumb Code   114  stm32f4xx_fsmc.o(.text)
    FSMC_NORSRAMCmd                          0x08007153   Thumb Code    46  stm32f4xx_fsmc.o(.text)
    FSMC_NANDDeInit                          0x08007181   Thumb Code    62  stm32f4xx_fsmc.o(.text)
    FSMC_NANDInit                            0x080071bf   Thumb Code   130  stm32f4xx_fsmc.o(.text)
    FSMC_NANDStructInit                      0x08007241   Thumb Code    54  stm32f4xx_fsmc.o(.text)
    FSMC_NANDCmd                             0x08007277   Thumb Code    86  stm32f4xx_fsmc.o(.text)
    FSMC_NANDECCCmd                          0x080072cd   Thumb Code    86  stm32f4xx_fsmc.o(.text)
    FSMC_GetECC                              0x08007323   Thumb Code    22  stm32f4xx_fsmc.o(.text)
    FSMC_PCCARDDeInit                        0x08007339   Thumb Code    40  stm32f4xx_fsmc.o(.text)
    FSMC_PCCARDInit                          0x08007361   Thumb Code   124  stm32f4xx_fsmc.o(.text)
    FSMC_PCCARDStructInit                    0x080073dd   Thumb Code    60  stm32f4xx_fsmc.o(.text)
    FSMC_PCCARDCmd                           0x08007419   Thumb Code    40  stm32f4xx_fsmc.o(.text)
    FSMC_ITConfig                            0x08007441   Thumb Code   128  stm32f4xx_fsmc.o(.text)
    FSMC_GetFlagStatus                       0x080074c1   Thumb Code    48  stm32f4xx_fsmc.o(.text)
    FSMC_ClearFlag                           0x080074f1   Thumb Code    62  stm32f4xx_fsmc.o(.text)
    FSMC_GetITStatus                         0x0800752f   Thumb Code   110  stm32f4xx_fsmc.o(.text)
    FSMC_ClearITPendingBit                   0x0800759d   Thumb Code    64  stm32f4xx_fsmc.o(.text)
    DMA_DeInit                               0x080075e5   Thumb Code   324  stm32f4xx_dma.o(.text)
    DMA_Init                                 0x08007729   Thumb Code    82  stm32f4xx_dma.o(.text)
    DMA_StructInit                           0x0800777b   Thumb Code    34  stm32f4xx_dma.o(.text)
    DMA_Cmd                                  0x0800779d   Thumb Code    22  stm32f4xx_dma.o(.text)
    DMA_PeriphIncOffsetSizeConfig            0x080077b3   Thumb Code    22  stm32f4xx_dma.o(.text)
    DMA_FlowControllerConfig                 0x080077c9   Thumb Code    22  stm32f4xx_dma.o(.text)
    DMA_SetCurrDataCounter                   0x080077df   Thumb Code     4  stm32f4xx_dma.o(.text)
    DMA_GetCurrDataCounter                   0x080077e3   Thumb Code     8  stm32f4xx_dma.o(.text)
    DMA_DoubleBufferModeConfig               0x080077eb   Thumb Code    24  stm32f4xx_dma.o(.text)
    DMA_DoubleBufferModeCmd                  0x08007803   Thumb Code    22  stm32f4xx_dma.o(.text)
    DMA_MemoryTargetConfig                   0x08007819   Thumb Code    10  stm32f4xx_dma.o(.text)
    DMA_GetCurrentMemoryTarget               0x08007823   Thumb Code    20  stm32f4xx_dma.o(.text)
    DMA_GetCmdStatus                         0x08007837   Thumb Code    20  stm32f4xx_dma.o(.text)
    DMA_GetFIFOStatus                        0x0800784b   Thumb Code    12  stm32f4xx_dma.o(.text)
    DMA_GetFlagStatus                        0x08007857   Thumb Code    54  stm32f4xx_dma.o(.text)
    DMA_ClearFlag                            0x0800788d   Thumb Code    40  stm32f4xx_dma.o(.text)
    DMA_ITConfig                             0x080078b5   Thumb Code    58  stm32f4xx_dma.o(.text)
    DMA_GetITStatus                          0x080078ef   Thumb Code    82  stm32f4xx_dma.o(.text)
    DMA_ClearITPendingBit                    0x08007941   Thumb Code    40  stm32f4xx_dma.o(.text)
    DCMI_DeInit                              0x08007989   Thumb Code    24  stm32f4xx_dcmi.o(.text)
    DCMI_Init                                0x080079a1   Thumb Code    60  stm32f4xx_dcmi.o(.text)
    DCMI_StructInit                          0x080079dd   Thumb Code    18  stm32f4xx_dcmi.o(.text)
    DCMI_CROPConfig                          0x080079ef   Thumb Code    26  stm32f4xx_dcmi.o(.text)
    DCMI_CROPCmd                             0x08007a09   Thumb Code    30  stm32f4xx_dcmi.o(.text)
    DCMI_SetEmbeddedSynchroCodes             0x08007a27   Thumb Code    26  stm32f4xx_dcmi.o(.text)
    DCMI_JPEGCmd                             0x08007a41   Thumb Code    30  stm32f4xx_dcmi.o(.text)
    DCMI_Cmd                                 0x08007a5f   Thumb Code    30  stm32f4xx_dcmi.o(.text)
    DCMI_CaptureCmd                          0x08007a7d   Thumb Code    30  stm32f4xx_dcmi.o(.text)
    DCMI_ReadData                            0x08007a9b   Thumb Code     6  stm32f4xx_dcmi.o(.text)
    DCMI_ITConfig                            0x08007aa1   Thumb Code    30  stm32f4xx_dcmi.o(.text)
    DCMI_GetFlagStatus                       0x08007abf   Thumb Code    44  stm32f4xx_dcmi.o(.text)
    DCMI_ClearFlag                           0x08007aeb   Thumb Code     6  stm32f4xx_dcmi.o(.text)
    DCMI_GetITStatus                         0x08007af1   Thumb Code    24  stm32f4xx_dcmi.o(.text)
    DCMI_ClearITPendingBit                   0x08007b09   Thumb Code     6  stm32f4xx_dcmi.o(.text)
    CAN_DeInit                               0x08007b15   Thumb Code    50  stm32f4xx_can.o(.text)
    CAN_Init                                 0x08007b47   Thumb Code   276  stm32f4xx_can.o(.text)
    CAN_FilterInit                           0x08007c5b   Thumb Code   258  stm32f4xx_can.o(.text)
    CAN_StructInit                           0x08007d5d   Thumb Code    32  stm32f4xx_can.o(.text)
    CAN_SlaveStartBank                       0x08007d7d   Thumb Code    48  stm32f4xx_can.o(.text)
    CAN_DBGFreeze                            0x08007dad   Thumb Code    22  stm32f4xx_can.o(.text)
    CAN_TTComModeCmd                         0x08007dc3   Thumb Code   118  stm32f4xx_can.o(.text)
    CAN_Transmit                             0x08007e39   Thumb Code   304  stm32f4xx_can.o(.text)
    CAN_TransmitStatus                       0x08007f69   Thumb Code   138  stm32f4xx_can.o(.text)
    CAN_CancelTransmit                       0x08007ff3   Thumb Code    48  stm32f4xx_can.o(.text)
    CAN_Receive                              0x08008023   Thumb Code   240  stm32f4xx_can.o(.text)
    CAN_FIFORelease                          0x08008113   Thumb Code    22  stm32f4xx_can.o(.text)
    CAN_MessagePending                       0x08008129   Thumb Code    30  stm32f4xx_can.o(.text)
    CAN_OperatingModeRequest                 0x08008147   Thumb Code   162  stm32f4xx_can.o(.text)
    CAN_Sleep                                0x080081e9   Thumb Code    30  stm32f4xx_can.o(.text)
    CAN_WakeUp                               0x08008207   Thumb Code    48  stm32f4xx_can.o(.text)
    CAN_GetLastErrorCode                     0x08008237   Thumb Code    12  stm32f4xx_can.o(.text)
    CAN_GetReceiveErrorCounter               0x08008243   Thumb Code    10  stm32f4xx_can.o(.text)
    CAN_GetLSBTransmitErrorCounter           0x0800824d   Thumb Code    12  stm32f4xx_can.o(.text)
    CAN_ITConfig                             0x08008259   Thumb Code    18  stm32f4xx_can.o(.text)
    CAN_GetFlagStatus                        0x0800826b   Thumb Code   120  stm32f4xx_can.o(.text)
    CAN_ClearFlag                            0x080082e3   Thumb Code    52  stm32f4xx_can.o(.text)
    CAN_GetITStatus                          0x08008327   Thumb Code   308  stm32f4xx_can.o(.text)
    CAN_ClearITPendingBit                    0x0800845b   Thumb Code   162  stm32f4xx_can.o(.text)
    SystemInit                               0x080085db   Thumb Code    88  system_stm32f4xx.o(.text)
    SystemCoreClockUpdate                    0x08008633   Thumb Code   174  system_stm32f4xx.o(.text)
    Reset_Handler                            0x0800870d   Thumb Code     8  startup_stm32f4xx.o(.text)
    ADC_IRQHandler                           0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    CAN1_RX1_IRQHandler                      0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    CAN1_SCE_IRQHandler                      0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    CAN1_TX_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    CAN2_RX0_IRQHandler                      0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    CAN2_RX1_IRQHandler                      0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    CAN2_SCE_IRQHandler                      0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    CAN2_TX_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    CRYP_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DCMI_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA1_Stream0_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA1_Stream1_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA1_Stream2_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA1_Stream3_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA1_Stream4_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA1_Stream5_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA1_Stream7_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA2_Stream0_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA2_Stream2_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA2_Stream3_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA2_Stream4_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA2_Stream5_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA2_Stream6_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    DMA2_Stream7_IRQHandler                  0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    ETH_IRQHandler                           0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    ETH_WKUP_IRQHandler                      0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    EXTI0_IRQHandler                         0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    EXTI15_10_IRQHandler                     0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    EXTI1_IRQHandler                         0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    EXTI2_IRQHandler                         0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    EXTI3_IRQHandler                         0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    EXTI4_IRQHandler                         0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    EXTI9_5_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    FLASH_IRQHandler                         0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    FPU_IRQHandler                           0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    FSMC_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    HASH_RNG_IRQHandler                      0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    I2C1_ER_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    I2C1_EV_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    I2C2_ER_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    I2C2_EV_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    I2C3_ER_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    I2C3_EV_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    OTG_FS_IRQHandler                        0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    OTG_FS_WKUP_IRQHandler                   0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    OTG_HS_EP1_IN_IRQHandler                 0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    OTG_HS_EP1_OUT_IRQHandler                0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    OTG_HS_IRQHandler                        0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    OTG_HS_WKUP_IRQHandler                   0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    PVD_IRQHandler                           0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    RCC_IRQHandler                           0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    RTC_Alarm_IRQHandler                     0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    RTC_WKUP_IRQHandler                      0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    SDIO_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    SPI1_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    SPI2_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    SPI3_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TAMP_STAMP_IRQHandler                    0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM1_BRK_TIM9_IRQHandler                 0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM1_CC_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM1_TRG_COM_TIM11_IRQHandler            0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM1_UP_TIM10_IRQHandler                 0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM2_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM3_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM4_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM5_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM6_DAC_IRQHandler                      0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM7_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM8_BRK_TIM12_IRQHandler                0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM8_CC_IRQHandler                       0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM8_TRG_COM_TIM14_IRQHandler            0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    TIM8_UP_TIM13_IRQHandler                 0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    UART4_IRQHandler                         0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    UART5_IRQHandler                         0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    USART1_IRQHandler                        0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    USART3_IRQHandler                        0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    USART6_IRQHandler                        0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    WWDG_IRQHandler                          0x08008727   Thumb Code     0  startup_stm32f4xx.o(.text)
    __aeabi_memset                           0x08008731   Thumb Code    14  memseta.o(.text)
    __aeabi_memset4                          0x08008731   Thumb Code     0  memseta.o(.text)
    __aeabi_memset8                          0x08008731   Thumb Code     0  memseta.o(.text)
    __aeabi_memclr                           0x0800873f   Thumb Code     4  memseta.o(.text)
    __aeabi_memclr4                          0x0800873f   Thumb Code     0  memseta.o(.text)
    __aeabi_memclr8                          0x0800873f   Thumb Code     0  memseta.o(.text)
    _memset$wrapper                          0x08008743   Thumb Code    18  memseta.o(.text)
    __aeabi_dadd                             0x08008755   Thumb Code   322  dadd.o(.text)
    __aeabi_dsub                             0x08008897   Thumb Code     6  dadd.o(.text)
    __aeabi_drsub                            0x0800889d   Thumb Code     6  dadd.o(.text)
    __aeabi_dmul                             0x080088a3   Thumb Code   228  dmul.o(.text)
    __aeabi_ddiv                             0x08008987   Thumb Code   222  ddiv.o(.text)
    __aeabi_i2d                              0x08008a65   Thumb Code    34  dflti.o(.text)
    __aeabi_d2iz                             0x08008a87   Thumb Code    62  dfixi.o(.text)
    __aeabi_f2d                              0x08008ac5   Thumb Code    38  f2d.o(.text)
    __aeabi_cdcmpeq                          0x08008aed   Thumb Code     0  cdcmple.o(.text)
    __aeabi_cdcmple                          0x08008aed   Thumb Code    38  cdcmple.o(.text)
    __aeabi_cdrcmple                         0x08008b15   Thumb Code    38  cdrcmple.o(.text)
    __aeabi_d2f                              0x08008b3d   Thumb Code    56  d2f.o(.text)
    __aeabi_uidiv                            0x08008b75   Thumb Code     0  uidiv.o(.text)
    __aeabi_uidivmod                         0x08008b75   Thumb Code    44  uidiv.o(.text)
    __aeabi_uldivmod                         0x08008ba1   Thumb Code    98  uldiv.o(.text)
    __aeabi_llsl                             0x08008c03   Thumb Code    30  llshl.o(.text)
    _ll_shift_l                              0x08008c03   Thumb Code     0  llshl.o(.text)
    __aeabi_llsr                             0x08008c21   Thumb Code    32  llushr.o(.text)
    _ll_ushift_r                             0x08008c21   Thumb Code     0  llushr.o(.text)
    __aeabi_lasr                             0x08008c41   Thumb Code    36  llsshr.o(.text)
    _ll_sshift_r                             0x08008c41   Thumb Code     0  llsshr.o(.text)
    __I$use$fp                               0x08008c65   Thumb Code     0  iusefp.o(.text)
    _float_round                             0x08008c65   Thumb Code    18  fepilogue.o(.text)
    _float_epilogue                          0x08008c77   Thumb Code    90  fepilogue.o(.text)
    _double_round                            0x08008cd1   Thumb Code    26  depilogue.o(.text)
    _double_epilogue                         0x08008ceb   Thumb Code   164  depilogue.o(.text)
    __aeabi_d2ulz                            0x08008d8f   Thumb Code    48  dfixul.o(.text)
    __scatterload                            0x08008dc1   Thumb Code    28  init.o(.text)
    __scatterload_rt2                        0x08008dc1   Thumb Code     0  init.o(.text)
    __decompress                             0x08008de5   Thumb Code     0  __dczerorl2.o(.text)
    __decompress1                            0x08008de5   Thumb Code    92  __dczerorl2.o(.text)
    __0sprintf                               0x08008e41   Thumb Code    34  printfa.o(i.__0sprintf)
    __1sprintf                               0x08008e41   Thumb Code     0  printfa.o(i.__0sprintf)
    __2sprintf                               0x08008e41   Thumb Code     0  printfa.o(i.__0sprintf)
    __c89sprintf                             0x08008e41   Thumb Code     0  printfa.o(i.__0sprintf)
    sprintf                                  0x08008e41   Thumb Code     0  printfa.o(i.__0sprintf)
    __hardfp_fabs                            0x08008e69   Thumb Code    20  fabs.o(i.__hardfp_fabs)
    __scatterload_copy                       0x08008e7d   Thumb Code    14  handlers.o(i.__scatterload_copy)
    __scatterload_null                       0x08008e8b   Thumb Code     2  handlers.o(i.__scatterload_null)
    __scatterload_zeroinit                   0x08008e8d   Thumb Code    14  handlers.o(i.__scatterload_zeroinit)
    ascii_8x16                               0x0800987c   Data        1536  ili9325.o(.constdata)
    ASCII_Table_16x24                        0x08009e7c   Data        4560  ili9325.o(.constdata)
    Region$$Table$$Base                      0x0800b04c   Number         0  anon$$obj.o(Region$$Table)
    Region$$Table$$Limit                     0x0800b06c   Number         0  anon$$obj.o(Region$$Table)
    UpdataTFT_flag                           0x20000000   Data           1  main.o(.data)
    SpeedLast                                0x20000002   Data           6  main.o(.data)
    data1                                    0x20000008   Data           2  main.o(.data)
    data2                                    0x2000000a   Data           2  main.o(.data)
    data3                                    0x2000000c   Data           2  main.o(.data)
    data4                                    0x2000000e   Data           2  main.o(.data)
    i                                        0x20000010   Data           4  main.o(.data)
    j                                        0x20000014   Data           4  main.o(.data)
    message                                  0x20000018   Data           4  main.o(.data)
    count                                    0x2000001c   Data           4  main.o(.data)
    send_flag                                0x20000020   Data           4  main.o(.data)
    HuorDistanceLast                         0x20000024   Data           2  main.o(.data)
    huor2                                    0x20000028   Data           4  main.o(.data)
    beep_starttime                           0x2000002c   Data           4  main.o(.data)
    beep_startcount                          0x20000030   Data           4  main.o(.data)
    button1                                  0x20000034   Data           1  main.o(.data)
    button2                                  0x20000035   Data           1  main.o(.data)
    button3                                  0x20000036   Data           1  main.o(.data)
    Gray_Image_Buffer                        0x20000038   Data           4  ov7725.o(.data)
    number                                   0x20000040   Data           4  image.o(.data)
    left_angle_flag                          0x20000044   Data           4  image.o(.data)
    right_angle_flag                         0x20000048   Data           4  image.o(.data)
    rr                                       0x2000004c   Data           4  image.o(.data)
    whitelost_left                           0x20000050   Data           4  image.o(.data)
    edge_row0                                0x20000054   Data           4  image.o(.data)
    center_row                               0x20000058   Data           4  image.o(.data)
    start_row_hd                             0x2000005c   Data           4  image.o(.data)
    stop_row_hd                              0x20000060   Data           4  image.o(.data)
    eff_row                                  0x20000064   Data           4  image.o(.data)
    white_count                              0x20000068   Data           4  image.o(.data)
    nu                                       0x2000006c   Data           4  image.o(.data)
    control_line                             0x20000070   Data           4  image.o(.data)
    pixel_value                              0x20000074   Data           4  image.o(.data)
    sp_flag                                  0x20000078   Data           4  image.o(.data)
    hd_flag                                  0x2000007c   Data           4  image.o(.data)
    xp_flag                                  0x20000080   Data           4  image.o(.data)
    zj_start                                 0x20000084   Data           4  image.o(.data)
    img_stop_flag                            0x20000088   Data           4  image.o(.data)
    img_cross_flag                           0x2000008c   Data           4  image.o(.data)
    hand_restart                             0x20000090   Data           4  image.o(.data)
    hd_stage_flag                            0x20000094   Data           4  image.o(.data)
    Detect                                   0x20000098   Data           4  image.o(.data)
    stop_time                                0x2000009c   Data           4  image.o(.data)
    sum_left                                 0x200000a0   Data           4  image.o(.data)
    sum_right                                0x200000a4   Data           4  image.o(.data)
    standard_row                             0x200000a8   Data           4  image.o(.data)
    zj_detect                                0x200000ac   Data           1  image.o(.data)
    control_message                          0x200000b0   Data           4  image.o(.data)
    control_message2                         0x200000b4   Data           4  image.o(.data)
    race                                     0x200000b8   Data           8  image.o(.data)
    race1                                    0x200000c0   Data           8  image.o(.data)
    white_count_ratio                        0x200000c8   Data           8  image.o(.data)
    row_sub                                  0x200000d0   Data           8  image.o(.data)
    start_row                                0x200000d8   Data           4  image.o(.data)
    eff_row_count                            0x200000dc   Data           1  image.o(.data)
    zj_keep_flag                             0x200000e0   Data           4  image.o(.data)
    restart_flag                             0x200000e4   Data           4  image.o(.data)
    center_base                              0x200000e8   Data           4  image.o(.data)
    stage_flag                               0x200000ec   Data           4  image.o(.data)
    hd_return_flag                           0x200000f0   Data           4  image.o(.data)
    beep_count                               0x200000f4   Data           4  image.o(.data)
    white_count_flag                         0x200000f8   Data           4  image.o(.data)
    cross_flag                               0x200000fc   Data           4  image.o(.data)
    speed_left                               0x20000100   Data           2  image.o(.data)
    speed_hd1                                0x20000102   Data           2  image.o(.data)
    speed_hd5                                0x20000104   Data           2  image.o(.data)
    speed_now_hd5                            0x20000106   Data           2  image.o(.data)
    speed_xp                                 0x20000108   Data           2  image.o(.data)
    speed_stop1                              0x2000010a   Data           2  image.o(.data)
    speed_stop2                              0x2000010c   Data           2  image.o(.data)
    speed_stop3                              0x2000010e   Data           2  image.o(.data)
    speed_stop4                              0x20000110   Data           2  image.o(.data)
    speed_last2                              0x20000112   Data           2  image.o(.data)
    speed_sc                                 0x20000114   Data           2  image.o(.data)
    speed_last                               0x20000116   Data           2  image.o(.data)
    speed_now                                0x20000118   Data           2  image.o(.data)
    race3                                    0x2000011c   Data           4  image.o(.data)
    early_late_flag                          0x20000120   Data           4  image.o(.data)
    zj_Vmax                                  0x20000124   Data           4  image.o(.data)
    Hang_now                                 0x20000128   Data           4  image.o(.data)
    carspeed                                 0x2000012c   Data           4  image.o(.data)
    zj_speed                                 0x20000130   Data           4  image.o(.data)
    Dajiaoafterlost_flag                     0x20000134   Data           4  image.o(.data)
    zj_hd_race                               0x20000138   Data           4  image.o(.data)
    lostwhitewhenOuthd                       0x2000013c   Data           4  image.o(.data)
    late_cut_down                            0x20000140   Data           4  image.o(.data)
    beep_send_flag                           0x20000144   Data           4  image.o(.data)
    beep_count_send                          0x20000148   Data           4  image.o(.data)
    beep_time_send                           0x2000014c   Data           4  image.o(.data)
    speed_time                               0x20000150   Data           4  image.o(.data)
    HdRaceChangeFlag                         0x20000154   Data           1  image.o(.data)
    XpRaceChangeFlag                         0x20000155   Data           1  image.o(.data)
    big_angle_row                            0x20000158   Data           4  image.o(.data)
    ZjClearDistance                          0x2000015c   Data           4  image.o(.data)
    ZjDetectDistance                         0x20000160   Data           4  image.o(.data)
    Hd1ToHd5Distance                         0x20000164   Data           4  image.o(.data)
    Hd1ToXpDistance                          0x20000168   Data           4  image.o(.data)
    XpScDistance                             0x2000016c   Data           4  image.o(.data)
    race_hd1                                 0x20000170   Data           4  image.o(.data)
    race_hd2                                 0x20000174   Data           4  image.o(.data)
    race_hd3                                 0x20000178   Data           4  image.o(.data)
    race_hd4                                 0x2000017c   Data           4  image.o(.data)
    race_hd5                                 0x20000180   Data           4  image.o(.data)
    Xp3RaceTop                               0x20000184   Data           4  image.o(.data)
    Xp3RaceCross                             0x20000188   Data           4  image.o(.data)
    small_angle_row                          0x2000018c   Data           4  image.o(.data)
    zj_sc_count                              0x20000190   Data           4  image.o(.data)
    center_average                           0x20000194   Data           4  image.o(.data)
    center_r_last                            0x20000198   Data           4  image.o(.data)
    center_r_last2                           0x2000019c   Data           4  image.o(.data)
    center_r_now                             0x200001a0   Data           4  image.o(.data)
    LostDirection                            0x200001a4   Data           1  image.o(.data)
    hd_correct_flag                          0x200001a5   Data           1  image.o(.data)
    center_stop_min                          0x200001a8   Data           4  image.o(.data)
    center_stop_max                          0x200001ac   Data           4  image.o(.data)
    LostSureFlag                             0x200001b0   Data           4  image.o(.data)
    dbg_show_enable                          0x200001b4   Data           1  usart.o(.data)
    HandKey_Receive                          0x200001b6   Data           2  usart.o(.data)
    HandRock_left_Receive                    0x200001b8   Data           2  usart.o(.data)
    HandRock_right_Receive                   0x200001ba   Data           2  usart.o(.data)
    HandMode_Receive                         0x200001bc   Data           1  usart.o(.data)
    USART2_RX_STA                            0x200001bd   Data           1  usart.o(.data)
    HuorDistance                             0x200001c0   Data           2  can1.o(.data)
    HuorDistance2                            0x200001c2   Data           2  can1.o(.data)
    DirectionFlag                            0x200001c4   Data           2  can1.o(.data)
    UltrosonicDistance                       0x200001c8   Data           4  can1.o(.data)
    Distance                                 0x200001cc   Data           4  can1.o(.data)
    Fdistance                                0x200001d0   Data           4  can1.o(.data)
    ID_Electromagnet                         0x200001d4   Data           2  can1.o(.data)
    m                                        0x200001d8   Data           4  can1.o(.data)
    last_position                            0x200001dc   Data           4  can1.o(.data)
    now_position                             0x200001e0   Data           4  can1.o(.data)
    Ek1                                      0x200001e4   Data           4  pid.o(.data)
    Ek2                                      0x200001e8   Data           4  pid.o(.data)
    Ek3                                      0x200001ec   Data           4  pid.o(.data)
    P                                        0x200001f0   Data           4  pid.o(.data)
    I                                        0x200001f4   Data           4  pid.o(.data)
    D                                        0x200001f8   Data           4  pid.o(.data)
    PulseDirection                           0x200001fc   Data           4  pid.o(.data)
    PulseCutDown                             0x20000200   Data           4  pid.o(.data)
    stop_angle_flag                          0x20000204   Data           4  pid.o(.data)
    hd0to1_flag                              0x20000208   Data           4  pid.o(.data)
    stop_angle                               0x2000020c   Data           4  pid.o(.data)
    Angle                                    0x20000210   Data           4  pid.o(.data)
    kp                                       0x20000214   Data           4  pid.o(.data)
    stop4_flag                               0x20000218   Data           2  pid.o(.data)
    message2                                 0x2000021c   Data           4  pid.o(.data)
    BigCarWaitingDistance                    0x20000220   Data           4  pid.o(.data)
    HandFanleafFlag                          0x20000224   Data           1  pid.o(.data)
    sc_test                                  0x20000228   Data           4  pid.o(.data)
    back_flag                                0x2000022c   Data           1  pid.o(.data)
    AngleLast                                0x20000230   Data           4  pid.o(.data)
    time_mid_flag                            0x20000234   Data           1  pid.o(.data)
    speed_back                               0x20000238   Data           4  pid.o(.data)
    XpScTime                                 0x2000023c   Data           4  pid.o(.data)
    XpScFlag                                 0x20000240   Data           4  pid.o(.data)
    translation_angle                        0x20000244   Data           4  pid.o(.data)
    DeviceCode                               0x20000248   Data           2  ili9325.o(.data)
    HandKey                                  0x2000024c   Data           2  ps2.o(.data)
    HandKey_old                              0x2000024e   Data           2  ps2.o(.data)
    HandRock_left                            0x20000250   Data           2  ps2.o(.data)
    HandRock_left_old                        0x20000252   Data           2  ps2.o(.data)
    HandRock_right                           0x20000254   Data           2  ps2.o(.data)
    HandRock_right_old                       0x20000256   Data           2  ps2.o(.data)
    send_picture_flag                        0x20000258   Data           4  ps2.o(.data)
    HandMode                                 0x2000025c   Data           1  ps2.o(.data)
    SystemCoreClock                          0x20000270   Data           4  system_stm32f4xx.o(.data)
    AHBPrescTable                            0x20000274   Data          16  system_stm32f4xx.o(.data)
    image                                    0x20000284   Data       128000  ov7725.o(.bss)
    left                                     0x2001f684   Data         164  image.o(.bss)
    center                                   0x2001f728   Data         168  image.o(.bss)
    right                                    0x2001f7d0   Data         164  image.o(.bss)
    aTxBuffer_UART2                          0x2001f874   Data          51  usart.o(.bss)
    TxBuffer_UART2                           0x2001f8a8   Data         212  usart.o(.bss)
    USART2_RX_BUF                            0x2001f97c   Data          32  usart.o(.bss)
    __initial_sp                             0x2001fda0   Data           0  startup_stm32f4xx.o(STACK)



==============================================================================

Memory Map of the image

  Image Entry point : 0x08000189

  Load Region LR_IROM1 (Base: 0x08000000, Size: 0x0000b2f0, Max: 0x00100000, ABSOLUTE, COMPRESSED[0x0000b0e0])

    Execution Region ER_IROM1 (Base: 0x08000000, Size: 0x0000b06c, Max: 0x00100000, ABSOLUTE)

    Base Addr    Size         Type   Attr      Idx    E Section Name        Object

    0x08000000   0x00000188   Data   RO          805    RESET               startup_stm32f4xx.o
    0x08000188   0x00000000   Code   RO          816  * .ARM.Collect$$$$00000000  mc_w.l(entry.o)
    0x08000188   0x00000004   Code   RO         1102    .ARM.Collect$$$$00000001  mc_w.l(entry2.o)
    0x0800018c   0x00000004   Code   RO         1105    .ARM.Collect$$$$00000004  mc_w.l(entry5.o)
    0x08000190   0x00000000   Code   RO         1107    .ARM.Collect$$$$00000008  mc_w.l(entry7b.o)
    0x08000190   0x00000000   Code   RO         1109    .ARM.Collect$$$$0000000A  mc_w.l(entry8b.o)
    0x08000190   0x00000008   Code   RO         1110    .ARM.Collect$$$$0000000B  mc_w.l(entry9a.o)
    0x08000198   0x00000000   Code   RO         1112    .ARM.Collect$$$$0000000D  mc_w.l(entry10a.o)
    0x08000198   0x00000000   Code   RO         1114    .ARM.Collect$$$$0000000F  mc_w.l(entry11a.o)
    0x08000198   0x00000004   Code   RO         1103    .ARM.Collect$$$$00002712  mc_w.l(entry2.o)
    0x0800019c   0x00000784   Code   RO            3    .text               main.o
    0x08000920   0x00000018   Code   RO          161    .text               stm32f4xx_it.o
    0x08000938   0x000000b0   Code   RO          188    .text               led.o
    0x080009e8   0x00000036   Code   RO          208    .text               delay.o
    0x08000a1e   0x00000002   PAD
    0x08000a20   0x00000394   Code   RO          228    .text               ov7725.o
    0x08000db4   0x00000330   Code   RO          260    .text               sccb.o
    0x080010e4   0x00002a40   Code   RO          280    .text               image.o
    0x08003b24   0x0000054c   Code   RO          312    .text               usart.o
    0x08004070   0x00000230   Code   RO          343    .text               can1.o
    0x080042a0   0x00000122   Code   RO          369    .text               mydataprocess.o
    0x080043c2   0x00000002   PAD
    0x080043c4   0x00000820   Code   RO          389    .text               pid.o
    0x08004be4   0x00000466   Code   RO          416    .text               ili9320_api.o
    0x0800504a   0x00000002   PAD
    0x0800504c   0x0000009c   Code   RO          436    .text               led_show.o
    0x080050e8   0x000010b8   Code   RO          457    .text               ili9325.o
    0x080061a0   0x00000094   Code   RO          485    .text               queue.o
    0x08006234   0x000000b0   Code   RO          502    .text               visual_scope.o
    0x080062e4   0x000000e4   Code   RO          574    .text               misc.o
    0x080063c8   0x0000025c   Code   RO          614    .text               stm32f4xx_gpio.o
    0x08006624   0x00000588   Code   RO          634    .text               stm32f4xx_rcc.o
    0x08006bac   0x0000041a   Code   RO          676    .text               stm32f4xx_usart.o
    0x08006fc6   0x00000002   PAD
    0x08006fc8   0x0000061c   Code   RO          696    .text               stm32f4xx_fsmc.o
    0x080075e4   0x000003a4   Code   RO          716    .text               stm32f4xx_dma.o
    0x08007988   0x0000018c   Code   RO          736    .text               stm32f4xx_dcmi.o
    0x08007b14   0x000009ec   Code   RO          759    .text               stm32f4xx_can.o
    0x08008500   0x0000020c   Code   RO          779    .text               system_stm32f4xx.o
    0x0800870c   0x00000024   Code   RO          806    .text               startup_stm32f4xx.o
    0x08008730   0x00000024   Code   RO          819    .text               mc_w.l(memseta.o)
    0x08008754   0x0000014e   Code   RO         1082    .text               mf_w.l(dadd.o)
    0x080088a2   0x000000e4   Code   RO         1084    .text               mf_w.l(dmul.o)
    0x08008986   0x000000de   Code   RO         1086    .text               mf_w.l(ddiv.o)
    0x08008a64   0x00000022   Code   RO         1088    .text               mf_w.l(dflti.o)
    0x08008a86   0x0000003e   Code   RO         1092    .text               mf_w.l(dfixi.o)
    0x08008ac4   0x00000026   Code   RO         1094    .text               mf_w.l(f2d.o)
    0x08008aea   0x00000002   PAD
    0x08008aec   0x00000028   Code   RO         1096    .text               mf_w.l(cdcmple.o)
    0x08008b14   0x00000028   Code   RO         1098    .text               mf_w.l(cdrcmple.o)
    0x08008b3c   0x00000038   Code   RO         1100    .text               mf_w.l(d2f.o)
    0x08008b74   0x0000002c   Code   RO         1119    .text               mc_w.l(uidiv.o)
    0x08008ba0   0x00000062   Code   RO         1121    .text               mc_w.l(uldiv.o)
    0x08008c02   0x0000001e   Code   RO         1123    .text               mc_w.l(llshl.o)
    0x08008c20   0x00000020   Code   RO         1125    .text               mc_w.l(llushr.o)
    0x08008c40   0x00000024   Code   RO         1127    .text               mc_w.l(llsshr.o)
    0x08008c64   0x00000000   Code   RO         1129    .text               mc_w.l(iusefp.o)
    0x08008c64   0x0000006c   Code   RO         1130    .text               mf_w.l(fepilogue.o)
    0x08008cd0   0x000000be   Code   RO         1132    .text               mf_w.l(depilogue.o)
    0x08008d8e   0x00000030   Code   RO         1134    .text               mf_w.l(dfixul.o)
    0x08008dbe   0x00000002   PAD
    0x08008dc0   0x00000024   Code   RO         1136    .text               mc_w.l(init.o)
    0x08008de4   0x0000005c   Code   RO         1148    .text               mc_w.l(__dczerorl2.o)
    0x08008e40   0x00000028   Code   RO         1056    i.__0sprintf        mc_w.l(printfa.o)
    0x08008e68   0x00000014   Code   RO          810    i.__hardfp_fabs     m_wm.l(fabs.o)
    0x08008e7c   0x0000000e   Code   RO         1142    i.__scatterload_copy  mc_w.l(handlers.o)
    0x08008e8a   0x00000002   Code   RO         1143    i.__scatterload_null  mc_w.l(handlers.o)
    0x08008e8c   0x0000000e   Code   RO         1144    i.__scatterload_zeroinit  mc_w.l(handlers.o)
    0x08008e9a   0x00000002   PAD
    0x08008e9c   0x0000015c   Code   RO         1061    i._fp_digits        mc_w.l(printfa.o)
    0x08008ff8   0x000006f0   Code   RO         1062    i._printf_core      mc_w.l(printfa.o)
    0x080096e8   0x00000026   Code   RO         1063    i._printf_post_padding  mc_w.l(printfa.o)
    0x0800970e   0x00000030   Code   RO         1064    i._printf_pre_padding  mc_w.l(printfa.o)
    0x0800973e   0x0000000a   Code   RO         1066    i._sputc            mc_w.l(printfa.o)
    0x08009748   0x00000128   Data   RO          230    .constdata          ov7725.o
    0x08009870   0x0000000c   Data   RO          437    .constdata          led_show.o
    0x0800987c   0x000017d0   Data   RO          458    .constdata          ili9325.o
    0x0800b04c   0x00000020   Data   RO         1140    Region$$Table       anon$$obj.o


    Execution Region RW_IRAM1 (Base: 0x20000000, Size: 0x0001fda0, Max: 0x00020000, ABSOLUTE, COMPRESSED[0x00000074])

    Base Addr    Size         Type   Attr      Idx    E Section Name        Object

    0x20000000   0x00000037   Data   RW            5    .data               main.o
    0x20000037   0x00000001   PAD
    0x20000038   0x00000004   Data   RW          231    .data               ov7725.o
    0x2000003c   0x00000004   PAD
    0x20000040   0x00000174   Data   RW          283    .data               image.o
    0x200001b4   0x0000000a   Data   RW          314    .data               usart.o
    0x200001be   0x00000002   PAD
    0x200001c0   0x00000024   Data   RW          344    .data               can1.o
    0x200001e4   0x00000064   Data   RW          390    .data               pid.o
    0x20000248   0x00000002   Data   RW          459    .data               ili9325.o
    0x2000024a   0x00000002   PAD
    0x2000024c   0x00000011   Data   RW          549    .data               ps2.o
    0x2000025d   0x00000010   Data   RW          635    .data               stm32f4xx_rcc.o
    0x2000026d   0x00000003   PAD
    0x20000270   0x00000014   Data   RW          780    .data               system_stm32f4xx.o
    0x20000284   0x0001f400   Zero   RW          229    .bss                ov7725.o
    0x2001f684   0x000001f0   Zero   RW          281    .bss                image.o
    0x2001f874   0x00000128   Zero   RW          313    .bss                usart.o
    0x2001f99c   0x00000004   PAD
    0x2001f9a0   0x00000400   Zero   RW          803    STACK               startup_stm32f4xx.o


==============================================================================

Image component sizes


      Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Object Name

       560         26          0         36          0       2856   can1.o
        54          0          0          0          0        932   delay.o
      1126          0          0          0          0       4209   ili9320_api.o
      4280         44       6096          2          0      17269   ili9325.o
     10816        996          0        372        496      17719   image.o
       176         16          0          0          0        937   led.o
       156         18         12          0          0       1112   led_show.o
      1924        322          0         55          0     295407   main.o
       228         22          0          0          0       2241   misc.o
       290          0          0          0          0       3330   mydataprocess.o
       916         36        296          4     128000       3728   ov7725.o
      2080        302          0        100          0       2631   pid.o
         0          0          0         17          0        687   ps2.o
       148          0          0          0          0       2526   queue.o
       816          4          0          0          0       3016   sccb.o
        36          8        392          0       1024        892   startup_stm32f4xx.o
      2540         38          0          0          0       8392   stm32f4xx_can.o
       396          6          0          0          0       7914   stm32f4xx_dcmi.o
       932         32          0          0          0       6593   stm32f4xx_dma.o
      1564         58          0          0          0       5831   stm32f4xx_fsmc.o
       604         36          0          0          0       4485   stm32f4xx_gpio.o
        24          0          0          0          0       1282   stm32f4xx_it.o
      1416         48          0         16          0      11531   stm32f4xx_rcc.o
      1050         26          0          0          0       8196   stm32f4xx_usart.o
       524         44          0         20          0       2283   system_stm32f4xx.o
      1356         54          0         10        296       4229   usart.o
       176          0          0          0          0       1206   visual_scope.o

    ----------------------------------------------------------------------
     34196       2136       6828        644     129820     421434   Object Totals
         0          0         32          0          0          0   (incl. Generated)
         8          0          0         12          4          0   (incl. Padding)

    ----------------------------------------------------------------------

      Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Library Member Name

        20          0          0          0          0        124   fabs.o
        92          0          0          0          0          0   __dczerorl2.o
         0          0          0          0          0          0   entry.o
         0          0          0          0          0          0   entry10a.o
         0          0          0          0          0          0   entry11a.o
         8          4          0          0          0          0   entry2.o
         4          0          0          0          0          0   entry5.o
         0          0          0          0          0          0   entry7b.o
         0          0          0          0          0          0   entry8b.o
         8          4          0          0          0          0   entry9a.o
        30          0          0          0          0          0   handlers.o
        36          8          0          0          0         68   init.o
         0          0          0          0          0          0   iusefp.o
        30          0          0          0          0         68   llshl.o
        36          0          0          0          0         68   llsshr.o
        32          0          0          0          0         68   llushr.o
        36          0          0          0          0        108   memseta.o
      2260         86          0          0          0        512   printfa.o
        44          0          0          0          0         80   uidiv.o
        98          0          0          0          0         92   uldiv.o
        40          2          0          0          0         68   cdcmple.o
        40          2          0          0          0         68   cdrcmple.o
        56          0          0          0          0         88   d2f.o
       334          0          0          0          0        148   dadd.o
       222          0          0          0          0        100   ddiv.o
       190          0          0          0          0        176   depilogue.o
        62          0          0          0          0         80   dfixi.o
        48          0          0          0          0         68   dfixul.o
        34          0          0          0          0         76   dflti.o
       228          0          0          0          0         96   dmul.o
        38          0          0          0          0         68   f2d.o
       108          0          0          0          0        168   fepilogue.o

    ----------------------------------------------------------------------
      4140        106          0          0          0       2392   Library Totals
         6          0          0          0          0          0   (incl. Padding)

    ----------------------------------------------------------------------

      Code (inc. data)   RO Data    RW Data    ZI Data      Debug   Library Name

        20          0          0          0          0        124   m_wm.l
      2714        102          0          0          0       1064   mc_w.l
      1400          4          0          0          0       1204   mf_w.l

    ----------------------------------------------------------------------
      4140        106          0          0          0       2392   Library Totals

    ----------------------------------------------------------------------

==============================================================================


      Code (inc. data)   RO Data    RW Data    ZI Data      Debug   

     38336       2242       6828        644     129820     417382   Grand Totals
     38336       2242       6828        116     129820     417382   ELF Image Totals (compressed)
     38336       2242       6828        116          0          0   ROM Totals

==============================================================================

    Total RO  Size (Code + RO Data)                45164 (  44.11kB)
    Total RW  Size (RW Data + ZI Data)            130464 ( 127.41kB)
    Total ROM Size (Code + RO Data + RW Data)      45280 (  44.22kB)

==============================================================================

