void init_port();
void setup() {
  // put your setup code here, to run once:
  init_port();
  init_timer();
  while(1){
     outportD(0x01);
     delay_sec(3);
     //delay_milli_sec(20);
  }
}
void init_timer()
{

  volatile char *tCCR1A = (volatile char *) 0x80;
  volatile char *tCCR1B = (volatile char *) 0x81;
  volatile short *tCNT1 = (volatile short *) 0x84;
  volatile short *oCR1A = (volatile short *) 0x88;
  volatile char *tMISK = (volatile char *) 0x6F;

  *tCCR1A = 0x00;
  *tCCR1B = 0x00;
  *tMISK  = 0x02;
  *tCCR1B = 0x08 | 0x05;
  *tCNT1  = 0x00;
     
  

}
void init_port()
{
  volatile char *portD_ddr = (volatile char*) 0x2A;
  *portD_ddr = 0xFF;
}
void outportD(volatile char data)
{
  volatile char *portD_data = (volatile char *) 0x2B;
  *portD_data ^= data;
}
void delay_sec(volatile char data)
{
  volatile char *tIFR0 = (volatile char *) 0x15;
  volatile short *oCR1A = (volatile short *) 0x88;
  
  *oCR1A = 15625*data;
  char x =0;
  while(x == 0){
      x = *tIFR0 & (0x01<<1);
  }

}
void delay_milli_sec(volatile short data)
{
  init_timer(0x04); //0x04 prescaled by 256

  volatile char *tIFR0 = (volatile char *) 0x15;
  volatile short *oCR1A = (volatile short *) 0x88;

  *oCR1A = 62.5*data;
  char x = 0;
  *tIFR0 = 0;
  while(x == 0){
      x = *tIFR0 & (0x01<<1);
  }
}
void delay_micros(volatile long data)
{
  init_timer(0x05);//0x05 prescaled by 1024
  volatile char *tIFR0 = (volatile char *) 0x15;//Timer/Counter0 Interrupt Flag Register
  volatile short *oCR1A = (volatile short*) 0x88;

  *oCR1A = 0.015*data;
  char x = 0;
  while(x == 0) x = *tIFR0 &(0x01<<1);
}
void loop() {
  // put your main code here, to run repeatedly:

}
