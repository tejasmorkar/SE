;assignment 5

section .data
        nline 		db	10,10
	nline_len	equ	$-nline

	ano	db 10, "Assignment No. 5", 10, "---------------------------------------------", 10, "assignment 5", 10
	ano_len		equ	$-ano
	
%macro	Print	2
	 MOV	RAX,1
	 MOV	RDI,1
         MOV	RSI,%1
         MOV	RDX,%2
    syscall
%endmacro

%macro	Read	2
	 MOV	RAX,0
	 MOV	RDI,0
         MOV	RSI,%1
         MOV	RDX,%2
    syscall
%endmacro

%macro Exit 0
	Print	nline,nline_len
	MOV	RAX,60
        MOV	RDI,0
    syscall
%endmacro

section .text
	global _start

_start:
       	Print	ano,ano_len
       	Exit

