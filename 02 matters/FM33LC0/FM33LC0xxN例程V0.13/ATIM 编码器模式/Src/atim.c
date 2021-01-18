#include "atim.h"
#include "main.h"

 void ATIM_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    LL_ATIM_InitTypeDef BaseInitStructer = {0};    
    LL_ATIM_SlaveInitTypeDef SlaveInitStructer = {0};
    LL_ATIM_IC_InitTypeDef ICInitStructer = {0};
    
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_4 | LL_GPIO_PIN_5;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    BaseInitStructer.ClockSource = LL_RCC_ATIME_OPERATION_CLOCK_SOURCE_APBCLK2; //时钟源选择APB2
    BaseInitStructer.ClockDivision = LL_ATIM_CLOCKDIVISION_DIV1;                //工作时钟分频
    BaseInitStructer.CounterMode = LL_ATIM_COUNTER_DIRECT_UP;                   //向上计数
    BaseInitStructer.Prescaler = 0;                                             //计数源分频系数
    BaseInitStructer.Autoreload = 65535;                                        //自动重装载值
    BaseInitStructer.AutoreloadState = ENABLE;                                  //自动重装载
    LL_ATIM_Init(ATIM,&BaseInitStructer);
  
    SlaveInitStructer.SlaveMode = LL_ATIM_SLAVE_MODE_TI2FP2_CNT_TI1FP1_CNT;
    LL_ATIM_SlaveMode_Init(ATIM, &SlaveInitStructer);
    
    ICInitStructer.ICPrescaler   = LL_ATIM_IC_PRESCALER_DIV_1;          //输入捕捉分频
    ICInitStructer.ICFilter      = LL_ATIM_IC_FILTER_FDIV1;             //输入捕捉滤波配置
    ICInitStructer.CaptureState  = ENABLE;                              //使能CCx通道
    
    ICInitStructer.ICPolarity    = LL_ATIM_IC_POLARITY_RISING;          //上升沿捕获
    ICInitStructer.ICActiveInput = LL_ATIM_CC1_MODE_INPUT_TI1;          //CC1配置为输入，IC1映射到TI1
    LL_ATIM_IC_Init(ATIM, LL_ATIM_CHANNEL_1, &ICInitStructer);
    
    ICInitStructer.ICPolarity    = LL_ATIM_IC_POLARITY_RISING;          //上升沿捕获
    ICInitStructer.ICActiveInput = LL_ATIM_CC2_MODE_INPUT_TI2;          //CC2配置为输入，IC1映射到TI2
    LL_ATIM_IC_Init(ATIM, LL_ATIM_CHANNEL_2, &ICInitStructer);
    
    LL_ATIM_ClearFlag_UPDATE(ATIM); //清除计数器中断标志位
    LL_ATIM_EnableCounter(ATIM);    //使能定时器
}

int16_t ATIM_Read(void)
{
    int16_t temp;
    temp = ATIM->CNT;
    ATIM->CNT = 0;
    return temp;
}
