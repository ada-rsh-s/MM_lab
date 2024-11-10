.model small 

printstr macro s
lea dx,s
mov ah,09h
int 21h
endm

readchar macro p
mov ah,01h
int 21h
endm

printchar macro s
mov ah,02h
int 21h
endm

.data
num1 db "Enter num1 : $"
num2 db "Enter num2 : $"
num1i db ?
num2i db ?
result db "The result is : $"
newline db 10,13,"$"

.code 
mov ax,@data
mov ds,ax

printstr num1
readchar
sub al,30h
mov num1i,al

printstr newline

printstr num2
readchar
sub al,30h
mov num2i,al

printstr newline

addl:
mov bl,num1i
mov bh,num2i
add bl,bh
mov al,bl
mov ah,00h
mov cl,0ah
div cl
mov dl,al
add dl,30h
mov bh,ah
printchar
mov dl,bh
add dl,30h
printchar

printstr newline


sub1:
mov bl,num1i
mov bh,num2i
sub bl,bh
mov al,bl
mov ah,00h
mov cl,0ah
div cl
mov dl,al
add dl,30h
mov bh,ah
printchar
mov dl,bh
add dl,30h
printchar

printstr newline

mul1:
mov al,num1i
mov bl,num2i
mul bl
mov ah,00h
mov cl,0ah
div cl
mov dl,al
add dl,30h
mov bh,ah
printchar
mov dl,bh
add dl,30h
printchar

printstr newline

div1:
mov al,num1i
mov bl,num2i
mov ah,00h
div bl
mov dl,al
add dl,30h
mov bh,ah
printchar
mov dl,bh
add dl,30h
printchar

printstr newline



exit
mov ah,4ch
int 21h
end