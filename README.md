# Unity ROS Mediator
The goal of the Mediator is to provide an interface which a Unity-based client can use to get a downsampled grid_map. In this way the computationally expensive part of the work is performed on the more powerful server hardware (for instance on the HEAp excavator) while not overwhelming the Unity client 

## ROS nodes used
* [grid_map](https://github.com/anybotics/grid_map/)
* [ROS-TCP endpoint](https://github.com/Unity-Technologies/ROS-TCP-Endpoint)

* [Unity robotics hub](https://github.com/Unity-Technologies/Unity-Robotics-Hub) <-contains URDF importer
## Starting project

Launch docker: `./bin/run.sh --type=cpu` 

**Running mediator:**
* `roslaunch mediator mediator.launch`

**Get Sample data via:**
* `time rosbag play -r 5 -l heap_state_2022-06-23-10-06-18.bag  heap_grid_map_2022-06-23-10-06-18.bag`
