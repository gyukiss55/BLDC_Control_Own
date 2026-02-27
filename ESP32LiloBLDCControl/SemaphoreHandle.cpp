// SemaphoreHandle.cpp
#include "SemaphoreHandle.h"


SemaphoreHandle_t mySemaphore;

void Task1(void* pvParameters) {
    while (true) {
        Serial.println("Task1: Waiting for semaphore...");

        // Wait indefinitely for semaphore
        if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE) {
            Serial.println("Task1: Semaphore received!");
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task2(void* pvParameters) {
    while (true) {
        Serial.println("Task2: Giving semaphore...");

        xSemaphoreGive(mySemaphore);

        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

void setupSemaphore() {

    // Create binary semaphore
    mySemaphore = xSemaphoreCreateBinary();

    if (mySemaphore == NULL) {
        Serial.println("Failed to create semaphore!");
        while (1);
    }

    // Create tasks (run on core 0 and 1 optionally)
    xTaskCreatePinnedToCore(
        Task1,
        "Task1",
        2048,
        NULL,
        1,
        NULL,
        0);

    xTaskCreatePinnedToCore(
        Task2,
        "Task2",
        2048,
        NULL,
        1,
        NULL,
        1);
}
