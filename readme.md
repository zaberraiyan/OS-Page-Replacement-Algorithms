# HOW TO RUN MEMSIM PROGRAM:



//argv1: tracefile: Memory traces that will be read into the program
//argv2: nframes: Number frames to allocate for page tables
//argv3: algo: Page replacement algorithm used
//argv4: percent(vms only): Percent of allocated frames for secondary buffer
//argv4/5: debug/quiet:
    - Debug: Display Page hits/Misses
    - Quiet: Display result


## Step 1: Navigate to project folder and run: make
## Step 2: Run the following command to use the simulator:
     ./memsim <tracefile> <frame_number> <fifo | vms | lru> <percentage: only for vms> <debug | quiet>
