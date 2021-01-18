#include "main.h"
#include "user_init.h"
#include "gptim.h"

void GPTIM0_IRQHandler(void)
{
    if (( LL_GPTIM_IsEnabledIT_UPDATE(GPTIM0) == SET ) &&(LL_GPTIM_IsActiveFlag_UPDATE(GPTIM0)==SET))
    {	 
        LL_GPTIM_ClearFlag_UPDATE(GPTIM0);    
        LED0_TOG();      
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
    
    GPTIM_Init();
    while(1)
    {     
      
    }
}


