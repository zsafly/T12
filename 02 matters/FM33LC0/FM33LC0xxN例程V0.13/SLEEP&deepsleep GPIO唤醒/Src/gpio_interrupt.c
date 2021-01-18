#include "user_init.h"
#include "main.h"
#include "gpio_interrupt.h"

//�����ж�
void GPIO_IRQHandler(void)
{  
    if(SET == LL_EXTI_IsActiveFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_9))
    {
        LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_9);
    } 
}
    

// �ⲿ�����жϳ�ʼ��
void GPIO_interrupt_init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};    
    
    //���ű��ش���ѡ��
    LL_RCC_Enable_SleepmodeExternalInterrupt();//����ʹ���ⲿ�жϲ���
    LL_RCC_Group1_EnableOperationClock(LL_RCC_OPERATION1_CLOCK_EXTI);//EXTI����ʱ��ʹ��    
    
    //�õ���GPIO����    ��Ϊ���� 
    GPIO_InitStruct.Pin = LINE_9_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(LINE_9_GPIO, &GPIO_InitStruct);


    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_9, LL_GPIO_EXTI_TRIGGER_NONE);//�رձ��ش���
    //ÿ��LINE ֻ��ѡһ������ 
    LL_GPIO_SetExitLine0(GPIO_COMMON, LL_GPIO_EXTI_LINE_9_PC6);//�ж�����ѡ��
    LL_EXTI_EnableDigitalFilter(GPIO_COMMON, LL_GPIO_EXTI_LINE_9);//EXTI�����˲�����
    LL_EXTI_SetTrigEdge(GPIO_COMMON, LL_GPIO_EXTI_LINE_9, LL_GPIO_EXTI_TRIGGER_FALLING);//����ѡ��    
    LL_EXTI_ClearFlag(GPIO_COMMON, LL_GPIO_EXTI_LINE_9);//����жϱ�־
    
    
    /*NVIC�ж�����*/
    NVIC_DisableIRQ(GPIO_IRQn);
    NVIC_SetPriority(GPIO_IRQn,2);//�ж����ȼ�����
    NVIC_EnableIRQ(GPIO_IRQn);
}
