#include "main.h"
#include "user_init.h"
#include "adc.h"

uint32_t Get122VSample;
uint64_t GetVSample;
uint32_t GetV;

int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    /* SHOULD BE KEPT!!! */
    MF_Clock_Init();
    
    /* Configure the system clock */
    /* SHOULD BE KEPT!!! */
    MF_SystemClock_Config();
    
    /* Initialize all configured peripherals */
    /* SHOULD BE KEPT!!! */
    MF_Config_Init();
    
    UserInit();
    AdcInit();

    while(1)
    { 
			Get122VSample = GetVref1p22Sample();
			GetVSample=GetVoltageSample();
			GetV =  (GetVSample *3000*(ADC_VREF))/(Get122VSample*4095); 	
			DelayMs(1000);	
    }
}


