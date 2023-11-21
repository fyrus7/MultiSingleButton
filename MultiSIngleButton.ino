
#define CL 2 // button is connected on Pin 2


int lastButtonState = HIGH;          // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
bool buttonState = HIGH;             // saving state of the switch
byte tapCounter;                     // for saving no. of times the switch is pressed
int timediff;                        // for saving the time in between each press and release of the switch
bool flag1, flag2;                   // just two variables
long double presstime, releasetime;  // for saving millis at press and millis at release


void setup() {
  
  Serial.begin(115200);      // for serial monitor
  pinMode(CL, INPUT_PULLUP); // setting pin 2 with internal pull up resistor

}


void loop() {

  int reading = digitalRead(CL);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
    }
  }
  //Serial.println(buttonState);

  //when switch is pressed
  if (buttonState == 0 && flag2 == 0)
  {
    presstime = millis(); //time from millis fn will save to presstime variable
    flag1 = 0;
    flag2 = 1;
    tapCounter++; // tap counter will increase by 1
    //delay(10); // for avoiding debouncing of the switch
  }
  //when sw is released
  if (buttonState == 1 && flag1 == 0)
  {
    releasetime = millis(); // time from millis fn will be saved to releasetime var
    flag1 = 1;
    flag2 = 0;

    timediff = releasetime - presstime; // here we find the time gap between press and release and stored to timediff var
    //Serial.println(timediff);
    //delay(10);
  }

  if ((millis() - presstime) > 400 && buttonState == 1) // wait for some time and if CL is in release position
  {
     if (tapCounter == 4) //if tapcounter is 4 then its 4 tap
    {
      Serial.println("four tap   ( 4 )");
    }
    else if (tapCounter == 3) //if tapcounter is 3 //then its triple tap
    {
      Serial.println("triple tap ( 3 )");
    }
    else if (tapCounter == 2 ) //if tapcounter is 2
    {
      if (timediff >= 400) // if timediff is greater than  400 then its single tap and hold
      {
        Serial.println("single tap and hold");
      }
      else // if timediff is less than 400 then its just double tap
      {
        Serial.println("double tap ( 2 )");
      }
    }
    else if (tapCounter == 1) //if tap counter is 1
    {
      if (timediff >= 400) //if time diff is larger than 400 then its a hold
      {
        Serial.println("Hold");
      }
      else //if timediff is less than 400 then its a single tap
      {
        Serial.println("single tap ( 1 )");
      }
    }
    tapCounter = 0;
  }
  lastButtonState = reading;
}
