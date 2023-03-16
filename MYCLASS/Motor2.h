#include "Arduino.h"
#ifndef __Motor_H__
#define __Motor_H__
class Motor
{
public:
    Motor(int MF_pin, int MR_pin, int PWM_channel, int Max_speed,int Min_speed); // 构造函数:正转、反转、PMW通道、最大速度400-1023 最小速度300-1023
    void run(int PWM);                            // 运转
private:
    int pri_MF_pin;
    int pri_MR_pin;
    int pri_channel;
    int pri_Max_speed;
    int pri_Min_speed;
};

Motor::Motor(int MF_pin, int MR_pin, int channel, int Max_speed,int Min_speed)
{
    // Serial.begin(9600);
    pri_MF_pin = MF_pin;
    pri_MR_pin = MR_pin;
    pri_channel = channel;
    pri_Max_speed = Max_speed;
    pri_Min_speed = Min_speed;
    if(pri_Max_speed>1023) pri_Max_speed = 1023;
    if(pri_Max_speed<300) pri_Max_speed = 300;
    pinMode(pri_MF_pin, OUTPUT);
    pinMode(pri_MR_pin, OUTPUT);
    digitalWrite(pri_MF_pin,LOW);
    digitalWrite(pri_MR_pin,LOW);
    ledcSetup(pri_channel, 1000, 10); //1000HZ，10bit
    // ledcAttachPin(pri_MF_pin, pri_channel);
    // ledcAttachPin(pri_MR_pin, pri_channel);
}
void Motor::run(int PWM)
{
    // PWM = int(PWM);
    if (PWM > 0)
    {
        if(PWM < pri_Min_speed) PWM = 0;  //实测最小PWM为150，小于了电机不转
        if(PWM > pri_Max_speed) PWM = pri_Max_speed;
        ledcAttachPin(pri_MF_pin, pri_channel);
        ledcDetachPin(pri_MR_pin);
        ledcWrite(pri_channel, PWM);  
        digitalWrite(pri_MR_pin, LOW);
    }
    else if (PWM < 0)
    {
        if(PWM > -pri_Min_speed) PWM = 0;
        if (PWM < -pri_Max_speed) PWM = -pri_Max_speed;
        ledcAttachPin(pri_MR_pin, pri_channel);
        ledcDetachPin(pri_MF_pin);
        ledcWrite(pri_channel, -PWM);
        digitalWrite(pri_MF_pin, LOW);
    }
    else
    {
        ledcDetachPin(pri_MR_pin);
        ledcDetachPin(pri_MF_pin);
        digitalWrite(pri_MR_pin, LOW);
        digitalWrite(pri_MF_pin, LOW);
    }
}
#endif