#include <string>
#include <iostream>
#include "PageTable.h"
#include <sstream>

using namespace std;

PageTable::PageTable() {
    maxPages = 0;
    faults = 0;
    timer = 0;
    totalFaults = 0;
    accessCounter = 0;
}

void PageTable::initArray(int pages) {
    maxPages = pages;

    // initialize all valid frames to -1 to indicate that no page exists
    // second number determines resident bit
    for(int i = 0; i < maxPages; i++) {
        frames[i][0] = -1;
        frames[i][1] = 0;
    }

    // set the rest of the unused frames to a number we will never search for
    for(int i = maxPages; i < MAX_FRAMES; i++) {
        frames[i][0] = -9999;
    }
    cout << "Page table created!" << endl;
}

int PageTable::findPage(int page) {
    // -9999 indicates page not found
    // -1 indicates no free frame
    // otherwise this will return the index of the page
    accessCounter++;
    if(frames[maxPages-1][0] != -1) {
        // -1 indicates no free frame
        totalFaults++;
        faults++;
        return -1;
    } else {
        for(int i = 0; i < maxPages; i++) {
            if(frames[i][0] == page) {
                return i;
            }
        }
    }
    totalFaults++;
    faults++;
    return -9999;
}

void PageTable::writeToFrame(int page) {
    for(int i = 0; i < maxPages; i++) {
        if(frames[i][0] == -1) {
            frames[i][0] = page;
            frames[i][1] = 1;
            return;
        }
    }
}

void PageTable::writeToFrame(int index, int page) {
    frames[index][1] = 1;
}

int PageTable::getResidentPages() {
    int count = 0;
    for(int i = 0; i < maxPages; i++) {
        if(frames[i][0] != -1) {
            count++;
        }
    }
    return count;
}

int PageTable::getAccessCount() {
    return accessCounter;
}

int PageTable::getFaultCount() {
    return totalFaults;
}

string PageTable::toString() {
    stringstream ss;
    for(int i = 0; i < maxPages; i++) {
        if(frames[i][0] != -1) {
            ss <<  "Index " << to_string(i) << ": Page: " << frames[i][0] << ", Resident bit: " << frames[i][1] << "\n";
        }
    }
    string output = ss.str();
    return output;
}

string PageTable::checkUseBits() {
    if(timer == MAX_INTERVAL || (faults == MAX_FAULTS && timer < MIN_INTERVAL)) {
        for(int i = 0; i < maxPages; i++) {
            if(frames[i][1] == 0) {
                frames[i][0] = -1;
            } else {
                frames[i][1] = 0;
            }
        }
        faults = 0;
        timer = 0;
        cout << "bits checked!" << endl;
        return toString();
    }
    return "";
}
