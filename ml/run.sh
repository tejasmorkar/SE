nasm -f elf64 $1.asm -o $1.o
ld -o $1 $1.o
./$1
