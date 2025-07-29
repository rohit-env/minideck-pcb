#include "Arduino.h"
#include <Keypad.h>
#include "USB.h"
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"
#include <Wire.h>
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>  


const char* FIRMWARE_VERSION = "1.0.0";


#define HA 8
#define VA 10
#define MOUSE_MID_BUTTON 9
#define LDR 14
#define LCD_BACKLIGHT 13
#define POWER_BUTTON 12
#define POWER_MAIN 11

// System feature
bool POWER_BUTTON_TO_POWER_OFF = true;
bool USB_DISCONNECT_TO_POWER_OFF = true; 
bool BATTERY_MONITOR_FUNCTION = false; 
bool LDR_MONITOR = false; 

// Define variables for I2C battery monitor
SFE_MAX1704X lipo(MAX1704X_MAX17049);  
double voltage = 0;                    
double batteryPercentage = 0;          
bool alert;                            
bool batteryMonitorDetected = false;  
bool LCD_ON = true;
static uint16_t powered_on = 1000;

// Define variables for USB disconnect detection
const unsigned long USB_DISCONNECT_TIMEOUT = 20000;
unsigned long usbDisconnectStartTime = 0;
bool waitingForReconnect = false;
bool pcIsOn = false;

// Define variables for Power button hold detection
const unsigned long POWER_BUTTON_HOLD_TIME = 5000;
unsigned long lastPowerButtonPressTime = 0;
bool lastPowerButtonState = HIGH; 

// For Mouse
USBHIDMouse mMouse;
int vertZero, horzZero;      
const int mouse_sensitivity = 300;  
bool pan = false;

// For Keypad
USBHIDKeyboard mKeyboard;
const byte KBD_ROWS = 5;
const byte KBD_COLS = 12;
static bool keymapState = 0;

// Keypad event codes:
#define LSW 0x95 // keyboard layout switch
#define SL1 0x97 // Sholder key leftside
#define SL2 0x99 // Sholder key leftside
#define SL3 0x94 // Sholder key leftside
#define SL4 0x96 // Sholder key leftside
//#define LCD_TOGG 0x93


static void lcd_backlight_toggle(void) {
  if (LCD_ON) {
    digitalWrite(LCD_BACKLIGHT, LOW);
    LCD_ON = false;
  } else {
    digitalWrite(LCD_BACKLIGHT, HIGH);
    LCD_ON = true;
  }

  Serial.print("lcd_backlight_toggle: ");
  Serial.println(LCD_ON);
}


static uint8_t keymapAlpha[] = {
  0x00, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x00,
//      1     2     3     4     5     6     7     8     9     0
  0x2B, 0x14, 0x1A, 0x08, 0x15, 0x17, 0x1C, 0x18, 0x0C, 0x12, 0x13, SL1,
//Tab,  Q     W     E     R     T     Y     U     I     O     P     SL1
  0x39, 0x04, 0x16, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x2A, SL4,
//CL    A     S     D     F     G     H     J     K     L     Bspce SL4
  0xE1, 0x1D, 0x1B, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x28, SL2,
//LSh   Z     X     C     V     B     N     M     ,     .     Enter SL2
  0xE0, 0xE2, 0x52, 0x51, 0x50, 0x4F, 0x2C, 0x00, 0x29, 0xE0, LSW,  SL3
//LCtl  LAlt  AUp   ADn   AL    AR    SPC         ESC   LCtl  LSW   SL3
};

