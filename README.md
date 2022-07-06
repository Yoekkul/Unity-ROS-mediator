# Unity ROS Mediator
The goal of the Mediator is to provide an interface which a Unity-based client can use to get a downsampled grid_map. In this way the computationally expensive part of the work is performed on the more powerful server hardware (for instance on the HEAp excavator) while not overwhelming the Unity client 

## ROS nodes used
* [grid_map](https://github.com/anybotics/grid_map/)
* [ROS-TCP endpoint](https://github.com/Unity-Technologies/ROS-TCP-Endpoint)

* [Unity robotics hub](https://github.com/Unity-Technologies/Unity-Robotics-Hub) <-contains URDF importer
## Starting project

Launch docker: `./bin/run.sh --type=cpu` 

**Running mediator:**
* `roscore`
* `rosrun mediator scale_grid_map_server`

**Get Sample data via:**
* `roslaunch grid_map_demos simple_demo.launch`

**Running TCP connector**
* `roslaunch ros_tcp_endpoint endpoint.launch`
