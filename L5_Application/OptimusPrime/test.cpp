/*
 * test.cpp
 *
 *  Created on: Mar 7, 2022
 *      Author: shaur
 */

#include "test.hpp"
#include "motor.hpp"

void motor_range_test()
{
    static uint8_t val = 0;
    static uint8_t val2 = 0;
    static bool dir = 1;

    //throttle->set_val(dir,val2++);
    steer->set_val(dir,val++);

    if(val == 100)
    {
        val = 0;
        dir ^=1;
    }

    if(val2 == 20)
    {
        val2 = 0;
        dir ^=1;
    }
}

void motor_test()
{
    //motor_range_test();
}
