/*
 * op_main.cpp
 *
 *  Created on: Mar 6, 2022
 *      Author: shaur
 */

#include <OptimusPrime/settings.hpp>
#include "io.hpp"
#include "op_main.hpp"
#include "motor.hpp"

void op_init()
{
    steer = new op_motor(PWM::pwm2, 100, motor_type::servo, SERVO_MIN,SERVO_MAX);
    throttle = new op_motor(PWM::pwm1, 100, motor_type::dc, DC_MIN,DC_MAX);
}

void op_1Hz()
{
    //settings_handler();
}

void op_10Hz()
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

void op_100Hz()
{

}

void op_1000Hz()
{

}
