#include<stm32f10x.h>
#include<stdlib.h>

// ���崮��RX������TX�Լ�LED��Ӧ�����ź�
#define UART_RX GPIO_Pin_9
#define UART_TX GPIO_Pin_10
#define LED     GPIO_Pin_0
// ���崮�ڻ���������ַ�����
#define BUFFER_LENGTH 10
// ����PWMռ�ձ����ֵ����Сֵ
#define MAX 39999
#define MIN 0
// ����PID�������е�KP��KI��KD����ϵ��
#define KP 0.1
#define KI 0.1
#define KD 0

char USART1_RX_BUFFER[BUFFER_LENGTH] = {'\0'}; // ���ڻ�����
int USART1_RX_LEN = 0; // ��¼��ǰ�������ַ���
int target = 0; // ��¼PID������Ŀ��ֵ
int sim_speed = 39999; // �ڵ�����ģ��ʵ��ֵ
int errs[3] = {0, 0, 0}; // PID����������ʷ���ļ�¼

// ��ʱ����
void delay_ms(u16 time) {    
   u16 i = 0;  
   while (time--) {
      i = 12000;  
      while (i--);    
   }
}

// LED��ʼ������
void LED_Initialization(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ʹ��GPIO������ʱ��
	GPIO_InitTypeDef GPIO_InitStructure; // ��ʼ��һ��GPIO_InitStruct�ṹ��
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ����ѡ��GPIO���ŵ�����Ϊ50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // ����ѡ��GPIO���ŵ����ģʽΪ�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // ����ѡ��0������
	GPIO_Init(GPIOA, &GPIO_InitStructure); // ���ÿ⺯����ʼ������GPIOA
}

// ���ڳ�ʼ������
void UART_Initialization(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ʹ��GPIO������ʱ��
	
	GPIO_InitTypeDef GPIO_InitStruct; // ��ʼ��һ��GPIO_InitStruct�ṹ��
	GPIO_InitStruct.GPIO_Pin = UART_RX | UART_TX; // ����ѡ�д��ڵĹܽ�
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // ����ѡ��GPIO���ŵ�����Ϊ50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // ����ѡ��GPIO���ŵ����ģʽΪ�����������
	GPIO_Init(GPIOA, &GPIO_InitStruct); // ���ÿ⺯����ʼ������GPIOA
	
	NVIC_InitTypeDef NVIC_InitStruct; // ��ʼ��һ��NVIC_InitStruct�ṹ��
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn; // ѡ�г�ʼ��USART1�ж�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; // IRQͨ��ʱ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3; // �趨��ռ���ȼ�Ϊ3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3; // �趨�����ȼ�Ϊ3
	NVIC_Init(&NVIC_InitStruct);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // ʹ�ܴ��ڵ�����ʱ��
	USART_InitTypeDef USART_InitStruct; // ��ʼ��һ��USART_InitStruct�ṹ��
	USART_InitStruct.USART_BaudRate = 9600; // �趨���ڲ�����Ϊ9600
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // �趨��Ӳ������������
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // �趨�շ�ģʽ
	USART_InitStruct.USART_Parity = USART_Parity_No; // �趨����żУ��λ
	USART_InitStruct.USART_StopBits = USART_StopBits_1; // �趨1λֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // �趨����Ϊ�ֳ�Ϊ8
	USART_Init(USART1, &USART_InitStruct); // ���ÿ⺯����ʼ������
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // ��������USART1�����ж�
	USART_Cmd(USART1, ENABLE); // ʹ��USART1
}

// ����1�жϴ�����
void USART1_IRQHandler(void) {
	char tmp = 0;
	int i;
	
	if (USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET) {
		tmp = USART_ReceiveData(USART1); // ����һ������
		if (tmp != 0x0A) { // �ж��Ƿ�����ֹ����\n
			// δ��ֹ���������ֽڴ��뻺����������������+1
			USART1_RX_BUFFER[USART1_RX_LEN] = tmp;
			USART1_RX_LEN ++;
			if (USART1_RX_LEN >= BUFFER_LENGTH) {
				USART1_RX_LEN = 0;
			}
		} else {
			// ��ֹ������PID������Ŀ��ֵ
			target = atoi(USART1_RX_BUFFER); // ���������ַ�ת��Ϊ����
			for (i = 0; i < 3; i ++) {
				// LED��˸3�Σ���ʾ�յ�����
				GPIO_SetBits(GPIOA, LED);
				delay_ms(50);
				GPIO_ResetBits(GPIOA, LED);
				delay_ms(50);
			}
			for (i = 0; i < BUFFER_LENGTH; i++) {
				// ��ջ�����
				USART1_RX_BUFFER[i] = '\0';
			}
			USART1_RX_LEN = 0; // ��������������0
		}
	}
}

