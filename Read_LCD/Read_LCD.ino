#include"atmega328p_port_init.h"
#define ONBUTTON 6
void setup() {
  // put your setup code here, to run once:
  init_port();

}
//initalization of port 
void init_port()
{
  char *portD_ddr = (char *) portD_ddr_register;
  char *portB_ddr = (char *) portB_ddr_register;
  char *portC_ddr = (char *) portC_ddr_register;

  *portD_ddr = 0xFF;
  *portB_ddr = 0xFF;
  *portC_ddr = 0x00;
}
void outportD(volatile char data)
{
  volatile char *portD_data = (volatile char *) portD_data_register;
  *portD_data = data;
  
}
void outportB(volatile char data)
{
  volatile char *portB_data = (volatile char *) portB_data_register;
  *portB_data = data;
}

void loop() {
  // put your main code here, to run repeatedly:

}
