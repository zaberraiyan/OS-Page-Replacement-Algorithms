#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <string.h>
#include "policies.h"

using namespace std;

int main (int argc, char *argv[])
{
    //argv1: tracefile
    //argv2: nframes
    //argv3: algo
    //argv4: percent(vms only)
    //argv4/5: debug/quiet

    try {
        if (strcmp(argv[3], "lru") == 0)
        {
            lru(argv[1], atoi(argv[2]), argv[4]);
        } else if (strcmp(argv[3], "fifo") == 0) {
            fifo(argv[1], atoi(argv[2]), argv[4]);
        } else if (strcmp(argv[3], "vms") == 0 && argc == 6) {
            segmented_fifo(argv[1], atoi(argv[2]), atoi(argv[4]), argv[5]);
        } else {
            throw invalid_argument("Wrong algorithm specified");
        }
    }
    catch(invalid_argument& e) {
        cerr << e.what() << endl;
        return -1;
    }

}

