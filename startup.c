#include "startup.h"

extern const uint32_t __sec_text_begin;
extern const uint32_t __sec_text_end;
extern const uint32_t __sec_data_begin;
extern const uint32_t __sec_data_end;
extern const uint32_t __sec_bss_begin;
extern const uint32_t __sec_bss_end;
extern const uint32_t __sec_stack_begin;
extern const uint32_t __sec_stack_end;

void __isr_default() {
	while (1) { }
}

void __isr_fault() {
	while (1) { }
}

void __isr_reset() {
	/* copy .data from rom to ram */
	uint8_t * src = (uint8_t *)&__sec_text_end;
	uint8_t * dst = (uint8_t *)&__sec_data_begin;
	while (dst < (uint8_t *)&__sec_data_end) {
		*dst++ = *src++;
	}
	/* zero-initialize .bss */
	dst = (uint8_t *)&__sec_bss_begin;
	while (dst < (uint8_t *)&__sec_bss_end) {
		*dst++ = 0;
	}

	main();

	while (1) { }
}

__attribute__((section(".vectors"))) const uint32_t * __vectors[] = {
	(const uint32_t *)&__sec_stack_end,
	(const uint32_t *)&__isr_reset,
	(const uint32_t *)&__isr_nmi,
	(const uint32_t *)&__isr_hard_fault,
	(const uint32_t *)&__isr_memory_management,
	(const uint32_t *)&__isr_bus_fault,
	(const uint32_t *)&__isr_usage_fault,
	(const uint32_t *)0,
	(const uint32_t *)0,
	(const uint32_t *)0,
	(const uint32_t *)0,
	(const uint32_t *)&__isr_svc,
	(const uint32_t *)&__isr_debug_monitor,
	(const uint32_t *)0,
	(const uint32_t *)&__isr_pending_svc,
	(const uint32_t *)&__isr_systick,

	(const uint32_t *)&__isr_window_watchdog,
	(const uint32_t *)&__isr_pvd,
	(const uint32_t *)&__isr_tamper__timestamp,
	(const uint32_t *)&__isr_rtc_wakeup,
	(const uint32_t *)&__isr_flash,
	(const uint32_t *)&__isr_rcc,
	(const uint32_t *)&__isr_exti0,
	(const uint32_t *)&__isr_exti1,
	(const uint32_t *)&__isr_exti2,
	(const uint32_t *)&__isr_exti3,
	(const uint32_t *)&__isr_exti4,
	(const uint32_t *)&__isr_dma1_stream0,
	(const uint32_t *)&__isr_dma1_stream1,
	(const uint32_t *)&__isr_dma1_stream2,
	(const uint32_t *)&__isr_dma1_stream3,
	(const uint32_t *)&__isr_dma1_stream4,
	(const uint32_t *)&__isr_dma1_stream5,
	(const uint32_t *)&__isr_dma1_stream6,
	(const uint32_t *)&__isr_adc,
	(const uint32_t *)&__isr_can_tx,
	(const uint32_t *)&__isr_can_rx0,
	(const uint32_t *)&__isr_can_rx1,
	(const uint32_t *)&__isr_can_sce,
	(const uint32_t *)&__isr_exti5_to_9,
	(const uint32_t *)&__isr_tim1_brk__tim9,
	(const uint32_t *)&__isr_tim1_up__tim10,
	(const uint32_t *)&__isr_tim1_trigger__tim11,
	(const uint32_t *)&__isr_tim1_cc,
	(const uint32_t *)&__isr_tim2,
	(const uint32_t *)&__isr_tim3,
	(const uint32_t *)&__isr_tim4,
	(const uint32_t *)&__isr_i2c1_event,
	(const uint32_t *)&__isr_i2c1_error,
	(const uint32_t *)&__isr_i2c2_event,
	(const uint32_t *)&__isr_i2c2_error,
	(const uint32_t *)&__isr_spi1,
	(const uint32_t *)&__isr_spi2,
	(const uint32_t *)&__isr_usart1,
	(const uint32_t *)&__isr_usart2,
	(const uint32_t *)&__isr_usart3,
	(const uint32_t *)&__isr_exti10_to_15,
	(const uint32_t *)&__isr_rtc_alarm,
	(const uint32_t *)&__isr_usb_otg_fs_wakeup,
	(const uint32_t *)&__isr_tim8_brk__tim12,
	(const uint32_t *)&__isr_tim8_up__tim_13,
	(const uint32_t *)&__isr_tim8_trigger__tim14,
	(const uint32_t *)&__isr_tim8_cc,
	(const uint32_t *)&__isr_dma1_stream7,
	(const uint32_t *)&__isr_fsmc,
	(const uint32_t *)&__isr_sdio,
	(const uint32_t *)&__isr_tim5,
	(const uint32_t *)&__isr_spi3,
	(const uint32_t *)&__isr_uart4,
	(const uint32_t *)&__isr_uart5,
	(const uint32_t *)&__isr_tim6__dac,
	(const uint32_t *)&__isr_tim7,
	(const uint32_t *)&__isr_dma2_stream0,
	(const uint32_t *)&__isr_dma2_stream1,
	(const uint32_t *)&__isr_dma2_stream2,
	(const uint32_t *)&__isr_dma2_stream3,
	(const uint32_t *)&__isr_dma2_stream4,
	(const uint32_t *)&__isr_eth,
	(const uint32_t *)&__isr_eth_wakeup,
	(const uint32_t *)&__isr_can2_tx,
	(const uint32_t *)&__isr_can2_rx0,
	(const uint32_t *)&__isr_can2_rx1,
	(const uint32_t *)&__isr_can2_sce,
	(const uint32_t *)&__isr_usb_otg_fs,
	(const uint32_t *)&__isr_dma2_stream5,
	(const uint32_t *)&__isr_dma2_stream6,
	(const uint32_t *)&__isr_dma2_stream7,
	(const uint32_t *)&__isr_usart6,
	(const uint32_t *)&__isr_i2c3_event,
	(const uint32_t *)&__isr_i2c3_error,
	(const uint32_t *)&__isr_usb_otg_hs_endp1_out,
	(const uint32_t *)&__isr_usb_otg_hs_endp1_in,
	(const uint32_t *)&__isr_usb_otg_hs_wakeup,
	(const uint32_t *)&__isr_usb_otg_hs,
	(const uint32_t *)&__isr_dcmi,
	(const uint32_t *)&__isr_cryp,
	(const uint32_t *)&__isr_hash_rng,
	(const uint32_t *)&__isr_fpu,
};
