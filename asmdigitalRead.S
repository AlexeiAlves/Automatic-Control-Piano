.syntax unified
.text
.macro ret
    bx lr
.endm
.globl asmdigitalRead

.equ IDR, 0x10

asmdigitalRead:
	ldr r2, [r0, #IDR] //Lê o valor do offset IDR do r0
	ands r2, r2, r1 //Reseta todos os bits exceto o do pino desejado

	cmp r2, 0 //Se o botão não estiver pressionado, retorna 0
	beq end

	//"For" que trás o bit que representa o pino para a "primeira casa"
	for:
		cmp r1, 1
		beq end

		lsrs r2, r2, 1
		lsrs r1, r1, 1
		b for

	end:
		movs r0, r2 //Armazena o resultado no r0 e retorna
		ret
