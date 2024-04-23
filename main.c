#include "lib/Config/DEV_Config.h"
#include "lib/PCA9685/PCA9685.h"
#include "gpioheader.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define PWMA PCA_CHANNEL_0
#define AIN1 PCA_CHANNEL_1
#define AIN2 PCA_CHANNEL_2
#define PWMB PCA_CHANNEL_5
#define BIN1 PCA_CHANNEL_3
#define BIN2 PCA_CHANNEL_4

#define FORWARD 0
#define BACKWARD 1

#define MOTORHAT_1 0x40
#define MOTORHAT_2 0x51

typedef struct {
  uint8_t direction;
  uint16_t speed;
  uint8_t pwm;      
  uint8_t IN1;  
  uint8_t IN2; 
  uint8_t motorhat; 
} motor_info;

void initMotorhat(uint8_t motorhat){
  PCA9685_Init(motorhat);
  PCA9685_SetPWMFreq(100);
}

void setMotorSpeedAndDirection(motor_info *motor) {
    PCA9685_SetPwmDutyCycle(motor->pwm, motor->speed);
    if (motor->direction == FORWARD) {
        PCA9685_SetLevel(motor->IN1, 0);
        PCA9685_SetLevel(motor->IN2, 1);
    } else {
        PCA9685_SetLevel(motor->IN1, 1);
        PCA9685_SetLevel(motor->IN2, 0);
    }
}

void stopMotor(motor_info *motor) {
    PCA9685_SetPwmDutyCycle(motor->pwm, 0);
}

int main() {
    initMotorhat(MOTORHAT_1);
    initMotorhat(MOTORHAT_2);

    motor_info motor1_hat1 = {FORWARD, 50, PWMA, AIN1, AIN2, MOTORHAT_1};
    motor_info motor2_hat1 = {FORWARD, 50, PWMB, BIN1, BIN2, MOTORHAT_1};

    motor_info motor1_hat2 = {FORWARD, 50, PWMA, AIN1, AIN2, MOTORHAT_2};
    motor_info motor2_hat2 = {FORWARD, 50, PWMB, BIN1, BIN2, MOTORHAT_2};

    setMotorSpeedAndDirection(&motor1_hat1);
    setMotorSpeedAndDirection(&motor2_hat1);
    setMotorSpeedAndDirection(&motor1_hat2);
    setMotorSpeedAndDirection(&motor2_hat2);


    printf("Motors are running...\n");

    sleep(3);

    printf("Stopping motors...\n");
    motor1_hat1.speed = 0;
    motor2_hat1.speed = 0;
    motor1_hat2.speed = 0;
    motor2_hat2.speed = 0;

    setMotorSpeedAndDirection(&motor1_hat1);
    setMotorSpeedAndDirection(&motor2_hat1);
    setMotorSpeedAndDirection(&motor1_hat2);
    setMotorSpeedAndDirection(&motor2_hat2);

    printf("Motors have stopped.\n");

    return 0;
}