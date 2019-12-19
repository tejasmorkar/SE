;write assembly code to find number of positive elements from 64 bit array

section .data
	msg0 db 10, "Assignment No. 1", 10, "---------------------------------------------", 10, "Positive/Negative elements from 64 bit array", 10
	msg0_len equ $-msg0
	msg1 db 10, "The number of positive elements are: "
	msg1_len equ $-msg1
	msg2 db 10, "The number of negative elements are: "
	msg2_len equ $-msg2
	br db 10, 10
	br_len equ $-br
	
	array dq -11111111H, 22222222H, -33333333H, 44444444H, 55555555H
	n equ 5
	
section .bss
	pos_ctr resq 1
	neg_ctr resq 1
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
	 	
	 	MOV rsi, array
	 	MOV rcx, n
	 	MOV rbx, 0  ;pos ctr
	 	MOV rdx, 0	;neg ctr
	 	
 	_nextNum:
	 	MOV rax, [rsi]
	 	ROL rax, 1
	 	JC _neg
	 	
 	_pos:
 		INC rbx
 		JMP _next
 		
	_neg:
		INC rdx
		
	_next:
		ADD rsi, 8
		DEC rcx
		JNZ _nextNum
		
		MOV [pos_ctr], rbx
		MOV [neg_ctr], rdx
	 	
	 	PRINT msg1, msg1_len
	 	MOV rax, [pos_ctr]
	 	CALL _display
	 	
	 	PRINT msg2, msg2_len
	 	MOV rax, [neg_ctr]
	 	CALL _display
	 	
	 	PRINT br, br_len
 		EXIT
 		
	_display:
 		MOV rbx, 16
 		MOV rcx, 2
 		MOV rsi, char_ans + 1
 		
	_cnt:
		MOV rdx, 0
		DIV rbx
		cmp dl, 09h
		JBE _add30
		ADD dl, 07h
		
	_add30:
		ADD dl, 30h
		MOV [rsi], dl
		DEC rsi
		DEC rcx
		JNZ _cnt
		PRINT char_ans, 2
		RET

