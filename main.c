/* ============================================================
   Smart Pill Reminder System
   Microcontroller : STM32F411CEU6 (Black Pill)
   Author          : Anwesha Mohanty
   Organisation    : NIELIT Chennai, Embedded Systems Group
   Supervisor      : Mr. Ishant Kumar Bajpai
   Date            : August 2025
   Description     : RTC-based medication reminder with buzzer,
                     LED alert, and snooze button functionality.
   ============================================================ */

#include <stm32f4xx_hal.h>

#define LED_PIN     GPIO_PIN_13
#define LED_PORT    GPIOC

#define BUZZER_PIN  GPIO_PIN_8
#define BUZZER_PORT GPIOA

#define BUTTON_PIN  GPIO_PIN_12
#define BUTTON_PORT GPIOB

/* Alarm times in hours (8 AM, 2 PM, 8 PM) */
uint8_t alarm_times[] = {8, 14, 20};
uint8_t current_hour  = 8;

int main(void)
{
    HAL_Init();

    /* Configure LED and Buzzer as outputs */
    GPIO_InitTypeDef gpio;

    gpio.Pin   = LED_PIN;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &gpio);

    gpio.Pin   = BUZZER_PIN;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BUZZER_PORT, &gpio);

    /* Configure Snooze Button as input */
    gpio.Pin  = BUTTON_PIN;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(BUTTON_PORT, &gpio);

    while (1)
    {
        /* Check all 3 alarm times every second */
        for (int i = 0; i < 3; i++)
        {
            if (current_hour == alarm_times[i])
            {
                /* Activate buzzer and LED */
                HAL_GPIO_WritePin(LED_PORT,    LED_PIN,    GPIO_PIN_SET);
                HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);

                /* Stay active for 30 seconds unless snoozed */
                for (int j = 0; j < 30; j++)
                {
                    /* If snooze button pressed — break early */
                    if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_RESET)
                    {
                        break;
                    }
                    HAL_Delay(1000); /* 1 second */
                }

                /* Turn off buzzer and LED */
                HAL_GPIO_WritePin(LED_PORT,    LED_PIN,    GPIO_PIN_RESET);
                HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);

                /* Wait 1 minute before checking again */
                HAL_Delay(60000);
            }
        }

        HAL_Delay(1000); /* Poll every second */
    }
}
