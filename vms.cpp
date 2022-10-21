#include "policies.h"
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

void segmented_fifo(char* file_name, int frames_num, int percent, string process)
{
    vector<int> page_table1; // fifo
    vector<int> page_table2; // lru
    vector<int>::iterator iter;

    map<int, char> memory1;
    map<int, char> memory2;

    int events = 0;
    int read = 0;
    int write = 0;

    int hit, miss = 0;

    int lru_frames = (frames_num * percent) / 100; // lru frames num
    int fifo_frames = frames_num - lru_frames; // fifo frames num

    //if % = 0 call function fifo only
    if (percent == 0) {
       fifo(file_name, frames_num, process);
    } else if (percent == 100) {
       lru(file_name, frames_num, process);
    }
    //if % = 100 condition call function lru only

   
    //mixed call, write vms
        //if address not in FIFO
            //FIFO not FULL
            //FIFO FULL
                //not in LRU
                    //LRU not full
                    //LRU Full
                //in LRU

        //if address in FIFO        (add debug hit)
   
    
    //-> open file
    else {
        unsigned address = 0;
        char rw = ' ';
        FILE *file = fopen(file_name, "r");

        if (file == NULL) {
            cout << "File open failed  " << file_name << endl;
            exit(EXIT_FAILURE);
        }

        while (fscanf(file,"%x %c",&address,&rw) != EOF)
        {
            //vms statements + debug statements
            address /= 4096; //4kb int

            if (memory1.find(address) == memory1.end()) {    //not in FIFO


                if (memory1.size() < fifo_frames)   //FIFO not full
                {

                    if(strcmp(process.c_str(), "debug") == 0) //printing page miss
                    {
                        cout << "Page Miss" << endl;
                        // miss++;
                    }

                    read++;//increment read disk
                    
                    page_table1.push_back(address);
                    memory1[address] = rw;
                    
                } 

                else  //FIFO full
                {
                    iter = find(page_table2.begin(), page_table2.end(), address);//iterator will use for LRU
                    //not in LRU
                        //LRU not FULL
                        //LRU FULL
                    //in LRU

                    if (memory2.find(address) == memory2.end()) {   //not in LRU

                        if(strcmp(process.c_str(), "debug") == 0) //printing page miss
                        {
                            cout << "Page Miss" << endl;
                            // miss++;
                        }

                        if(memory2.size() < lru_frames)    //LRU not FULL
                        {
                            read++;
                    
                            //add oldest fifo to lru
                            page_table2.push_back(page_table1.front());
                            memory2[page_table1.front()] = memory1[page_table1.front()];

                            //erase from fifo
                            memory1.erase(page_table1.front());
                            page_table1.erase(page_table1.begin());

                            // add new address in FIFO
                            memory1[address] = rw;
                            page_table1.push_back(address);
                        }
                        else    //LRU FULL
                        {
                            read++;
                            
                            if (memory2[page_table2.front()] == 'W')
                            {
                                write++;
                            }
                    
                            // erase oldest in lru
                            memory2.erase(page_table2.front());
                            page_table2.erase(page_table2.begin());

                            // add oldest address in fifo to lru
                            page_table2.push_back(page_table1.front());
                            memory2[page_table1.front()] = memory1[page_table1.front()];

                            // erase oldest from fifo
                            memory1.erase(page_table1.front());
                            page_table1.erase(page_table1.begin());

                            // add new address to fifo
                            memory1[address] = rw;
                            page_table1.push_back(address);
                        }
                        
                    } 
                    
                    else if (iter != page_table2.end()) {    //in LRU

                        if(strcmp(process.c_str(), "debug") == 0) //printing page hit
                        {
                            cout << "Page Hit" << endl;
                            // hit++;
                        }
                    
                        if (rw == 'W') // if it is 'W'
                        {
                            memory2[address] = 'W';
                        }
                
                        // move to fifo
                        memory1[address] = memory2[address];
                        page_table1.push_back(address);
                        
                        // erase from lru
                        memory2.erase(address);
                        page_table2.erase(iter);
                
                        // put oldest in LRU
                        page_table2.push_back(page_table1.front());
                        memory2[page_table1.front()] = memory1[page_table1.front()];
                        
                        // erase oldest from FIFO
                        memory1.erase(page_table1.front());
                        page_table1.erase(page_table1.begin());
                    }
                }

            } else {    //in FIFO

                if(strcmp(process.c_str(), "debug") == 0) //printing page hit
                {
                    cout << "Page Hit" << endl;
                    // hit++;
                }

                if (rw == 'W') {
                    memory1[address] = rw;
                }

            }
            events++;
        }

        fclose(file);

        cout << "Total Memory Frames: " << frames_num << endl;
        cout << "Events in trace: " << events << endl;
        cout << "Total Disk Reads: " << read << endl;
        cout << "Total Disk Writes: " << write << endl;

        // cout << "Hits: " << events - read << endl;
        // cout << "Misses: " << read << endl; 
        //For debugging
    }
}