static uint8_t keymapSymbols[] = {
  0x00, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x00,
//      F1    F2    F3    F4    F5    F6    F7    F8    F9    F10
  0x2B, 0x44, 0x45, 0x00, 0x00, 0x00, 0x00, 0x35, 0x2F, 0x30, 0x31, SL1,
//Tab   F11   F12   0     0     0     0     `     [     ]     \     SL1
  0x39, 0x57, 0x56, 0x55, 0x54, 0x67, 0x00, 0x38, 0x33, 0x34, 0x2A, SL4,
//CL    +     -     *     ÷     =     0     /     ;     '     Bspce SL4
  0xE1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x37, 0x28, SL2,
//LSh   0     0     0     0     0     0     0     ,     .     Enter SL2
  0xE0, 0xE2, 0x52, 0x51, 0x50, 0x4F, 0x2C, 0x00, 0x29, 0xE0, LSW,  SL3
//LCtl  LAlt  AUp   ADn   AL    AR    SPC         ESC   LCtl  LSW   SL3
};

static char dummyKeypad[KBD_ROWS][KBD_COLS] = {
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 },
  { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 },
  { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 },
  { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47 },
  { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59 }
};

byte kbd_row_pins[KBD_ROWS] = { 37, 35, 41, 40, 38 };                       //connect to the row pinouts of the keypad
byte kbd_col_pins[KBD_COLS] = { 34, 36, 42, 39, 1, 2, 3, 6, 7, 5, 4, 33 };  //connect to the column pinouts of the

//initialize an instance of class NewKeypad
Keypad Keyboard = Keypad(makeKeymap(dummyKeypad), kbd_row_pins, kbd_col_pins, KBD_ROWS, KBD_COLS);

static void switch_Keymap(void) {
  if (keymapState) {
    keymapState = 0;
  } else {
    keymapState = 1;
  }
}

static uint8_t mapKey(char key) {
  if (keymapState)
    return keymapSymbols[key];

  return keymapAlpha[key];
}

static void processKeys(void) {
  if (!Keyboard.getKeys())
    return;
  int i;

  for (i = 0; i < LIST_MAX; i++) {
    if (!Keyboard.key[i].stateChanged) {
      continue;
    }

    uint8_t key = mapKey(Keyboard.key[i].kchar);

    switch (Keyboard.key[i].kstate) {
      case PRESSED:
        {
          Serial.println(key);
          if (key == LSW) {
            //Serial.println("LSW");
            switch_Keymap();
          } else if (key == SL1) {
            //Serial.println("SL1");
            mMouse.click(MOUSE_RIGHT);
          } else if (key == SL2) {
            //Serial.println("SL2");
            mMouse.click(MOUSE_LEFT);
          } else if (key == SL3) {
            //Serial.println(0xE3);
            mKeyboard.pressRaw(uint8_t(0xE3));
          } else if (key == SL4) {
            //Serial.println("SL4");
            scroll = true;
          } else {
            //Serial.println(key);
            mKeyboard.pressRaw(key);
          }
        }
        break;
      case RELEASED:
        {
          if(key == LSW || key == SL1 || key == SL2 || key == SL3 || key == SL4){
            mKeyboard.releaseRaw(uint8_t(0xE3));
            scroll = false;
            pan = false;
          } else {
            mKeyboard.releaseRaw(key);
          }
        }
        break;
    }
  }
}



static void processMouse() {
  // read and scale the two axes:
  int xReading = analogRead(VA) - vertZero;  // read vertical offset
  int yReading = analogRead(HA) - horzZero;  // read horizontal offset

  if (abs(xReading) > 5 || abs(yReading) > 5) {
    if (scroll) {
      delay(500);
      mMouse.move(0, 0, -(xReading / 1000), (yReading / 1000));  //Wheel only supports 0-1 value
    } else {
      mMouse.move((yReading / mouse_sensitivity), (xReading / mouse_sensitivity));
    }
  }

  if (!digitalRead(MOUSE_MID_BUTTON)) {
    mMouse.click(MOUSE_MIDDLE);
    //Serial.println("pressMiddle");
    delay(20);
  }
}

static void power_off(void) {
  
  delay(100);

  
  Serial.println("power_off");
  delay(500);
  digitalWrite(POWER_MAIN, LOW);
}

