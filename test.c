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
int16_t OffsetValue = 0;
uint16_t dev = 0x29;
uint16_t distance = 0;
uint8_t isDataReady = 0;
uint8_t rangeStatus = 0;
uint8_t state = 0;
uint8_t tmp = 0;
int sleep_time = 2000;
int ms = 200;
uint64_t start_time,current_time;

int main (void) {
    // uint8_t byte_data_read[16]; //readした値の格納用
    // uint8_t byte_data_write[16];//書き込む値の格納用
    // uint8_t _I2CBuffer[256];
    // byte_data_write[0] = 2; 
    // byte_data_write[1] = 1;
    // uint16_t index = 0x00E5;
    // uint16_t test =  0x010F;
    // _I2CBuffer[0] = index>>8;
	// _I2CBuffer[1] = index&0xFF;
    // uint8_t byteREAD[16];

    stdio_init_all();
    i2c_init(I2C_PORT,i2C_CLOCK);//ハードウェアの初期化
    gpio_set_function(SDA_PIN,GPIO_FUNC_I2C);//GPIO機能をi2cに選択(SDA)
    gpio_set_function(SCL_PIN,GPIO_FUNC_I2C);//GPIO機能をi2cに選択(SCL)
    gpio_set_pulls(SDA_PIN, true, false);// enable internal pull-up of SDA_PIN=GP26
    gpio_set_pulls(SCL_PIN, true, false);// enable internal pull-up of SCL_PIN=GP27
    // /* Platform Initialization code here*/
    // /* Wait for device booted*/

    sleep_ms(3000);

    // Status = i2c_write_timeout_us(I2C_PORT,dev,byte_data_write,2,false,600); 
    // Status = i2c_read_timeout_us(I2C_PORT,dev,byte_data_read,1,false,600);

    while((state&1) == 0 ) {
        Status = VL53L1X_BootState(dev, &state);
        sleep_ms(ms);
        // printf("state : %d\n",state&1);
        // printf("Status : %d\n",Status);
    };

    // /* Sensor Initialization */
    Status = VL53L1X_SensorInit(dev);

    // while(1){
    //     printf("Status(sensor init) : %d\n",Status);
    // }

    // /* Modify the default configuration */
    // // Status = VL53L1X_SetInterMeasurementPeriod();
    // Status = VL53L1X_SetOffset(dev,OffsetValue);
    Status = VL53L1X_SetDistanceMode(dev,2);
    Status = VL53L1X_SetTimingBudgetInMs(dev,500);
    Status = VL53L1X_SetInterMeasurementInMs(dev,500);

    //Enable the ranging
    Status = VL53L1X_StartRanging(dev);

    // /* ranging loop */
    start_time = time_us_64();
    current_time = start_time;
    while(1){
        while(isDataReady==0){
            Status = VL53L1X_CheckForDataReady(dev, &isDataReady);
            // printf("--------------------------------------\n");
            // printf("Status (isDataReady loop) : %d\n", Status);
            // printf("isDataReady (isDataReady loop) : %d\n", isDataReady);
            // printf("--------------------------------------\n");
        }
        // while(1){
        //     printf("Status(ranging loop) : %d\n",Status);
        //     printf("isDataReady (ranging loop) : %d\n", isDataReady);
        // }
        isDataReady =0;
        Status = VL53L1X_GetRangeStatus(dev,&rangeStatus);
        Status = VL53L1X_GetDistance(dev,&distance);
        Status = VL53L1X_ClearInterrupt(dev);
        // printf(" Status(ranging loop) : %d\n ",Status);
        printf("%9.6f %4d\n",(current_time-start_time)/1000000.0,distance);
        current_time = time_us_64();
        // printf("distance : %d\n",distance);
    }
}