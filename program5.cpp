#include <iostream>
#include <iomanip>
#include <fstream>
#include "PageTable.h"
#define MAX_PROCESSES 4

using namespace std;

int main (int argc,char *argv[]) {
    string filename = argv[1];
    int processID, page, buff, faults, accesses;
    char operation;
    PageTable table[MAX_PROCESSES];

    // Prepare for File I/O
    ifstream input;
    ofstream output;
    input.open(filename);
    output.open("status.txt");

    while(!input.eof()){
        input >> processID;
        input >> operation;
        input >> page;

        switch (tolower(operation)) {
            case 'n':
                // new process
                // Create a new page table with the number of pages specified
                table[processID].initArray(page);
                output << "Process " << processID << " has been created. ";
                output << "Page table size is " << page << ". ";
                output << "Number of resident pages is 0." << endl;
                break;
            case 'r':
                // read
                buff = table[processID].findPage(page);
                if(buff == -9999) {
                    // page not found
                    table[processID].writeToFrame(page);
                } else if(buff == -1) {
                    // no free frame
                    output << "No free frame fault" << endl;
                } else {
                    // read page
                    table[processID].writeToFrame(buff, page);
                }
                output << "Process " << processID << " is reading from virtual page " << page << " which occupies frame " << table[processID].findPage(page) << ". ";
                output << "Number of resident pages is " << table[processID].getResidentPages() << endl;
                break;
            case 'w':
                // write
                buff = table[processID].findPage(page);
                if(buff == -9999) {
                    // page not found
                    table[processID].writeToFrame(page);
                } else if(buff == -1) {
                    // no free frame
                    output << "No free frame fault" << endl;
                } else {
                    // read page
                    table[processID].writeToFrame(buff, page);
                }
                output << "Process " << processID << " is writing from virtual page " << page << " which occupies frame " << table[processID].findPage(page) << ". ";
                output << "Number of resident pages is " << table[processID].getResidentPages() << endl;
                break;
            case 't':
                // terminate
                accesses = table[processID].getAccessCount();
                faults = table[processID].getFaultCount();
                output << "Process " << processID << " terminated. ";
                output << "Total memory accesses: " << accesses << ". ";
                output << "Total page faults: " << faults << ". ";
                output << "Page fault percentage: " << (((double)faults) / accesses) * 100 << "%." << endl;
                output << table[processID].toString() << endl;
                break;
            default:
                output << "invalid operation" << endl;
                break;

        }
        // do the thing
        for(int i = 0; i < MAX_PROCESSES; i++) {
            output << table[processID].checkUseBits();
        }

    }
    input.close();
    output.close();
    return 0;
}
