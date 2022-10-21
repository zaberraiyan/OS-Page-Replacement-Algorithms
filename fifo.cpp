#include "policies.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

void fifo(char *name_of_file, unsigned int num_of_frame, string mode) {
  queue<int> p_table; // page table
  map<int, char> mem;   // member
  int eve = 0; // event
  int r = 0; // read
  int w = 0;  // write

  int hit, miss = 0;

  unsigned addr = 0; //address
  char rw = ' ';  // read and write
  FILE *fp = fopen(name_of_file, "r");
//open file

  if (fp == NULL) {
    cout << "File open failed  " << name_of_file << endl;
    exit(EXIT_FAILURE);
  }
   // input validation
  while (fscanf(fp, "%x %c", &addr, &rw) != EOF) {
  
    addr = addr / 4096;

    if (mem.find(addr) == mem.end()) {
     if (strcmp(mode.c_str(), "debug") == 0) {
        cout << "page miss" << endl;
        // miss++;
      }
      r++;

      if (mem.size() < num_of_frame) {  //add to page table
        p_table.push(addr);
        mem[addr] = rw;
      }

      else { //page table is full
      
        if (mem[p_table.front()] == 'W') {
          w++;
        }


        mem.erase(p_table.front()); //pop front of queue
        p_table.pop();

        mem[addr] = rw;
        p_table.push(addr);
      }
    }
  // if 'R' encountered, update event and store read with writing as PAGE
      // hit
    else {

        if (strcmp(mode.c_str(), "debug") == 0) {
          cout << "page hit" << endl;
          // hit++;
        }

        if (mem[addr] == 'R') {
          mem[addr] = rw;
        }
    }
    eve++;
  }
  fclose(fp);

  cout << "total memory frames: " << num_of_frame << endl;
  cout << "Events during in trace: " << eve << endl;
  cout << "read all disks: " << r << endl;
  cout << "wrote all disks: " << w << endl;

  // cout << "Hits: " << eve - r << endl;
  // cout << "Misses: " << r << endl;
  //For debugging
} 
