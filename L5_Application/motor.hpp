/*
 * motor.hpp
 *
 *  Created on: Feb 3, 2022
 *      Author: shaur
 */

#ifndef MOTOR_HPP_
#define MOTOR_HPP_

#include "lpc_pwm.hpp"

#define SERVO_MIN 10.0
#define SERVO_MAX 20.0
#define THROTTLE_MIN 10.0
#define THROTTLE_MAX 20.0

typedef enum {
    steer,
    throttle
} motor_type;

class op_motor
{
private:
    float min;
    float max;
    float mid;
    PWM *motor;

public:
    motor_type type;
    op_motor(PWM::pwmType pwm_pin, unsigned int frequency, motor_type type, float min, float max);
    bool set_val(bool m_dir, uint8_t m_val);
    // get_val()??

    void set_mid();
    void calibrate();
};


#endif /* MOTOR_HPP_ */
