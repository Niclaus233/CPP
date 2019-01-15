#include<iostream>
using namespace std;

enum CPU_Rank{P1=1,P2,P3,P4,P5,P6,P7};

class CPU
{
private :
    CPU_Rank rank1;
    static int a;
    int frequency ;
    float voltage;


public:
    CPU (CPU_Rank c,int f,float v);

    //下面定义可以访问内部成员的函数
    CPU_Rank GetRank1() {return rank1;}
    int GetFrequency(){return frequency;}
    float GetVoltage(){return voltage;}

};

CPU::CPU(CPU_Rank c,int f,float v):rank1(c),frequency(f),voltage(v){}

int main()
{
    CPU cpu(P1,0,5.2);
    cout<< cpu.GetRank1() <<" "<< cpu.GetFrequency() <<" "<< cpu.GetVoltage() <<endl;
    return 0;
}
