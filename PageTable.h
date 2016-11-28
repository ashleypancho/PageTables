#ifndef PAGETABLE_H
#define PAGETABLE_H

#define MIN_INTERVAL 4
#define MAX_INTERVAL 6
#define MAX_FAULTS 3
#define MAX_FRAMES 32

class PageTable {
    public:
        PageTable();
        void initArray(int pages); // constructor
        int findPage(int page);
        void writeToFrame(int page);
        void writeToFrame(int index, int page);
        int getResidentPages();
        int getAccessCount();
        int getFaultCount();
        std::string toString();
        std::string checkUseBits();
    private:
        int frames[MAX_FRAMES][2];
        int maxPages;
        int faults;
        int totalFaults;
        int timer;
        int accessCounter;
};

#endif
