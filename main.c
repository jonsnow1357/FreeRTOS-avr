#include <avr/io.h>

#include "FreeRTOS.h"
#include "task.h"

void init() {
    // set PC0 as output and set low
    DDRC |= _BV(PC0);
    PORTC &= ~_BV(PC0);
    // set PC1 as output and set low
    DDRC |= _BV(PC1);
    PORTC &= ~_BV(PC1);
}

void task1(void *pvParameters) {
    uint8_t state = PINC & _BV(PC0);

    if (state == 0) {
        PORTC &= ~_BV(PC0);
    } else {
        PORTC |= _BV(PC0);
    }
    vTaskDelay(500);
}

void task2(void *pvParameters) {
    uint8_t state = PINC & _BV(PC1);

    if (state == 0) {
        PORTC &= ~_BV(PC1);
    } else {
        PORTC |= _BV(PC1);
    }
    vTaskDelay(750);
}

int main(void) {
    init();

    xTaskCreate(task1,
            "task1",
            configMINIMAL_STACK_SIZE,
            NULL,
            tskIDLE_PRIORITY,
            NULL);
    xTaskCreate(task2,
            "task2",
            configMINIMAL_STACK_SIZE,
            NULL,
            tskIDLE_PRIORITY,
            NULL);

    vTaskStartScheduler();
}
