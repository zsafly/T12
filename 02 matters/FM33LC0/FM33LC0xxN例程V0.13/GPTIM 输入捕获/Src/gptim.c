#include "gptim.h"
#include "main.h"

void GPTIM_Init(void)
{
    LL_GPTIM_InitTypeDef        InitStructer;    
    
    InitStructer.Prescaler             = 7999;                                         //分频系数8000
    InitStructer.CounterMode           = LL_GPTIM_COUNTER_DIRECT_UP;                    //向上计数
    InitStructer.Autoreload            = 999;                                          //自动重装载值1000
    InitStructer.ClockDivision         = LL_GPTIM_CLOCKDIVISION_DIV1;                   //死区和滤波设置
    InitStructer.AutoreloadState       = DISABLE;                                      //自动重装载禁止preload
    LL_GPTIM_Init(GPTIM0, &InitStructer);
    
    NVIC_DisableIRQ(GPTIM0_IRQn);
    NVIC_SetPriority(GPTIM0_IRQn,2);//中断优先级配置
    NVIC_EnableIRQ(GPTIM0_IRQn);	
  
    LL_GPTIM_ClearFlag_UPDATE(GPTIM0);  //清除计数器中断标志位
  
    LL_GPTIM_EnableIT_UPDATE(GPTIM0); //开启计数器中断
 
    LL_GPTIM_EnableCounter(GPTIM0); //使能定时器
}

void GPTIM_PWM_Init(void)
{
    LL_GPTIM_InitTypeDef        InitStructer1;    
    LL_GPTIM_OC_InitTypeDef     InitStructer2;
    LL_GPIO_InitTypeDef         GPIO_InitStruct={0};
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    GPIO_InitStruct.RemapPin = ENABLE;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);  //CH1 
    
    InitStructer1.Prescaler             = 7999;                                         //分频系数8000
    InitStructer1.CounterMode           = LL_GPTIM_COUNTER_DIRECT_UP;                    //向上计数
    InitStructer1.Autoreload            = 999;                                          //自动重装载值1000
    InitStructer1.ClockDivision         = LL_GPTIM_CLOCKDIVISION_DIV1;                   //死区和滤波分频
    InitStructer1.AutoreloadState       = ENABLE;                                       //预装载preload使能                        
    LL_GPTIM_Init(GPTIM0, &InitStructer1);
    
    InitStructer2.OCMode       = LL_GPTIM_OC_MODE_PWM1;                    //输出比较模式PWM1
    InitStructer2.OCETRFStatus = DISABLE;                                  //OC1REF不受ETR影响
    InitStructer2.OCFastMode   = DISABLE;                                  //关闭快速使能  
    InitStructer2.CompareValue = 500;                                      //比较值500
    InitStructer2.OCPolarity   = LL_GPTIM_OC_POLARITY_NOMAL;               //OC 正常输出
    InitStructer2.OCPreload    = DISABLE;                                  //OC preload 无效
    LL_GPTIM_OC_Init(GPTIM0, LL_GPTIM_CHANNEL_1, &InitStructer2);
 
    LL_GPTIM_EnableCounter(GPTIM0); //使能定时器
}

void GPTIM_CAPTURE_Init(void)
{   
    LL_GPTIM_InitTypeDef        InitStructer1;    
    LL_GPTIM_IC_InitTypeDef     InitStructer2;
    LL_GPTIM_SlaveInitTypeDef   InitStructer3;
    LL_GPIO_InitTypeDef         GPIO_InitStruct={0};
    
    GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = DISABLE;
    GPIO_InitStruct.RemapPin = ENABLE;
    
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);  //CH1 
    
    InitStructer1.Prescaler             = 0;                                            //不分频
    InitStructer1.CounterMode           = LL_GPTIM_COUNTER_DIRECT_UP;                  //向上计数
    InitStructer1.Autoreload            = 65535;                                      //自动装载值65536
    InitStructer1.ClockDivision         = LL_GPTIM_CLOCKDIVISION_DIV1;                 // 死区和数字滤波分频
    InitStructer1.AutoreloadState       = ENABLE;                                     //自动重装载ARPE使能
    LL_GPTIM_Init(GPTIM0, &InitStructer1);
    
    InitStructer3.SlaveMode     = LL_GPTIM_SLAVE_MODE_TRGI_RISE_RST;   //从机复位模式
    InitStructer3.TriggerSrc    = LL_GPTIM_TIM_TS_TI1FP1;              //触发源选择 TI1FP1
    InitStructer3.TriggerDelay  = DISABLE;                            //TRGI延迟禁止
    LL_GPTIM_SlaveMode_Init(GPTIM0, &InitStructer3);
    
    InitStructer2.ICPolarity    = LL_GPTIM_IC_POLARITY_RISING;          //上升沿捕获
    InitStructer2.ICActiveInput = LL_GPTIM_CC1_MODE_INPUT_TI1;          //CC1配置为输入，IC1映射到TI1
    InitStructer2.ICPrescaler   = LL_GPTIM_IC_PRESCALER_DIV_1;          //输入捕捉分频
    InitStructer2.ICFilter      = LL_GPTIM_IC_FILTER_FDIV1;             //输入捕捉滤波配置
    InitStructer2.CaptureState  = ENABLE;                              //使能CC1通道
    LL_GPTIM_IC_Init(GPTIM0, LL_GPTIM_CHANNEL_1, &InitStructer2);
    
    NVIC_DisableIRQ(GPTIM0_IRQn);
    NVIC_SetPriority(GPTIM0_IRQn, 2);//中断优先级配置
    NVIC_EnableIRQ(GPTIM0_IRQn);
    
    LL_GPTIM_ClearFlag_CC(GPTIM0, LL_GPTIM_CHANNEL_1);     //清除CC1捕捉标志      
    LL_GPTIM_EnableIT_CC(GPTIM0, LL_GPTIM_CHANNEL_1);      //使能CC1捕捉中断
    
    LL_GPTIM_EnableCounter(GPTIM0); //使能定时器
}

