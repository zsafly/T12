#include "main.h"
#include "user_init.h"
#include "gptim.h"

uint32_t  IC1Value=0;
uint32_t  Frequency=0;

void GPTIM0_IRQHandler(void)
{    
    if ((LL_GPTIM_IsEnabledIT_CC(GPTIM0, LL_GPTIM_CHANNEL_1) == SET) &&
        (LL_GPTIM_IsActiveFlag_CC(GPTIM0, LL_GPTIM_CHANNEL_1) == SET))
    {
        LL_GPTIM_ClearFlag_CC(GPTIM0, LL_GPTIM_CHANNEL_1);
        
        IC1Value = LL_GPTIM_GetCompareCH1(GPTIM0);
        //频率 主时钟为8MHZ、不分频的计算公式
        Frequency= (8000000/1/IC1Value);
    }
}

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
    
    // Debug时运行GPTIM0
    CLEAR_BIT(DBG->CR, 0x1 << 10);
    
    GPTIM_CAPTURE_Init();
    
    while(1)
    {     
      
    }
}


