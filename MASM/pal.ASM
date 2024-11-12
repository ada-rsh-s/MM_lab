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
notpalindrome db "The string is not palindrome $"
palindrome db "The string is palindrome $"

newline db 10,13,"$"


.code 
mov ax,@data
mov ds,ax
mov si,00h

printstr readmsg
printstr newline

loopinput:
readchar
mov arr[si],al
inc si
cmp al,0dh
jne loopinput

dec si
dec si 
mov di,00h; 
mov cl,00h

loopoutput:
mov al,arr[di]
mov ah,arr[si]
cmp al,ah
jne notpal
dec si
inc di
cmp si,di
jg loopoutput

printstr palindrome
jmp exit
notpal:printstr notpalindrome

exit:mov ah,4ch
int 21h
end