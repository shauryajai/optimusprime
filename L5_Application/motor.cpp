/*
 * motor.cpp
 *
 *  Created on: Feb 3, 2022
 *      Author: shaur
 */
#include "motor.hpp"

op_motor::op_motor(PWM::pwmType pwm_pin, unsigned int frequency, motor_type type, float min, float max)
{
    this->min = min;
    this->max = max;
    this->type = type;

    motor = new PWM(pwm_pin, frequency);

    set_mid();
    motor->set(this->mid);
}

bool op_motor::set_val(bool m_dir, uint8_t m_val)
{
    if(m_dir)
    {
        motor->set(mid + ((max-mid)*m_val/100));
    }
    else
    {
        motor->set(min + ((mid-min)*m_val/100));
    }

    return 0;
}

void op_motor::set_mid()
{
    // check the motor type
    // open motor.txt file
    // if file exist > read the respective mid value
    // else create a new file.
    // set the mid val as (Max-Min)/2 in the file
    // set this->mid

    /*
     * motor.txt
     * S 15.0 T 15.0
     */
}

void calibrate()
{
    // increment or decrement the mid val using switches
    // set the mid values in motor.txt
}


op_motor throttle(PWM::pwm1, 100, throttle, THROTTLE_MIN,THROTTLE_MAX);
op_motor steer(PWM::pwm2, 100, steer, SERVO_MIN,SERVO_MAX);

