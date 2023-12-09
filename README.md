<h1>Disk Scheduler</h1>
Created by Ethan Edwards on 11/15/23, based off a project template provided by Dr. Ali Kooshesh

A simulated disk scheduler.

<h2>Build instructions</h2>
This project utilizes a makefile. The following commands make different scheduling algorithms.
<ul>
  <li><b>make sim.x OR make</b> : Full project with scheduler included, adds a timer, summary and more data about each disk read.</li>
  <li><b>make fcfs.x</b> : First come, first served</li>
  <li><b>make st.x</b> : Same track</li>
  <li><b>make pickup.x</b> : Pickup</li>
  <li><b>make look.x</b> : Look</li>
  <li><b>make clook.x</b> : CLook</li>
  <li><b>make clean</b> : Removes any/all of the above excecutables from the working directory.</li>
</ul>

To run: ./[name of algorithm].x [input file]
