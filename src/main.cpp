#include <mbed.h>

#define DRY_VALUE 0.86f
#define WET_VALUE 0.40f

int main(void)
{
    AnalogIn soil_sensor(A0);
    PwmOut GREEN{PTC10};
    PwmOut RED{PTC11};

    GREEN.period_ms(1);
    RED.period_ms(1);

    while (true)
    {
        float sensor_value = soil_sensor.read();
        float moisture_level = (sensor_value - DRY_VALUE) / (WET_VALUE - DRY_VALUE);
        printf("Soil moisture: %.2f\n", moisture_level);

        if (moisture_level < 0.5f)
        {
            GREEN.write(0.0f);
            RED.write(1.0f);
            printf("Water the plant!\n");
        }
        else
        {
            RED.write(0.0f);
            GREEN.write(1.0f);
            printf("Plant is watered!\n");
        }

        ThisThread::sleep_for(1s);
    }

    return 0;
}