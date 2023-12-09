
# This Makefile is not intended to take advantage of separate compilation.
# It serves as a short-cut to command-line compilation

# Store this file in the project directory (DiskSim)

.DEFAULT_GOAL := sim.x

sim.x:
	g++ -std=c++17 main.cpp CommonFiles/Request.cpp eventNode.h Disk.cpp eventQueue.cpp summary.h FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp PickUp_Queue/PickupQueue.cpp PickUp_Queue/PickupQueueNode.cpp Look_Queue/LookQueue.cpp Look_Queue/LookQueueNode.cpp CLook_Queue/CLookQueue.cpp CLook_Queue/CLookQueueNode.cpp -o sim.x

fcfs.x:
	g++ -std=c++17 CommonFiles/Request.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp FCFS_Queue/main.cpp -o fcfs.x

st.x:
	g++ -std=c++17 CommonFiles/Request.cpp ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp ST_Queue/main.cpp  -o st.x

pickup.x:
	g++ -std=c++17 CommonFiles/Request.cpp PickUp_Queue/main.cpp PickUp_Queue/PickUpQueue.cpp PickUp_Queue/PickUpQueueNode.cpp -o pickup.x

look.x:
	g++ -std=c++17 CommonFiles/Request.cpp Look_Queue/main.cpp Look_Queue/LookQueue.cpp Look_Queue/LookQueueNode.cpp -o look.x

clook.x:
	g++ -std=c++17 CommonFiles/Request.cpp CLook_Queue/main.cpp CLook_Queue/CLookQueue.cpp CLook_Queue/CLookQueueNode.cpp -o clook.x

clean:
	rm -f fcfs.x st.x pickup.x look.x clook.x sim.x
