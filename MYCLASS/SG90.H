
//周期是20ms 的脉宽调制（PWM)信号，其中脉冲宽度从0.5ms-2.5ms，相对应舵盘的位置为0—180度
#include "Arduino.h"
#ifndef __SG90_H__
#define __SG90_H__

class SG90
{
  public:
    SG90(int pin,int channel); //引脚，通道
    void pos(int);  //角度0-180
  private:
    int pri_pin,pri_channel,pri_pwm;
    int pri_ferq = 1000/20; //20ms周期转换成50HZ频率
    int pri_bits = 12;
};
SG90::SG90(int pin,int channel)
{
  pri_pin = pin;
  pri_channel = channel;
  ledcSetup(pri_channel, pri_ferq, pri_bits); 
  ledcAttachPin(pri_pin,pri_channel); //绑定引脚到通道  
}
void SG90::pos(int position)  
{
  pri_pwm = map(position,0,180,500,2500)*4096/20000; //高电平需要0.5-2.5ms对应0-180度
  ledcWrite(pri_channel,pri_pwm);
}
#endif