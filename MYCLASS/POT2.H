#include <Arduino.h>
#ifndef __Pot_H__
#define __Pot_H__

/*
    自动获取摇杆电位器最大值、最小值、原点位置
    工作原理：
    上电时不动摇杆，自动获取原点位置
    使用时判断每次值与原点位置差值更新最大值与最小值
*/

class Pot // potentiometer 电位器类
{
public:
    Pot(int Pin, int SENSITIVITY);      // 构造方法:引脚,灵敏度:(摇杆灵敏度：取值为1-100，小于灵敏度则为0,大于灵敏度则为100)
    int pos();         // 返回电位器位置,return:-100至100
    void rst_Origin(); // 重置电位器原点方法
    void rst_All();    // 重置电位器方法：重置最大值、最小值、原点值
    int Pri_Pin;
    int Pri_Pot_MaxValue; //最大值
    int Pri_Pot_MinValue; //最小值
    int Pri_Pot_OriValue; //原点值
    int Pri_Pot_Value; //当前值
    int Pri_SENSITIVITY; //灵敏度
};

Pot::Pot(int Pin, int SENSITIVITY)
{
    Pri_Pin = Pin;
    Pri_SENSITIVITY = SENSITIVITY;
    Pri_Pot_OriValue = analogRead(Pri_Pin);
    Pri_Pot_MaxValue = Pri_Pot_OriValue*1.8; //因最小值接近于0，所以中值的0.2倍不会超过下限，同理：中值的1.8倍也一般不会超过上限，上限理论值接近中值的2倍。
    Pri_Pot_MinValue = Pri_Pot_OriValue*0.2;
    // rst_All(); // 重置所有数据
}
int Pot::pos()
{
    Pri_Pot_Value = analogRead(Pri_Pin); //Pot_Value接收当前analogRead值
    if (Pri_Pot_Value > Pri_Pot_MaxValue) //与最大值比较
        Pri_Pot_MaxValue = Pri_Pot_Value; // 更新电位器最大值
    if (Pri_Pot_Value < Pri_Pot_MinValue) //与最小值比较
        Pri_Pot_MinValue = Pri_Pot_Value;     // 更新电位器最小值
    int Pos = 0;                      // 定义一个位置
    if (Pri_Pot_Value - Pri_Pot_OriValue > 0) // 正向拨动摇杆
    {
        Pos = map(Pri_Pot_Value, Pri_Pot_OriValue, Pri_Pot_MaxValue, 0, 100);
    }
    else if (Pri_Pot_Value - Pri_Pot_OriValue < 0) // 反向拨动摇杆
    {
        Pos = -map(Pri_Pot_Value,Pri_Pot_OriValue,Pri_Pot_MinValue, 0,100 );
    }
    if(abs(Pos) < Pri_SENSITIVITY) Pos = 0;
    if(Pos > (100 - Pri_SENSITIVITY)) Pos = 100;
    if(Pos < (Pri_SENSITIVITY - 100)) Pos = -100;
    return Pos; // 返回位置，-100至100
}
void Pot::rst_Origin()
{
    Pri_Pot_OriValue = analogRead(Pri_Pin);
}
void Pot::rst_All() 
{
    rst_Origin();
    Pri_Pot_OriValue = analogRead(Pri_Pin);
    Pri_Pot_MaxValue = Pri_Pot_OriValue*2/10; //因最小值接近于0，所以中值的0.2倍不会超过下限，同理：中值的1.8倍也一般不会超过上限，上限理论值接近中值的2倍。
    Pri_Pot_MinValue = Pri_Pot_OriValue*18/10;
}
#endif
