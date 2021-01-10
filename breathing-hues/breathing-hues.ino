#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS 59
#define DATA_PIN 5


CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // 3 second delay for recovery
  FastLED.addLeds<LED_TYPE, DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); 
  FastLED.setBrightness(96);
}



int bright_direction = 1; 
uint8_t hue = 0;
uint8_t hue_delta = 12; 
uint8_t saturation = 128;
uint8_t saturation_delta = 1;
uint8_t brightness = 40;
uint8_t start_hue_val = 0; 
uint8_t end_hue_val_delta = 255; 

CHSV start_hue; 
CHSV end_hue;
int current_led = 0; 
uint8_t running_hue = 0; 
 
void loop() {

      FastLED.show(); 

      EVERY_N_MILLISECONDS(100){
        if ((brightness > 100) && ( bright_direction ==1)) {
          start_hue_val++;
          // addGlitter(5);
        }

         
      }

      
     //EVERY_N_MILLISECONDS( 10 ){

         // fill_rainbow (leds, NUM_LEDS, hue, 5);
          start_hue = CHSV( start_hue_val, saturation, brightness); 
          //end_hue = CHSV(start_hue_val + (sin8(end_hue_val_delta)/4), saturation, brightness);
          end_hue = CHSV(start_hue_val + 5 + (sin8(end_hue_val_delta)/20), saturation, brightness);
          fill_gradient (leds, NUM_LEDS, start_hue, end_hue,SHORTEST_HUES);
          end_hue_val_delta++; 

   //  }
      
 
      EVERY_N_MILLISECONDS( 40 ) {
        
        if (brightness > 100)
        {
          saturation = saturation + saturation_delta; 
          if (saturation > 250) saturation_delta = -1; 
          if (saturation <180) saturation_delta = 1; 
        }
        
        brightness = brightness + bright_direction; 
        if (brightness > 180) bright_direction = -1; 
        if (brightness < 40) bright_direction = 1; 
      }
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::DarkViolet;
  }
}
