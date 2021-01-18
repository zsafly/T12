#include "gptim.h"
#include "main.h"

void GPTIM_Init(void)
{
    LL_GPTIM_InitTypeDef        InitStructer;    
    
    InitStructer.Prescaler             = 7999;                                         //��Ƶϵ��8000
    InitStructer.CounterMode           = LL_GPTIM_COUNTER_DIRECT_UP;                    //���ϼ���
    InitStructer.Autoreload            = 999;                                          //�Զ���װ��ֵ1000
    InitStructer.ClockDivision         = LL_GPTIM_CLOCKDIVISION_DIV1;                   //�������˲�����
    InitStructer.AutoreloadState       = DISABLE;                                      //�Զ���װ�ؽ�ֹpreload
    LL_GPTIM_Init(GPTIM0, &InitStructer);
    
    NVIC_DisableIRQ(GPTIM0_IRQn);
    NVIC_SetPriority(GPTIM0_IRQn,2);//�ж����ȼ�����
    NVIC_EnableIRQ(GPTIM0_IRQn);	
  
    LL_GPTIM_ClearFlag_UPDATE(GPTIM0);  //����������жϱ�־λ
  
    LL_GPTIM_EnableIT_UPDATE(GPTIM0); //�����������ж�
 
    LL_GPTIM_EnableCounter(GPTIM0); //ʹ�ܶ�ʱ��
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
    
    InitStructer1.Prescaler             = 7999;                                         //��Ƶϵ��8000
    InitStructer1.CounterMode           = LL_GPTIM_COUNTER_DIRECT_UP;                    //���ϼ���
    InitStructer1.Autoreload            = 999;                                          //�Զ���װ��ֵ1000
    InitStructer1.ClockDivision         = LL_GPTIM_CLOCKDIVISION_DIV1;                   //�������˲���Ƶ
    InitStructer1.AutoreloadState       = ENABLE;                                       //Ԥװ��preloadʹ��                        
    LL_GPTIM_Init(GPTIM0, &InitStructer1);
    
    InitStructer2.OCMode       = LL_GPTIM_OC_MODE_PWM1;                    //����Ƚ�ģʽPWM1
    InitStructer2.OCETRFStatus = DISABLE;                                  //OC1REF����ETRӰ��
    InitStructer2.OCFastMode   = DISABLE;                                  //�رտ���ʹ��  
    InitStructer2.CompareValue = 500;                                      //�Ƚ�ֵ500
    InitStructer2.OCPolarity   = LL_GPTIM_OC_POLARITY_NOMAL;               //OC �������
    InitStructer2.OCPreload    = DISABLE;                                  //OC preload ��Ч
    LL_GPTIM_OC_Init(GPTIM0, LL_GPTIM_CHANNEL_1, &InitStructer2);
 
    LL_GPTIM_EnableCounter(GPTIM0); //ʹ�ܶ�ʱ��
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
    
    InitStructer1.Prescaler             = 0;                                            //����Ƶ
    InitStructer1.CounterMode           = LL_GPTIM_COUNTER_DIRECT_UP;                  //���ϼ���
    InitStructer1.Autoreload            = 65535;                                      //�Զ�װ��ֵ65536
    InitStructer1.ClockDivision         = LL_GPTIM_CLOCKDIVISION_DIV1;                 // �����������˲���Ƶ
    InitStructer1.AutoreloadState       = ENABLE;                                     //�Զ���װ��ARPEʹ��
    LL_GPTIM_Init(GPTIM0, &InitStructer1);
    
    InitStructer3.SlaveMode     = LL_GPTIM_SLAVE_MODE_TRGI_RISE_RST;   //�ӻ���λģʽ
    InitStructer3.TriggerSrc    = LL_GPTIM_TIM_TS_TI1FP1;              //����Դѡ�� TI1FP1
    InitStructer3.TriggerDelay  = DISABLE;                            //TRGI�ӳٽ�ֹ
    LL_GPTIM_SlaveMode_Init(GPTIM0, &InitStructer3);
    
    InitStructer2.ICPolarity    = LL_GPTIM_IC_POLARITY_RISING;          //�����ز���
    InitStructer2.ICActiveInput = LL_GPTIM_CC1_MODE_INPUT_TI1;          //CC1����Ϊ���룬IC1ӳ�䵽TI1
    InitStructer2.ICPrescaler   = LL_GPTIM_IC_PRESCALER_DIV_1;          //���벶׽��Ƶ
    InitStructer2.ICFilter      = LL_GPTIM_IC_FILTER_FDIV1;             //���벶׽�˲�����
    InitStructer2.CaptureState  = ENABLE;                              //ʹ��CC1ͨ��
    LL_GPTIM_IC_Init(GPTIM0, LL_GPTIM_CHANNEL_1, &InitStructer2);
    
    NVIC_DisableIRQ(GPTIM0_IRQn);
    NVIC_SetPriority(GPTIM0_IRQn, 2);//�ж����ȼ�����
    NVIC_EnableIRQ(GPTIM0_IRQn);
    
    LL_GPTIM_ClearFlag_CC(GPTIM0, LL_GPTIM_CHANNEL_1);     //���CC1��׽��־      
    LL_GPTIM_EnableIT_CC(GPTIM0, LL_GPTIM_CHANNEL_1);      //ʹ��CC1��׽�ж�
    
    LL_GPTIM_EnableCounter(GPTIM0); //ʹ�ܶ�ʱ��
}

