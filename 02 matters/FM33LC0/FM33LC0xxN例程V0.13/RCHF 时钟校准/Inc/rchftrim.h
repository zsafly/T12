#ifndef RCHFTRIM_H
#define RCHFTRIM_H

#include <stdint.h>
#include "fm33lc0xx.h"

int32_t RchfAdjust(GPTIM_Type *GPTIMx, uint32_t clkMode);

#endif
