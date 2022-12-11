//references: https://www.youtube.com/watch?v=Ukq0tH2Tnkc；https://www.youtube.com/watch?v=2owTxbrmY-s&t=192s; https://create.arduino.cc/projecthub/pibots555/how-to-connect-dht11-sensor-with-arduino-uno-f4d239; https://arduinogetstarted.com/tutorials/arduino-temperature-humidity-sensor; https://create.arduino.cc/projecthub/arcaegecengiz/how-to-use-a-touch-sensor-81b7f4
#include <DHT.h> // call the humanity sensor library
#include <FastLED.h>// call the stript light sensor
#define NUM_LEDS  60 // the number of led on stript light that will be used
#define LED_PIN   2
#define touch 3
#define DHTPIN A1
#define DHTTYPE DHT11  //let arduino match the type of humanity sensor
DHT dht(DHTPIN, DHTTYPE);
CRGB leds[NUM_LEDS];

int potVal;

uint8_t colorIndex[NUM_LEDS];
//create the gradient type
DEFINE_GRADIENT_PALETTE( talk ) { 
  0,   222,  27, 27,
  59,  255,  0,  137,
  110, 255, 0, 137,
  158, 122, 255, 120,
  255, 222,27,27,
};
CRGBPalette16 greenblue = talk; //activate the light

void setup() {
pinMode(touch,INPUT);
pinMode(LED_PIN,OUTPUT);  
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS); //set up the strip light
  FastLED.setBrightness(30);
  Serial.begin(9600);
 dht.begin();
for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8(); //filling the array with random numbers between 0-255, let each led start from a different part of the pattern 
  }
}

void loop() {
 potVal = analogRead(A1);  
 float h = dht.readHumidity();
  //Serial.println(F("Humidity: "));
  Serial.println(h);                
 int touchValue =digitalRead(touch);
  if(touchValue== LOW){
uint8_t pos = map(beat8(20, 0), 0, 255, 0, NUM_LEDS -1);//creste a beat8 sawtooth wave(dosen't have low/high vowel parameter--use as position
  leds[pos] = CRGB::ForestGreen ;//give the strip light color from CRGB
                                //find crgb in here: http://fastled.io/docs/3.1/struct_c_r_g_b.html
  fadeToBlackBy(leds, NUM_LEDS, 8);

  FastLED.show();
  }else{
for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(greenblue, colorIndex[i]);// set the color of each led to its color index that is specified in the array from 0-255
  // each led will start at different point of the palette
  }
  
  EVERY_N_MILLISECONDS(3){ //every 3 seconds
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex[i]++;//increase the color index to cycle the color palette
    }
     FastLED.show();
  }
  delay(100);
  }
}