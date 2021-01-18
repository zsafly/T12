#include "rchftrim.h"
#include "user_init.h"

static void Soft_DelayUs(uint16_t us)
{
    uint32_t count;
    
    switch (RCHF_CLOCK)
    {
        case LL_RCC_RCHF_FREQUENCY_8MHZ: count = us * 1; break;
        case LL_RCC_RCHF_FREQUENCY_16MHZ: count = us * 2; break;
        case LL_RCC_RCHF_FREQUENCY_24MHZ: count = us * 3; break;
        default: count = us * 1; break;
    }
    
    while (count--)
    {
        __NOP(); __NOP(); __NOP(); __NOP();
    }
}

static int32_t GPTIMxCapture(GPTIM_Type *GPTIMx, int32_t timeout)
{
    int32_t count;
    uint32_t capture[2];
    
    LL_GPTIM_ClearFlag_CC(GPTIMx, LL_GPTIM_CHANNEL_1);
    LL_GPTIM_EnableNormalChannelOutput(GPTIMx, LL_GPTIM_CHANNEL_1);
    LL_GPTIM_EnableCounter(GPTIMx);

    while ((timeout--) > 0)
    {
        Soft_DelayUs(10);   // �����ʱ: >10us��ѯһ����־
        if (SET == LL_GPTIM_IsActiveFlag_CC(GPTIMx, LL_GPTIM_CHANNEL_1))
        {
            LL_GPTIM_ClearFlag_CC(GPTIMx, LL_GPTIM_CHANNEL_1);
            break;                    
        }
    }
    capture[0] = LL_GPTIM_GetCompareCH1(GPTIMx);
    
    count = 16;
    while ((count--) > 0)
    {
        while ((timeout--) > 0)
        {
            Soft_DelayUs(10);   // �����ʱ: >10us��ѯһ����־
            if (SET == LL_GPTIM_IsActiveFlag_CC(GPTIMx, LL_GPTIM_CHANNEL_1))
            {
                LL_GPTIM_ClearFlag_CC(GPTIMx, LL_GPTIM_CHANNEL_1);
                break;                    
            }
        }
    }
    capture[1] = LL_GPTIM_GetCompareCH1(GPTIMx);

    LL_GPTIM_DisableCounter(GPTIMx);
    LL_GPTIM_DisableNormalChannelOutput(GPTIMx, LL_GPTIM_CHANNEL_1);
    if (timeout <= 0)
    {
        return -1;
    }
    else
    {
        return (65536 + capture[1] - capture[0]) % 65536;
    }
}

static void GPTIMxConfig(GPTIM_Type *GPTIMx, uint8_t psc)
{
    if (GPTIMx == GPTIM0)
    {
        LL_RCC_Group4_EnableBusClock(LL_RCC_BUS4_CLOCK_GTIM0);
        NVIC_DisableIRQ(GPTIM0_IRQn);
        
        LL_GPTIM_SetGPTIM0ITR2Input(GPTIM0, LL_GPTIM_ITR2SEL_XTLF);
    }
    else if (GPTIMx == GPTIM1)
    {
        LL_RCC_Group4_EnableBusClock(LL_RCC_BUS4_CLOCK_GTIM1);
        NVIC_DisableIRQ(GPTIM1_IRQn);
        
        LL_GPTIM_SetGPTIM1ITR2Input(GPTIM1, LL_GPTIM_ITR2SEL_XTLF);
    }
    else
    {
        // TODO: Error
        return;
    }
    
    LL_GPTIM_SetSlaveMode(GPTIMx, LL_GPTIM_SLAVE_MODE_PROHIBITED);
    LL_GPTIM_SetTriggerInput(GPTIMx, LL_GPTIM_TIM_TS_ITR2);
    
    LL_GPTIM_EnableARRPreload(GPTIMx);          // Ԥװ��ʹ��
    LL_GPTIM_SetCounter(GPTIMx, 0);             // �趨����ֵ
    LL_GPTIM_SetAutoReload(GPTIMx, 0xffff);     // �Զ�����ֵ
    LL_GPTIM_SetPrescaler(GPTIMx, psc - 1);     // Ԥ��Ƶ�趨
    LL_GPTIM_SetChannelMode(GPTIMx, 
        LL_GPTIM_CC_MODE_INPUT_TRC, LL_GPTIM_CHANNEL_1);
    LL_GPTIM_SetICModePrescaler(GPTIMx,
        LL_GPTIM_IC_PRESCALER_DIV_8, LL_GPTIM_CHANNEL_1);
    
    LL_GPTIM_GenerateEvent_UPDATE(GPTIMx);
}

