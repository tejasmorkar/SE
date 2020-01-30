;Conversion From HEX to BCD and BCD to HEX Number

section .data
    br db 10,10
	br_len equ $-br
	
	msg0 db 10, "Assignment No. 3", 10, "---------------------------------------------", 10, "Conversion From HEX to BCD and BCD to HEX Number", 10
	msg0_len equ $-msg0

	menu db	10,"1.Hex To BCD.",
		 db	10,"2.BCD To Hex.",
		 db	10,"3.Exit."
		 db	10,"Enter Your Choice >> "
	menu_len equ $-menu

	hmsg db	10,"Enter 4 digit Hex Number >> "
	hmsg_len equ $-hmsg

	bmsg db	10,"Enter 5 digit BCD Number >> "
	bmsg_len equ $-bmsg

	ebmsg db 10,"The Equivalent BCD Number is >> "
	ebmsg_len equ $-ebmsg

	ehmsg db 10,"The Equivalent Hex Number is >> "
	ehmsg_len equ $-ehmsg

	emsg db 10,"INVALID NUMBER INPUT",10
	emsg_len equ $-emsg

section .bss
	buf resB 6
	char_ans resB 4
	ans resW 1
	

%MACRO PRINT 2
	MOV RAX, 1
	MOV RDI, 1
	MOV	RSI, %1
    MOV RDX, %2
    SYSCALL
%ENDMACRO

%MACRO READ 2
	MOV RAX, 0
	MOV RDI, 0
	MOV RSI, %1
	MOV RDX, %2
	SYSCALL
%ENDMACRO


%MACRO EXIT 0
	PRINT br, br_len
	MOV	RAX, 60
	MOV	RDI, 0
	SYSCALL
%ENDMACRO

section .text
	global _start

	_start:
		PRINT msg0, msg0_len
	
		MENU:	
			PRINT menu, menu_len
			READ buf, 2

			mov	AL, [buf]	

		c1:	
			CMP	AL, '1'
			JNE	c2
			call HEX_BCD
			JMP	MENU

		c2:	
			CMP	AL, '2'
			JNE	c3
			CALL BCD_HEX
			JMP	MENU

		c3:	
			cmp	AL, '3'
			JNE	invalid
			EXIT

	invalid:
		PRINT emsg, emsg_len
		JMP	MENU

HEX_BCD:
	PRINT hmsg,hmsg_len
	CALL Accept_16		
	MOV	AX, BX			

	MOV	BX, 10			
	XOR	BP, BP		

	back:	
		XOR	DX, DX			
		DIV	BX			
		PUSH DX			
		INC	BP		

		CMP	AX, 0			
		JNE	back		

		PRINT ebmsg, ebmsg_len

	back1:	
		POP DX			
		ADD	DL, 30h			
		MOV	[char_ans], DL		
		PRINT char_ans, 1

		DEC	BP	
		JNZ	back1			
		RET

BCD_HEX:
	PRINT bmsg, bmsg_len
	READ buf, 6		
 
	MOV	RSI, buf		
	XOR	AX, AX		
	MOV	RBP, 5		
	MOV	RBX, 10		
	
	next:	
		XOR	CX, CX		
		MUL	BX		
		MOV	CL, [rsi]
		SUB	CL, 30h
		ADD	AX, CX

		INC	RSI		
		DEC	RBP
		JNZ	next

		MOV	[ans], AX	
		PRINT ehmsg, ehmsg_len
	
		MOV	AX, [ans]
		CALL Disp_16		
	RET

Disp_16:				
	MOV	RSI,char_ans+3
	MOV	RCX,4           
	MOV	RBX,16			

	next_digit:
		XOR	RDX,RDX
		DIV	RBX

		CMP	DL,9	
		JBE	add30
		ADD	DL,07H

	add30:
		ADD	DL,30H
		MOV	[RSI],DL

		DEC	RSI
		DEC	RCX
		JNZ	next_digit

		PRINT char_ans,4
	RET

Accept_16:			
	READ buf, 5

	MOV	RCX,4
	MOV	RSI,buf
	XOR	BX,BX

	next_byte:
		SHL	BX,4
		MOV	AL,[RSI]
	
		CMP	AL,'0'
		JB	error
		CMP	AL,'9'
		JBE	sub30

		CMP	AL,'A'
		JB	error
		CMP	AL,'F'
		JBE	sub37
	
		CMP	AL,'a'
		JB	error
		CMP	AL,'f'
		JBE	sub57

	error:
		PRINT emsg, emsg_len
		EXIT

	sub57:	
		SUB	AL,20H
	
	sub37:	
		SUB	AL,07H
	
	sub30:	
		SUB	AL,30H
	
		ADD BX,AX
		INC	RSI
		DEC	RCX
		JNZ	next_byte		
	RET