static void batteryStats() {
  // lipo.getVoltage() returns a voltage value (e.g. 3.93)
  voltage = lipo.getVoltage();
  // lipo.getSOC() returns the estimated state of charge (e.g. 79%)
  batteryPercentage = lipo.getSOC();
  // lipo.getAlert() returns a 0 or 1 (0=alert not triggered)
  alert = lipo.getAlert();

  // Print the variables:
  Serial.print("Voltage: ");
  Serial.print(voltage);  
  Serial.println(" V");

  Serial.print("Percentage: ");
  Serial.print(batteryPercentage);  
  Serial.println(" %");

  Serial.print("Alert: ");
  Serial.println(alert);
  Serial.println();

  delay(500);
}

void setup(void) {
  pinMode(POWER_MAIN, OUTPUT);
  digitalWrite(POWER_MAIN, HIGH);

  pinMode(LDR, INPUT);
  pinMode(VA, INPUT);
  pinMode(HA, INPUT);
  pinMode(MOUSE_MID_BUTTON, INPUT_PULLUP);
  pinMode(POWER_BUTTON, INPUT_PULLUP);
  pinMode(LCD_BACKLIGHT, OUTPUT);

  // Serial setup
  Serial.begin(115200);
  Serial.print("Starting version: ");
  Serial.println(FIRMWARE_VERSION);
  Serial.println();

  //I2C pins
  Wire.begin(18, 17);

  vertZero = analogRead(VA);  
  horzZero = analogRead(HA);  

 
  lcd_backlight_toggle();
  delay(500);
  lcd_backlight_toggle();

 
  Serial.println("Wait for SBC to Finish booting, 30 sec");
  delay(30000);
  Serial.println("end");


  mMouse.begin();
  mKeyboard.begin();
  USB.begin();


  Keyboard.setHoldTime(1);
  Keyboard.setDebounceTime(0);
  delay(500);

  if (BATTERY_MONITOR_FUNCTION) {
   
    if (lipo.begin() == false) {  
      Serial.println(F("MAX17049 not detected"));
      batteryMonitorDetected = false;
    } else {
      Serial.println(F("MAX17049 detected"));
      batteryMonitorDetected = true;

      
      lipo.quickStart();

      
      lipo.setThreshold(20);  
    }
  }
}

void loop(void) {

  /
  if (powered_on > 0) {
    powered_on--;
  } else {
  
    if (POWER_BUTTON_TO_POWER_OFF) {
     
      bool currentPowerButtonState = digitalRead(POWER_BUTTON);

     
      if (currentPowerButtonState == LOW && lastPowerButtonState == HIGH) {
        lastPowerButtonPressTime = millis();
      }

      bool hold = (millis() - lastPowerButtonPressTime) > POWER_BUTTON_HOLD_TIME;

      if (currentPowerButtonState == LOW && hold && digitalRead(POWER_MAIN)) {
        Serial.println("POWER_DOWN - Power button");
        power_off();
      }

  
      lastPowerButtonState = currentPowerButtonState;
    }


    if (USB_DISCONNECT_TO_POWER_OFF) {
    
      pcIsOn = (bool)USB;

      if (!pcIsOn) {
   
        if (!waitingForReconnect) {
          waitingForReconnect = true;
          usbDisconnectStartTime = millis();
          Serial.println("USB disconnect detected - waiting for reconnect");
        }

        else if ((millis() - usbDisconnectStartTime) > USB_DISCONNECT_TIMEOUT) {
          Serial.println("POWER_DOWN - No USB response after timeout");
          power_off();
        }
      } else {

        waitingForReconnect = false;
        usbDisconnectStartTime = 0;  
      }
    }
  }


  processKeys();
  processMouse();

 
  if (BATTERY_MONITOR_FUNCTION && batteryMonitorDetected) { 
    batteryStats(); 
  }


  if(LDR_MONITOR){
    int LDR_m = analogRead(LDR);
    Serial.print("LDR_value: ");
    Serial.println(LDR_m);
  }

  delay(1);  
}