//xtlf��32768Hzʱ����Ϊ�ο�Դ
//��ʱ��8��Ƶ��׽����׽16�Σ�ʵ�ֲ�׽XTLF 128��Ƶ�ź�
//��������������APB����Ƶ�����
//ClkMode 1 = 8M
//ClkMode 2 = 16M
//ClkMode 3 = 24M
int32_t RchfAdjust(GPTIM_Type *GPTIMx, uint32_t clkMode)
{
    const uint32_t TRY_TIMES = 5;   // ����ʱʱ���Դ���
    int32_t captureTemp;
    uint8_t tempbyte, rchfTrim;
    uint32_t m;
    
    // FDETO ͣ����ģ�����
    if (RESET == LL_RCC_IsActiveFlag_XTLF_Vibrating())
    {
        // ��⵽XTLFͣ��ֱ���˳�
		return -1;
    }
    
    switch(clkMode)
	{
		case LL_RCC_RCHF_FREQUENCY_8MHZ://8
			GPTIMxConfig(GPTIMx, 1);//����Դ1��Ƶ
			break;
		
		case LL_RCC_RCHF_FREQUENCY_16MHZ://16/2
			GPTIMxConfig(GPTIMx, 2);//����Դ2��Ƶ
			break;
		
		case LL_RCC_RCHF_FREQUENCY_24MHZ://24/3
			GPTIMxConfig(GPTIMx, 3);//����Դ3��Ƶ
			break;
		
		default:// �Ƿ�������ֱ���˳�
			return -2;	
	}	
    
    for (m = 0; m < TRY_TIMES; m++)
    {
        LL_RCC_ClearFlag_XTLF_Fail();
        captureTemp = GPTIMxCapture(GPTIM0, 1000);
        if (SET == LL_RCC_IsActiveFlag_XTLF_Fail())
        {
            // �����ڼ�ֹͣ��־����ֱ���˳�
            return -3;
        }
        
        if (captureTemp < 0)
        {
            continue;
        }
        
        // 31250 = (1/(32768/8/16))/(1/8 000 000)
        // 117 = 31250 * (30KHz/8MHz) (0.385%�ľ���)
        // 156.25 = (40KHz/8MHz) * 31250
        if ((captureTemp > (31250 - 117)) &&
            (captureTemp < (31250 + 117)))
		{
            // ����������ֱֵ�ӷ���
			break;
		}
		else
		{
			rchfTrim = LL_RCC_GetRCHFTrimValue();	//��ȡRCHFУ׼ֵ
            
			if (captureTemp > 31250)
			{
				captureTemp = captureTemp - 31250;
				tempbyte = (uint8_t)(captureTemp / 156.25 + 0.5);
				
				if ( tempbyte > 0x20)
                {
                    tempbyte = 0x20;
				}
                
				if (rchfTrim >= tempbyte)
				{
					LL_RCC_SetRCHFTrimValue(rchfTrim - tempbyte); // ����RCHFУ׼ֵ
				}
				else
				{
					LL_RCC_SetRCHFTrimValue(0x00); // ����RCHFУ׼ֵ
				}			
			}
			else
			{
				captureTemp = 31250 - captureTemp;
				tempbyte = (uint8_t)(captureTemp / 156.25 + 0.5);
				
				if (tempbyte > 0x20)
                {
                    tempbyte = 0x20;
                }
				
				if ((rchfTrim + tempbyte) <= 0x7F)
				{
					LL_RCC_SetRCHFTrimValue(rchfTrim + tempbyte);//����RCHFУ׼ֵ
				}
				else
				{
					LL_RCC_SetRCHFTrimValue(0x7F);//����RCHFУ׼ֵ
				}
			}
			
			if (m == (TRY_TIMES - 1))	//δ�ҵ�����ֵ,�������2�ε�ֵȡƽ��
			{
				rchfTrim += LL_RCC_GetRCHFTrimValue();
				LL_RCC_SetRCHFTrimValue((uint8_t)(rchfTrim / 2.0 + 0.5));				
			}
		}
    }
    
    return 0;
}
