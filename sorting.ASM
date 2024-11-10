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
arr db 100 dup(?)
len dw ?
readlength db "Enter the length of array: $"
readarray db "Enter the array elements: $"
sorted db "The sorted array is $"
newline db 10,13,"$"

.code 
mov ax,@data
mov ds,ax
mov si,00h

;read length
printstr readlength
readchar
sub al,30h
mov ah,00h
mov len,ax

;read array
printstr newline
printstr readarray

loopinput:
readchar
sub al,30h
mov arr[si],al
inc si
cmp si,len
jl loopinput

mov si,00h

siloop:
mov di,si

diloop:
mov bl,arr[di]
cmp bl,arr[si]
jge notlowest
xchg arr[si],bl
mov arr[di],bl

notlowest:
inc di
cmp di,len
jl diloop

inc si
cmp si,len
jl siloop

mov si,00h
printstr newline
loopoutput:
mov dl,arr[si]
add dl,30h
printchar
inc si
cmp si,len
jl loopoutput


mov ah,4ch
int 21h
end