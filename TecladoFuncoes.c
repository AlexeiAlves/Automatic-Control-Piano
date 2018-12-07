#include "TecladoFuncoes.h"

int scanForClick(unsigned long *tecladoOut, unsigned long *tecladoIn, int N,
		int M) {
	for (int i = 0; i < N; i++) {
		HAL_GPIO_WritePin(GPIOA, tecladoOut[i], LOW);
	}

	while (1) {
		HAL_GPIO_WritePin(GPIOA, tecladoOut[N - 1], LOW);

		for (int i = 0; i < N; i++) {
			HAL_GPIO_WritePin(GPIOA, tecladoOut[i], HIGH);

			if (i > 0)
				HAL_GPIO_WritePin(GPIOA, tecladoOut[i - 1], LOW);

			int col = colPressed(tecladoIn, M);

			if (col >= 0) {
				return numPressed(i, col);
			}
		}
	}
}

int colPressed(unsigned long *tecladoIn, int M) {
	for (int i = 0; i < M; i++) {
		if (HAL_GPIO_ReadPin(GPIOB, tecladoIn[i])) {
			return i;
		}
	}

	return -1;
}

int getDigito(unsigned long *tecladoOut, unsigned long *tecladoIn, int N, int M) {
	int digito = scanForClick(tecladoOut, tecladoIn, N, M);
	while (colPressed(tecladoIn, 3) != -1)
		;

	return digito;
}

int numPressed(int linha, int coluna) {
	int mat[4][4] = { { 1, 2, 3, 10 }, { 4, 5, 6, 11 }, { 7, 8, 9, 12 }, { 14,
			0, 15, 13 } };

	return mat[linha][coluna];
}

void writeLeds(unsigned long *leds, int num, int N) {
	int ledW[4] = { (num >> 0) & 1, (num >> 1) & 1, (num >> 2) & 1, (num >> 3)
			& 1 };

	for (int i = 0; i < N; i++) {
		digitalWrite(leds[i], ledW[i]);
	}
}
