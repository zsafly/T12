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
    
    BaseInitStructer.ClockSource = LL_RCC_ATIME_OPERATION_CLOCK_SOURCE_APBCLK2; //ʱ��Դѡ��APB2
    BaseInitStructer.ClockDivision = LL_ATIM_CLOCKDIVISION_DIV1;                //����ʱ�ӷ�Ƶ
    BaseInitStructer.CounterMode = LL_ATIM_COUNTER_DIRECT_UP;                   //���ϼ���
    BaseInitStructer.Prescaler = 0;                                             //����Դ��Ƶϵ��
    BaseInitStructer.Autoreload = 65535;                                        //�Զ���װ��ֵ
    BaseInitStructer.AutoreloadState = ENABLE;                                  //�Զ���װ��
    LL_ATIM_Init(ATIM,&BaseInitStructer);
  
    SlaveInitStructer.SlaveMode = LL_ATIM_SLAVE_MODE_TI2FP2_CNT_TI1FP1_CNT;
    LL_ATIM_SlaveMode_Init(ATIM, &SlaveInitStructer);
    
    ICInitStructer.ICPrescaler   = LL_ATIM_IC_PRESCALER_DIV_1;          //���벶׽��Ƶ
    ICInitStructer.ICFilter      = LL_ATIM_IC_FILTER_FDIV1;             //���벶׽�˲�����
    ICInitStructer.CaptureState  = ENABLE;                              //ʹ��CCxͨ��
    
    ICInitStructer.ICPolarity    = LL_ATIM_IC_POLARITY_RISING;          //�����ز���
    ICInitStructer.ICActiveInput = LL_ATIM_CC1_MODE_INPUT_TI1;          //CC1����Ϊ���룬IC1ӳ�䵽TI1
    LL_ATIM_IC_Init(ATIM, LL_ATIM_CHANNEL_1, &ICInitStructer);
    
    ICInitStructer.ICPolarity    = LL_ATIM_IC_POLARITY_RISING;          //�����ز���
    ICInitStructer.ICActiveInput = LL_ATIM_CC2_MODE_INPUT_TI2;          //CC2����Ϊ���룬IC1ӳ�䵽TI2
    LL_ATIM_IC_Init(ATIM, LL_ATIM_CHANNEL_2, &ICInitStructer);
    
    LL_ATIM_ClearFlag_UPDATE(ATIM); //����������жϱ�־λ
    LL_ATIM_EnableCounter(ATIM);    //ʹ�ܶ�ʱ��
}

int16_t ATIM_Read(void)
{
    int16_t temp;
    temp = ATIM->CNT;
    ATIM->CNT = 0;
    return temp;
}
