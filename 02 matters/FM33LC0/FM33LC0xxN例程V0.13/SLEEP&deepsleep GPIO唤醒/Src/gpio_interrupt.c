#include "user_init.h"
#include "main.h"
#include "gpio_interrupt.h"

//引脚中断
void GPIO_IRQHandler(void)
{  
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_9))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_9);
    } 
}
    

// 外部引脚中断初始化
void GPIO_interrupt_init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};    
    
    //引脚边沿触发选择
    LL_RCC_Enable_SleepmodeExternalInterrupt();//休眠使能外部中断采样
    LL_RCC_Group1_EnableOperationClock(LL_RCC_OPERATION1_CLOCK_EXTI);//EXTI工作时钟使能    
    
    //用到的GPIO引脚    设为输入 
    GPIO_InitStruct.Pin = LINE_9_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(LINE_9_GPIO, &GPIO_InitStruct);


    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_9, LL_GPIO_EXTI_TRIGGER_NONE);//关闭边沿触发
    //每条LINE 只能选一个引脚 
    LL_GPIO_SetExitLine0(GPIO_COMMON, LL_GPIO_EXTI_LINE_9_PC6);//中断引脚选择
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_9);//EXTI数字滤波功能
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_9, LL_GPIO_EXTI_TRIGGER_FALLING);//边沿选择    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_9);//清除中断标志
    
    
    /*NVIC中断配置*/
    NVIC_DisableIRQ(GPIO_IRQn);
    NVIC_SetPriority(GPIO_IRQn,2);//中断优先级配置
    NVIC_EnableIRQ(GPIO_IRQn);
}
