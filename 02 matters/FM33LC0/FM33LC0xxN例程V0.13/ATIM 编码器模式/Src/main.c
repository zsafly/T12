#include "main.h"
#include "user_init.h"
#include "atim.h"

int32_t count;

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
    ATIM_Init();
    
    while(1)
    {     
        DelayMs(100);
        count = ATIM_Read();
    }
}


