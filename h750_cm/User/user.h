#include "Emm_V5.h"
#include "pack.h"
#include "robotarm.h"
#include "belt.h"
#include "main.h"
#include "stm32h7xx_it.h"
#include <stdio.h>

#define PREAMO 30000//设置打包架初始高度

void setup(void);
void loop(void);
void back(void);
void push(void);