# -CPU-Scheduling-optimiser

### :rocket: Set up
<h6> CPU scheduling is the process by which the operating system allocates CPU resources to different processes, and the entire process of CPU scheduling is carried out by the short-term scheduler (a process scheduler) in the operating system. Whenever the CPU is idle, the short-term scheduler selects a process from the ready queue located in memory and gives it to the CPU for execution.</h6>

<h6>The target is that create a new CPU scheduling  algorithm to maximize the CPU working efficiency.</h6>

<h6>This assignment is based on some CPU scheduling algorithms. E.g  Non-preemptive scheduling and preemptive scheduling.</h6>

### 🏝️Video presentation
[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/bcdKHnG-KS8/0.jpg)](https://www.youtube.com/watch?v=bcdKHnG-KS8)

### ℹ️Data Format
<h6>An input data file is a simulated list of arriving customers. Input data files will be named "data_*.txt", where asterisk will be replaced by a random number (not relevant for you). Each row in such a file describes customer ID, priority (0 for high, 1 for regular), arrival time, and the desired amount of play time. </h6>

<h6>Example:

c00 0 6 23

c01 1 20 13

c02 1 28 17

c03 1 38 28

...</h6>

<h6>In the first line, customer c00 arrived at time 6. This customer is a member and has a high priority. This customer wishes to play for 23 units of time in total. Note that 0 denotes high priority, while 1 denotes regular priority.</h6>

<h6>An output data file is a log of machine usage as a result of a particular scheduling approach. For a given input file, an output file can be generated either using a program in "baseline.cpp" (provided) or your program in "scheduler.cpp" (your submission). Each such output file is also called a scheduling.</h6>

<h6>Each row of the output file describes who was occupying the machine at a particular time slot (starting from 0). If the machine was not occupied, the row will list -1, otherwise it will show customer ID (without letter "c").</h6>

<h6>Example:

0 -1
  
1 -1
  
2 -1
  
3 -1
</h6>
  
<h6>In this example, the machine was unoccupied in time slots 0, ..., 5. Then starting from time slot 6, the machine was used by customer 0.In this example, the machine was unoccupied in time slots 0, ..., 5. Then starting from time slot 6, the machine was used by customer 0.</h6>

### 💻output format
<h6>
 You need to write a program that takes an input data file and generates an output file with a valid scheduling for this input. Implement your program in a single file named "scheduler.cpp". Your program should be a standalone console based application requiring exactly two command line arguments: name of the input file and name of the output file.
</h6>
<h6>
For example, suppose that your program is compiled into ./scheduler, and you also have ./data_1111.txt in the current directory. Then > ./scheduler data_1111.txt out_1111.txt should produce out_1111.txt in this directory, and this file should describe a valid scheduling with respect to input in data_1111.txt. For example, demand of each customer in data_1111.txt must be satisfied in out_1111.txt.
 </h6>
