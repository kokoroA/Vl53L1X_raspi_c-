#include "test.h"
// #define I2C_TIME_OUT_BASE   10
// #define I2C_TIME_OUT_BYTE   1
// #define I2C_PORT i2c1
// #define I2C_ADDRESS 0x0001
// #define i2C_CLOCK (400*1000)
// #define NORMAL_WAIT 500
// #define SDA_PIN 26  // GP27 = Pin.31 = SDA
// #define SCL_PIN 27  // GP26 = Pin.32 = SCL

int8_t Status = 0;
int16_t OffsetValue =0;
uint16_t dev = 0x52;
uint16_t distance = 0;
uint8_t isDataReady = 0;
uint8_t rangeStatus = 0;
uint8_t state = 1;
int sleep_time = 2000;
int ms = 2;

int main (void) {
    stdio_init_all();
    i2c_init(I2C_PORT,i2C_CLOCK);//ハードウェアの初期化
    gpio_set_function(SDA_PIN,GPIO_FUNC_I2C);//GPIO機能をi2cに選択(SDA)
    gpio_set_function(SCL_PIN,GPIO_FUNC_I2C);//GPIO機能をi2cに選択(SCL)
    gpio_set_pulls(SDA_PIN, true, false);// enable internal pull-up of SDA_PIN=GP26
    gpio_set_pulls(SCL_PIN, true, false);// enable internal pull-up of SCL_PIN=GP27
    // /* Platform Initialization code here*/
    // /* Wait for device booted*/

    // while(1){
    //     printf("finish setup\n");
    // }

    while(state) {
        Status = VL53L1X_BootState(dev, &state);
        sleep_ms(ms);
        printf(Status);
    };

    // /* Sensor Initialization */
    // Status = VL53L1X_SensorInit(dev);
    // /* Modify the default configuration */
    // // Status = VL53L1X_SetInterMeasurementPeriod();
    // Status = VL53L1X_SetOffset(dev,OffsetValue);
    // printf("Finish intialize\n");

    // /* ranging loop */
    // while(1){
    //     while(isDataReady==0){
    //         Status = VL53L1X_CheckForDataReady (dev, &isDataReady);
    //     }
    //     isDataReady =0;
    //     Status = VL53L1X_GetRangeStatus(dev,&rangeStatus);
    //     Status = VL53L1X_GetDistance(dev,&distance);
    //     Status = VL53L1X_ClearInterrupt(dev);
    //     printf(Status);
    //     printf("Hello\n");
    // }
    // while(1){
    //     printf("Hello\n");
    // }
}