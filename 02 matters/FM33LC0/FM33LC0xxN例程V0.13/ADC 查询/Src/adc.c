#include "adc.h"
#include "user_init.h"

uint8_t ADCComplete=0;

//uint64_t VSample;
//uint32_t Get122VSample;
//uint32_t GetV;

void AdcInit(void)
{
	LL_GPIO_InitTypeDef         GPIO_InitStruct;	
	LL_ADC_CommonInitTypeDef    ADC_CommonInitStruct;
	LL_ADC_InitTypeDef          ADC_InitStruct ;

	//ÅäÖÃÒý½ÅÎªÄ£Äâ¹¦ÄÜ
	//ADC ADC_0 Òý½Å PC9 
	GPIO_InitStruct.Pin        = LL_GPIO_PIN_9;
	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull       = DISABLE;
	GPIO_InitStruct.RemapPin   = DISABLE;	
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
//	//ADC ADC_1 Òý½Å PC10 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_10;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

//	//ADC ADC_2 Òý½Å PD11 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_11;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
//	
//	//ADC ADC_3 Òý½Å PD0 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_0;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

//	//ADC ADC_4 Òý½Å PD1 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_1;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
//	
//	//ADC ADC_5 Òý½Å PD2 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_2;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

//	//ADC ADC_6 Òý½Å PA13 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_13;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//	
//	//ADC ADC_7 Òý½Å PD14 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_14;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//	//ADC ADC_8 Òý½Å PC7 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_7;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//	
//	//ADC ADC_9 Òý½Å PC8 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_8;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//	
//	//ADC ADC_10 Òý½Å PA15 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_15;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//	//ADC ADC_11 Òý½Å PC6 
//	GPIO_InitStruct.Pin        = LL_GPIO_PIN_6;
//	GPIO_InitStruct.Mode       = LL_GPIO_MODE_ANALOG;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull       = DISABLE;
//	GPIO_InitStruct.RemapPin   = DISABLE;	
//	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	//ADC Ê±ÖÓÉèÖÃ
	ADC_CommonInitStruct.AdcClockSource    = LL_RCC_ADC_OPERATION_CLOCK_PRESCALLER_RCHF; //RCHF
	ADC_CommonInitStruct.AdcClockPrescaler = LL_RCC_ADC_OPERATION_CLOCK_PRESCALER_DIV8; //16·ÖÆµ
	LL_ADC_CommonInit(&ADC_CommonInitStruct);
	
	//ADC ¼Ä´æÆ÷ÉèÖÃ
	  ADC_InitStruct.ADC_ContinuousConvMode  = LL_ADC_CONV_SINGLE;//µ¥´ÎÄ£Ê½
    ADC_InitStruct.ADC_AutoMode            = LL_ADC_SINGLE_CONV_MODE_AUTO;//×Ô¶¯
    ADC_InitStruct.ADC_ScanDirection       = LL_ADC_SEQ_SCAN_DIR_FORWARD;//Í¨µÀÕýÐòÉ¨Ãè
    ADC_InitStruct.ADC_ExternalTrigConv    = LL_ADC_EXT_TRIGGER_NONE;//½ûÖ¹´¥·¢ÐÅºÅ
		ADC_InitStruct.ADC_SamplingTrigSource  = LL_ADC_TRIG_EXT_PA8;//Ó²¼þ´¥·¢Ô´Ñ¡Ôñ
    ADC_InitStruct.ADC_OverrunMode 		   	 = LL_ADC_OVR_DATA_OVERWRITTEN;//¸²¸ÇÉÏ´ÎÊý¾Ý
    ADC_InitStruct.ADC_WaitMode 		       = LL_ADC_WAIT_MODE_WAIT;//µÈ´ý 
    ADC_InitStruct.ADC_Channel_Swap_Wait   = LL_ADC_SAMPLEING_INTERVAL_11_CYCLES;//Í¨µÀÇÐ»»µÈ´ýÊ±¼ä
    ADC_InitStruct.ADC_Channel_Fast_Time   = LL_ADC_FAST_CH_SAMPLING_TIME_4_ADCCLK;//¿ìËÙÍ¨µÀ²ÉÑùÊ±¼ä
    ADC_InitStruct.ADC_Channel_Slow_Time   = LL_ADC_SLOW_CH_SAMPLING_TIME_192_ADCCLK;//ÂýËÙÍ¨µÀ²ÉÑùÊ±¼ä
    ADC_InitStruct.ADC_Oversampling        = DISABLE;//¹ý²ÉÑù¹Ø±Õ
    ADC_InitStruct.ADC_OverSampingRatio    = LL_ADC_OVERSAMPLING_8X;//8±¶¹ý²ÉÑù
    ADC_InitStruct.ADC_OversamplingShift   = LL_ADC_OVERSAMPLING_RESULT_DIV8;//Êý¾ÝÓÒÒÆ, /8	
    LL_ADC_Init(ADC, &ADC_InitStruct);

}

