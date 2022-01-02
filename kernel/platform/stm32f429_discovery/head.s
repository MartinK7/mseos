
	.global _start
	
	.extern k_const
	.extern k_init
	.extern k_zero
	
	.section .ivt
	.word noop
	.word k_const
	.word k_init
	.word k_zero
	.word noop
	
	.section .text
_start:
	bl boot
loop:
	b loop
noop:
	b noop

