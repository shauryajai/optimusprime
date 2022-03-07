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

#define SW1 (1<<0)
#define SW2 (1<<1)
#define SW3 (1<<2)
#define SW4 (1<<3)

void settings_handler()
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

        }
    }

    switch (sw_state)
    {
        case (SW1): // switch 1 active
                printf("switch 1 active\n");
                break;
        case (SW2): // switch 2 active
                printf("switch 2 active\n");
                break;
        case (SW3): // switch 3 active
                printf("switch 3 active\n");
                break;
        case (SW4): // switch 4 active
                printf("switch 4 active\n");
                break;
        case (SW1|SW2): // switch 1 and 2 active
                printf("switch 1 and 2 active\n");
                break;
        default: // no switch active
                break;
    }

}


