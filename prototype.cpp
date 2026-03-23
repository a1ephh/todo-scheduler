#include <iostream>
#include <algorithm>
using namespace std;
// implementing in cpp as proof of concept

struct Task
{
    int id;
    string title;
    double duration;
    double priority;
    int deadline; // as minutes from start of week (0 to 10080)
    bool isCompleted = false;
    bool isSplittable;
    int minChunkSize = 30;

    // density: value per minute (like the ratio we used in class)
    double getDensity() const
    {
        return priority / duration;
    }
};

enum SlotStatus

{

    EMPTY,

    BUSY,

    SLEEP,

    RECURRING_EVENT

};

void greedyScheduler(vector<Task> &taskList, int totalMinutesInWeek)
{
    // sort by density (highest value per minute first)
    sort(taskList.begin(), taskList.end(), [](const Task &a, const Task &b)
         { return a.getDensity() > b.getDensity(); });

    // -1 = EMPTY, -2 = SLEEP/RECURRING. Otherwise, stores Task ID.
    vector<int> timeline(totalMinutesInWeek, -1);
    double totalValue = 0;

    for (const auto &task : taskList)
    {
        if (task.isSplittable) // splittable tasks
        {
            int minutesAssigned = 0;
            // filling any available gap backwards from the deadline
            for (int j = task.deadline - 1; j >= 0 && minutesAssigned < task.duration; --j)
            {
                if (timeline[j] == -1)
                {
                    timeline[j] = task.id;
                    minutesAssigned++;
                }
            }
            if (minutesAssigned == task.duration)
                totalValue += task.priority;
        }
        else
        {
            // for non splittable tasks we find a slot that can fill the given time
            bool scheduled = false;
            for (int start = task.deadline - (int)task.duration; start >= 0; --start)
            {
                bool isFree = true;
                for (int k = 0; k < task.duration; ++k)
                {
                    if (timeline[start + k] != -1)
                    {
                        isFree = false;
                        break;
                    }
                }
                if (isFree)
                {
                    for (int k = 0; k < task.duration; ++k)
                        timeline[start + k] = task.id;
                    totalValue += task.priority;
                    scheduled = true;
                    break;
                }
            }
        }
    }
}
void dp()
{
}

int main()
{
}