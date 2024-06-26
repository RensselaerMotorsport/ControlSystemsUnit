//Adapted from Waveshare's example "main" file
#include "SensorADC.h"

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
    // Sets up Jetson Nano GPIO
    std::cout << "Mux LSB Pin Num: " << GPIO_MUX_LSB << std::endl;
    std::cout << "Mux MSB Pin Num: " << GPIO_MUX_MSB << std::endl;
    std::cout << "Output Pin: " << GPIO::OUT << std::endl;
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(GPIO_MUX_LSB, GPIO::OUT);
    GPIO::setup(GPIO_MUX_MSB, GPIO::OUT);

    // 0 is singleChannel, 1 is diffChannel
    ADS1263_SetMode(0);

    // The faster the rate, the worse the stability
    // and the need to choose a suitable digital filter(REG_MODE1)
    //contains reset, check chip id, config
    // initializing adc's in samples per second (sps)
    // #ifndef TEST_MODE
    if (ADS1263_init_ADC1(ADS1263_4800SPS) == 1) { Handler(0); }
    if (ADS1263_init_ADC2(ADS1263_ADC2_800SPS) == 1) { Handler(0); }
    // #endif
}

//Sets the correct channel group on the multiplexer
void SetChannelGroup(int channelGroup){
    switch(channelGroup) {
        case 1:
            GPIO::output(GPIO_MUX_MSB, GPIO::LOW);
            GPIO::output(GPIO_MUX_LSB, GPIO::LOW);
            break;
        case 2:
            GPIO::output(GPIO_MUX_MSB, GPIO::LOW);
            GPIO::output(GPIO_MUX_LSB, GPIO::HIGH);
            break;
        case 3:
            GPIO::output(GPIO_MUX_MSB, GPIO::HIGH);
            GPIO::output(GPIO_MUX_LSB, GPIO::LOW);
            break;
        case 4:
            GPIO::output(GPIO_MUX_MSB, GPIO::HIGH);
            GPIO::output(GPIO_MUX_LSB, GPIO::HIGH);
            break;
        default:
            //channel 0 is the "fake" channel, don't do anything
            break;
    }

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
