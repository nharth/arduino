#include <LiquidCrystal.h>
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
int dt = 2000;
String msg1 = "Enter a number : ";
String msg2 = "Enter 2nd num: ";
String msg3 = "Enter an operator (+, -, *, or /): ";
float operand1;
float operand2;
float answer; 
String op;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);

}

void loop() {
  // put your main code here, to run repeatedly:
  operand1 = getOperand(msg1);
  operand2 = getOperand(msg2);
  op = getOperator(msg3);
  delay(dt);
  if (op != "/" &&  op != "*" && op != "+" && op != "-") {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Invalid Operator");
  } else {
    if (op == "/") {
      answer = operand1 / operand2;
    } else if (op == "*") {
      answer = operand1 * operand2;
    } else if (op == "+") {
      answer = operand1 + operand2;
    } else  {
      answer = operand1 - operand2;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("The answer is: ");
    lcd.setCursor(0, 1);
    lcd.print(operand1);
    lcd.print(" ");
    lcd.print(op);
    lcd.print(" ");
    lcd.print(operand2);
    lcd.print(" = ");
    if ( op == "/" && operand2 == 0) {
      lcd.print("undefined");
    } else {
      lcd.print(answer);
    }

    
  }
  delay(dt*5);
  lcd.clear();
  

}

int getOperand(String msg) {
  float operand;
  lcd.setCursor(0, 0);
  lcd.print(msg);
  while(Serial.available() == 0) {

  }
  operand = Serial.parseFloat();
  lcd.setCursor(0, 1);
  lcd.print(operand);
  delay(dt);
  lcd.clear();
  return operand;
}

String getOperator(String msg) {
  String operate;
  lcd.setCursor(0, 0);
  lcd.print(msg);
  while(Serial.available() == 0) {
    
  }
  operate = Serial.readString();
  lcd.setCursor(0, 1);
  lcd.print(operate);
  return operate;
}
