#include <stm32f10x.h>

#define UART_RX GPIO_Pin_9
#define UART_TX GPIO_Pin_10
#define BUFFER_LENGTH 10

u8 USART1_RX_BUFFER[BUFFER_LENGTH];
u8 USART1_RX_LEN = 0;

void Initializiton(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);      // 使能GPIOA时钟
	GPIO_InitTypeDef GPIO_InitStruct;                          // 创建GPIO初始化设置参数结构体
	GPIO_InitStruct.GPIO_Pin = UART_RX | UART_TX;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}
	
void RS232_Send_Data(u8 *buf, u8 len) {
	u8 cnt;
	
	for (cnt = 0; cnt < len; cnt ++) {
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1, buf[cnt]);
	}
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void USART1_IRQHandler(void) {
	u8 tmp = 0;
	
	if (USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET) {
		tmp = USART_ReceiveData(USART1);
		if (tmp != 0x0A) {
			USART1_RX_BUFFER[USART1_RX_LEN] = tmp;
			USART1_RX_LEN ++;
			if (USART1_RX_LEN >= BUFFER_LENGTH) {
				USART1_RX_LEN = 0;
			}
		} else {
			RS232_Send_Data(USART1_RX_BUFFER, USART1_RX_LEN);
			USART1_RX_LEN = 0;
		}
	}
}

int main() {
	Initializiton();
}