// PWM��ʼ������
void PWM_Initialization(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ʹ��GPIO�ⲿʱ��Դ
	GPIO_InitTypeDef GPIO_InitStructure; // ��ʼ��һ��GPIO_InitStruct�ṹ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // �����������ģʽΪ�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // ѡ�����ź�6��7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ��������Ƶ��Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure); // ���ÿ⺯����ʼ��GPIOA
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // ʹ��TIM3�ⲿʱ��Դ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // ��ʼ��һ��TIM_TimeBaseStructure�ṹ��
	TIM_OCInitTypeDef TIM_OCInitStruture; // ��ʼ��һ��TIM_OCInitStruct�ṹ��
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; // ����CR�Ĵ���
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ü���ģʽΪ���ϼ���
	TIM_TimeBaseStructure.TIM_Period = 39999; // ����PSC�Ĵ���
	TIM_TimeBaseStructure.TIM_Prescaler = 35; // ����ARR�Ĵ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); // ���ÿ⺯����ʼ��TIM3
	
	TIM_OCInitStruture.TIM_OCMode = TIM_OCMode_PWM2; // �������ģʽΪPWM2ģʽ
	TIM_OCInitStruture.TIM_OCPolarity = TIM_OCPolarity_Low; // ���ü���Ϊ��
	TIM_OCInitStruture.TIM_OutputState = TIM_OutputState_Enable; // ʹ��OC���
	TIM_OCInitStruture.TIM_Pulse = 39999; // Ԥ��Ƚ�ֵΪ39999��100%ռ�ձȣ�
	TIM_OC1Init(TIM3, &TIM_OCInitStruture); // ���ÿ⺯����ʼ��TIM3
	TIM_Cmd(TIM3, ENABLE); // ʹ��TIM3
}

// ��ʱ��2��ʼ������
void TIM_Initialization(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // ʹ��TIM2�ⲿʱ��Դ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // ��ʼ��һ��TIM_TimeBaseInitStructure�ṹ��

	TIM_TimeBaseStructure.TIM_ClockDivision = 0; // ����CR�Ĵ���
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ü���ģʽΪ���ϼ���
	TIM_TimeBaseStructure.TIM_Period = 39999; // ����PSC�Ĵ���
	TIM_TimeBaseStructure.TIM_Prescaler = 35; // ����ARR�Ĵ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // ������װ�ڴ���Ϊ0
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); // ���ÿ⺯����ʼ��TIM2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // ������ʱ��TIM2�����ж�
	TIM_Cmd(TIM2, ENABLE); // ʹ��TIM2
	
	NVIC_InitTypeDef NVIC_InitStructure; // ����һ��NVIC_InitStructure�ṹ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); // ѡ���0��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // ָ����ʱ��2�ж�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // IRQͨ��ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // ������ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // ���������ȼ�Ϊ0
	NVIC_Init(&NVIC_InitStructure); // ���ÿ⺯����ʼ���ж�
}

// ���ݿ�������������ź�
void set_motor(int speed) {
	// ��ʵ�ֽ����ڷ��棬���޸�ȫ�ֱ���sim_speed�����������������
	if (speed > MAX) {
		speed = MAX;
	} else if (speed < MIN) {
		speed = MIN;
	} // Լ�������������ⳬ��
	TIM_SetCompare1(TIM3, speed); // �޸�PWM�ȽϼĴ�����ֵ
	sim_speed = speed; // Ϊȫ�ֱ�����ֵ
}

// �Ե�����в���
int get_motor(void) {
	// �˺��������ڷ��棬�Է���ȫ�ֱ���sim_speed��ֵ����������ת��
	return sim_speed;
}

// ��ʱ��2�жϴ�����
void TIM2_IRQHandler(void) {
	int speed, err, derr, dderr, delta;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) { // ���TIM2�����ж��Ƿ���
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // ���TIM2�����ն˱�־
		
		speed = get_motor(); // �������ת��
		errs[2] = errs[1];
		errs[1] = errs[0];
		errs[0] = target - speed; // ���㵱ǰֵ��Ŀ��ֵ�Ĳ�ֵ
		err = errs[0];
		derr = errs[0] - errs[1];
		dderr = errs[0] - 2 * errs[1] + errs[2];
		delta = KP * err + KI * derr + KD * dderr; // �������֮��ֵ
		speed += delta; // ���������
		set_motor(speed); // ���������
	}
}

// ��ں���
int main(void) {
	LED_Initialization();
	UART_Initialization();
	PWM_Initialization();
	TIM_Initialization();
}
