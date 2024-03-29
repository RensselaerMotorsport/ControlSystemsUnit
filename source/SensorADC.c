//Adapted from Waveshare's example "main" file

#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <time.h>
#include "ADS1263.h"
#include "stdio.h"
#include <string.h>

//Change this to whatever the Jetson Nano calls its pins
#define GPIO_MUX_LSB GPIO20 //20 on the ADC, 38 on the Jetson Nano
#define GPIO_MUX_MSB GPIO21 //21 on the ADC, 40 on the Jetson Nano

// ADC1 test part
#define TEST_ADC1       1
// ADC1 rate test par
#define TEST_ADC1_RATE  1
// ADC2 test part
#define TEST_ADC2       1
// RTD test part    
#define TEST_RTD        1

#define REF         5.08        //Modify according to actual voltage
                                //external AVDD and AVSS(Default), or internal 2.5V

void Handler(int signo)
{
    //System Exit
    printf("\r\n END \r\n");
    DEV_Module_Exit();
    exit(0);
}

//Start up the ADC
void InitADC(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    
    printf("Initializing ADS1263... \r\n");
    //sets up Jetson Nano GPIO
    DEV_Module_Init();

    // 0 is singleChannel, 1 is diffChannel
    ADS1263_SetMode(0);
    
    // The faster the rate, the worse the stability
    // and the need to choose a suitable digital filter(REG_MODE1)
    //contains reset, check chip id, config
    if(ADS1263_init_ADC1(ADS1263_38400SPS) == 1) {
        printf("\r\n END \r\n");
        DEV_Module_Exit();
        exit(0);
    }
}



//Sets the correct channel group on the multiplexer
void SetChannelGroup(int channelGroup){
    //FIXME Not sure if this is the correct format for the Jetson Nano
    UWORD LSB = GPIO_MUX_LSB;
    UWORD MSB = GPIO_MUX_MSB;

    if(channelGroup == 1){
        DEV_Digital_Write(MSB, 0);
        DEV_Digital_Write(LSB, 0);
    }
    else if(channelGroup == 2){
        DEV_Digital_Write(MSB, 0);
        DEV_Digital_Write(LSB, 1);
    }
    else if(channelGroup == 3){
        DEV_Digital_Write(MSB, 1);
        DEV_Digital_Write(LSB, 0);
    }
    else if(channelGroup == 4){
        DEV_Digital_Write(MSB, 1);
        DEV_Digital_Write(LSB, 1);
    }
    //channel 0 is the "fake" channel, don't do anything


    //Waiting for data is already in GetChannalValue, but in case that doesn't work: 
    //struct timespec remaining, request = { 0, 30000 };
    //nanosleep(&request, &remaining);
}

//Returns voltage of port
UDOUBLE FetchSensor(int muxChannel, int port){
    SetChannelGroup(muxChannel);

    //This function includes waiting for the data to be ready
    //also sets pin mode, etc
    UDOUBLE rawData = ADS1263_GetChannalValue(port);
    if((rawData>>31) == 1)
        return (REF*2 - rawData/2147483648.0 * REF);      //7fffffff + 1
    else
        return (rawData/2147483647.0 * REF);       //7fffffff


}

//Run the included demo code from Waveshare
void RunWaveshareTests(void)
{
    UDOUBLE ADC[10];
    UWORD i;
    double RES, TEMP;
    /* Test DAC */
    // ADS1263_DAC(ADS1263_DAC_VLOT_3, Positive_A6, Open);      
    // ADS1263_DAC(ADS1263_DAC_VLOT_2, Negative_A7, Open);
    
    if(TEST_ADC1) {
        printf("TEST_ADC1\r\n");
        
        #define ChannelNumber 5
        UBYTE ChannelList[ChannelNumber] = {0, 1, 2, 3, 4};    // The channel must be less than 10
            
        UDOUBLE Value[ChannelNumber] = {0};
        while(1) {
            ADS1263_GetAll(ChannelList, Value, ChannelNumber);  // Get ADC1 value
            for(i=0; i<ChannelNumber; i++) {
                if((Value[i]>>31) == 1)
                    printf("IN%d is -%lf \r\n", ChannelList[i], REF*2 - Value[i]/2147483648.0 * REF);      //7fffffff + 1
                else
                    printf("IN%d is %lf \r\n", ChannelList[i], Value[i]/2147483647.0 * REF);       //7fffffff
            }
            for(i=0; i<ChannelNumber; i++) {
                printf("\33[1A");   // Move the cursor up
            }
        }
    }
    else if(TEST_ADC2) {
        printf("TEST_ADC2\r\n");
        if(ADS1263_init_ADC2(ADS1263_ADC2_100SPS) == 1) {
            printf("\r\n END \r\n");
            DEV_Module_Exit();
            exit(0);
        }
        while(1) {
            ADS1263_GetAll_ADC2(ADC);   // Get ADC2 value
            for(i=0; i<10; i++) {
                if((ADC[i]>>23) == 1)
                    printf("IN%d is -%lf \r\n", i, REF*2 - ADC[i]/8388608.0 * REF);     //7fffff + 1
                else
                    printf("IN%d is %lf \r\n", i, ADC[i]/8388607.0 * REF);      //7fffff
            }
            printf("\33[10A");//Move the cursor up
        }
    }
    else if(TEST_ADC1_RATE) {
        printf("TEST_ADC1_RATE\r\n");
        struct timespec start={0, 0}, finish={0, 0}; 
        clock_gettime(CLOCK_REALTIME, &start);
        double time;
        UBYTE isSingleChannel = 0;
        if(isSingleChannel) {
            for(i=0; i<10000; i++) {
                ADS1263_GetChannalValue(0);
            }
            clock_gettime(CLOCK_REALTIME, &finish);
            time =  (double)(finish.tv_sec-start.tv_sec)*1000.0 + (double)(finish.tv_nsec-start.tv_nsec)/1000000.0;
            printf("%lf ms\r\n", time);
            printf("single channel %lf kHz\r\n", 10000 / time);

        }
        else {
            for(i=0; i<10000; i++) {
                ADS1263_GetChannalValue(0);
            }
            clock_gettime(CLOCK_REALTIME, &finish);
            time =  (double)(finish.tv_sec-start.tv_sec)*1000.0 + (double)(finish.tv_nsec-start.tv_nsec)/1000000.0;
            printf("%lf ms\r\n", time);
            printf("multi channel %lf kHz\r\n", 10000 / time);
        }

    }
    else if(TEST_RTD) {
        printf("TEST_RTD\r\n");
        ADC[0] = ADS1263_RTD(ADS1263_DELAY_8d8ms, ADS1263_GAIN_1, ADS1263_20SPS);
        RES = ADC[0]/2147483647.0 * 2.0 * 2000.0;   //2000.0 -- 2000R, 2.0 -- 2*i
        printf("Res is %lf \r\n", RES);
        TEMP = (RES/100.0 - 1.0) / 0.00385;     //0.00385 -- pt100
        printf("Temp is %lf \r\n", TEMP);
        printf("\33[2A");//Move the cursor up
    }
}
