#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ads7830.h>

#define ADC_ADDRESS 0x4b  // Default I2C address for many ADC devices
#define JOYSTICK_X_CHANNEL 1
#define JOYSTICK_Y_CHANNEL 0

int main() {
    ADC_device joystick_adc;
    int x_value, y_value;
    int result;
    
    // Initialize WiringPi
    if (wiringPiSetup() == -1) {
        printf("Failed to initialize WiringPi\n");
        return 1;
    }
    
    // Initialize ADC device
    result = ADC_init(&joystick_adc, ADC_ADDRESS);
    if (result < 0) {
        printf("Failed to initialize ADC device at address 0x%02X\n", ADC_ADDRESS);
        return 1;
    }
    
    printf("Joystick Test Program\n");
    printf("Press Ctrl+C to exit\n\n");
    
    // Continuously read joystick values
    while (1) {
        // Read X and Y values
        x_value = ADC_read(&joystick_adc, JOYSTICK_X_CHANNEL);
        y_value = ADC_read(&joystick_adc, JOYSTICK_Y_CHANNEL);
        
            printf("Joystick Position: X = %3d, Y = %3d\r", x_value, y_value);
            fflush(stdout);  // Ensure the output is displayed immediately
        
        usleep(100000);  // Sleep for 100ms (10 readings per second)
    }
    
    return 0;
}
