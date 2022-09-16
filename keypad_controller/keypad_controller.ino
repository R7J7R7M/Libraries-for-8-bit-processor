#include"atmega328p_port_init.h"

//function used  for LCD

void LCD_write(char*);
void print_LCD(volatile char);
void init_LCD();
void pulse_write_data();
void pulse_write_commmand();

//function for keypad
void init_keypad();
void convert_ketpad();
volatile char scan_keypad();

// normal function
void init_port();
void outportD(volatile char,volatile char);
void outportB(volatile char);


//Global variables
volatile char output;
volatile char str[20] = "GOKUlRAJARAM";
volatile char keypad[20];
volatile char arr[20];
void setup() {
  // put your setup code here, to run once:
 
  init_port();
  init_LCD();
  LCD_write(str);
  outportB(0xC0);  // shifting cursor in second line
  pulse_write_command();
  init_keypad();
  
}
void init_keypad()
{
  volatile char answer;
  convert_keypad();
  answer = scan_keypad();
  while(answer == 0){
    answer = scan_keypad();
  }
  if(answer == 0x0D) return;
  else {
     print_LCD(arr[answer]);
     init_keypad();
  }
 
}
void convert_keypad()
{
  arr[0x01] = '7';
  arr[0x02] = '8';
  arr[0x03] = '9';
  arr[0x04] = '/';
  arr[0x05] = '4';
  arr[0x06] = '5';
  arr[0x07] = '6';
  arr[0x08] = '*';
  arr[0x09] = '1';
  arr[0x0A] = '2';
  arr[0x0B] = '3';
  arr[0x0C] = '-';
  arr[0x0D] = '=';
  arr[0x0E] = '0';
  arr[0x0F] = '=';
  arr[0x10] = '+';
  
}
volatile char scan_keypad()
{
  volatile char answer;
  volatile char row,col;
  volatile char R,C;
  volatile char i,j;
  for(i=4;i<8;i++){
    outportD(0x01,i);
    col = inportC();
    delay(1);
    if(col != 0x00){
      row = i;
      for(j=0;j<4;j++)
      if(col == 1<<j){
        C = j;
        answer = row*4+C+1;
        return answer;
      }
      else outportD(0x00,i);
    }
    
    
  }
}
// LCD intialization
void LCD_write(char *str)
{
  volatile char len,k=0;
  for(len=0;str[len]!='\0';len++);
  
  while(len){
    print_LCD(str[k]);
    k++;
    len--;
  }
}
void print_LCD(volatile char data)
{
  outportB(data);
  pulse_write_data();
}
void pulse_write_data()
{
  outportD(0x01,0);
  outportD(0x00,1);
  outportD(0x00,2);

  delay(1);

  outportD(0x01,0);
  outportD(0x00,1);
  outportD(0x01,2);

  delay(1);
  
  outportD(0x01,0);
  outportD(0x00,1);
  outportD(0x00,2);
  
}
void init_LCD()
{
  
  outportB(0x38);  // 8bit 2 line mode
  pulse_write_command();
  outportB(0x01); //clear the display
  pulse_write_command();
  outportB(0x80);  // cursor on the first line
  pulse_write_command();
  outportB(0x0F); // cursor design
  pulse_write_command();
  outportB(0x06);  //shifting the cursor  
  pulse_write_command();
}
void pulse_write_command()
{
  outportD(0x00,0);
  outportD(0x00,1);
  outportD(0x00,2);

  delay(1);

  outportD(0x00,0);
  outportD(0x00,1);
  outportD(0x01,2);
  delay(1);

  outportD(0x00,0);
  outportD(0x00,1);
  outportD(0x00,2);
  
  
}

// GPIO intialization

void init_port(void)
{
  char *portD_ddr = (char *) portD_ddr_register;
  char *portB_ddr = (char *) portB_ddr_register;
  char *portC_ddr = (char *) portC_ddr_register;
  *portD_ddr = 0xFF ;
  *portB_ddr = 0xFF;
  *portC_ddr = 0x00;
  
}

void outportB(volatile char data)
{
  volatile char *portB_data = (volatile char *) portB_data_register;
  *portB_data = data;
}

void outportD(volatile char data,volatile char pin)
{
  volatile char *portD_data = (volatile char *) portD_data_register;
  if( data == 0x01){
    output |= data<<pin;
  }
  else if(data == 0x00){
    output &= ~((0x01<<pin));
  }
  *portD_data = output;
}
volatile char inportC()
{
  volatile char *portC_data = (volatile char *) portC_input_register;
  volatile char data;
  data = *portC_data;
  return data;
}
void loop() {
  // put your main code here, to run repeatedly:

}
