;
;  Test cases. All numbers are in hex.
;
;      111122223333 *     555566667777 =          5B061D958BF0ECA7C0481B5
;  3456FEDCAAAA1000 * EDBA00112233FF01 = 309A912AF7188C57E62072DD409A1000
;  FFFFEEEEDDDDCCCC * BBBBAAAA99998888 = BBBB9E2692C5DDDCC28F7531048D2C60
;  FFFFFFFFFFFFFFFF * FFFFFFFFFFFFFFFF = FFFFFFFFFFFFFFFE0000000000000001
;  00000001FFFFFFFF * 00000001FFFFFFFF = 0000000000000003FFFFFFFC00000001
;  FFFEFFFFFFFFFFFF * FFFF0001FFFFFFFF = FFFE0002FFFDFFFE0001FFFE00000001
;

;  void llmultiply(unsigned long long int l1,
;                  unsigned long long int l2,
;                  unsigned char *result);
        
;  a = AH * (2 << 32) + AL
;  b = BH * (2 << 32) + BL
;        
;  a * b = (AH * BH            * (2 << 64)) +
;          (AH * BL + AL * BH) * (2 << 32)  +
;           AL * BL

; For more infromation, see the lab manual!
        
	SECTION .data
	;; Init function
	;; optimizations
	;; Registers // avoid memory access

	SECTION .text
	ALIGN	16
	BITS	32

	;; To access parameter BH on the stack you do
	;;   MOV EAX, [EBP + 20]
	;; Replace the zero below with the correct value to be able
	;; to write your assembly code a little bit more readable: 
	;;   MOV EAX, [EBP + BH_OFF]
	;; Databyte 4 byte + addressing 4 byte
AL_OFF	EQU     8	; Offset from EBP to low  bits of a (AL)
AH_OFF	EQU     12	; Offset from EBP to high bits of a (AH)
BL_OFF	EQU     16	; Offset from EBP to low  bits of b (BL)
BH_OFF	EQU    	20	; Offset from EBP to high bits of b (BH)
RES_OFF	EQU     24	; Offset from EBP to result array pointer
	;;    ^^^^^ Replace 0 with correct values above
        
	GLOBAL llmultiply

llmultiply:
	PUSH EBP
	MOV EBP, ESP

	;; IMPLEMENTATION ;;

	;; Clearing the variable results memory ;;
	;; ECX 32 BIT REGISTER ;;
	MOV ECX, [EBP + RES_OFF]
	MOV EAX, 0					;Loading register "EAX" with value "0"
	MOV [ECX], EAX					;Saving value "EAX" to "ECX" bytes
	MOV [ECX + 4], EAX				;Saving value "EAX" to "ECX + 4" bytes
	MOV [ECX + 8], EAX				;Saving value "EAX" to "ECX + 8" bytes
	MOV [ECX + 12], EAX				;Saving value "EAX" to "ECX + 12" bytes

	
	;; Results of AL * BL ;;
	MOV EAX, [EBP + AL_OFF]				;Value of "EBP + AL_OFF" moved into "EAX"
	MOV EBX, [EBP + BL_OFF]				;Value of "EBP + BL_OFF" moved into "EBX"
	MUL EBX						;Multiplication
	MOV ECX, [EBP + RES_OFF]			;Saving carry into variable "RES_OFF"
	MOV [ECX], EAX					;Register EAX = low bytes
	MOV [ECX + 4], EDX				;Register EDX = high bytes

	
	;; Results of "AH * BL" saved into memory location "ECX + 4" ;;
	MOV EAX, [EBP + AH_OFF]				;Value of "EBP + AH_OFF" moved into "EAX"
	MOV EBX, [EBP + BL_OFF]				;Value of "EBP + BL_OFF" moved into "EBX"
	MUL EBX						;Multiplication
	AND EBX, 0					;Load register "EBX" with value "0"
	ADD [ECX + 4], EAX				;Addition
	ADC [ECX + 8], EDX				;Addition with carry
	ADC [ECX + 12], EBX				;Addition with carry


	;; Results of "AL * BH" saved into memory location "ECX + 8" ;;
	MOV EAX, [EBP + AL_OFF]				;Value of "EBP + AL_OFF" moved into "EAX"
	MOV EBX, [EBP + BH_OFF]				;Value of "EBP + BH_OFF" moved into "EBX"
	MUL EBX						;Multiplication
	AND EBX, 0					;Load register "EBX" with value "0"
	ADD [ECX + 4], EAX				;Addition
	ADC [ECX + 8], EDX				;Addition with carry
	ADC [ECX + 12], EBX				;Addition with carry

	
	;; Results of "AH * BH" saved into memory location "ECX + 12"
	MOV EAX, [EBP + AH_OFF]				;Value of "EBP + AH_OFF" moved into "EAX"
	MOV EBX, [EBP + BH_OFF]				;Value of "EBP + BH_OFF" moved into "EBX"
	MUL EBX						;Multiplication
	AND EBX, 0					;Load register "EBX" with value "0"
	ADC [ECX + 8], EAX				;Addition with carry
	ADC [ECX + 12], EDX				;Addition with carry

	
	;; END OF IMPLEMENTATION ;;
	POP EBP						; restore EBP reg
	RET						; return
