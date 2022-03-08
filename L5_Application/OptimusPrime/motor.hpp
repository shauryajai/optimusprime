/*
 * motor.hpp
 *
 *  Created on: Feb 3, 2022
 *      Author: shaur
 */

#ifndef MOTOR_HPP_
#define MOTOR_HPP_

#include "lpc_pwm.hpp"
#include <stdint.h>
#include <stdio.h>
#include "settings.hpp"

#define SERVO_MIN 10.0
#define SERVO_MID 13.5
#define SERVO_MAX 20.0
#define DC_MIN 10.0
#define DC_MID 15.0
#define DC_MAX 20.0

typedef enum {
    servo,
    dc
} motor_type;

typedef enum
{
    trim_none,
    trim_low,
    trim_high,
} trim_e;

class op_motor
{
private:
    float       m_min;
    float       m_max;
    float       m_mid;
    trim_e      m_trim = trim_none;
    motor_type  m_type;
    char        m_file[13];
    PWM        *motor;
    bool        m_mid_updated = false;

    void set_mid_from_macro();

public:
    op_motor(PWM::pwmType pwm_pin, unsigned int frequency, motor_type type, float min, float max);
    bool set_val(bool dir, uint8_t val);
    // get_val()??

    bool is_mid_updated() { return m_mid_updated; }
    void write_m_mid_to_file();

    void set_mid();

    void set_trim(trim_e trim) { this->m_trim = trim; }

    float get_mid() { return m_mid; }

    void calibrate();

    ~op_motor(); //TODO: We need call this destructor in case remote control override is required

    op_motor() { printf("Default Construct...\n");}
};

extern op_motor *steer;
extern op_motor *throttle;

void init_motors();
void calibrate_motors(motor_type m_type, trim_e m_trim);
void motor_files();


#endif /* MOTOR_HPP_ */
