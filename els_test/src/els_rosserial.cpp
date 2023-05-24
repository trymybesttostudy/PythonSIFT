#include "ros/ros.h"
#include "serial/serial.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
 
std_msgs::String buffermsg;
 
void doMsg(const std_msgs::String::ConstPtr& msg){
    buffermsg = *msg;
    ROS_INFO("I hear:%s",msg->data.c_str());
    // ROS_INFO("我听见:%s",(*msg_p).data.c_str());
}
 
int main(int argc, char** argv)
{
    uint8_t change[2]="x";
    uint8_t buffer[2]="x";
 
    ros::init(argc, argv, "serial_port");
    //创建句柄（虽然后面没用到这个句柄，但如果不创建，运行时进程会出错）
    ros::NodeHandle nh;
    //订阅者
    ros::Subscriber serialsub = nh.subscribe<std_msgs::String>("cmd",10,doMsg);
    //创建一个serial类
    serial::Serial sp;
    //创建timeout
    serial::Timeout to = serial::Timeout::simpleTimeout(100);
    //设置要打开的串口名称
    sp.setPort("/dev/ttyUSB0");
    //设置串口通信的波特率
    sp.setBaudrate(9600);
    //串口设置timeout
    sp.setTimeout(to);
 
    try
    {
        //打开串口
        sp.open();
    }
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
        return -1;
    }
     
    //判断串口是否打开成功
    if(sp.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyUSB0 is opened.");
    }
    else
    {
        return -1;
    }
     
    ros::Rate loop_rate(500);
    while(ros::ok())
    {
            ros::spinOnce();
        //获取缓冲区内的字节数
            for(int m=0;m<1;m++){
            change[m] = buffer[m];
            }
            //读出数据
            for(int j=0;j<1;j++){
            buffer[j] = (uint8_t)(buffermsg.data[j]);
            }
            size_t n = sizeof(buffer);
            if(change[0]!=buffer[0]){
                for(int i=0; i<(n-1); i++)
                {
                    //16进制的方式打印到屏幕
                    std::cout << std::hex << (buffer[i] & 0xff) << " ";
                }
                std::cout << std::endl;
                //把数据发送回去
                sp.write(buffer, n);
                loop_rate.sleep();
            }
    }
    //关闭串口
    sp.close();
    return 0;
}
