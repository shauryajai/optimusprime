/*
 * motor.cpp
 *
 *  Created on: Feb 3, 2022
 *      Author: shaur
 */
#include "motor.hpp"
#include <stdlib.h>

op_motor::op_motor(PWM::pwmType pwm_pin, unsigned int frequency, motor_type type, float min, float max)
{
    m_min = min;
    m_max = max;
    m_type = type;

    motor = new PWM(pwm_pin, frequency);

    set_mid();

    printf("Constructed..%d\n\n",type);
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
    FRESULT result;
    char data[5] = { 0 };
    char filename[13];
    char mid_val[4];

    sprintf(filename,"1:motor_%d.txt",m_type);
    const char* fn = filename;
    printf("\nfn: %s\n",fn);

    Storage::read("1:dummy_read", NULL, 0, 0); // Send dummy read for SD card as it fails on the first attempt

    result = Storage::read(fn, (void*)data, sizeof(data)-1, 0);
    printf(" storage read_result = %d\n",result);

    if(FR_NO_FILE == result)
    {
        if(m_type)
        {
            m_mid = DC_MID;
        }
        else
        {
            m_mid = SERVO_MID;
        }

        sprintf(mid_val,"%f",m_mid);

        printf(" storage write_result = %d\n",Storage::write(fn, (void*)mid_val, sizeof(mid_val), 0));
    }
    else if(FR_OK == result)
    {
         m_mid=(float)atof(data);
         printf(" Read m_mid from file -> ");
    }
    else
    {
        printf(" Unknown file read result\n");
    }

    printf("m_mid = %f\n",m_mid);
    motor->set(m_mid);
}

void calibrate()
{
    // increment or decrement the mid val using switches
    // set the mid values in motor.txt
}

op_motor *steer;
op_motor *throttle;
