/*
 * motor.cpp
 *
 *  Created on: Feb 3, 2022
 *      Author: shaur
 */
#include "motor.hpp"
#include <stdlib.h>
#include "storage.hpp"

op_motor *steer;
op_motor *throttle;

void init_motors()
{
    steer = new op_motor(PWM::pwm2, 100, motor_type::servo, SERVO_MIN,SERVO_MAX);
    throttle = new op_motor(PWM::pwm1, 100, motor_type::dc, DC_MIN,DC_MAX);
}

op_motor::op_motor(PWM::pwmType pwm_pin, unsigned int frequency, motor_type type, float min, float max)
{
    m_min = min;
    m_max = max;
    m_type = type;

    sprintf(m_file,"1:motor_%d.txt",m_type);

    motor = new PWM(pwm_pin, frequency);

    set_mid(); // Read m_mid value from motor_*.txt file

    printf("Constructed..%d\n\n",type);
}

op_motor::~op_motor()
{
    delete motor;

    printf("Destroyed...\n");
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

void op_motor::set_mid_from_macro()
{
    if(m_type == dc)
    {
        m_mid = DC_MID;
    }
    else
    {
        m_mid = SERVO_MID;
    }
}

void op_motor::write_m_mid_to_file()
{
    char mid_val[4];
    const char* fn = m_file;
    FRESULT result;

    sprintf(mid_val,"%.1f",m_mid);

    printf("sizeof(%s) = %d \n", mid_val, sizeof(mid_val));
    printf("fn = %s\n", fn);

    result = Storage::write(fn, (void*)mid_val, sizeof(mid_val), 0);

    if (result != FR_OK)
    {
        printf ("File write failed (result = %d)\n",result);
    }

    m_mid_updated = false;
}

void op_motor::set_mid()
{
    FRESULT result;
    char data[5] = { 0 };

    const char* fn = m_file;
    printf("\nfn: %s\n",fn);

    Storage::read("1:dummy_read", NULL, 0, 0); // Send dummy read for SD card as it fails on the first attempt

    result = Storage::read(fn, (void*)data, sizeof(data)-1, 0);
    printf(" Storage read_result = %d\n",result);

    if(FR_NO_FILE == result)
    {
        set_mid_from_macro();
        m_mid_updated = true;
    }
    else if(FR_OK == result)
    {
         m_mid=(float)atof(data);
         printf(" Read m_mid from file -> ");

         if (m_mid <= 0.0)
         {
             set_mid_from_macro();
             m_mid_updated = true;
         }
    }
    else
    {
        printf(" Unknown file read result\n");
    }

    printf("m_mid = %f\n",m_mid);
    motor->set(m_mid);
}

void op_motor::calibrate()
{
    switch (m_trim)
    {
        case (trim_low):
                m_mid -= 0.1;
                break;

        case (trim_high):
                m_mid += 0.1;
                break;

        default:
                break;
    }

    if (m_mid <= m_min)
    {
        m_mid = m_min;
    }
    else if (m_mid >= m_max)
    {
        m_mid = m_max;
    }

    m_mid_updated = true;

    printf("m_mid = %f\n",m_mid);
    motor->set(m_mid);

    m_trim = trim_none;
}

void calibrate_motors(motor_type m_type, trim_e m_trim)
{
    switch (m_type)
    {
        case (servo):
                steer->set_trim(m_trim);
                steer->calibrate();
                break;
        case (dc):
                throttle->set_trim(m_trim);
                throttle->calibrate();
                break;
        default:
                break;
    }
}

void motor_files()
{
    if (steer->is_mid_updated())
    {
        steer->write_m_mid_to_file();
    }

    if (throttle->is_mid_updated())
    {
        throttle->write_m_mid_to_file();
    }
}
