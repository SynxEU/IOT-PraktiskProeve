// Includes
#include "RTClib.h"
#include "time.h"
#include "temp.h"
#include "humidity.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include <EasyButton.h>

// Defines
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)

#define DHTPIN 2
#define DHTTYPE DHT11  // DHT 11

#define ACTIVATION_BUTTON_PIN 6
#define SCROLL_BUTTON_PIN 5

// Easy Button
EasyButton activationBtn(ACTIVATION_BUTTON_PIN);
EasyButton scrollBtn(SCROLL_BUTTON_PIN);

// OLED Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RTC
// Initialize RTC
RTC_DS3231 rtc;

// DHT
// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

// Extra
int item_sel = 0; // Hovered menu selection
int total_selections = 2; // Selection 0, 1 and 2. So we start from 0
int selected_Item = 0; // We start on the first selection
bool menuSelected = false; // Swtiches between menu and selected item

// Funtion ProtoTyping
void menu();
void itemHovered();
void menuScroll();
void menuActivation();
void activationButtonISR();
void scrollButtonISR();

void setup() {
  Serial.begin(9600);

  // DHT
  dht.begin();

  // RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  // RTC Adjust
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Don't proceed, loop forever
  }

  display.cp437(true);  // Code page 437

  // Easy Buttons
  // Initializes buttons
  scrollBtn.begin();
  activationBtn.begin();

  // What methode gets used on each button
  scrollBtn.onPressed(menuScroll);
  activationBtn.onPressed(menuActivation);

  // Makes sure i don't have to check the state of the buttons in the loop
  if(scrollBtn.supportsInterrupt()){
    scrollBtn.enableInterrupt(scrollButtonISR);
  }

  if(activationBtn.supportsInterrupt()){
    activationBtn.enableInterrupt(activationButtonISR);
  }
}

void loop() {
  menu();
  display.display();
}

void menu(){
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  if (!menuSelected){
    itemHovered();
	  display.setCursor(1,1); // Place Cursor to start at the top-left corner
    display.print("Clock");
	  display.setCursor(1,22); // Place Cursor under Clock
    display.print("Humidity");
    display.setCursor(1,41); // Place Cursor under Humidity
    display.print("Temperture");
  } else {
    display.clearDisplay();
    display.setCursor(1,1);
    switch (item_sel){
      case 0:
        showTimeDisplay(rtc,display);
        break;
      case 1:
        showHumidityDisplay(dht,display);
        break;
      case 2:
        showTempDisplay(dht,display);
        break;
    }
  }
}

void itemHovered(){
  switch (item_sel){
    case 0:
      display.drawRoundRect(0, 0, 127, 18, 2, WHITE);
      display.drawRoundRect(0, 21, 127, 18, 2, BLACK);
      display.drawRoundRect(0, 40, 127, 18, 2, BLACK);
      break;
    case 1:
      display.drawRoundRect(0, 0, 127, 18, 2, BLACK);
      display.drawRoundRect(0, 21, 127, 18, 2, WHITE);
      display.drawRoundRect(0, 40, 127, 18, 2, BLACK);
      break;
    case 2:
      display.drawRoundRect(0, 0, 127, 18, 2, BLACK);
      display.drawRoundRect(0, 21, 127, 18, 2, BLACK);
      display.drawRoundRect(0, 40, 127, 18, 2, WHITE);
      break;
  }
}

// Easy button methods

void menuScroll(){
  if(!menuSelected){
    if(item_sel < 2){
      item_sel++;
    } else {
      item_sel = 0;
    }
  } else {
    menuSelected = false;
  }
}

void menuActivation(){
  menuSelected = !menuSelected;
}

void activationButtonISR(){
  activationBtn.read();
}

void scrollButtonISR(){
  scrollBtn.read();
}
