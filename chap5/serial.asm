		SECTION	.data
		EXTERN	inbound_queue		; (defined in main.C)
	
		LSR_THRE_MASK	EQU 0x20	; Bit 5 variable
		RBR_MASK 	EQU 0x01	; Bit 1 variable
	
data		DB	0			; put rcvd byte here

		SECTION	.text
		ALIGN	16
		BITS	32

BASE_PORT	EQU	3F8h			; we have this in our lab

LSR_PORT	EQU	BASE_PORT+5
RBR_PORT	EQU	BASE_PORT
THR_PORT	EQU	BASE_PORT

; -------------------------------------------------------------------------------------------------------------------------------------------------
; void SerialPut(char ch)
; -------------------------------------------------------------------------------------------------------------------------------------------------
; This function uses programmed waiting loop I/O to output the ASCII character 'ch' to the UART. ;
; Wait for THRE = 1 (Transmitter Holding Register Empty - bit 5 i LSR_PORT) ;
; Output character to UART ;
; Return to caller ;
; DX uses full 16-bit port number  ; 

		GLOBAL	SerialPut

SerialPut:		
		MOV 	DX, LSR_PORT 		; Moves address of Line Status Register (LSR) into DX register
		IN 	AL, DX			; Reads byte from LSR and stores it in AL register		
		AND	AL, LSR_THRE_MASK 	; Masks all bits except the 5th-bit which is "THRE"
		CMP	AL, LSR_THRE_MASK 	; Compares value of AL register to Interrupt controller
		JNE 	SerialPut		; Loop to controll if "THRE = 1", if not true then jump back to SerialPut
		MOV 	DX, THR_PORT		; Moves address of Transmit Holding Register (THR - holds data to be transmitted) into DX register
		MOV 	AL, [ESP + 4]		; Move byte at offset + 4 to top of AL register, represents data to be transmitted 
		OUT 	DX, AL			; Send data in AL register to THR
		RET
; -------------------------------------------------------------------------------------------------------------------------------------------------
; void interrupt SerialISR(void)
; -------------------------------------------------------------------------------------------------------------------------------------------------
; This is an Interrupt Service Routine (ISR) for serial receive interrupts.  Characters received are placed in a queue by calling Enqueue(char). ;
; Preserve all registers ;
; Get character from UART ;
; Put character into queue ;
; Param #2: address of data ;
; Param #1: address of queue ;

	;; TEST //TESTAR BÅDA PÅ EN GÅNG MED "AND" OCH "CMP"
	;; 
		GLOBAL	SerialISR
		EXTERN	QueueInsert		; (provided by LIBPC)

SerialISR:    		
		STI				; Enables (higher-priority) IRQs by setting up Interrupt flag (IF) 
		PUSHAD				; Pushes all general-purpose registers (EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI) to the stack
		MOV	DX, LSR_PORT		; Moves Line Status Register (LSR) into the DX register
		IN	AL, DX			; Reads a byte from from LSR and stores it in AL register
		AND	AX, RBR_MASK		; Masks all the bits except the first bit to see if data is recieved
		CMP	AX, RBR_MASK		; Compares value of AX register to hexadecimal 0x01
		JNE	_Eoi			; Loop to controll to see if data is recieved, if not equal to 0x01 then jump to _Eoi
	
		MOV	DX, RBR_PORT		; Moves the adress of Recieve Buffer Register (RBR - holds incoming data) into DX register
		IN	AL, DX			; Reads a byte from the RBR and store it into AL register
		MOV	[data], AL		; Moves value of AL register into data variable
		PUSH	dword data		; Pushes the variable data onto the stack as double word
		PUSH	dword [inbound_queue]	; Pushes the variable inbound_queue onto the stack as double word
		CALL	QueueInsert		
		ADD	ESP,8			
;/////////////////////////////////////////////////////////////////////////////////////////////;
; Enable lower priority interrupts ;
; Send Non-Specific EOI to PIC ;
; Restore all registers ;
; Return to interrupted code ;
	
_Eoi:						; Entry point for ISR (Interrupt Service Routine)		
		MOV	AX, LSR_THRE_MASK	; Send End Of Interrupt (EOI)
		MOV	DX, LSR_THRE_MASK	; Send End Of Interrupt (EOI)
		OUT 	DX, AX			; Send out I/O output to hardware
		POPAD				; Pops values of general-purpose registers saved on the stack
		IRET				; Interrupt return (ISR) and popping values of the IP (Instruction pointer) and CS (Code segment)
	
