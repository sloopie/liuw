;学生成绩管理系统
; 2006 级信息安全 2 班 刘炜 制作
;最后修改 2007.11.20 Rev. 5
.586
.model flat

stacks segment use16
db 256 dup(0)
stacks ends

datas segment use16

STUDENT struct
stunumber       db      0
stuname         db      20 dup('0')
score1          dw      0
score2          dw      0
score3          dw      0
score4          dw      0
score5          dw      0
score6          dw      0
score7          dw      0
average         dw      0
STUDENT ends
subNum          =       7

stuList         STUDENT <,'张  三    $',90,70,60,54,24,65,23,0>
                STUDENT <,'李  四    $',100,21,100,37,57,26,98,0>
                STUDENT <,'王  五    $',95,66,88,44,59,68,35,0>
                STUDENT <,'赵  六    $',20,90,99,87,69,87,86,0>
                STUDENT <,'小  明    $',90,89,95,20,67,69,68,0>
                STUDENT <,'小  红    $',79,36,59,59,51,52,53,0>
                STUDENT <,'小  白    $',53,80,15,28,54,55,56,0>
                STUDENT <,'小  黑    $',38,81,86,29,36,37,38,0>
                STUDENT <,'PETER     $',90,80,95,30,58,59,60,0>
                STUDENT <,'MOHINDER  $',31,32,33,34,35,36,37,0>
                STUDENT <,'JESSICA   $',91,92,93,94,21,22,23,0>
                STUDENT <,'ANGILA    $',1,2,100,54,3,100,100,0>
                STUDENT <,'PARKMAN   $',77,72,76,75,74,73,85,0>
                STUDENT <,'ADAM      $',10,20,30,40,50,60,70,0>
                STUDENT <,'HIRO      $',80,70,60,50,40,30,20,0>
		STUDENT <,'TOM       $',10,20,39,40,21,100,45,0>
		STUDENT <,'          $',19,24,88,91,24,56,65,0>
		STUDENT <,'JACK      $',13,45,67,21,99,21,48,0>
		STUDENT <,'BINGO     $',21,57,92,81,75,19,58,0>
		STUDENT <,'无名      $',45,11,25,21,56,12,78,0>
stuNum          =       ($-stuList)/(type STUDENT)

averQueue       db      1, 2, 3

OFFSET1          =       21

divider         dw      subNum
Menu            db      '请选择操作: ', 0dh, 0ah
                db      '1. 打印所有成绩.', 0dh, 0ah
                db      '2. 查询某一科目的最高分和最低分.', 0dh, 0ah
                db      '3. 按平均成绩排序.', 0dh, 0ah
                db      '4. 退出系统.', 0dh, 0ah, '$'

ExitMsg		db	0ah, 0dh, '06级信安2班 刘炜制作$'
HiLowPrompt     db      '请选择科目编号(1-7): $' 

datas ends

codes segment use16
assume cs: codes, ds: datas, ss: stacks

PRINT macro s
push ax
push dx
lea dx, s
mov ah, 09h
int 21h
pop dx
pop ax
endm

GETKEY macro
mov ah, 01h
int 21h
endm

BLANK macro
push ax
push dx
mov ah, 02h
mov dl, ' '
int 21h
pop dx
pop ax
endm

CRLF macro
push ax
push dx
mov ah, 02h
mov dl, 0dh
int 21h
mov ah, 02h
mov dl, 0ah
int 21h
pop dx
pop ax
endm


HILOW macro X
mov cx, stuNum
lea bx, stuList
.repeat
mov [bx].STUDENT.stunumber, 0
add bx, type STUDENT
.untilcxz

mov dx, 0
push dx
lea bx, stuList
mov cx, stuNum
.repeat
.if [bx].STUDENT.stunumber == 0
mov ax, [bx].STUDENT.score&X
.break
.else
add bx, type STUDENT
.endif
.untilcxz

lea bx, stuList
mov cx, stuNum
.repeat
.if [bx].STUDENT.stunumber == 0
.if [bx].STUDENT.score&X& >= ax
mov ax, [bx].STUDENT.score&X
mov di, bx
.endif
.endif
add bx, type STUDENT
.untilcxz
CRLF
CRLF
mov bx, di
pop dx
inc dl
push dx
PRINT [bx].STUDENT.stuname
mov ax, [di].STUDENT.score&X
invoke DisplayNum
mov dx, 0
push dx

mov cx, stuNum
lea bx, stuList
.repeat
mov [bx].STUDENT.stunumber, 0
add bx, type STUDENT
.untilcxz

lea bx, stuList
mov cx, stuNum
.repeat
.if [bx].STUDENT.stunumber == 0
mov ax, [bx].STUDENT.score&X
.break
.else
add bx, type STUDENT
.endif
.untilcxz

lea bx, stuList
mov cx, stuNum
.repeat
.if [bx].STUDENT.stunumber == 0
.if [bx].STUDENT.score&X& <= ax
mov ax, [bx].STUDENT.score&X
mov di, bx
.endif
.endif
add bx, type STUDENT
.untilcxz
BLANK
BLANK
mov bx, di
pop dx
inc dl
push dx
PRINT [bx].STUDENT.stuname
mov ax, [di].STUDENT.score&X
invoke DisplayNum
CRLF
pop dx
pop dx
ret
endm




ClearScr proc
pusha
mov ah, 06h
mov al, 0
mov bh, 7
mov ch, 0
mov cl, 0
mov dh, 24
mov dl, 79
int 10h
mov dx, 0
mov bh, 0
mov ah, 2
int 10h
popa
ret
ClearScr endp


