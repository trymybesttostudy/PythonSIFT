#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_srvs/SetBool.h"
#include "std_srvs/Empty.h"
#include "std_srvs/Trigger.h"
#include "jetmax_control/SetJetMax.h"
#include "jetmax_control/SetServo.h"
#include <sstream>
#include <iostream>
#include <cstring>

 
#define HIGH 180
#define LOW 20
#define LOW_T 26
#define BAI_X 93
#define BAI_Y -135
#define MOVE_Y 122
#define X_ERROR -104
#define Y_ERROR -169
#define X_RATIO 66.17
#define Y_RATIO 66.67

 
using std::string;
using std::stringstream;
 
float pose[] = {0.0 , -200.0 , 0.0 , 0.0 , 0.0 , 0.0};

std_msgs::String msg;
std_msgs::Float64MultiArray pose_sub_red , pose_sub_brown , pose_sub_orange , pose_sub_blue , pose_sub_green , pose_sub_purple , pose_sub_yellow;
jetmax_control::SetJetMax target_position;
jetmax_control::SetServo servo;
std_srvs::SetBoolRequest sucker,sucker_E;
std_srvs::TriggerRequest sucker_T;
 
 
 
void sendcmd(std::stringstream& scmd){
    msg.data = scmd.str();
    ROS_INFO("向下位机传递的数据是:%s",scmd.str().c_str());
}
 
void Do_red_sub(const std_msgs::Float64MultiArray msg){
    pose_sub_red.data = msg.data;
    ROS_INFO("position && angle:(%f,%f,%f) ",pose_sub_red.data.at(0),pose_sub_red.data.at(1),pose_sub_red.data.at(4));
    pose[0] = pose_sub_red.data.at(0)/X_RATIO+X_ERROR;
    pose[1] = pose_sub_red.data.at(1)/Y_RATIO+Y_ERROR;
    pose[4] = pose_sub_red.data.at(4);
}
 
void Do_brown_sub(const std_msgs::Float64MultiArray msg){
    pose_sub_brown.data = msg.data;
    ROS_INFO("position && angle:(%f,%f,%f) ",pose_sub_brown.data.at(0),pose_sub_brown.data.at(1),pose_sub_brown.data.at(4));
    pose[0] = pose_sub_brown.data.at(0)/X_RATIO+X_ERROR;
    pose[1] = pose_sub_brown.data.at(1)/Y_RATIO+Y_ERROR;
    pose[4] = pose_sub_brown.data.at(4);
}
 
void Do_orange_sub(const std_msgs::Float64MultiArray msg){
    pose_sub_orange.data = msg.data;
    ROS_INFO("position && angle:(%f,%f,%f) ",pose_sub_orange.data.at(0),pose_sub_orange.data.at(1),pose_sub_orange.data.at(4));
    pose[0] = pose_sub_orange.data.at(0)/X_RATIO+X_ERROR;
    pose[1] = pose_sub_orange.data.at(1)/Y_RATIO+Y_ERROR;
    pose[4] = pose_sub_orange.data.at(4);
}
 
void Do_blue_sub(const std_msgs::Float64MultiArray msg){
    pose_sub_blue.data = msg.data;
    ROS_INFO("position && angle:(%f,%f,%f) ",pose_sub_blue.data.at(0),pose_sub_blue.data.at(1),pose_sub_blue.data.at(4));
    pose[0] = pose_sub_blue.data.at(0)/X_RATIO+X_ERROR;
    pose[1] = pose_sub_blue.data.at(1)/Y_RATIO+Y_ERROR;
    pose[4] = pose_sub_blue.data.at(4);
}
 
void Do_green_sub(const std_msgs::Float64MultiArray msg){
    pose_sub_green.data = msg.data;
    ROS_INFO("position && angle:(%f,%f,%f) ",pose_sub_green.data.at(0),pose_sub_green.data.at(1),pose_sub_green.data.at(4));
    pose[0] = pose_sub_green.data.at(0)/X_RATIO+X_ERROR;
    pose[1] = pose_sub_green.data.at(1)/Y_RATIO+Y_ERROR;
    pose[4] = pose_sub_green.data.at(4);
}
 
void Do_purple_sub(const std_msgs::Float64MultiArray msg){
    pose_sub_purple.data = msg.data;
    ROS_INFO("position && angle:(%f,%f,%f) ",pose_sub_purple.data.at(0),pose_sub_purple.data.at(1),pose_sub_purple.data.at(4));
    pose[0] = pose_sub_purple.data.at(0)/X_RATIO+X_ERROR;
    pose[1] = pose_sub_purple.data.at(1)/Y_RATIO+Y_ERROR;
    pose[4] = pose_sub_purple.data.at(4);
}
 
