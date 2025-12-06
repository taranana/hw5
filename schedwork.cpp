#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool assignWorker(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsUsed, size_t day, size_t slot);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }

    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();
    sched.clear();

    sched.resize(numDays, vector<Worker_T>(dailyNeed,INVALID_ID));

    vector<size_t> shiftsUsed(numWorkers,0);

    return assignWorker(avail, dailyNeed, maxShifts, sched, shiftsUsed, 0 ,0);
    // Add your code below




}


bool assignWorker(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftsUsed, size_t day, size_t slot) {
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();

    if(day == numDays) {
        return true;
    }


    if(slot == dailyNeed) {
        return assignWorker(avail,dailyNeed,maxShifts,sched,shiftsUsed,day+1,0);
    }

    for(size_t w = 0; w < numWorkers; w++){
        if(!avail[day][w]) {
            continue;
        }

        if(shiftsUsed[w] >= maxShifts) {
            continue;
        }

        bool used = false;
        for(size_t x = 0; x < slot; x++) {
            if(sched[day][x] == w){
                used = true;
                break;
            }
        }
        if(used) {
            continue;
        }

        sched[day][slot] = w;
        shiftsUsed[w]++;

        if(assignWorker(avail,dailyNeed,maxShifts,sched,shiftsUsed,day,slot+1)) {
            return true;
        }

        sched[day][slot] = INVALID_ID;
        shiftsUsed[w]--;

    }

    return false;
}