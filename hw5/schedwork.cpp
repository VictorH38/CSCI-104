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
bool schedHelper(AvailabilityMatrix avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& shiftsWorking, int row, int col);

bool isValid(AvailabilityMatrix avail, size_t maxShifts, DailySchedule& sched, vector<int>& shiftsWorking, int row, int col);

void printSchedule(const DailySchedule& sched);

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
    sched.clear();
    // Add your code below
		for (size_t i = 0; i < avail.size(); i++) {
				vector<Worker_T> day(dailyNeed);
				sched.push_back(day);
				for (size_t j = 0; j < dailyNeed; j++) {
						sched[i][j] = INVALID_ID;
				}
		}

		vector<int> shiftsWorking((int)avail[0].size(), 0);
		return schedHelper(avail, dailyNeed, maxShifts, sched, shiftsWorking, 0, 0);
}

bool schedHelper(AvailabilityMatrix avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& shiftsWorking, int row, int col) {
		if(row == (int)avail.size()) {
			return true;
		}

		int next_row, next_col;
		next_row = row;
		next_col = col + 1;
		if (next_col == (int)dailyNeed){
				next_row = row + 1;
				next_col = 0;
		}

		for (Worker_T worker = 0; worker < avail[0].size(); worker++) {
				sched[row][col] = worker;
				shiftsWorking[worker] += 1;

				if (isValid(avail, maxShifts, sched, shiftsWorking, row, col)) {
						if (schedHelper(avail, dailyNeed, maxShifts, sched, shiftsWorking, next_row, next_col) == true) {
								return true;
						}
						else {
								sched[row][col] = INVALID_ID;
								shiftsWorking[worker] -= 1;
						}
				}
				else {
						sched[row][col] = INVALID_ID;
						shiftsWorking[worker] -= 1;
				}
		}

		return false;
}


bool isValid(AvailabilityMatrix avail, size_t maxShifts, DailySchedule& sched, vector<int>& shiftsWorking, int row, int col) {
		Worker_T worker = sched[row][col];
		vector<Worker_T> day = sched[row];

		day.erase(day.begin() + col);
		vector<Worker_T>::iterator it = find(day.begin(), day.end(), worker);
		if (it != day.end()) {
				return false;
		}

		if (avail[row][worker] == 0) {
				return false;
		}

		if (shiftsWorking[worker] > (int)maxShifts) {
				return false;
		}

		return true;
}
