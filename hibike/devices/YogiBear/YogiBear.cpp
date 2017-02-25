#include "YogiBear.h"
#include "pid.h"
#include "encoder.h"
#include "current_limit.h"
#include "motor.h"
#include "LED.h"

//A space for constants.
float pwmInput = 0; //Value that is received from hibike and is the goal PWM
uint8_t driveMode = 0; 

//Timers.
#include <FlexiTimer2.h>


void setup()
{
    motorSetup();
    currentLimitSetup();
    encoderSetup();
    PIDSetup();
    setup_LEDs();
    test_LEDs();
    hibike_setup();

}

/* 
Manual Controls:
s <x> - sets pwm to x
c     - clears faults
p <x> - turns on PID mode, velocity if x = v, position if x = p
m     - turns on manual input mode
e     - enables motor
d     - disables motor
r     - displays 1 print of all readable values
t     - toggles continual printing of pos and vel
b     - send heartbeat
h     - switch hibike mode
z     - switch human controls
w <x> <y> - writes the value y to the variable x
*/
void loop()
{
    ctrl_LEDs();
    hibike_loop();

}




// You must implement this function.
// It is called when the device receives a Device Write packet.
// Updates param to new value passed in data.
//    param   -   Parameter index
//    data    -   value to write, in little-endian bytes
//    len     -   number of bytes in data
//
//   return  -   size of bytes written on success; otherwise return 0

uint32_t device_write(uint8_t param, uint8_t* data, size_t len) {
    switch (param) {
        case ENABLE:
            if (data[0] == 0) {
                motorDisable();
            } else {
                motorEnable();
            }
            return sizeof(bool);
            break;

        case COMMAND_STATE: 
            driveMode = data[0];

            switch (driveMode) {
                case MANUALDRIVE:
                    disablePID();
                    break;
                case PID_VEL:
                    enableVel();
                    break;
                case PID_POS:
                    enablePos();
                    break;
                default:
                    driveMode = MANUALDRIVE;
                    disablePID();
                    break;
            }

            return sizeof(uint8_t);
            break;

        case DUTY_CYCLE: 
            pwmInput = ((float *)data)[0];
            return sizeof(float);
            break;

        case PID_POS_SETPOINT: 
            setPosSetpoint(((float *)data)[0]);
            return sizeof(float);
            break;

        case PID_POS_KP: 
            setPosKP(((float *)data)[0]);
            return sizeof(float);
            break;

        case PID_POS_KI: 
            setPosKI(((float *)data)[0]);
            return sizeof(float);
            break;

        case PID_POS_KD: 
            setPosKD(((float *)data)[0]);
            return sizeof(float);
            break;

        case PID_VEL_SETPOINT: 
            setVelSetpoint(((float *)data)[0]);
            return sizeof(float);
            break;

        case PID_VEL_KP: 
            setVelKP(((float *)data)[0]);
            return sizeof(float);
            break;

        case PID_VEL_KI: 
            setVelKI(((float *)data)[0]);
            return sizeof(float);
            break;

        case PID_VEL_KD: 
            setVelKD(((float *)data)[0]);
            return sizeof(float);
            break;

        case CURRENT_THRESH: 
            setCurrentThreshold(((float *)data)[0]);
            return sizeof(float);
            break;

        case ENC_POS: 
            if((float) data[0] == 0) {
                zeroEncoder();
                return sizeof(float);
            }

            break;

        case ENC_VEL: 
            break;

        case MOTOR_CURRENT: 
            break;

        default:
            return 0;
    }

    return 0;
}


// You must implement this function.
// It is called when the device receives a Device Data Update packet.
// Modifies data_update_buf to contain the parameter value.
//    param           -   Parameter index
//    data_update_buf -   buffer to return data in, little-endian
//    buf_len         -   Maximum length of the buffer
//
//    return          -   sizeof(value) on success; 0 otherwise

uint8_t device_read(uint8_t param, uint8_t* data_update_buf, size_t buf_len) {
    float* float_buf;

    switch (param) 
    {
        case ENABLE:
            data_update_buf[0] = readMotorEnabled();
            return sizeof(bool);
            break;

        case COMMAND_STATE: 
            data_update_buf[0] = driveMode;
            return sizeof(uint8_t);
            break;

        case DUTY_CYCLE: 
            float_buf = (float *) data_update_buf;
            float_buf[0] = readPWMInput();
            return sizeof(float);
            break;

        case PID_POS_SETPOINT: 
            break;
        
        case PID_POS_KP: 
            break;
        
        case PID_POS_KI:
            break;
        
        case PID_POS_KD: 
            break;
        
        case PID_VEL_SETPOINT: 
            break;
        
        case PID_VEL_KP: 
            break;
        
        case PID_VEL_KI: 
            break;
        
        case PID_VEL_KD: 
            break;
        
        case CURRENT_THRESH: 
            break;
        
        case ENC_POS: 
            float_buf = (float *) data_update_buf;
            float_buf[0] = readPos();
            return sizeof(float);
            break;

        case ENC_VEL: 
            float_buf = (float *) data_update_buf;
            float_buf[0] = readVel();
            return sizeof(float);
            break;

        case MOTOR_CURRENT: 
            float_buf = (float *) data_update_buf;
            float_buf[0] = readCurrent();
            return sizeof(float);
            break;

        default:
            return 0;
    }

    return 0;
}


float readPWMInput() {
    return pwmInput;
}

uint8_t readDriveMode() {
    return driveMode;
}
