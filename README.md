**This is the server part of a larger project. The remaining documentation can be found here: https://github.com/Yoekkul/Docs-MR-remote-for-HEAP**
# Unity ROS Mediator
The goal of the Mediator is to provide an interface which a Unity-based client can use to get a downsampled grid_map. In this way the computationally expensive part of the work is performed on the more powerful server hardware (for instance on the HEAP excavator) while not overwhelming the Unity client.

Unity uses the [ROS-TCP-Endpoint](https://github.com/Unity-Technologies/ROS-TCP-Endpoint) to communicate to the `mediator` via services. In this way the Unity client can decide the frequency at which it receives new data, this is to prevent overtaxing the client.
## ROS nodes used
* [grid_map](https://github.com/anybotics/grid_map/)
* [ROS-TCP endpoint](https://github.com/Unity-Technologies/ROS-TCP-Endpoint)

* [Unity robotics hub](https://github.com/Unity-Technologies/Unity-Robotics-Hub) <-contains URDF importer
## Starting project

Launch docker: `./bin/run.sh --type=cpu` 

**Building mediator**
* Ensure that the `python` command calls python3. If this is not the case use `apt install python-is-python3`. This is essential for the TCP module to function
* Ensure that the `costmap-2d` module is installed, using `apt install ros-noetic-costmap-2d`

**Running mediator:**
* `roslaunch mediator mediator.launch`

---

**Get Sample data via:**
* `time rosbag play -r 5 -l heap_state_2022-06-23-10-06-18.bag  heap_grid_map_2022-06-23-10-06-18.bag`
