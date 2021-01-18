#include "lpuart.h"
#include "main.h"

void LPUART_Init(LPUART_Type* LPUARTx)
{
    LL_LPUART_InitTypeDef  InitStructer = {0};
    LL_GPIO_InitTypeDef  GPIO_InitStruct = {0};
    volatile uint8_t tmp08;
      
    if(LPUARTx==LPUART0)
    {
        GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;              //���ֹ���
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;     //�������
        GPIO_InitStruct.Pull = ENABLE;                            //����ʹ������
        GPIO_InitStruct.RemapPin = ENABLE;                        //ʹ�ܶ������ֹ���  
        LL_GPIO_Init(GPIOA,&GPIO_InitStruct);                     //PA13
        
        GPIO_InitStruct.Pin = LL_GPIO_PIN_14;                     
        GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;               //���ֹ���
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;      //�������
        GPIO_InitStruct.Pull = DISABLE;                            //���Ͳ�����
        GPIO_InitStruct.RemapPin = ENABLE;                         //ʹ�ܶ������ֹ���  
        LL_GPIO_Init(GPIOA,&GPIO_InitStruct);                      //PA14
    }
    if(LPUARTx==LPUART1)
    {
        GPIO_InitStruct.Pin = LL_GPIO_PIN_13;                           
        GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;                //���ֹ���
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;       //�������
        GPIO_InitStruct.Pull = ENABLE;                              //����ʹ������
        GPIO_InitStruct.RemapPin = ENABLE;                          //ʹ�ܶ������ֹ��� 
        LL_GPIO_Init(GPIOB,&GPIO_InitStruct);                       //PB13
      
        GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;                //���ֹ���
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;       //�������
        GPIO_InitStruct.Pull = DISABLE;                             //���Ͳ�����
        GPIO_InitStruct.RemapPin = ENABLE;                          //ʹ�ܶ������ֹ��� 
        LL_GPIO_Init(GPIOB,&GPIO_InitStruct);                       //PB14
    }
    InitStructer.ClockSrc 			= LL_RCC_LPUART_OPERTION_CLOCK_SOURCE_LSCLK;  //ʱ��ԴLSCLK
    InitStructer.BaudRate            = LL_LPUART_BAUDRATE_9600;  //������9600
	  InitStructer.DataWidth           = LL_LPUART_DATAWIDTH_8B;   //8λ����λ
	  InitStructer.StopBits            = LL_LPUART_STOP_1BITS;     //1λֹͣλ
	  InitStructer.Parity              = LL_LPUART_PARITY_EVEN ;   //żУ��
	  InitStructer.TransferDirection   = LL_LPUART_DIRECTION_TX_RX;   //ʹ�ܷ��ͺͽ���
    LL_LPUART_Init(LPUARTx,&InitStructer);     
    
}

void LPUART_Test(LPUART_Type* LPUARTx)
{
    uint8_t TestTxData[12] = {0x55,0x5A,0x53};
    uint8_t i;
	  volatile uint8_t tmp;
    
    
    for(i=0; i<3; i++)
	  {
      LL_LPUART_TransmitData(LPUARTx,TestTxData[i]);//����������д�뷢�ͼĴ���
      while(LL_LPUART_IsActiveFlag_TXSE(LPUARTx)==0);//�ȴ��������
      LL_LPUART_ClearFlag_TXSE(LPUARTx);
	  }  
 
    while(1)
	  {
		  if(LL_LPUART_IsActiveFlag_RXBF(LPUARTx))		//�ȴ����յ�һ���ֽ�
		  { 
			  tmp = LL_LPUART_ReceiveData(LPUARTx);		//LPUART��������
        LL_LPUART_ClearFlag_RXBF(LPUARTx);    
		  } 
	  }   
}
