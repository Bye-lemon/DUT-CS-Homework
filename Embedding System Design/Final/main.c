#include<stm32f10x.h>
#include<stdlib.h>

// 定义串口RX、串口TX以及LED对应的引脚号
#define UART_RX GPIO_Pin_9
#define UART_TX GPIO_Pin_10
#define LED     GPIO_Pin_0
// 定义串口缓冲区最大字符长度
#define BUFFER_LENGTH 10
// 定义PWM占空比最大值和最小值
#define MAX 39999
#define MIN 0
// 定义PID控制器中的KP、KI、KD三个系数
#define KP 0.1
#define KI 0.1
#define KD 0

char USART1_RX_BUFFER[BUFFER_LENGTH] = {'\0'}; // 串口缓冲区
int USART1_RX_LEN = 0; // 记录当前缓冲区字符数
int target = 0; // 记录PID控制器目标值
int sim_speed = 39999; // 在调试中模拟实际值
int errs[3] = {0, 0, 0}; // PID控制器中历史误差的记录

// 延时函数
void delay_ms(u16 time) {    
   u16 i = 0;  
   while (time--) {
      i = 12000;  
      while (i--);    
   }
}

// LED初始化函数
void LED_Initialization(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIO的外设时钟
	GPIO_InitTypeDef GPIO_InitStructure; // 初始化一个GPIO_InitStruct结构体
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 设置选中GPIO引脚的速率为50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 设置选中GPIO引脚的输出模式为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // 设置选中0号引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure); // 调用库函数初始化外设GPIOA
}

// 串口初始化函数
void UART_Initialization(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIO的外设时钟
	
	GPIO_InitTypeDef GPIO_InitStruct; // 初始化一个GPIO_InitStruct结构体
	GPIO_InitStruct.GPIO_Pin = UART_RX | UART_TX; // 设置选中串口的管脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // 设置选中GPIO引脚的速率为50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 设置选中GPIO引脚的输出模式为复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStruct); // 调用库函数初始化外设GPIOA
	
	NVIC_InitTypeDef NVIC_InitStruct; // 初始化一个NVIC_InitStruct结构体
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn; // 选中初始化USART1中断
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; // IRQ通道时能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3; // 设定抢占优先级为3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3; // 设定子优先级为3
	NVIC_Init(&NVIC_InitStruct);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // 使能串口的外设时钟
	USART_InitTypeDef USART_InitStruct; // 初始化一个USART_InitStruct结构体
	USART_InitStruct.USART_BaudRate = 9600; // 设定串口波特率为9600
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 设定无硬件数据流控制
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 设定收发模式
	USART_InitStruct.USART_Parity = USART_Parity_No; // 设定无奇偶校验位
	USART_InitStruct.USART_StopBits = USART_StopBits_1; // 设定1位停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // 设定数据为字长为8
	USART_Init(USART1, &USART_InitStruct); // 调用库函数初始化串口
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 开启串口USART1接收中断
	USART_Cmd(USART1, ENABLE); // 使能USART1
}

// 串口1中断处理函数
void USART1_IRQHandler(void) {
	char tmp = 0;
	int i;
	
	if (USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET) {
		tmp = USART_ReceiveData(USART1); // 接受一次数据
		if (tmp != 0x0A) { // 判断是否是中止符号\n
			// 未中止，将接受字节存入缓冲区，缓冲区长度+1
			USART1_RX_BUFFER[USART1_RX_LEN] = tmp;
			USART1_RX_LEN ++;
			if (USART1_RX_LEN >= BUFFER_LENGTH) {
				USART1_RX_LEN = 0;
			}
		} else {
			// 中止，更新PID控制器目标值
			target = atoi(USART1_RX_BUFFER); // 将缓冲区字符转化为数字
			for (i = 0; i < 3; i ++) {
				// LED闪烁3次，表示收到数据
				GPIO_SetBits(GPIOA, LED);
				delay_ms(50);
				GPIO_ResetBits(GPIOA, LED);
				delay_ms(50);
			}
			for (i = 0; i < BUFFER_LENGTH; i++) {
				// 清空缓冲区
				USART1_RX_BUFFER[i] = '\0';
			}
			USART1_RX_LEN = 0; // 将缓冲区长度置0
		}
	}
}

