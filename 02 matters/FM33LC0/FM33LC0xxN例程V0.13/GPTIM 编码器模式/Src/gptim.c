#include "gptim.h"
#include "main.h"

 void GPTIM_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    LL_GPTIM_InitTypeDef BaseInitStructer = {0};    
    LL_GPTIM_SlaveInitTypeDef SlaveInitStructer = {0};
    LL_GPTIM_IC_InitTypeDef ICInitStructer = {0};
    
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_10);
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_11);
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.Pull = DISABLE;
    GPIO_InitStruct.RemapPin = ENABLE;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    BaseInitStructer.ClockDivision = LL_GPTIM_CLOCKDIVISION_DIV1;   //不分频
    BaseInitStructer.CounterMode = LL_GPTIM_COUNTER_DIRECT_UP;      //向上计数
    BaseInitStructer.Prescaler = 0;                                 //计数源分频系数
    BaseInitStructer.Autoreload = 65535;                            //自动重装载值
    BaseInitStructer.AutoreloadState = ENABLE;                      //自动重装载
    LL_GPTIM_Init(GPTIM0, &BaseInitStructer);
  
    SlaveInitStructer.SlaveMode = LL_GPTIM_SLAVE_MODE_TI2FP2_CNT_TI1FP1_CNT;
    LL_GPTIM_SlaveMode_Init(GPTIM0, &SlaveInitStructer);
    
    ICInitStructer.ICPrescaler   = LL_GPTIM_IC_PRESCALER_DIV_1;          //输入捕捉分频
    ICInitStructer.ICFilter      = LL_GPTIM_IC_FILTER_FDIV1;             //输入捕捉滤波配置
    ICInitStructer.CaptureState  = ENABLE;                              //使能CCx通道
    
    ICInitStructer.ICPolarity    = LL_GPTIM_IC_POLARITY_RISING;          //上升沿捕获
    ICInitStructer.ICActiveInput = LL_GPTIM_CC1_MODE_INPUT_TI1;          //CC1配置为输入，IC1映射到TI1
    LL_GPTIM_IC_Init(GPTIM0, LL_GPTIM_CHANNEL_1, &ICInitStructer);
    
    ICInitStructer.ICPolarity    = LL_GPTIM_IC_POLARITY_RISING;          //上升沿捕获
    ICInitStructer.ICActiveInput = LL_GPTIM_CC2_MODE_INPUT_TI2;          //CC2配置为输入，IC1映射到TI2
    LL_GPTIM_IC_Init(GPTIM0, LL_GPTIM_CHANNEL_2, &ICInitStructer);
    
    LL_GPTIM_ClearFlag_UPDATE(GPTIM0); //清除计数器中断标志位
    LL_GPTIM_EnableCounter(GPTIM0);    //使能定时器
}

int16_t GPTIM_Read(void)
{
    int16_t temp;
    temp = GPTIM0->CNT;
    GPTIM0->CNT = 0;
    return temp;
}
