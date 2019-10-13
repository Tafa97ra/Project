/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Nyaaz
 *
 * Created on 12 October 2019, 20:43
 */

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>

#include "CurrentTime.h"
#include "ADC.h"

/* 
 * DEFINE Variables
 */

// GLOBAL
int RTC_Time;
int SYS_Time;
int HumidT = 0; 
int Temp = 0;
int Light = 0;
int DAC_Out = 0;
int Alarm_ON = 0;
int warn_secs = 0;

// 
long lastInterruptTime = 0;
int DispFreq;
int hours, mins, secs;
int sys_h, sys_m, sys_s;



void initGPIO(){
    
    // RTC
    
    printf("Welcome/n Please wait... /n");
    wiringPiSetup();
    
    RTC = wiringPiI2CSetup(RTCAddr);
    
    
    // Buttons
    for(int j =0;j < sizeof(BTNS)/sizeof(BTNS[0]); j++){
		pinMode(BTNS[j], INPUT);
		pullUpDnControl(BTNS[j], PUD_UP);
	}
    
    wiringPiISR(BTNS[0], INT_EDGE_FALLING, &DispFreqChange);
    wiringPiISR(BTNS[1], INT_EDGE_FALLING, &Reset_Timer);
    wiringPiISR(BTNS[2], INT_EDGE_FALLING, &Stop);
    wiringPiISR(BTNS[3], INT_EDGE_FALLING, &DismissAlarm);
    
    
    // LEDs (Alarm)
    pwmSetRange(60);
    pinMode(LEDS[0], PWM_OUTPUT);
    pinMode(LEDS[1], PWM_OUTPUT);
    pinMode(LEDS[2], PWM_OUTPUT);
    
    
    // LDR
    // Temperature
    // Humidity
    // Vout
    
    printf("Done Setting Up/n")
    delay(500);

}

void initialize(){
    hours = 0;
    mins = 0;
    secs = 0;
    sys_h = 0;
    sys_m = 0;
    sys_s = 0;
    DispFreq = 1;
            
    
    //RTC set
    wiringPiI2CWriteReg8(RTC, HOUR, 0x0+TIMEZONE);
    wiringPiI2CWriteReg8(RTC, MIN, 0x0);
    wiringPiI2CWriteReg8(RTC, SEC, 0x80);
}



/*
 * 
 */
int main(void) {
    
    initGPIO();
    initialize();
    
    
   /* 
    for (;;){
		//Fetch RTC time
                hours = (wiringPiI2CReadReg8(RTC, HOUR));
		mins = (wiringPiI2CReadReg8(RTC, MIN));
                secs = (wiringPiI2CReadReg8(RTC, SEC));
                int osc = 0b1000000;
                
                
                // Print RTC time
		printf("Time of Day: %d", hours);
                if(mins < 10){
                    printf(":0%d", mins);
                }else{
                    printf(":%d", mins);}
                if(secs < 10){
                    printf(":0%d\n", secs);
                }else{
                    printf(":%d\n", secs);}
                
                // Print SYS time
                printf("System time: %d", sys_h);
                if(mins < 10){
                    printf(":0%d", sys_m);
                }else{
                    printf(":%d", sys_m);}
                if(secs < 10){
                    printf(":0%d\n", sys_m);
                }else{
                    printf(":%d\n", sys_m);}
                
                
                printf("Light %d\n", Light);
                printf("Temp %d\n", Temp);
                printf("Humidity %d\n", HumidT);
                
                
		//using a delay to make our program "less CPU hungry"
		delay(1000); //milliseconds
	}
    * 
    * */
    return (0);
}

void ADC(){}

void Reset_Timer(){
}

void DispFreqChange(){
    // Debounce
    long interruptTime = millis();
    
    if(interruptTime - lastInterruptTime > 200){
        if (DispFreq == 1)
            DispFreq = 2;
        if (DispFreq == 2)
            DispFreq = 5;
        if (DispFreq == 5)
            DispFreq = 1;
    }
    lastInterruptTime = interruptTime;
}

int Stop(){}

void Alarm(){       //Thread
    
    if (warn_sec <= 180){
        
    }else{
        warn_sec = 0;
        
    }
}

int DismissAlarm(){
    // Debounce
    long interruptTime = millis();
        
    if (interruptTime - lastInterruptTime>200){
	pwmWrite(LEDS[0], 0);
        pwmWrite(LEDS[1], 0);
        pwmWrite(LEDS[2], 0);	  
    }
    lastInterruptTime = interruptTime;
    
    Alarm_ON = 0;
}

void Alarm_LEDs(){
    
    int i = 40;
    int a = 0; 
    int b = 20;
    int c = 40;
    
    for(;;){
        if (a > 40)
            a = 0;
        if (b > 40)
            b = 0;
        if (c > 40)
            c = 0;
        
        pwmWrite(LEDS[0], i - a);
        pwmWrite(LEDS[1], i - b);
        pwmWrite(LEDS[2], i - c);
        
        a += 1;
        b += 1;
        c += 1;
    }
    return;
    
}

int Temprature(){}

int Light(){}

int Humidity(){}

int Vout(){}




