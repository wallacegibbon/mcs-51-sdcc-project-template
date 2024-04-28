	.area		ASM_UTIL (CODE)

	.globl		_delay_1ms

	ar0		= 0x00
	ar1		= 0x01

	;; This function runs on @11.0592MHz
	;; You need to change this function when your baudrate changed.
_delay_1ms:
	push		ar0
	push		ar1
	mov		ar0, #15
	mov		ar1, #88
next:
	djnz		ar1, next
	djnz		ar0, next
	pop		ar1
	pop		ar0
	ret

