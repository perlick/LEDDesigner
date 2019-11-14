#include <FastLED.h>
#include <IRremote.h>

#define NUM_LEDS 300
#define DATA_PIN 5

CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

const int RECV_PIN = 7;
const int SEND_PIN = 12;

IRrecv irrecv(RECV_PIN);
decode_results results;

unsigned long current_time;
unsigned long previous_time = 0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  pinMode(SEND_PIN, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        show_select(results.value);
        irrecv.resume();
  }
}

void show_select(unsigned long value){
  if(value == 0xFF6897){
    show0();
  }else if(value == 0xFF30CF){
    show1(60, 0, 0, 3000, 25, 15, true);
  }else if(value == 0xFF18E7){
    show2();
  }else if(value == 0xFF7A85){
    show3(60, 60, 60, 16, 0);
    show3(60, 60, 60, 16, 1);
    show3(60, 60, 60, 16, 2);
    show3(60, 60, 60, 16, 3);
  }else if(value == 0xFF10EF){
    show4();
  }else if(value == 0xFF38C7){
    show5();
  }else if(value == 0xFF5AA5){
    show6();
  }else if(value == 0xFF42BD){
    show7();
  }else if(value == 0xFF4AB5){
    show8();
  }else if(value == 0xFF52AD){
    show9();
  }else if(value == 0xFFE21D){
    color_shift(-1,true);
  }else if(value == 0xFF629D){
    color_shift(-1,false);
  }else if(value == 0xFFC23D){
    color_shift(0,true);
  }else if(value == 0xFF02FD){
    color_shift(0,false);
  }else if(value == 0xFF906F){
    color_shift(1,true);
  }else if(value == 0xFFA857){
    color_shift(1,false);
  }
}

//fade from current color to color defined in arguments over specified # of num_steps
//think about adding way to fade certain LEDS based on function
void show0(){
  unsigned long start = millis();
  
  unsigned long last_update = 0;
  unsigned long last_update_1 = 0;
  unsigned long last_update_2 = 0;
  unsigned long last_update_3 = 0;
  while(millis() <= start+10000){
    last_update_2 = fade(150, 175, start, start + 2000, last_update_2, 0, 128, 64);
    last_update_2 = fade(150, 175, start +2000, start + 4000, last_update_2, 0, 0, 0);
    last_update_2 = fade(150, 175, start + 4000, start + 6000, last_update_2, 0, 128, 64);
    last_update_2 = fade(150, 175, start + 6000, start + 8000, last_update_2, 0, 0, 0);
    last_update_2 = fade(150, 175, start + 8000, start + 10000, last_update_2, 0, 128, 64);
    
    last_update = walk_loop(176, 299, start, start+10000, last_update, 50);
    last_update_1 = walk_loop(149, 0, start, start+10000, last_update_1, 50);
  }
}

//sparkle. High values of lights per update may exceed xd6
void show1(int r, int g, int b, int duration, int ms_per_update, int lights_per_update, boolean return_to_bg){
  lights_per_update = constrain(lights_per_update, 0, 25);
  CRGB temp[lights_per_update];
  int temp2[lights_per_update];
  boolean valid = true;

  for( int j = 0; j<(duration/ms_per_update);j++){
    for(int i = 0; i<lights_per_update;i++){
      int light = random(0,299);

      for(int k = 0; k<=i;k++){
        if(temp2[k] == light){
          valid = false;
          i--;
          break;
        }
      }

      if(valid){temp2[i] = light;}
      valid=true;
    }
    for(int i = 0; i<lights_per_update;i++){
      temp[i].r = leds[temp2[i]].r;
      temp[i].g = leds[temp2[i]].g;
      temp[i].b = leds[temp2[i]].b;

      leds[temp2[i]].r = r;
      leds[temp2[i]].g = g;
      leds[temp2[i]].b = b;
      }
    FastLED.show();
    if(return_to_bg){
      for(int i = 0; i<lights_per_update;i++){
        leds[temp2[i]].r = temp[i].r;
        leds[temp2[i]].g = temp[i].g;
        leds[temp2[i]].b = temp[i].b;
      }
    }

    delay(ms_per_update);
  }
  FastLED.show();
}

