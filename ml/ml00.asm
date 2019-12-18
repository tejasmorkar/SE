section .data
	msg0 db 10, "Hello World", 10, 10
	msg0_len equ $-msg0
	msg1 db 10, "NASM is Awesome!", 10, 10
	msg1_len equ $-msg1

	%macro print 2
		MOV rax, 1
		MOV rdi, 1
		MOV rsi, %1
		MOV rdx, %2
		SYSCALL
	%endmacro
	
	%macro exit 0
		MOV rax, 60
		MOV rdi, 0
		SYSCALL
	%endmacro
	
section .text
	global _start
_start:
	print msg0, msg0_len
	print msg1, msg1_len
	exit

