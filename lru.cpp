#include "policies.h"
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void lru(char* file_name, unsigned int frames_num, string process)
{
    vector<int> page_table;
    vector<int>::iterator iter;
    map<int, char> memory;

    unsigned int events = 0;
    unsigned int read = 0;
    unsigned int write = 0;

    int hit, miss = 0;

    //open file
    unsigned address = 0;
    char rw = ' ';
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        cout << "File open failed  " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    while (fscanf(file,"%x %c",&address,&rw) != EOF)
    {
        address /= 4096; //4kb int

        iter = find(page_table.begin(), page_table.end(), address);

        if(iter == page_table.end()) // IF PAGE MISS
        {
            if(strcmp(process.c_str(), "debug") == 0) //printing page miss
            {
                cout << "Page Miss" << endl;
                //miss++;
            }

            read++;

            if (memory.size() < frames_num)
            {
                page_table.push_back(address);
                memory[address] = rw;
            }
            

            else
            {
                if (memory[page_table.front()] == 'W')
                {
                    write++;
                }
              
                memory.erase(page_table.front());
                page_table.erase(page_table.begin());
  
                memory[address] = rw;
                page_table.push_back(address);
            }
        }

        else //IF PAGE HIT
        {
            if(strcmp(process.c_str(), "debug") == 0) //printing page hit
            {
                cout << "Page Hit" << endl;
                //hit++;
            }

            page_table.erase(iter);
            page_table.push_back(address);
  
            if(memory[address] == 'R')
            {
                memory[address] = rw;
            }
          }
          events++;
    }
    
    fclose(file);
      
    cout << "Total Memory Frames: " << frames_num << endl;
    cout << "Events in trace: " << events << endl;
    cout << "Total Disk Reads: " << read << endl;
    cout << "Total Disk Writes: " << write << endl;

    // cout << "Hits: " << events - read  << endl;
    // cout << "Misses: " << read << endl;
    //For debugging
}
