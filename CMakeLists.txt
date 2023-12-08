cmake_minimum_required(VERSION 3.12)
project(DiskSim.x)

set(CMAKE_CXX_STANDARD 17)

# Wheeeeee
add_executable(disksim.x main.cpp CommonFiles/Request.cpp eventNode.h Disk.cpp eventQueue.cpp
               FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp
               ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp
               Pickup_Queue/PickupQueue.cpp Pickup_Queue/PickupQueueNode.cpp
               Look_Queue/LookQueue.cpp Look_Queue/LookQueueNode.cpp
               CLook_Queue/CLookQueue.cpp CLook_Queue/CLookQueueNode.cpp
        main_old.cpp
)
