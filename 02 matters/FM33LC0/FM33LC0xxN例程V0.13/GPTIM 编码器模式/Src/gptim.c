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
    
    BaseInitStructer.ClockDivision = LL_GPTIM_CLOCKDIVISION_DIV1;   //����Ƶ
    BaseInitStructer.CounterMode = LL_GPTIM_COUNTER_DIRECT_UP;      //���ϼ���
    BaseInitStructer.Prescaler = 0;                                 //����Դ��Ƶϵ��
    BaseInitStructer.Autoreload = 65535;                            //�Զ���װ��ֵ
    BaseInitStructer.AutoreloadState = ENABLE;                      //�Զ���װ��
    LL_GPTIM_Init(GPTIM0, &BaseInitStructer);
  
    SlaveInitStructer.SlaveMode = LL_GPTIM_SLAVE_MODE_TI2FP2_CNT_TI1FP1_CNT;
    LL_GPTIM_SlaveMode_Init(GPTIM0, &SlaveInitStructer);
    
    ICInitStructer.ICPrescaler   = LL_GPTIM_IC_PRESCALER_DIV_1;          //���벶׽��Ƶ
    ICInitStructer.ICFilter      = LL_GPTIM_IC_FILTER_FDIV1;             //���벶׽�˲�����
    ICInitStructer.CaptureState  = ENABLE;                              //ʹ��CCxͨ��
    
    ICInitStructer.ICPolarity    = LL_GPTIM_IC_POLARITY_RISING;          //�����ز���
    ICInitStructer.ICActiveInput = LL_GPTIM_CC1_MODE_INPUT_TI1;          //CC1����Ϊ���룬IC1ӳ�䵽TI1
    LL_GPTIM_IC_Init(GPTIM0, LL_GPTIM_CHANNEL_1, &ICInitStructer);
    
    ICInitStructer.ICPolarity    = LL_GPTIM_IC_POLARITY_RISING;          //�����ز���
    ICInitStructer.ICActiveInput = LL_GPTIM_CC2_MODE_INPUT_TI2;          //CC2����Ϊ���룬IC1ӳ�䵽TI2
    LL_GPTIM_IC_Init(GPTIM0, LL_GPTIM_CHANNEL_2, &ICInitStructer);
    
    LL_GPTIM_ClearFlag_UPDATE(GPTIM0); //����������жϱ�־λ
    LL_GPTIM_EnableCounter(GPTIM0);    //ʹ�ܶ�ʱ��
}

int16_t GPTIM_Read(void)
{
    int16_t temp;
    temp = GPTIM0->CNT;
    GPTIM0->CNT = 0;
    return temp;
}
