#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_cv/grid_map_cv.hpp>

#include <mediator/GetScaledGridMap.h>
#include <mediator/GetStateServed.h>

#include <m545_msgs/M545State.h>
//#include <m545_msgs>

grid_map::GridMap map;
m545_msgs::M545State state;

bool scale_map(mediator::GetScaledGridMap::Request &req, mediator::GetScaledGridMap::Response &res){
    //TODO How can I get the proper map?
    grid_map::GridMap modifiedMap;
    grid_map::GridMapCvProcessing::changeResolution(map, modifiedMap, req.resolution);

    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(modifiedMap, message);
    res.map = message;

    ROS_INFO("Scaled map to %lf [meters/cell]",req.resolution);
    return true;
}

bool get_state(mediator::GetStateServed::Request &req, mediator::GetStateServed::Response &res){

    res.state = state;
    ROS_INFO("Returned state as requested");
    return true;
}

void map_update_callback(const grid_map_msgs::GridMap &message){
    grid_map::GridMapRosConverter::fromMessage(message, map);
    //ROS_INFO("Received new grid map");
}

void state_update_callback(const m545_msgs::M545State &message){
    state = message;    //TODO chec nothing gets lost here
    //ROS_INFO("new State");
}

int main(int argc, char **argv){
    ros::init(argc,argv, "scale_grid_map_server");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("/elevation_mapping/elevation_map", 1000, map_update_callback);
    ros::ServiceServer service = n.advertiseService("scale_grid_map",scale_map);
    ROS_INFO("Ready to simplify map");

    ros::Subscriber stateSub = n.subscribe("/m545_state",1000, state_update_callback);
    ros::ServiceServer stateService = n.advertiseService("m545_state_srv",get_state);

    ROS_INFO("State service ready");
    ros::spin();

    return 0;
}