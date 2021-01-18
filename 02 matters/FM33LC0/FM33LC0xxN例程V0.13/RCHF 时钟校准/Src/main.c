#include "main.h"
#include "user_init.h"
#include "rchftrim.h"

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
    
    // 测试用：调偏RCHF
//    LL_RCC_SetRCHFTrimValue(0x00);
    
    RchfAdjust(GPTIM0, RCHF_CLOCK);
    
    while(1)
    {     
        if (RchfAdjust(GPTIM0, RCHF_CLOCK) != 0)
        {
            // TODO: 调校失败处理
        }
        
        LED0_TOG();
        DelayMs(1000);
    }
}


