#include <stm32f10x.h>
 
 
void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  
      while(i--) ;    
   }
}

int main(){
    
    GPIO_InitTypeDef GPIO_InitStruct;                                      //声明一个GPIO_InitStructure结构体
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);                  //使能GPIO对应的外设时钟
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;                                 //选择待设置的GPIO管脚
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;                         //设置选中GPIO管脚的速率
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;                          //设置选中GPIO管脚的模式
    GPIO_Init(GPIOA, &GPIO_InitStruct);                                    //调用库函数初始化外设GPIOX

    while(1){
       GPIO_SetBits(GPIOA, GPIO_Pin_0);//设置引脚电平
       delay_ms(100);
       GPIO_ResetBits(GPIOA, GPIO_Pin_0);//设置引脚电平
       delay_ms(100);
    }
}
