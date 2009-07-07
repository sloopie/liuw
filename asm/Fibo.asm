TITLE A test program by Liu Wei.
INCLUDE Irvine32.inc
.data
val1 byte 1
val2 byte 1
.code
main PROC
	mov al, val1
	call dumpregs
	call dumpregs
	mov ecx, 5
	L1:
	mov al, val1
	add al, val2
	mov dl, val1
	mov val2, dl
	mov val1, al
	call dumpregs
	loop L1
	exit
main ENDP
END main
