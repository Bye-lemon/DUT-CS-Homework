#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

#define LED_RED GPIO_Pin_0
#define LED_GREEN GPIO_Pin_1
#define LED_YELLOW GPIO_Pin_2
#define BUTTON0 GPIO_Pin_0
#define BUTTON1 GPIO_Pin_1
#define BUTTON2 GPIO_Pin_2
#define BUTTON3 GPIO_Pin_3
#define BUTTON4 GPIO_Pin_4
 
void delay_ms(u16 time) {    
   u16 i = 0;  
   while (time--) {
      i = 12000;  
      while (i--);    
   }
}

void GPIO_Initializiton(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);      // 使能GPIOA时钟
	GPIO_InitTypeDef GPIO_InitStruct;                          // 创建GPIO初始化设置参数结构体
	
	// 设置GPIOA_PIN0
	GPIO_InitStruct.GPIO_Pin = LED_RED | LED_GREEN | LED_YELLOW;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = BUTTON0 | BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void horse_race(void) {
	GPIO_SetBits(GPIOA, LED_RED);
	delay_ms(100);
	GPIO_ResetBits(GPIOA, LED_RED);
	GPIO_SetBits(GPIOA, LED_GREEN);
	delay_ms(100);
	GPIO_ResetBits(GPIOA, LED_GREEN);
	GPIO_SetBits(GPIOA, LED_YELLOW);
	delay_ms(100);
	GPIO_ResetBits(GPIOA, LED_YELLOW);
}

int main() {
	GPIO_Initializiton();
	
	unsigned char flag = 0;
	unsigned char last_btn4 = 0;

    while(1){
		if (GPIO_ReadInputDataBit(GPIOB, BUTTON4) && !last_btn4) {
			flag = !flag;
		}
		last_btn4 = GPIO_ReadInputDataBit(GPIOB, BUTTON4);
		
		if (GPIO_ReadInputDataBit(GPIOB, BUTTON0)) {
			GPIO_SetBits(GPIOA, LED_RED);
		} else {
			GPIO_ResetBits(GPIOA, LED_RED);
		}
		
		if (GPIO_ReadInputDataBit(GPIOB, BUTTON1)) {
			GPIO_SetBits(GPIOA, LED_GREEN);
		} else {
			GPIO_ResetBits(GPIOA, LED_GREEN);
		}
		
		if (GPIO_ReadInputDataBit(GPIOB, BUTTON2)) {
			GPIO_SetBits(GPIOA, LED_YELLOW);
		} else {
			GPIO_ResetBits(GPIOA, LED_YELLOW);
		}
		
		if (flag) {
			horse_race();
		} else if (GPIO_ReadInputDataBit(GPIOB, BUTTON3)) {
			horse_race();
		}
	}
}