InsertBlank proc
push ax
push dx
mov dl, ' '
mov ah, 02h
int 21h
pop dx
pop ax
ret
InsertBlank endp


DisplayNum proc
pusha
mov bl, 100
div bl
mov bh, ah
mov dl, al
add dl, 30h
mov ah, 02h
int 21h
mov al, bh
mov ah, 0
mov bl, 10
div bl
mov dl, al
mov dh, ah
add dl, 30h
mov ah, 02h
int 21h
mov dl, dh
add dl, 30h
mov ah, 02h
int 21h
popa
ret
DisplayNum endp

DisplayAll proc
pusha
CRLF
CRLF
lea bx, stuList
mov cx, stuNum
.repeat
PRINT [bx].STUDENT.stuname
invoke InsertBlank
;mov ax, [bx].STUDENT.average
;invoke DisplayNum
invoke InsertBlank
mov ax, [bx].STUDENT.score1
invoke DisplayNum
invoke InsertBlank
mov ax, [bx].STUDENT.score2
invoke DisplayNum
invoke InsertBlank
mov ax, [bx].STUDENT.score3
invoke DisplayNum
invoke InsertBlank
mov ax, [bx].STUDENT.score4
invoke DisplayNum
invoke InsertBlank
mov ax, [bx].STUDENT.score5
invoke DisplayNum
invoke InsertBlank
mov ax, [bx].STUDENT.score6
invoke DisplayNum
invoke InsertBlank
mov ax, [bx].STUDENT.score7
invoke DisplayNum
;mov ax, [averQueue+4]
;invoke DisplayNum
CRLF
add bx, type STUDENT
.untilcxz
CRLF
popa
ret
DisplayAll endp

CalcAverage proc
;local dw divider
pusha
lea bx, stuList
mov cx, stuNum
.repeat
mov ax, [bx].STUDENT.score1
add ax, [bx].STUDENT.score2
add ax, [bx].STUDENT.score3
add ax, [bx].STUDENT.score4
add ax, [bx].STUDENT.score5
add ax, [bx].STUDENT.score6
add ax, [bx].STUDENT.score7
cwd
mov divider, subNum
div divider
mov [bx].STUDENT.average, ax
add bx, type STUDENT
.untilcxz
popa
ret
CalcAverage endp

PopSort proc
pusha
lea di, averQueue
mov bx, -1
L1:
cmp bx, -1
jne SORTED
xor bx, bx
mov cx, stuNum-1
lea si, stuList
L2:
mov ax, [si].STUDENT.average
cmp ax, [si+type STUDENT].STUDENT.average
jle NOCHANGE
mov ax, word ptr [di+type word]
xchg [di], ax
mov word ptr [di+type word], ax
mov bx, -1
NOCHANGE:
add si, type STUDENT
add di, type word
loop L2
jmp L1
SORTED:
popa
ret
PopSort endp


HighLow proc
;pusha
CRLF
PRINT HiLowPrompt
GETKEY
.if al == '1'
HILOW 1
.elseif al == '2'
HILOW 2
.elseif al == '3'
HILOW 3
.elseif al == '4'
HILOW 4
.elseif al == '5'
HILOW 5
.elseif al == '6'
HILOW 6
.elseif al == '7'
HILOW 7
.endif
CRLF
;popa
ret
HighLow endp


DisplaySorted proc
mov cx, stuNum
lea bx, stuList
.repeat
mov [bx].STUDENT.stunumber, 0
add bx, type STUDENT
.untilcxz
mov dx, 0
push dx
CRLF
begin:
lea bx, stuList
mov cx, stuNum
.repeat
.if [bx].STUDENT.stunumber == 0
mov ax, [bx].STUDENT.average
.break
.else
add bx, type STUDENT
.endif
.untilcxz
lea bx, stuList
mov cx, stuNum
.repeat
.if [bx].STUDENT.stunumber == 0
.if [bx].STUDENT.average >= ax
mov ax, [bx].STUDENT.average
mov di, bx
.endif
.endif
add bx, type STUDENT
.untilcxz
CRLF
mov bx, di
pop dx
inc dl
push dx
mov [bx].STUDENT.stunumber, dl
mov dl, [bx].STUDENT.stunumber
.if dl == 20
mov dl, 32h
mov ah, 02h
int 21h
mov dl, 30h
mov ah, 02h
int 21h
jmp OUT1
.endif
.if dl <= 9
add dl, 30h
mov ah, 02h
int 21h
BLANK
.else
mov dl, 31h
mov ah, 02h
int 21h
mov dl, [bx].STUDENT.stunumber
add dl, 26h
mov ah, 02h
int 21h
.endif
OUT1:
BLANK
lea dx, [bx].STUDENT.stuname
mov ah, 09h
int 21h
mov di, bx
BLANK
mov ax, [di].STUDENT.average
invoke DisplayNum
pop dx
push dx
.if dl == stuNum
pop dx
CRLF
CRLF
ret
.endif
jmp begin
DisplaySorted endp


Debug proc
pusha
lea bx, stuList
mov al, type [bx].STUDENT.stuname
add al, 30h
mov dl, al
mov ah, 02h
int 21h
popa
ret
Debug endp

_start:
mov ax, datas
mov ds, ax

invoke ClearScr
invoke Debug
invoke CalcAverage
restart:
PRINT Menu
GETKEY

.if al == '4'
jmp _exit
.elseif al == '1'
invoke DisplayAll
jmp restart
.elseif al == '2'
invoke HighLow
jmp restart
.elseif al == '3'
invoke DisplaySorted
jmp restart
.endif

_exit:
PRINT ExitMsg
CRLF
mov ah, 4ch
int 21h
codes ends
end _start
