
# This Makefile is not intended to take advantage of separate compilation.
# It serves as a short-cut to command-line compilation

# Store this file in the project directory (DiskSim)


fcfs.x:
	g++ -std=c++17 CommonFiles/Request.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp FCFS_Queue/main.cpp -o fcfs.x

st.x:
	g++ -std=c++17 ST_Queue/main.cpp -o st.x

clean:
	rm -f fcfs.x st.x
