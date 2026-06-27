#define RCC_BASE 0x40021000UL

#define RCC_CR (RCC_BASE+0x00)
#define HSEON 16
#define PLLRDY 25
#define PLLON 24

#define RCC_CFGR (RCC_BASE+0x04)
#define PLLXTPRE 17
#define PLLSRC 16
#define PLLMUL 18
#define HPRE 4
#define PPRE1 8
#define SW 0