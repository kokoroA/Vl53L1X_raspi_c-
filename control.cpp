#include "control.hpp"

uint8_t range_gbuf[16];
int8_t Status = 0;
int16_t OffsetValue = 0;
uint16_t dev = 0x29;
uint16_t distance = 0;
uint8_t isDataReady = 0;
uint8_t rangeStatus = 0;
uint8_t state = 0;
int ms = 200;

int main (void) {
    //I2c initialization
    stdio_init_all();
    i2c_init(I2C_PORT,i2C_CLOCK);//ハードウェアの初期化
    gpio_set_function(SDA_PIN,GPIO_FUNC_I2C);//GPIO機能をi2cに選択(SDA)
    gpio_set_function(SCL_PIN,GPIO_FUNC_I2C);//GPIO機能をi2cに選択(SCL)
    gpio_set_pulls(SDA_PIN, true, false);// enable internal pull-up of SDA_PIN=GP26
    gpio_set_pulls(SCL_PIN, true, false);// enable internal pull-up of SCL_PIN=GP27

    // /* Platform Initialization code here*/
    // /* Wait for device booted*/
    sleep_ms(3000);

    while((state&1) == 0 ) {
        Status = VL53L1X_BootState(dev, &state);
        sleep_ms(ms);
    };

    // /* Sensor Initialization */
    Status = VL53L1X_SensorInit(dev);

    // /* Modify the default configuration */
    Status = VL53L1X_SetDistanceMode(dev,2);
    Status = VL53L1X_SetTimingBudgetInMs(dev,20);
    Status = VL53L1X_SetInterMeasurementInMs(dev,20);

    //Enable the ranging
    Status = VL53L1X_StartRanging(dev);

    // /* ranging loop */
    while(1){
        //センサーの準備が整うまで待機
        if (isDataReady == 0){
            Status = VL53L1X_CheckForDataReady(dev,&isDataReady);
        }
        //値の受け取り
        else if(isDataReady == 1){
            isDataReady =0;
            Status = VL53L1X_GetRangeStatus(dev,&rangeStatus);
            Status = VL53L1X_GetDistance(dev,&distance);
            Status = VL53L1X_ClearInterrupt(dev);
            printf("%4d \n",distance);
        }
    }
}