#include <string>

using namespace std;

#ifndef policies
#define policies
void lru(char* file_name, unsigned int frames_num, string process);
void fifo(char *name_of_file, unsigned int num_of_frame, string mode);
void segmented_fifo(char* file_name, int frames_num, int percent, string process);

#endif