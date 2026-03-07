//Import OLED libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Import BME libraries
#include <BME280I2C.h>

#define SCREEN_WIDTH 128 //OLED display width in pixels
#define SCREEN_HEIGHT 64 //OELD display height in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// ESP-32 22(SCL) 21 (SDA)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//Create BME object
BME280I2C bme;


void setup() {
  Serial.begin(115200);

  Wire.begin(21,22);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    while(1){
      Serial.println("test");
    }
  }

  //Initialize BME
  while(!bme.begin())
  {
    Serial.println("test");
  }
  

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  //Set-up settings
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}


void loop(){
  displayEnvironment();

  delay(10);
}


//Displays information from the environmental sensor
void displayEnvironment(){
  //Read the data
  float temp(NAN), hum(NAN), pres(NAN);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  bme.read(pres, temp, hum, tempUnit, presUnit);

  //Clear display
  display.clearDisplay();

  //Display title
  display.setCursor(0,0);
  display.println("ENVIRONMENT INFO");
  display.println();

  //Display temperature
  display.print("Temperature: ");
  display.print(temp);
  display.println(" °C");

  //Display humidity
  display.print("Humidity: ");
  display.print(hum);
  display.println("%");

  //Display pressure
  display.print("Pressure: ");
  display.print(pres);
  display.println(" Pa");

  //Update the display
  display.display();
}
