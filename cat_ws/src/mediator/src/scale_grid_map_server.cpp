#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_cv/grid_map_cv.hpp>
#include <mediator/GetScaledGridMap.h>

grid_map::GridMap map;
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

void map_update_callback(const grid_map_msgs::GridMap &message){
    grid_map::GridMapRosConverter::fromMessage(message, map);
    ROS_INFO("Received new grid map");
}

int main(int argc, char **argv){
    ros::init(argc,argv, "scale_grid_map_server");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("/elevation_mapping/elevation_map", 1000, map_update_callback);
    ros::ServiceServer service = n.advertiseService("scale_grid_map",scale_map);
    ROS_INFO("Ready to simplify map");
    ros::spin();

    return 0;
}