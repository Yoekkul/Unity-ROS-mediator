# Unity ROS Mediator


## ROS nodes used
* [grid_map](https://github.com/anybotics/grid_map/)
* [ROS-TCP endpoint](https://github.com/Unity-Technologies/ROS-TCP-Endpoint)

* [Unity robotics hub](https://github.com/Unity-Technologies/Unity-Robotics-Hub) <-contains URDF importer
## Starting project

Launch docker: `./bin/run.sh --type=cpu` 

Running mediator:
* `roscore`
* `rosrun mediator scale_grid_map_server`

Get Sample data via:
* `roslaunch grid_map_demos simple_demo.launch`
