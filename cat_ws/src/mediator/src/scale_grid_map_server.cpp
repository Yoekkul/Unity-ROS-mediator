#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_cv/grid_map_cv.hpp>

#include <mediator/GetScaledGridMap.h>
#include <mediator/GetStateServed.h>

#include <m545_msgs/M545State.h>

grid_map::GridMap map;
m545_msgs::M545State state;

// Step 3. --------------- Utility functions --------------------------

// The map gets scaled in the same way as shown in the grid_map resolution_change demo -> https://github.com/ANYbotics/grid_map/blob/master/grid_map_demos/src/resolution_change_demo_node.cpp
// This service receives the desired resolution and scales the grid_map down to it
bool scale_map(mediator::GetScaledGridMap::Request &req, mediator::GetScaledGridMap::Response &res){

    grid_map::GridMap modifiedMap;
    grid_map::GridMapCvProcessing::changeResolution(map, modifiedMap, req.resolution);

    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(modifiedMap, message);
    res.map = message;

    ROS_INFO("Scaled map to %lf [meters/cell]",req.resolution);
    return true;
}


// The state of the machine is returned to the service caller (It contains for instance joint angles and machine position)
bool get_state(mediator::GetStateServed::Request &req, mediator::GetStateServed::Response &res){

    res.state = state;
    ROS_INFO("Returned state as requested");
    return true;
}

// Step 2. --------------- Callbacks ----------------------

void map_update_callback(const grid_map_msgs::GridMap &message){
    grid_map::GridMapRosConverter::fromMessage(message, map);
    //ROS_INFO("Received new grid map");
}

void state_update_callback(const m545_msgs::M545State &message){
    state = message;
    //ROS_INFO("new State");
}


// Step 1. --------------- Main Function ----------------------

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