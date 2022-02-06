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
//#include "io.hpp"
#include "storage.hpp"
#include <stdio.h>

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

class op_motor
{
private:
    float m_min;
    float m_max;
    float m_mid;
    PWM *motor;

public:
    motor_type m_type;
    op_motor(PWM::pwmType pwm_pin, unsigned int frequency, motor_type type, float min, float max);
    bool set_val(bool dir, uint8_t val);
    // get_val()??

    void set_mid();
    void calibrate();

    ~op_motor() { printf("Destroyed...\n");}
    op_motor() { printf("Default Construct...\n");}
};

extern op_motor *steer;
extern op_motor *throttle;

#endif /* MOTOR_HPP_ */
