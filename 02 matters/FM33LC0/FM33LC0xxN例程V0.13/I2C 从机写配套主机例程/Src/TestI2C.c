#include "TestI2C.h"

#define	I2CREAD		1	//I2C读操作
#define	I2CWRITE	0	//I2C写操作

#define	STARTBIT	0	
#define	RESTARTBIT	1
#define	STOPBIT		2

#define DEVICE_ADD	0x40	//器件地址
#define ADDRLEN	1		//数据地址长度为1字节

uint8_t I2C_Send_Bit(uint8_t BIT_def ) 
{
	
	switch(BIT_def)
	{
		case STARTBIT:
					LL_I2C_MasterMode_Enable_I2C_Start(I2C);
					while(!LL_I2C_MasterMode_IsActiveFlag_Start(I2C));
			break;
		
		case RESTARTBIT:
					LL_I2C_MasterMode_Enable_I2C_Rstart(I2C);
					while(!LL_I2C_MasterMode_IsActiveFlag_Start(I2C));		
			break;
		
		case STOPBIT:
					LL_I2C_MasterMode_Enable_I2C_Stop(I2C);
					while(!LL_I2C_MasterMode_IsActiveFlag_Stop(I2C));		
			break;
		
		default:
			break;
	}
		
	return 0; //ok

}

uint8_t I2C_Send_Byte( uint8_t x_byte ) 
{

	LL_I2C_MasterMode_WriteDataBuff(I2C,x_byte);

	while(!LL_I2C_MasterMode_IsActiveFlag_TransmitCompleted(I2C));
	LL_I2C_MasterMode_ClearFlag_TransmitCompleted(I2C);

	if(!LL_I2C_MasterMode_IsActiveFlag_Nack(I2C))
	{
		return 0;
	}
	else
	{
		LL_I2C_MasterMode_ClearFlag_Nack(I2C);
		return 1;
	}

}

uint8_t I2C_Receive_Byte( uint8_t *x_byte ) 
{

	//i2c en, rcen
	LL_I2C_MasterMode_EnableReceive(I2C);
	while(!LL_I2C_MasterMode_IsActiveFlag_ReceiveCompleted(I2C));
	LL_I2C_MasterMode_ClearFlag_ReceiveCompleted(I2C);
	*x_byte=LL_I2C_MasterMode_ReadDataBuff(I2C);
	return 0;
}

uint8_t Sendaddr( uint16_t Device, uint8_t AddrLen, uint8_t Opt ) 
{
	uint16_t result, Devi_Addr;
	
	Devi_Addr = Device;


	if( Opt == I2CREAD ) //读操作
	{
	//-------------- start bit -------------
	result = I2C_Send_Bit( STARTBIT );//发送起始位
	if( result != 0 ) return 1; //failure.
	
	//-------------- disable read -------------
	LL_I2C_MasterMode_DisableReceive(I2C);
	//-------------- device addr -------------
	if(AddrLen == 2)					
	{
		result = I2C_Send_Byte( Devi_Addr>>8 |1 ); 
		if( result != 0 ) return 2; //failure.
		result = I2C_Send_Byte( Devi_Addr>>0 ); 
		if( result != 0 ) return 2; //failure.
	}
	else
	{
		result = I2C_Send_Byte( Devi_Addr>>0 |1 ); 
		if( result != 0 ) return 2; //failure
	}
	}

	
	if( Opt == I2CWRITE ) //读操作
	{
	//-------------- start bit -------------
	result = I2C_Send_Bit( STARTBIT );//发送起始位
	if( result != 0 ) return 1; //failure.
	
	//-------------- disable read -------------
	LL_I2C_MasterMode_DisableReceive(I2C);
	//-------------- device addr -------------
	if(AddrLen == 2)					
	{
		result = I2C_Send_Byte( Devi_Addr>>8 ); 
		if( result != 0 ) return 2; //failure.
		result = I2C_Send_Byte( Devi_Addr>>0 ); 
		if( result != 0 ) return 2; //failure.
	}
	else
	{
		result = I2C_Send_Byte( Devi_Addr>>0 ); 
		if( result != 0 ) return 2; //failure
	}
	}	
		
	return 0; //ok
}



uint8_t I2C_Read_Bottom(uint16_t Device, uint8_t AddrLen, uint8_t *Buf, uint8_t Len)
{
	uint8_t k, n, status;
	
	if(Len > 128) return 0xFF;//一次最多操作128字节
	
	for( k=0; k<3; k++ )//每遍最多读3次
	{
		status = 0;
		if( Sendaddr( Device, AddrLen, I2CREAD ) )
      status = 1; //写入失败
		else 
		{
			for( n=0; n<Len; n++ )
			{
				if( n < (Len-1) )
					LL_I2C_MasterMode_SetMasterRespond(I2C,LL_I2C_SSP_MASTER_RESPOND_ACK);
				else
					LL_I2C_MasterMode_SetMasterRespond(I2C,LL_I2C_SSP_MASTER_RESPOND_NACK);
				
				//接收一个字节
				if( I2C_Receive_Byte( Buf+n ) ) 
        {
          status = 1; 
          break;
        } 
	
			}
		}
		//发送停止位
		if( I2C_Send_Bit( STOPBIT ) ) 
      status = 1;	//失败
		
		if( status == 0 ) break;//读正确
	}
	
	return( status );
}


void I2C_Init(void)
{
	LL_I2C_MasterMode_InitTypeDef   IICInitStructer;    
	LL_GPIO_InitTypeDef    GPIO_InitStruct={0};

	GPIO_InitStruct.Pin = LL_GPIO_PIN_11|LL_GPIO_PIN_12;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_DIGITAL;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = DISABLE;
	LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
	IICInitStructer.ClockSource = LL_RCC_I2C_OPERATION_CLOCK_SOURCE_APBCLK1;
	IICInitStructer.BaudRate = 100000;
	LL_I2C_MasterMode_Init(I2C,&IICInitStructer);	
}

uint8_t Test_I2C(void)
{
	uint16_t Device = DEVICE_ADD;
	uint8_t AddrLen = ADDRLEN;
	uint8_t Buf[2]={0};
	uint8_t Len = 0;
	uint8_t Result = 0;
	
	
	Len = 2;
	I2C_Init();
		
	Result=I2C_Read_Bottom(Device,AddrLen,Buf,Len);
	return Result;
}
