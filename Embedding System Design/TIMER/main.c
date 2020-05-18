#include<stm32f10x.h>

typedef enum {
	FALSE =0,
	TRUE =!FALSE
} bool;

typedef enum {
	UP, DOWN
} direction;

bool led = FALSE;
direction dir = UP;
u16 pulse = 0;

void initialization(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStruture;
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 39999;
	TIM_TimeBaseStructure.TIM_Prescaler = 35;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_OCInitStruture.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStruture.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStruture.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruture.TIM_Pulse = 19999;
	TIM_OC1Init(TIM3, &TIM_OCInitStruture);
	TIM_Cmd(TIM3, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);	
}


void TIM2_IRQHandler(void) {	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		if (led) {
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			led = FALSE;
		} else {
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
			led = TRUE;
		}
		
		if (dir == UP) {
			pulse += 1000;
		} else {
			pulse -= 1000;
		}
		
		if (pulse == 39000) {
			dir = DOWN;
		} else if (pulse == 0) {
			dir = UP;
		}
		
		TIM_SetCompare1(TIM3, pulse);
	}
}

int main(void) {
	initialization();
}
