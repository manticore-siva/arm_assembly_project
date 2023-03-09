////////////////////////////////////////////////////////////////////////////
//                                                                         //
//   Authore Name : Sivaprakasam.v                                         //
//   Title : ARM Assembly TIMER10_HSE_ON 2sec delay LED_blink              //
//   Date  : 09/03/2023                                                    //
//                                                                         // 
/////////////////////////////////////////////////////////////////////////////


// ADDRESS CONFIGURATION
volatile unsigned int *RCC_CTRL    =(volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_AHB1ENR =(volatile unsigned int *)0x40023830;
volatile unsigned int *RCC_APB2ENR =(volatile unsigned int *)0x40023844;
volatile unsigned int *RCC_CFGR    =(volatile unsigned int *)0x40023808;

volatile unsigned int *GPIOC_MODER =(volatile unsigned int *)0x40020800;
volatile unsigned int *GPIOC_ODR   =(volatile unsigned int *)0x40020814;

volatile unsigned int *TIM10_CR    =(volatile unsigned int *)0x40014400;
volatile unsigned int *TIM10_SR    =(volatile unsigned int *)0x40014410;
volatile unsigned int *TIM10_EGR   =(volatile unsigned int *)0x40014414;
volatile unsigned int *TIM10_CNT   =(volatile unsigned int *)0x40014424;
volatile unsigned int *TIM10_PSC   =(volatile unsigned int *)0x40014428;
volatile unsigned int *TIM10_ARR   =(volatile unsigned int *)0x4001442c;
#define LED_ON (~(1<<13))
#define LED_OFF 1<<13

void clock_config(void);
void portc_config(void);
void tim10_delay(void);

int main()
{
	clock_config();
	portc_config();

	while(1)
	{
		//LED OFF
		*GPIOC_ODR = LED_OFF;

		//DELAY
		tim10_delay();

		//LED ON
		*GPIOC_ODR = LED_ON;

		//DELAY
		tim10_delay();

	}
}

void clock_config(void)
{
	// HSE on	
	*RCC_CTRL = *RCC_CTRL | 1<<16;

	// RCC clock configuration register
	*RCC_CFGR = *RCC_CFGR | 0x5;

	//RCC_APB2ENR TIMER 10 enable
	*RCC_APB2ENR = *RCC_APB2ENR | 1<<17;

	//RCC_CLOCK enable,GPIOCEN: IO port C clock enable
	*RCC_AHB1ENR = *RCC_AHB1ENR | 4;	
}

void portc_config(void)
{
	// c13 pin set as output mode
	*GPIOC_MODER = 1<<26;
}

void tim10_delay(void)
{
	
	//Enable Update disable
	*TIM10_CR = *TIM10_CR | (1<<1);

	//clear UIF status
	*TIM10_SR = *TIM10_SR * ~(1<<0);

	//Set count value
	*TIM10_CNT = 0;  

	//Set prescaler value
	*TIM10_PSC = 50000;            

	//Set reload value
	*TIM10_ARR = 1000;

	//Update disable OFF
	*TIM10_CR = *TIM10_CR & ~(1<<1); 

	//Update request source
	*TIM10_CR = *TIM10_CR | (1<<7);

	//Auto-reload preload enable
	*TIM10_CR = *TIM10_CR | (1<<2);

	//Counter enable
	*TIM10_CR = *TIM10_CR | 1;

	// condition
	  
	while((*TIM10_SR & 1)==0);
}
