#ifndef PIANO_H_
#define PIANO_H_

#include "main.h"
#include "TecladoFuncoes.h"

//------------------------------------------------------------------

void buzzerOn(TIM_HandleTypeDef *tim);
void buzzerOff(TIM_HandleTypeDef *tim);
void buzzerFreq(TIM_HandleTypeDef *tim, int freq);

//------------------------------------------------------------------

void servoAngle(TIM_HandleTypeDef *tim, int angle);

//------------------------------------------------------------------

void teclaSelect(TIM_HandleTypeDef *tim, int tecla);
void teclaToca(TIM_HandleTypeDef *servo, TIM_HandleTypeDef *buzzer, int tecla);

//------------------------------------------------------------------

void pianoToca(TIM_HandleTypeDef *select, TIM_HandleTypeDef *touch,
		TIM_HandleTypeDef *buzzer, int *tecla, int N);

void userToca(TIM_HandleTypeDef *buzzer, unsigned long *tecladoOut,
		unsigned long *tecladoIn, int N, int M);

//------------------------------------------------------------------

void modo12(TIM_HandleTypeDef *servo, unsigned long *tecladoOut,
		unsigned long *tecladoIn, int N, int M);

void modo2(TIM_HandleTypeDef *buzzer, unsigned long *tecladoOut,
		unsigned long *tecladoIn, int N, int M);

void modo1(TIM_HandleTypeDef *servoS, TIM_HandleTypeDef *servoT,
		TIM_HandleTypeDef *buzzer, unsigned long *tecladoOut,
		unsigned long *tecladoIn, int N, int M);

//------------------------------------------------------------------

void acendeLed(unsigned long *rgb, char state);

//------------------------------------------------------------------

#endif /* PIANO_H_ */
