cmake_minimum_required(VERSION 3.12)
project(DiskSim.x)

set(CMAKE_CXX_STANDARD 17)

add_executable(fcfs.x FCFS_Queue/main.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp CommonFiles/Request.cpp)
add_executable(st.x ST_Queue/main.cpp ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp CommonFiles/Request.cpp)
add_executable(pickup.x Pickup_Queue/main.cpp Pickup_Queue/PickupQueue.cpp Pickup_Queue/PickupQueueNode.cpp CommonFiles/Request.cpp)
add_executable(look.x Look_Queue/main.cpp Look_Queue/LookQueue.cpp Look_Queue/LookQueueNode.cpp CommonFiles/Request.cpp)