void show2(){
  for(int i=0; i<NUM_LEDS; i++){
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }
    FastLED.show();
}

void show3(int r, int g, int b, int mod, int offset){
  for(int i=0; i<NUM_LEDS; i++){
    if(i%mod==offset){
      leds[i].r = r;
      leds[i].g = g;
      leds[i].b = b;
    }
  }
    FastLED.show();
}

void show4(){
  for(int i=0; i<NUM_LEDS; i++){
      leds[i].r = (int) random(0,255);
      leds[i].g = (int) random(0,255);
      leds[i].b = (int) random(0,255);
    }
    FastLED.show();
}

void show5(){
  leds[299].r = 128;
  leds[299].g = 0;
  leds[299].b = 0;
  FastLED.show();
}

void show6(){
  int x = 1;
}

void show7(){
  int x = 1;
}

void show8(){
  int x = 1;
}

void show9(){
  int x = 1;
}

//fade from from the current rgb value to r,g,b
//needs to be corrected to implement a linear fade
unsigned long fade(int start_led, int end_led, unsigned long start_millis, unsigned long end_millis, unsigned long last_update, int r, int g, int b){
  unsigned long cur_millis = millis();

  if(cur_millis>=start_millis and cur_millis<end_millis){
    if(last_update == 0){
      last_update = millis();
    }
    float adjust_by = ((float) (cur_millis - start_millis))/(last_update - start_millis);
    for(int i=start_led; i<=end_led; i++){
      // leds[i].r += (int) (r - leds[i].r)*adjust_by;
      // leds[i].g += (int) (g - leds[i].g)*adjust_by;
      // leds[i].b += (int) (b - leds[i].b)*adjust_by;
      leds[i].r = (((float) (r - leds[i].r)*(cur_millis - last_update))/(end_millis - last_update)) + leds[i].r;
      leds[i].g = (((float) (g - leds[i].g)*(cur_millis - last_update))/(end_millis - last_update)) + leds[i].g;
      leds[i].b = (((float) (b - leds[i].b)*(cur_millis - last_update))/(end_millis - last_update)) + leds[i].b;
    }
    last_update = cur_millis;
    FastLED.show();
  }
  return last_update;
}

//walk current animation down the strip
unsigned long walk_loop(int start_index, int end_index, unsigned long start_time, unsigned long end_time, unsigned long last_update, unsigned long millis_per_update){
  unsigned long curr_time = millis();
  if (curr_time>=start_time and curr_time<end_time and (curr_time - last_update)>= millis_per_update){
    int tr;
    int tg;
    int tb;
    if(start_index < end_index){
      tr = leds[end_index].r;
      tg = leds[end_index].g;
      tb = leds[end_index].b;
      for(int j=end_index;j>start_index;j--){
        leds[j].r = leds[j-1].r;
        leds[j].g = leds[j-1].g;
        leds[j].b = leds[j-1].b;
      }
      leds[start_index].r = tr;
      leds[start_index].g = tg;
      leds[start_index].b = tb;
    }else{
      tr = leds[end_index].r;
      tg = leds[end_index].g;
      tb = leds[end_index].b;
      for(int j=end_index;j<start_index;j++){
        leds[j].r = leds[j+1].r;
        leds[j].g = leds[j+1].g;
        leds[j].b = leds[j+1].b;
      }
      leds[start_index].r = tr;
      leds[start_index].g = tg;
      leds[start_index].b = tb;
    }
    last_update = curr_time;
  }
  FastLED.show();
  return last_update;
}


void color_shift(int color, boolean sign){
  if(sign){
    for(int i=0; i<NUM_LEDS;i++){
      if(color==-1){
        leds[i].r += 6;
      }else if(color==0){
        leds[i].g += 6;
      }else if(color==1){
        leds[i].b += 6;
      }
    }
  }else{
    for(int i=0; i<NUM_LEDS;i++){
      if(color==-1){
        leds[i].r -= 6;
      }else if(color==0){
        leds[i].g -= 6;
      }else if(color==1){
        leds[i].b -= 6;
      }
    }
  }
  FastLED.show();
}
