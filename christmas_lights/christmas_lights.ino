/*
Program: Christmas lights
Version: 0.1
Author: oxfn@ya.ru
 */
#include <math.h>

#define PIN_A 13
#define PIN_B 12
#define PIN_C 11
#define PIN_D 10
#define DELAY_MAX 200
#define DELAY_MIN 50
#define DELAY_STEP 5
#define MODE_RUN 0x01
#define MODE_STROBE 0x02
#define POWER_OFF 0x00
#define POWER_ON 0x01

unsigned short int g_power = POWER_ON;
unsigned short int g_mode = MODE_STROBE;
unsigned short int g_delay = DELAY_MAX;
unsigned short int g_state = 0;
short int g_delay_mode = -1;
//unsigned short int 

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  // Change delay mode
  if (g_delay >= DELAY_MAX) {
    g_delay_mode = -1;
    
    // Change operation mode
    if (g_mode == MODE_RUN) {
      g_mode = MODE_STROBE;
    } else {
      g_mode = MODE_RUN;
    }
    
    // Reset state
    g_state = 0;
  } else if (g_delay <= DELAY_MIN) {
    g_delay_mode = 1;
  }
  
  // Operate in strobe mode
  if (g_mode == MODE_STROBE) {
    if (g_state == 0x01) {
      digitalWrite(PIN_A, HIGH);
      digitalWrite(PIN_B, HIGH);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, HIGH);
      g_state = 0x00;
    } else {
      digitalWrite(PIN_A, LOW);
      digitalWrite(PIN_B, LOW);
      digitalWrite(PIN_C, LOW);
      digitalWrite(PIN_D, LOW);
      g_state = 0x01;
    }
  } else if (g_mode = MODE_RUN) {
    
    // PIN A
    if (g_state == 1) {
      digitalWrite(PIN_A, HIGH);
      g_state = 2;
    } else {
      digitalWrite(PIN_A, LOW);
    
      // PIN B
      if (g_state == 2) {
        digitalWrite(PIN_B, HIGH);
        g_state = 4;
      } else {
        digitalWrite(PIN_B, LOW);
        
        // PIN C  
        if (g_state == 4) {
          digitalWrite(PIN_C, HIGH);
          g_state = 8;
        } else {
          digitalWrite(PIN_C, LOW);
          
          // PIN D
          if (g_state == 8) {
            digitalWrite(PIN_D, HIGH);
            g_state = 0;
          } else {
            digitalWrite(PIN_D, LOW);
            if (g_state == 0) {
              g_state = 1;
            }
          }
        }
      }
    }
  }
  
  // Update delay
  g_delay += DELAY_STEP * g_delay_mode;
  
  // Delay
  if (g_mode == MODE_STROBE) {
    delay(g_delay + 20);
  } else {
    delay(g_delay);
  }
}
