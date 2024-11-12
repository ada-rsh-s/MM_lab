.model small

printstr macro p
lea dx,p
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
arr db 10 dup(?)
readmsg db "Enter a character: $"
newline db 10,13,"$"


.code 
mov ax,@data
mov ds,ax
mov si,00h

loopinput:
readchar
mov arr[si],al
inc si
cmp al,0dh
jne loopinput

dec si

loopoutput:
mov dl,arr[si]
printchar
dec si
cmp si,-1
jne loopoutput

mov ah,4ch
int 21h
end