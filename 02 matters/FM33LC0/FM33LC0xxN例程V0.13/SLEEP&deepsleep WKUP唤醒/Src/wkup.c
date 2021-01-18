#include "user_init.h"
#include "main.h"
#include "wkup.h"

void NMI_Handler(void)
{
    //NWKUPĬ�����ӵ���cpu��NMI���������жϣ�����NVIC���ƣ�����ȫ���ж�ʹ�ܿ��ƣ����Ѻ��Ȼ��NMI�ж�
    if( SET == LL_PMU_IsActiveFlag_WakeupPIN(PMU , LL_PMU_WKUP4PIN) )
    {    
        LL_PMU_ClearFlag_WakeupPIN(PMU , LL_PMU_WKUP4PIN);
    }   
}

// WKUP�����жϳ�ʼ��
void WKUP_init(void)
{
LL_GPIO_InitTypeDef GPIO_InitStruct = {0};    

    //WKUP0
    //PA15��Ϊ���� 
    GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    //WKUP ʹ��
    LL_GPIO_SetWkupEntry(GPIO_COMMON, LL_GPIO_WKUP_INT_ENTRY_NMI);//NMI�ж����
    LL_GPIO_SetWkupPolarity(GPIO_COMMON, LL_GPIO_WKUP_4, LL_GPIO_WKUP_POLARITY_FALLING);//�½��ػ���
    LL_GPIO_EnableWkup(GPIO_COMMON, LL_GPIO_WKUP_4);//ʹ��NWKUP����
    

}


/*
//������wkupʹ��38���ж���ڽ����ж� ֻ�о���wkup0 ��wkup1~7���������NMI�ж��Լ���
void WKUP_IRQHandler(void)
{
    if( SET == LL_PMU_IsActiveFlag_WakeupPIN(PMU , LL_PMU_WKUP0PIN) )
    {    
        LL_PMU_ClearFlag_WakeupPIN(PMU , LL_PMU_WKUP0PIN);
    }
}

// �ⲿ�����жϳ�ʼ��
void WKUP_init(void)
{
LL_GPIO_InitTypeDef GPIO_InitStruct = {0};    

    //WKUP0
    //PA15��Ϊ���� 
    GPIO_InitStruct.Pin = LL_GPIO_PIN_15;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = DISABLE;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    //WKUP ʹ��
    LL_GPIO_SetWkupEntry(GPIO_COMMON, LL_GPIO_WKUP_INT_ENTRY_NUM_38);//NMI�ж����
    LL_GPIO_SetWkupPolarity(GPIO_COMMON, LL_GPIO_WKUP_0, LL_GPIO_WKUP_POLARITY_FALLING);//�½��ػ���

	//NVIC�ж�����
	NVIC_DisableIRQ(WKUP_IRQn);
	NVIC_SetPriority(WKUP_IRQn,2);//�ж����ȼ�����
	NVIC_EnableIRQ(WKUP_IRQn);	

    //ʹ��NWKUP����
    LL_GPIO_EnableWkup(GPIO_COMMON, LL_GPIO_WKUP_0);
}
*/
