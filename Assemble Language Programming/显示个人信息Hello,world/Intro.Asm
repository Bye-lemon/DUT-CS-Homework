.MODEL TINY
.CODE
.STARTUP
    MOV DX, OFFSET STRING
    MOV AH, 9
    INT 21H
.EXIT 0
STRING DB 'Name:liyingping', 0DH, 0AH, 
          'Number:201685040', 0DH, 0AH,
          'Phone:13941475810', 0DH,0AH,
          'Email:Bye_lemon@mail.dlut.edu.cn', 0DH, 0AH,
          '$'       
END