//
/* tank_low_level_sens, tank_high_level_sens, water_level_low_sens are floating switchers
 *  we consider floating switch will turn on if the water level is higher than the switch
*/

#include<LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // sets the interfacing pins

#define tank_low_level_sens 13
#define tank_high_level_sens 12
#define water_level_low_sens 11
#define buzzer 10
#define motor 9
#define water_level_low_indicator 8
#define motor_on_indicator 1

int state;

void setup() {
  pinMode(tank_low_level_sens, INPUT);
  pinMode(tank_high_level_sens, INPUT);
  pinMode(water_level_low_sens, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(water_level_low_indicator, OUTPUT);
  pinMode(motor_on_indicator, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();  
}

void loop() {
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("WATER PUMP SYS");
  if(digitalRead(water_level_low_sens) == LOW){
      state = 2;
      digitalWrite(water_level_low_indicator,HIGH);
      digitalWrite(motor_on_indicator,LOW);
      digitalWrite(motor,LOW);
      lcd.setCursor(0,1);
      lcd.print("WATER LEVEL LOW");
      delay(100);
  }else{
      digitalWrite(water_level_low_indicator,LOW);
      if(digitalRead(tank_low_level_sens) == LOW){
          state = 1;    
      }
      if( (digitalRead(tank_low_level_sens) == HIGH) && (digitalRead(tank_high_level_sens) == HIGH) ){
          state = 2;
          lcd.setCursor(0,1);
          lcd.print("WATER TANK FULL");
          delay(100);   
      }
      if(state == 1){
          digitalWrite(motor_on_indicator,HIGH);
          digitalWrite(motor,HIGH);
          lcd.setCursor(0,1);
          lcd.print("WATER PUMP ON");
          delay(100);
      }else{
          digitalWrite(motor_on_indicator,LOW);
          digitalWrite(motor,LOW);
      }  
  }
}
