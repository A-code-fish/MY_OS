; wm_OS_ipl
; TAB=4
CYLS	EQU		30
		ORG		0x7c00
; 标准FAT12格式软盘专用的代码
​		JMP		entry
		DB		0x90
		DB		"INTOWMOS"		
		DW		512				
		DB		1				
		DW		1				
		DB		2				
		DW		224				
		DW		2880			
		DB		0xf0			
		DW		9				
		DW		18				
		DW		2				
		DD		0			
		DD		2880			
		DB		0,0,0x29		
		DD		0xffffffff		
		DB		"WM-OS      "	
		DB		"FAT12   "		
		RESB	18	

entry:
        	MOV     		AX,0            ; 初始化寄存器
        	MOV    		SS,AX
        	MOV    		SP,0x7c00
        	MOV   		DS,AX
       		MOV		AX,0x0820
		MOV		ES,AX
		MOV		CH,0			
		MOV		DH,0			
		MOV		CL,2		
readloop:	
		MOV		SI,0
retry:
		MOV		AH,0x02			
		MOV		AL,1			
		MOV		BX,0
		MOV		DL,0x00			
		INT			0x13			
		JNC			next			
		ADD			SI,1			
		CMP			SI,5			
		JAE			error			
		MOV		AH,0x00
		MOV		DL,0x00			
		INT			0x13			
		JMP			retry
next:
		MOV		AX,ES			
		ADD			AX,0x0020
		MOV		ES,AX			
		ADD			CL,1			
		CMP			CL,18			
		JBE			readloop		
		MOV		CL,1
		ADD			DH,1
		CMP			DH,2
		JB			readloop		
		MOV		DH,0
		ADD			CH,1
		CMP			CH,CYLS
		JB			readloop	
		MOV		[0x0ff0],CH	
		JMP			0xc200

fin:
        	HLT                     ; 让CPU停止，等待指令
        	JMP     		fin             ; 无限循环
error:
		MOV		SI,msg

putloop:
        	MOV     		AL,[SI]
        	ADD     		SI,1            ; 给SI加1
        	CMP     		AL,0
        	JE      		fin
        	MOV     		AH,0x0e         ; 显示一个文字
        	MOV     		BX,15           ; 指定字符颜色
        	INT     		0x10            ; 调用显卡BIOS
        	JMP     		putloop
msg:
        	DB			0x0a, 0x0a		
		DB			"something error"
		DB			0x0a		
		DB			0
		RESB	0x7dfe-$		
		DB			0x55, 0xaa