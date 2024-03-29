///////////////////////////////////////////////////////////
//                                                       //
//   Authore Name : Sivaprakasam.v                       //
//   Title : C program Systic Delay LED Blinking         //
//   Date  : 22/02/2023                                  //
//                                                       // 
///////////////////////////////////////////////////////////


  //PORT CONFIGURATION ADDRESS
  
  unsigned int *RCC_AHB1    = (unsigned int *)0x40023830;         // peripheral clock enable register (RCC_AHB1ENR    )
  unsigned int *GPIOC_MODER = (unsigned int *)0x40020800;         // GPIO port mode register (GPIOC_MODER)
  unsigned int *GPIOC_ODR   = (unsigned int *)0x40020814;         // GPIO port output data register (GPIOx_ODR) 
  
  //SYSTIC CONFIGUARATION ADDRESS
  
  unsigned int *SYST_RVR    = (unsigned int *)0xE000E014;         // SysTick Reload Value Register, SYST_RVR 
  unsigned int *SYST_CSR    = (unsigned int *)0xE000E010;         // SysTick Control and Status Register, SYST_CSR
  
  void systic_timer(void);
  
  int main()
  {
          *RCC_AHB1     = *RCC_AHB1 | 0X04;               // enable clock on C port
  
          *GPIOC_MODER  = *GPIOC_MODER | (1<<26) ;        // C13 out put mode
  
          while(1)
          {
  
                 *GPIOC_ODR = *GPIOC_ODR |  (1<<13); // LED OFF
  
                 systic_timer();
  
                 *GPIOC_ODR    = (*GPIOC_ODR  & ~(1<<13)) ; //LED ON
  
                 systic_timer();
  
          }
  }
  
  void systic_timer(void)
  {
          *SYST_RVR  = 16000000;                 //RVR Reload value
  
          *SYST_CSR  = *SYST_CSR | 1<<2 ;       //select clock internal source
 
          *SYST_CSR  = *SYST_CSR | 1<<0 ;       // Enable counter
  
          while((*SYST_CSR & (1<<16))==0);      //waiting for flag update
}