void Do_yellow_sub(const std_msgs::Float64MultiArray msg){
    pose_sub_yellow.data = msg.data;
    ROS_INFO("position && angle:(%f,%f,%f) ",pose_sub_yellow.data.at(0),pose_sub_yellow.data.at(1),pose_sub_yellow.data.at(4));
    pose[0] = pose_sub_yellow.data.at(0)/X_RATIO+X_ERROR;
    pose[1] = pose_sub_yellow.data.at(1)/Y_RATIO+Y_ERROR;
    pose[4] = pose_sub_yellow.data.at(4);
}
 
 
void set_position(float x,float y,float z,float t,float angle,float angle_t){
    target_position.x=x;
    target_position.y=y;
    target_position.z=z;
    target_position.duration = t;
    servo.data = 90 + angle;
    servo.duration = angle_t;
}
 
 
 
int Do_pose_sub(char chose , float angle){
    switch(chose){
        case 'r':
            set_position(pose[0], pose[1], HIGH, 0.3, pose[4]+angle, 0.1);
            if(pose[0] == 0){return 1;}
            else return 0;
            break;
        case 'b':
            set_position(pose[0], pose[1], HIGH, 0.3, pose[4]+angle, 0.1);
            if(pose[0] == 0){return 1;}
            else return 0;
            break;
        case 'o':
            set_position(pose[0], pose[1], HIGH, 0.3, pose[4]+angle, 0.1);
            if(pose[0] == 0){return 1;}
            else return 0;
            break;
        case 'l':
            set_position(pose[0], pose[1], HIGH, 0.3, pose[4]+angle, 0.1);
            if(pose[0] == 0){return 1;}
            else return 0;
            break;
        case 'g':
            set_position(pose[0], pose[1], HIGH, 0.3, pose[4]+angle, 0.1);
            if(pose[0] == 0){return 1;}
            else return 0;
            break;
        case 'p':
            set_position(pose[0], pose[1], HIGH, 0.3, pose[4]+angle, 0.1);
            if(pose[0] == 0){return 1;}
            else return 0;
            break;
        case 'y':
            set_position(pose[0], pose[1], HIGH, 0.3, pose[4]+angle, 0.1);
            if(pose[0] == 0){return 1;}
            else return 0;
            break;
    }
}
 
 
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"demo_1");
    ros::NodeHandle nh;
    ros::Publisher cmdpub = nh.advertise<std_msgs::String>("cmd",10);
    ros::Publisher pose_pub = nh.advertise<jetmax_control::SetJetMax>("/jetmax/command",10);
    ros::Publisher servo_pub = nh.advertise<jetmax_control::SetServo>("/jetmax/end_effector/servo1/command",10);
    ros::Publisher sucker_pub = nh.advertise<std_srvs::SetBoolRequest>("/jetmax/end_effector/sucker/command",10);
    ros::Publisher sucker_E_pub = nh.advertise<std_srvs::SetBoolRequest>("/jetmax/end_effector/sucker/statue",10);

    ros::Subscriber red_sub = nh.subscribe<std_msgs::Float64MultiArray>("red",10,Do_red_sub);
    ros::Subscriber browm_sub = nh.subscribe<std_msgs::Float64MultiArray>("brown",10,Do_brown_sub);
    ros::Subscriber orange_sub = nh.subscribe<std_msgs::Float64MultiArray>("orange",10,Do_orange_sub);
    ros::Subscriber blue_sub = nh.subscribe<std_msgs::Float64MultiArray>("blue",10,Do_blue_sub);
    ros::Subscriber green_sub = nh.subscribe<std_msgs::Float64MultiArray>("green",10,Do_green_sub);
    ros::Subscriber purple_sub = nh.subscribe<std_msgs::Float64MultiArray>("purple",10,Do_purple_sub);
    ros::Subscriber yellow_sub = nh.subscribe<std_msgs::Float64MultiArray>("yellow",10,Do_yellow_sub);
     
    std::stringstream ss;
    int flag = 0;
    bool move_flag = true;
    int count = 0;
