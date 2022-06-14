/* =====================================================================
    __  __      _____  ______  _   _  _______   _____   ____   _____
    \ \ \ \    / ____||  ____|| \ | ||__   __| / ____| / __ \ |  __ \
  __ \ \ \ \  | (___  | |__   |  \| |   | |   | (___  | |  | || |__) |
  \ \ \ \ \_\  \___ \ |  __|  |     |   | |    \___ \ | |  | ||  _  /
   \ \ \ \     ____) || |____ | |\  |   | |    ____) || |__| || | \ \
    \_\ \_\   |_____/ |______||_| \_|   |_|   |_____/  \____/ |_|  \_\

  Project      : Uno Plus - Self test
  Description  : Do basic test to check built-in functionality
  Author       : SENTSOR
  Note         : Using ATmega328PB on MicroCore bootloader

  ===================================================================== */

#define DEBUG Serial
#define onboardLed 23
#define onboardRGB 24
#define ssPin 10

#include <SD.h>
#include <RTClib.h>
#include <Adafruit_NeoPixel.h>

RTC_DS1307 rtc;
Adafruit_NeoPixel rgb = Adafruit_NeoPixel(1, onboardRGB, NEO_GRB + NEO_KHZ800);

void setup() {
  //Start serial and begin the test
  Serial.begin(9600, SERIAL_8N1);
  DEBUG.print(F("\n\nSENTSOR Uno Plus Self-Test\n"));
  delay(500);

  //RTC test: RTC init, check RTC timekeep, print current timestamp
  DEBUG.print(F("DEBUG >> Initializing RTC... "));
  if (rtc.begin()) {
    DEBUG.print(F("OK\n"));
    rtc.writeSqwPinMode(DS1307_OFF);
    delay(500);

    DEBUG.print(F("DEBUG >> Checking RTC timekeep... "));
    if (!rtc.isrunning()) {
      //It means our RTC didn't keeping time, usually because the battery is removed or dead
      DEBUG.print(F("FAILED\n"));
      DEBUG.print(F("DEBUG >> Reseting RTC to sketch upload time\n"));
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    else {
      DEBUG.print(F("OK\n"));
    }
    DEBUG.print(F("DEBUG >> RTC timestamp is "));
    DateTime time = rtc.now();
    DEBUG.print(time.timestamp(DateTime::TIMESTAMP_DATE)); DEBUG.print(F(" "));
    DEBUG.print(time.timestamp(DateTime::TIMESTAMP_TIME)); DEBUG.print(F("\n"));
    delay(500);
  }
  else {
    DEBUG.print(F("FAILED\n"));
    DEBUG.print(F("DEBUG >> RTC not initialized\n"));
    delay(500);
  }

  //SD test: SD init with slave select (SS) at pin 10, write/read/delete file
  DEBUG.print(F("DEBUG >> Initializing memory card... "));
  if (SD.begin(ssPin)) {
    DEBUG.print(F("OK\n"));
    delay(500);

    File file;
    const char filename[15] = "sentsor.txt";
    char text[30] = "Hello from SENTSOR Board!";

    DEBUG.print(F("DEBUG >> Writing test file... "));
    file = SD.open(filename, FILE_WRITE);
    if (file) {
      DEBUG.print(F("\"")); DEBUG.print(text); DEBUG.print(F("\" "));
      file.print(text);
      file.close();
      DEBUG.print(F("OK\n"));
      delay(500);

      DEBUG.print(F("DEBUG >> Reading test file... "));
      file = SD.open(filename, FILE_READ);
      if (file) {
        file.read(text, 30);
        DEBUG.print(F("\"")); DEBUG.print(text); DEBUG.print(F("\" "));
        file.close();
        DEBUG.print(F("OK\n"));
        delay(500);
      }
      else {
        DEBUG.print(F("FAILED\n"));
        DEBUG.print(F("DEBUG >> Unable to read file\n"));
        delay(500);
      }

      DEBUG.print(F("DEBUG >> Removing test file... "));
      if (SD.remove(filename)) {
        DEBUG.print(F("OK\n"));
        delay(500);
      }
      else {
        DEBUG.print(F("FAILED\n"));
        DEBUG.print(F("DEBUG >> Unable to remove file\n"));
        delay(500);
      }
    }
    else {
      DEBUG.print(F("FAILED\n"));
      DEBUG.print(F("DEBUG >> Unable to write file\n"));
      delay(500);
    }
  }
  else {
    //SD.begin return false if didn't detect the MicroSD card
    DEBUG.print(F("FAILED\n"));
    DEBUG.print(F("DEBUG >> Memory card not initialized\n"));
    delay(500);
  }

  //Blink onboard LED at pin 23
  DEBUG.print(F("DEBUG >> Configuring pin D22 as output for onboard LED\n"));
  pinMode(onboardLed, OUTPUT);
  DEBUG.print(F("DEBUG >> Onboard LED should blink 3 times"));
  for (uint8_t i = 0; i < 3; i++) {
    DEBUG.print(F("."));
    digitalWrite(onboardLed, LOW);
    delay(1000);
    digitalWrite(onboardLed, HIGH);
    delay(1000);
  }
  DEBUG.print(F(" OK\n"));

  //RGB LED at pin 23
  DEBUG.print(F("DEBUG >> Configuring pin IO4 as output for onboard RGB LED\n"));
  rgb.begin();
  rgb.setBrightness(20);
  DEBUG.print(F("DEBUG >> Onboard RGB LED should be light: "));
  DEBUG.print(F("red"));
  rgb.setPixelColor(0, rgb.Color(255, 0, 0));
  rgb.show();
  delay(1000);
  DEBUG.print(F("-green"));
  rgb.setPixelColor(0, rgb.Color(0, 255, 0));
  rgb.show();
  delay(1000);
  DEBUG.print(F("-blue"));
  rgb.setPixelColor(0, rgb.Color(0, 0, 255));
  rgb.show();
  delay(1000);
  rgb.setPixelColor(0, rgb.Color(0, 0, 0));
  rgb.show();
  DEBUG.print(F(" OK\n"));

  DEBUG.print(F("DEBUG >> Onboard RGB LED should cycling rainbow color 3 times"));
  for (uint16_t i = 0; i < 256 * 3; i++) {
    if (i % 256 == 0) DEBUG.print(F("."));

    for (uint16_t j = 0; j < rgb.numPixels(); j++) {
      rgb.setPixelColor(j, colorWheel(((j * 256 / rgb.numPixels()) + i) & 255));
    }
    rgb.show();
    delay(10);
  }
  DEBUG.print(F(" OK\n"));

  DEBUG.print(F("DEBUG >> Self-test complete\n"));
  DEBUG.print(F("DEBUG >> Entering standby mode\n"));
  DEBUG.print(F("\n"));
  delay(500);
}

void loop() {
  //Idle: blinking LED, RGB color wheel, print timestamp
  static uint32_t lastMillis;
  if (millis() - lastMillis >= 5000L) {
    lastMillis = millis();
    
    //LED blink
    digitalWrite(onboardLed, LOW);
    delay(100);
    digitalWrite(onboardLed, HIGH);

    //Print timestamp
    DEBUG.print(F("STANDBY >> RTC: "));
    DateTime time = rtc.now();
    DEBUG.print(time.timestamp(DateTime::TIMESTAMP_DATE)); DEBUG.print(F(" "));
    DEBUG.print(time.timestamp(DateTime::TIMESTAMP_TIME)); DEBUG.print(F("\n"));
  }

  //RGB color wheel
  for (uint16_t j = 0; j < 256; j++) {
    for (uint16_t i = 0; i < rgb.numPixels(); i++) {
      rgb.setPixelColor(i, colorWheel(((i * 256 / rgb.numPixels()) + j) & 255));
    }
    rgb.show();
    delay(10);
  }
}

uint32_t colorWheel(uint8_t pos) {
  pos = 255 - pos;
  if (pos < 85) {
    return rgb.Color(255 - pos * 3, 0, pos * 3);
  } else if (pos < 170) {
    pos -= 85;
    return rgb.Color(0, pos * 3, 255 - pos * 3);
  } else {
    pos -= 170;
    return rgb.Color(pos * 3, 255 - pos * 3, 0);
  }
}

// End of File [SENTSOR]
