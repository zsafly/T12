#include "TestI2C.h"


void I2C_Init(void)
{
	LL_I2C_SlaveMode_InitTypeDef   IICInitStructer;    
	LL_GPIO_InitTypeDef    GPIO_InitStruct={0};

	GPIO_InitStruct.Pin = LL_GPIO_PIN_11|LL_GPIO_PIN_12;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = DISABLE;
	LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
	IICInitStructer.ACK= ENABLE;
	IICInitStructer.OwnAddr = 0X20;
	IICInitStructer.OwnAddrSize10bit = DISABLE;
	IICInitStructer.SCLSEN = DISABLE;
	LL_I2C_SlaveMode_Init(I2C,&IICInitStructer);	
}

uint8_t Test_I2C(void)
{
	uint8_t writedata[2]={0x55,0xaa};
	uint8_t Result = 0;
	uint8_t tmp;
	I2C_Init();
	
	while(!LL_I2C_SlaveMode_IsActiveFlag_AddrMatched(I2C));
	tmp = LL_I2C_SlaveMode_ReadDataBuff(I2C);
	LL_I2C_SlaveMode_ClearFlag_AddrMatched(I2C);
	LL_I2C_SlaveMode_ClearFlag_ReceiveCompleted(I2C);
	
	LL_I2C_SlaveMode_WriteDataBuff(I2C,writedata[0]);
	while(!LL_I2C_SlaveMode_IsActiveFlag_TransmitCompleted(I2C));
	LL_I2C_SlaveMode_ClearFlag_TransmitCompleted(I2C);
	
	LL_I2C_SlaveMode_WriteDataBuff(I2C,writedata[1]);
	while(!LL_I2C_SlaveMode_IsActiveFlag_TransmitCompleted(I2C));
	LL_I2C_SlaveMode_ClearFlag_TransmitCompleted(I2C);
	
	
	return Result;
}
