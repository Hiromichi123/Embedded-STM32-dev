#include "Emm_V5.h"
#include "main.h"

#define uartVertical_1 huart4
#define uartVertical_2 huart8
#define uartHorizon huart5

#define PushTime 4500
#define DOWNAMO 17000
#define PACKAMO 5500
#define TAPEAMO 800
#define SNAPAMO 5000

void pack(void);
void stick(void);
void tape_move(void);

extern int start_tick;
