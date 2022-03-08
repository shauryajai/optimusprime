/*
 * op_settings.cpp
 *
 *  Created on: Feb 7, 2022
 *      Author: shaur
 */

#include <stdint.h>
#include <stdio.h>
#include "io.hpp"
#include "settings.hpp"
#include "motor.hpp"

#define SW1 (1<<0)
#define SW2 (1<<1)
#define SW3 (1<<2)
#define SW4 (1<<3)

enum
{
    START_MAIN_MENU,
    motor,
    gps,
    camera,
    sensor,
    END_MAIN_MENU,
};

uint8_t menu;
motor_type m_type;

void init_settings()
{
    menu = START_MAIN_MENU;
    m_type = servo;
}

void main_menu()
{
    menu ++;

    if (menu >= END_MAIN_MENU)
    {
        menu = START_MAIN_MENU;
    }

    m_type = servo; // Set motor type back to default

    printf("Main menu %d\n",menu);
}

void sub_menu()
{
    switch (menu)
    {
        case (motor):
            if (m_type == dc)
            {
                m_type = servo;
            }
            else
            {
                m_type = dc;
            }

            printf("Motor type (0 = Servo, 1 = DC) %d\n",m_type);
            break;

        default:
            break;
    }
}

void trim(trim_e m_trim)
{
    if (menu == motor)
    {
        printf("Motor trim (1 = Low, 2 = High) %d\n",m_trim);

        calibrate_motors(m_type, m_trim);
    }
}

void settings()
{
    static uint8_t sw_state = 0;
    uint8_t switchValues = SW.getSwitchValues();
    //printf("sw_state = %d\n",sw_state);

    if (switchValues)
    {
        sw_state = switchValues;
    }
    else
    {
        if (sw_state)
        {
            switch (sw_state)
            {
                case (SW1): // switch 1 active
                        main_menu();
                        break;
                case (SW2): // switch 2 active
                        sub_menu();
                        break;
                case (SW3): // switch 3 active
                        trim(trim_low);
                        break;
                case (SW4): // switch 4 active
                        trim(trim_high);
                        break;
                case (SW1|SW2): // switch 1 and 2 active
                        printf("Switch 1 and 2 activated\n");
                        break;
                default: // no switch active
                        break;
            }

            sw_state = 0;
        }
    }
}


