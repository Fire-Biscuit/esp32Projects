#include "ssd1306.h"//library for interacting with the Oled display
#include "pinNumbers.h"//getting the right gpio pins for sda and scl connections


void ClearScreen();

/// @brief sets up the i2c connection to the Oled
/// @return handle used to interact via the i2c connection
ssd1306_handle_t oledSetup(){
    static ssd1306_handle_t ssd1306_dev = NULL;

    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = (gpio_num_t)I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = (gpio_num_t)I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    printf("conf initialised\n");

    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);

    printf("parms set\n");

    ssd1306_dev = ssd1306_create(I2C_MASTER_NUM, SSD1306_I2C_ADDRESS);
    ssd1306_refresh_gram(ssd1306_dev);
    ClearScreen(ssd1306_dev);
    
    printf("i2c connection made correctly\n");

    return ssd1306_dev;
}

/// @brief resets the Oled screen to a blank slate
/// @param ssd1306_dev 
void ClearScreen(ssd1306_handle_t ssd1306_dev){
    ssd1306_fill_rectangle(ssd1306_dev,0,0,128,64,0);
    ssd1306_refresh_gram(ssd1306_dev);
}