uint32_t GetVref1p22Sample(void)
{
	uint16_t ADCRdresult;
	LL_RCC_SetADCPrescaler(LL_RCC_ADC_OPERATION_CLOCK_PRESCALER_DIV8);
  LL_VREF_EnableVREFBuffer(VREF);//Ê¹ÄÜVREF BUFFER
	LL_ADC_EnalbleSequencerChannel(ADC, LL_ADC_INTERNAL_CH_VREF);//Í¨µÀÑ¡ÔñVREF
			
	LL_ADC_ClearFlag_EOC(ADC);//Çå±êÖ¾			
  LL_ADC_Enable(ADC);   	 // Æô¶¯ADC
	LL_ADC_StartConversion(ADC);  // ¿ªÊ¼×ª»»
    // µÈ´ý×ª»»Íê³É
  while (LL_ADC_IsActiveFlag_EOC(ADC) == RESET);
  LL_ADC_ClearFlag_EOC(ADC);//Çå±êÖ¾
	ADCRdresult =LL_ADC_ReadConversionData12(ADC);//»ñÈ¡²ÉÑùÖµ

  LL_ADC_Disable(ADC);    // ¹Ø±ÕADC
	LL_ADC_DisableSequencerChannel(ADC, LL_ADC_INTERNAL_CH_VREF);//Í¨µÀ¹Ø±ÕVREF	
  LL_VREF_DisableVREFBuffer(VREF);//¹Ø±ÕVREF BUFFER			
    // ×ª»»½á¹û 
  return ADCRdresult;
}

uint32_t GetVoltageSample(void)
{
	uint16_t ADCRdresult;
	LL_RCC_SetADCPrescaler(LL_RCC_ADC_OPERATION_CLOCK_PRESCALER_DIV1);
	LL_ADC_EnalbleSequencerChannel(ADC, LL_ADC_EXTERNAL_CH_0);//Í¨µÀÑ¡ÔñADC_0

	LL_ADC_ClearFlag_EOC(ADC);//Çå±êÖ¾			
	LL_ADC_Enable(ADC);   	 // Æô¶¯ADC
	LL_ADC_StartConversion(ADC);  // ¿ªÊ¼×ª»»
   // µÈ´ý×ª»»Íê³É
	while (LL_ADC_IsActiveFlag_EOC(ADC) == RESET);
	LL_ADC_ClearFlag_EOC(ADC);//Çå±êÖ¾
	ADCRdresult =LL_ADC_ReadConversionData12(ADC);//»ñÈ¡²ÉÑùÖµµ

  LL_ADC_Disable(ADC);    // ¹Ø±ÕADC
	LL_ADC_DisableSequencerChannel(ADC, LL_ADC_EXTERNAL_CH_0);//Í¨µÀ¹Ø±ÕADC_0		 	 
    // ×ª»»½á¹û 
  return ADCRdresult;
}

