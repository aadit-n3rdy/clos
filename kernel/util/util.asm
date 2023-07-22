
section .data

section .text

global get_msw
get_msw:
	smsw eax
	ret
