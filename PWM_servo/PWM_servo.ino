void init_port();
void init_timer(volatile char);
void setup() {
  // put your setup code here, to run once:
  PWM_milli(1,20);

}
void init_port()
{
  volatile char *portB_ddr = (volatile char*) 0x24;
  *portB_ddr = 0xFF;
}
void init_timer(volatile char data)
{
  volatile char *tCCR1A = (volatile char*) 0x80; //Timer/Counter1 Control Register A;
  volatile char *tCCR1B = (volatile char*) 0x81; //Timer/Counter1 Control Register B;
  volatile short *tCNT1 = (volatile short*) 0x84; //data in counter
  volatile char *tIMSK1 = (volatile char*) 0x6F; // Enable the Mask

  // initializer
  *tCCR1B = 0x00; 
  *tCCR1A = 0x00;
  *tCNT1 = 0x00;

  *tCCR1B = 0x18 | data ; //Fast PWM and prescale representation
  *tCCR1A = 0x82;
  *tIMSK1 = 0x02;

}

void PWM_milli(volatile float on_period,volatile char time_period)
{
  init_timer(0x04);
  volatile short *oCR1A = (volatile short *) 0x88;
  volatile short *iCR1A = (volatile short*) 0x86;

  *oCR1A = 62.5*on_period;
  *iCR1A = 62.5*time_period;
}

void loop() {
  // put your main code here, to run repeatedly:

}
