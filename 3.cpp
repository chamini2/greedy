#include <vector>
#include <algorithm>
#include <stdio.h>

typedef std::pair<int, int> period_pair;

bool period(period_pair a, period_pair b) {
    return a.second < b.second;
}

int main(int argc, char const *argv[]) {

    int cases;
    int N;
    int now, total;
    std::vector<period_pair> jobs;

    scanf("%d", &cases);

    // for each worker
    for (; cases > 0; --cases) {
        scanf("%d", &N);

        jobs.reserve(N);
        now = 0;
        total = 0;

        // get every job
        for (; N > 0; --N) {
            period_pair job;
            scanf("%d %d", &(job.first), &(job.second));
            jobs.push_back(job);
        }

        // sort the jobs by end time
        std::sort(jobs.begin(), jobs.end(), period);

        // try one by one to see if it can be scheduled
        for (auto job : jobs) {
            if (now <= job.first) {
                now = job.second;
                total++;
            }
        }

        printf("%d\n", total);

        jobs.clear();
    }

    return 0;

}
