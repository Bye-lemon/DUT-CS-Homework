.MODEL TINY
.CODE
.STARTUP
	MOV  AL, 03H
	MOV  AH, 00H
	INT  10H
    
	MOV  DX, 00H
    
	MOV  BP, OFFSET NAME_STR
	MOV  CX, NAME_LEN
	MOV  BL, 02H
	CALL PRINT
    
	MOV  BP, OFFSET ID_STR
	MOV  CX, ID_LEN
	MOV  BL, 04H
	CALL PRINT
    
	MOV  BP, OFFSET PHONE_STR
	MOV  CX, PHONE_LEN
	MOV  BL, 03H
	CALL PRINT
    
	MOV  BP, OFFSET MAIL_STR
	MOV  CX, MAIL_LEN
 	MOV  BL, 06H
	CALL PRINT

.EXIT 0


PRINT PROC
	
    	MOV AL, 01H
    	MOV AH, 13H
    	INT 10H
    	INC DH
	RET

PRINT ENDP


NAME_STR  DB   'Name:liyingping', 0DH, 0AH, '$'
NAME_LEN  EQU  $ - NAME_STR
ID_STR    DB   'Number:201685040', 0DH, 0AH, '$'
ID_LEN    EQU  $ - ID_STR
PHONE_STR DB   'Phone:13941475810', 0DH, 0AH, '$'
PHONE_LEN EQU  $ - PHONE_STR
MAIL_STR  DB   'Email:Bye_lemon@mail.dlut.edu.cn', 0DH, 0AH, '$'
MAIL_LEN  EQU  $ - MAIL_STR

END