// PWM初始化函数
void PWM_Initialization(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIO外部时钟源
	GPIO_InitTypeDef GPIO_InitStructure; // 初始化一个GPIO_InitStruct结构体
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 设置引脚输出模式为复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // 选中引脚号6和7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 设置引脚频率为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure); // 调用库函数初始化GPIOA
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // 使能TIM3外部时钟源
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // 初始化一个TIM_TimeBaseStructure结构体
	TIM_OCInitTypeDef TIM_OCInitStruture; // 初始化一个TIM_OCInitStruct结构体
	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; // 设置CR寄存器
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 设置计数模式为向上计数
	TIM_TimeBaseStructure.TIM_Period = 39999; // 设置PSC寄存器
	TIM_TimeBaseStructure.TIM_Prescaler = 35; // 设置ARR寄存器
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); // 调用库函数初始化TIM3
	
	TIM_OCInitStruture.TIM_OCMode = TIM_OCMode_PWM2; // 设置输出模式为PWM2模式
	TIM_OCInitStruture.TIM_OCPolarity = TIM_OCPolarity_Low; // 设置极性为负
	TIM_OCInitStruture.TIM_OutputState = TIM_OutputState_Enable; // 使能OC输出
	TIM_OCInitStruture.TIM_Pulse = 39999; // 预设比较值为39999（100%占空比）
	TIM_OC1Init(TIM3, &TIM_OCInitStruture); // 调用库函数初始化TIM3
	TIM_Cmd(TIM3, ENABLE); // 使能TIM3
}

// 定时器2初始化函数
void TIM_Initialization(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 使能TIM2外部时钟源
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // 初始化一个TIM_TimeBaseInitStructure结构体

	TIM_TimeBaseStructure.TIM_ClockDivision = 0; // 设置CR寄存器
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 设置计数模式为向上计数
	TIM_TimeBaseStructure.TIM_Period = 39999; // 设置PSC寄存器
	TIM_TimeBaseStructure.TIM_Prescaler = 35; // 设置ARR寄存器
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // 设置重装在次数为0
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); // 调用库函数初始化TIM2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 开启定时器TIM2更新中断
	TIM_Cmd(TIM2, ENABLE); // 使能TIM2
	
	NVIC_InitTypeDef NVIC_InitStructure; // 创建一个NVIC_InitStructure结构体
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); // 选择第0组
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // 指定定时器2中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 设置抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // 设置子优先级为0
	NVIC_Init(&NVIC_InitStructure); // 调用库函数初始化中断
}

// 根据控制量输出控制信号
void set_motor(int speed) {
	// 此实现仅用于仿真，以修改全局变量sim_speed代替向电机输出控制量
	if (speed > MAX) {
		speed = MAX;
	} else if (speed < MIN) {
		speed = MIN;
	} // 约束控制量，避免超限
	TIM_SetCompare1(TIM3, speed); // 修改PWM比较寄存器的值
	sim_speed = speed; // 为全局变量赋值
}

// 对电机进行采样
int get_motor(void) {
	// 此函数仅用于仿真，以返回全局变量sim_speed的值代替采样电机转速
	return sim_speed;
}

// 定时器2中断处理函数
void TIM2_IRQHandler(void) {
	int speed, err, derr, dderr, delta;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) { // 检查TIM2更新中断是否发生
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除TIM2更新终端标志
		
		speed = get_motor(); // 采样电机转速
		errs[2] = errs[1];
		errs[1] = errs[0];
		errs[0] = target - speed; // 计算当前值和目标值的差值
		err = errs[0];
		derr = errs[0] - errs[1];
		dderr = errs[0] - 2 * errs[1] + errs[2];
		delta = KP * err + KI * derr + KD * dderr; // 计算控制之差值
		speed += delta; // 计算控制量
		set_motor(speed); // 输出控制量
	}
}

// 入口函数
int main(void) {
	LED_Initialization();
	UART_Initialization();
	PWM_Initialization();
	TIM_Initialization();
}
