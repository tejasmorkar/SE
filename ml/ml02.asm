;Block Transfer non Overlapped without String Instruction

section .data
	msg0 db 10, "Assignment No. 2", 10, "---------------------------------------------", 10, "Block Transfer non Overlapped without String Instruction", 10
	msg0_len equ $-msg0
	msg1 db 10, "Before Transfer: "
	msg1_len equ $-msg1
	msg2 db 10, "After Tranfer: "
	msg2_len equ $-msg2
	msg3 db 10, "Source Block: "
	msg3_len equ $-msg3
	msg4 db 10, "Destination Block: "
	msg4_len equ $-msg4
	br db 10, 10
	br_len equ $-br
	
	sblock db 11h,22h,33h,44h,55h
	dblock times 5 db 0
	
section .bss
	char_ans resb 16

%MACRO PRINT 2
	MOV rax, 1
	MOV rdi, 1
	MOV rsi, %1
	MOV rdx, %2
	SYSCALL
%ENDMACRO

%MACRO EXIT 0
	MOV rax, 60
	MOV rdi, 0
	SYSCALL
%ENDMACRO
	
section .text
	 global _start
	 _start:
	 	PRINT msg0, msg0_len
	 	PRINT msg1, msg1_len
	 	PRINT msg2, msg2_len
	 	PRINT msg3, msg3_len
	 	PRINT msg4, msg4_len	
	 	
	 	PRINT br, br_len
 		EXIT
 		
	_display:
 		

