#include "Piano.h"

//------------------------------------------------------------------

//Liga o buzzer
void buzzerOn(TIM_HandleTypeDef *tim) {
	tim->Instance->CCR1 = 500;
}

//Desliga o buzzer
void buzzerOff(TIM_HandleTypeDef *tim) {
	tim->Instance->CCR1 = 0;
}

//Altera a frequência do buzzer
void buzzerFreq(TIM_HandleTypeDef *tim, int freq) {
	tim->Instance->PSC = (int) 8000000 / (freq * 1000);
}

//------------------------------------------------------------------

//Muda o ângulo do servo
void servoAngle(TIM_HandleTypeDef *tim, int angle) {
	tim->Instance->CCR1 = (int) (75 * angle + 4500) / 180;
}

//------------------------------------------------------------------

//Servo se move em direção à tecla desejada
void teclaSelect(TIM_HandleTypeDef *tim, int tecla) {
	switch (tecla) {
	case 1:
		servoAngle(tim, 0);
		break;
	case 2:
		servoAngle(tim, 20);
		break;
	case 3:
		servoAngle(tim, 40);
		break;
	case 4:
		servoAngle(tim, 53);
		break;
	case 5:
		servoAngle(tim, 65);
		break;
	case 6:
		servoAngle(tim, 85);
		break;
	case 7:
		servoAngle(tim, 100);
		break;
	}
}

//Servo toca a tecla
void teclaToca(TIM_HandleTypeDef *servo, TIM_HandleTypeDef *buzzer, int tecla) {
	int freqs[7] = { 440, 495, 528, 594, 660, 704, 792 };

	servoAngle(servo, 30);
	buzzerFreq(buzzer, freqs[tecla - 1]);
	buzzerOn(buzzer);

	HAL_Delay(500);

	servoAngle(servo, 0);
	buzzerOff(buzzer);

	HAL_Delay(200);
}

//------------------------------------------------------------------

//Piano toca sozinho com base em uma sequência de teclas
void pianoToca(TIM_HandleTypeDef *select, TIM_HandleTypeDef *touch,
		TIM_HandleTypeDef *buzzer, int *tecla, int N) {

	for (int i = 0; i < N; i++) {
		teclaSelect(select, tecla[i]);
		HAL_Delay(300);
		teclaToca(touch, buzzer, tecla[i]);
	}
}

//Usuário toca manualmente. Som sai do buzzer
void userToca(TIM_HandleTypeDef *buzzer, unsigned long *tecladoOut,
		unsigned long *tecladoIn, int N, int M) {

	int freqs[7] = { 440, 495, 528, 594, 660, 704, 792 };
	unsigned long rgb[3] = { GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3 };

	acendeLed(rgb, 'b');
	int digito = scanForClick(tecladoOut, tecladoIn, N, M);

	while (digito != 14) {
		if (digito <= 7 && digito != 0) {
			buzzerFreq(buzzer, freqs[digito - 1]);
			buzzerOn(buzzer);

			while (colPressed(tecladoIn, 3) != -1)
				;

			buzzerOff(buzzer);
		} else {
			acendeLed(rgb, 'r');
			HAL_Delay(250);
			acendeLed(rgb, 'b');
		}

		digito = scanForClick(tecladoOut, tecladoIn, N, M);
	}

	acendeLed(rgb, ' ');
}

//------------------------------------------------------------------

//Modo que recebe uma sequência de teclas pro piano tocar sozinho
void modo1(TIM_HandleTypeDef *servoS, TIM_HandleTypeDef *servoT,
		TIM_HandleTypeDef *buzzer, unsigned long *tecladoOut,
		unsigned long *tecladoIn, int N, int M) {

	unsigned long rgb[3] = { GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3 };

	acendeLed(rgb, 'b');
	int casa2 = getDigito(tecladoOut, tecladoIn, N, M);
	acendeLed(rgb, 'g');

	HAL_Delay(250);

	acendeLed(rgb, 'b');
	int casa1 = getDigito(tecladoOut, tecladoIn, N, M);
	acendeLed(rgb, 'g');

	HAL_Delay(250);

	const int n = casa2 * 10 + casa1;
	int teclas[n];

	for (int i = 0; i < n; i++) {
		acendeLed(rgb, 'b');
		int digito = getDigito(tecladoOut, tecladoIn, N, M);

		if (digito == 14) {
			acendeLed(rgb, ' ');
			return;
		} else if (digito > 7 || digito == 0) {
			acendeLed(rgb, 'r');
			HAL_Delay(250);
			i--;
		} else {
			acendeLed(rgb, 'g');
			HAL_Delay(250);

			teclas[i] = digito;
		}
	}

	pianoToca(servoS, servoT, buzzer, teclas, n);

	servoAngle(servoS, 30);
	HAL_Delay(500);
	servoAngle(servoS, 0);

	acendeLed(rgb, ' ');
}

//Temporário
void modo12(TIM_HandleTypeDef *servo, unsigned long *tecladoOut,
		unsigned long *tecladoIn, int N, int M) {
	int digito = 0;

	while (digito != 8) {
		int casa3 = getDigito(tecladoOut, tecladoIn, N, M);
		int casa2 = getDigito(tecladoOut, tecladoIn, N, M);
		int casa1 = getDigito(tecladoOut, tecladoIn, N, M);

		int num = (casa3 * 100 + casa2 * 10 + casa1);

		if (num > 180) {
			num = 180;
		}

		servoAngle(servo, num);

		digito = getDigito(tecladoOut, tecladoIn, N, M);
	}
}

//Modo onde o usuário toca o piano
void modo2(TIM_HandleTypeDef *buzzer, unsigned long *tecladoOut,
		unsigned long *tecladoIn, int N, int M) {
	userToca(buzzer, tecladoOut, tecladoIn, N, M);
}

//------------------------------------------------------------------

//Acende o led com a cor desejada
void acendeLed(unsigned long *rgb, char state) {
	if (state == 'r') {
		HAL_GPIO_WritePin(GPIOA, rgb[0], 0);
		HAL_GPIO_WritePin(GPIOA, rgb[1], 1);
		HAL_GPIO_WritePin(GPIOA, rgb[2], 1);
	} else if (state == 'g') {
		HAL_GPIO_WritePin(GPIOA, rgb[0], 1);
		HAL_GPIO_WritePin(GPIOA, rgb[1], 0);
		HAL_GPIO_WritePin(GPIOA, rgb[2], 1);
	} else if (state == 'b') {
		HAL_GPIO_WritePin(GPIOA, rgb[0], 1);
		HAL_GPIO_WritePin(GPIOA, rgb[1], 1);
		HAL_GPIO_WritePin(GPIOA, rgb[2], 0);
	} else if (state == 'y') {
		HAL_GPIO_WritePin(GPIOA, rgb[0], 0);
		HAL_GPIO_WritePin(GPIOA, rgb[1], 0);
		HAL_GPIO_WritePin(GPIOA, rgb[2], 1);
	} else {
		HAL_GPIO_WritePin(GPIOA, rgb[0], 1);
		HAL_GPIO_WritePin(GPIOA, rgb[1], 1);
		HAL_GPIO_WritePin(GPIOA, rgb[2], 1);
	}
}

//------------------------------------------------------------------
