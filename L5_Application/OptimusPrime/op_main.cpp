/*
 * op_main.cpp
 *
 *  Created on: Mar 6, 2022
 *      Author: shaur
 */

#include "io.hpp"
#include "op_main.hpp"
#include "motor.hpp"
#include "test.hpp"
#include "settings.hpp"

void op_init()
{
    init_motors();
    init_settings();
}

void op_1Hz()
{
    motor_files();
}

void op_10Hz()
{
    motor_test();
}

void op_100Hz()
{
    settings();
}

void op_1000Hz()
{

}
