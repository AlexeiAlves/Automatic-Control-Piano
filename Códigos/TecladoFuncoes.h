#ifndef TECLADOFUNCOES_H_
#define TECLADOFUNCOES_H_

#include "main.h"

#define LOW 0
#define HIGH 1

int scanForClick(unsigned long *tecladoOut, unsigned long *tecladoIn, int N,
		int M);
int colPressed(unsigned long *tecladoIn, int M);
int getDigito(unsigned long *tecladoOut, unsigned long *tecladoIn, int N, int M);
int numPressed(int linha, int coluna);
void writeLeds(unsigned long *leds, int num, int N);

#endif /* TECLADOFUNCOES_H_ */
