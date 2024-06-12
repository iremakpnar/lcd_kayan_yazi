#include <LiquidCrystal.h>

#define TRUE 1
#define FALSE 0
#define MAAX_COLUMN 16

LiquidCrystal lcd(9,8,5,4,3,2);
int timctr;
bool flag_50ms, flag_100ms, flag_500ms, flag_1000ms;

void kayanyazi(void);



ISR(TIMER1_OVF_vect)
{
  TCNT1 = 45535; // Timer Preloading
  // Handle The Timer Overflow Interrupt
  //...
  if(timctr%5==0)
  {
    flag_50ms= TRUE;
  }
  
  if(timctr%10==0){
    flag_100ms = TRUE;
  }
  if(timctr%50==0){
    flag_500ms =TRUE;
  }
  if(timctr>=100){
    flag_1000ms =TRUE;
    timctr=0;
  }
  timctr++;
}

void InitializeTimer1(void){
  timctr=0;
  flag_50ms=flag_100ms=flag_500ms=flag_1000ms=0;
  
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= B00000010;  // Prescaler = 8
  TCNT1 = 45535;        // Timer Preloading
  TIMSK1 |= B00000001;  // Enable Timer Overflow Interrupt
}




void setup() {
  lcd.begin(16,2);
  InitializeTimer1();


}

void loop() {
   if(flag_50ms)
  {
    flag_50ms= FALSE;    
  }
  if(flag_100ms){
    flag_100ms = FALSE;
     
  }
  if(flag_500ms){
    flag_500ms =FALSE;
    kayanyazi();
  }
  if(flag_1000ms){
    flag_1000ms =FALSE;
   

  }
  

}


void kayanyazi(void){
  static int position =0;
//  lcd.setCursor(3,0); // LCD ekranın konumunu belirtiyoruz. 
  
    lcd.setCursor(position,0);
    lcd.print("LCD");
    if(position > 0){
      lcd.setCursor(position-1,0);
      lcd.print(" ");
    }

    lcd.setCursor(position,1);
    lcd.print("Kayan Yazi");
    if(position > 0){
      lcd.setCursor(position-1,1);
      lcd.print(" ");
    }


    position++;
    if(position>15)
      position =0;
}



