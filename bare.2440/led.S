/**
 * @file start.S
 *
 * initialization code for setup base enviroment.
 */
/* Newbie BUG, Copyright (C) 2014.  All rights reserved. */

.arm
.section .init
.globl _start

_start:

	;@ init irq mode stack pointer
	;@ 0xd2 = IRQ mode|fiq disable|irq_disable
	mov r0, #0xd2
	msr cpsr_c, r0
	mov sp, #0x2000

	;@ init fiq mode stack pointer
	;@ 0xd1 = FIQ mode|fiq disable|irq_disable
	mov r0, #0xd1
	msr cpsr_c, r0
	mov sp, #0x3000

	;@ init svc mode stack pointer
	;@ 0xd3 = SVC mode|fiq disable|irq_disable
	mov r0, #0xd3
	msr cpsr_c, r0
	mov sp, #0x4000

_loop:
	B _loop
