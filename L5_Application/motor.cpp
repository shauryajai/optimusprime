/*
 * motor.cpp
 *
 *  Created on: Feb 3, 2022
 *      Author: shaur
 */
#include "motor.hpp"

op_motor::op_motor(PWM::pwmType pwm_pin, unsigned int frequency, motor_type type, float min, float max)
{
    m_min = min;
    m_max = max;
    m_type = type;

    motor = new PWM(pwm_pin, frequency);

    set_mid();
    motor->set(m_mid);
    printf("Constructed..%d\n",type);
}

bool op_motor::set_val(bool dir, uint8_t val)
{
    float pwm_val = 0;

    if(dir)
    {
        pwm_val = m_mid + ((m_max-m_mid)*val/100);
        motor->set(pwm_val);
    }
    else
    {
        pwm_val = m_mid - ((m_mid-m_min)*val/100);
        motor->set(pwm_val);
    }

    //printf("Motor_type = %d, dir = %d, val = %d, pwm_val = %f\n",m_type, dir, val, pwm_val);
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
/*
    char data[4] = { 0 };
    char *filename;
    sprintf(filename,"1:motor_%d.txt",m_type);

    if(FR_NO_FILE != Storage::read(filename, data, sizeof(data)-1, 0))
    {
        Storage::write(filename, "15.0", sizeof(data)-1, 0);
        m_mid = 15.0;
    }
    else
    {
        // convert data to float
        // copy to mid
    }
*/
    if(m_type == servo) m_mid = SERVO_MID;
    else if(m_type == dc) m_mid = DC_MID;
}

void calibrate()
{
    // increment or decrement the mid val using switches
    // set the mid values in motor.txt
}

op_motor *steer;
op_motor *throttle;