/* Fill in the target point and angle */
    float target_xy[34][2]={
        {-40,0},{-108,13},{-165,-5},{-43,-25},{-110,-15},
        {-43,-45},{-79.736,-50},{-120,-50},{-175,-40},{-15,-68},
        {-169,-82},{-118,-90},{-92,-85},{-36,-100},{-75,-140},
        {-76.5,-120},{-140,-110},{-163,-130},{-33,-130},{-34.5,-168},
        {-135,-136},{-63,-170},{-117,-160},{-155,-170},{-164,-205},
        {-110,-190},{-25,-207},{-45,-203},{-138,-220},{-178,-240},
        {-89.5,-220},{-28,-248},{-55,-252},{-110,-250}
    };
/* Fill in the target color and status angle */
    char color[34]={
        'r' , 'r' , 'o' , 'r' , 'r' , 
        'r' , 'b' , 'g' , 'y' , 'p' , 
        'l' , 'b' , 'y' , 'b' , 'y' , 
        'g' , 'l' , 'o' , 'b' , 'l' , 
        'y' , 'o' , 'y' , 'l' , 'g' , 
        'g' , 'l' , 'p' , 'p' , 'p' , 
        'p' , 'b' , 'o' , 'o' };
    float Angle[35]={
        0 , 0 , 0 , 0 , 0 , 
        180 , -90 , 0 , 90 , 180 , 
        -90 , 0 , 90 , 180 , -90 , 
        0 , 90 , 180 , -90 , 0 , 
        90 , 180 , -90 , 0 , 90 , 
        180 , -90 , 0 , 90 , -90 , 
        -90 , 0 , 90 , 180 , -90 };
 
    ros::Rate rate(1);
    set_position(0, -150, 100, 0.5, 0, 0.1);
    pose_pub.publish(target_position);
 
    while(ros::ok())
    {
        sucker.data = true;
        sucker_pub.publish(sucker);
        if(count == 68){
            ROS_INFO("THE END");
            break;
        }
        ROS_INFO("%d",count);
        if(count == 36){
            ss.str("");
            ss << "a";
            sendcmd(ss);
            cmdpub.publish(msg);
            ros::Duration(1).sleep();
        }
        if(count%2 == 0){
            flag = 0;
            Do_pose_sub(color[count] , Angle[count]);//set_position
            servo_pub.publish(servo);
            pose_pub.publish(target_position);//poblish target_posion-HIGH
            ros::Duration(1).sleep(); //1s
            target_position.z = LOW;
            pose_pub.publish(target_position);//poblish target_posion-LOW
            ros::Duration(0.8).sleep();//0.8s
            target_position.z = HIGH;
            pose_pub.publish(target_position);//poblish target_posion-HIGH
            ros::Duration(1).sleep();//1s
        }

        if(count%2 == 1){
            ss.str("");
            ss << "q";
            sendcmd(ss);
            cmdpub.publish(msg);//Pneumatic to swing plate areas
            ros::Duration(1).sleep();//1s
            flag = Do_pose_sub(color[(count+1)/2] , Angle[(count+1)/2]);//Read data function to determine if there is data
            if(flag == 1){ //Move without any images
                if(move_flag == true){
                    ss.str("");
                    ss << "n";
                    sendcmd(ss);
                    cmdpub.publish(msg);
                }
                if(move_flag == false){
                    ss.str("");
                    ss << "m";
                    sendcmd(ss);
                    cmdpub.publish(msg);
                }
                move_flag = !move_flag; //Used for back and forth movement
            }
            if(count < 36)
            set_position(target_xy[(count-1)/2][0]+BAI_X, target_xy[(count-1)/2][1]+BAI_Y, HIGH, 0.3, 0, 0.1);
            if(count >= 36)
            set_position(target_xy[(count-1)/2][0]+BAI_X, target_xy[(count-1)/2][1]+BAI_Y+MOVE_Y, HIGH, 0.3, 0, 0.1);
            pose_pub.publish(target_position);
            servo_pub.publish(servo);//poblish target_posion-HIGH
            ros::Duration(0.5).sleep();//0.5s
            target_position.z = LOW_T;
            pose_pub.publish(target_position);//poblish target_posion-LOW_T
            sucker.data = false;
            sucker_pub.publish(sucker);
            sucker_E.data = false;
            sucker_E_pub.publish(sucker_E);
            ros::Duration(1.8).sleep();//1.8s
            target_position.z = HIGH;
            target_position.y = -160;
            pose_pub.publish(target_position);//poblish target_posion-HIGH
            ros::Duration(0.8).sleep();//0.8s
            ss.str("");
            ss << "w";
            sendcmd(ss);
            cmdpub.publish(msg); //Pneumatic to sacttered areas
            ros::Duration(0.4).sleep();//0.4s
        }
        count++;
        rate.sleep();
        ros::spinOnce();//处理回调函数
    }
    return 0;
}
