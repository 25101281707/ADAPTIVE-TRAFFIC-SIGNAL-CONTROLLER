// Core idea only: priority queue (max-heap) + aging for fairness.
// No serial, no Arduino code — just the decision logic

#include <iostream>
#include <queue>
#include <vector>

struct Lane {
    int id;
    int vehicleCount;
    int waitTime;

    double priority(double alpha = 2.0, double beta = 1.0) const {
        return alpha * vehicleCount + beta * waitTime; // aging: waitTime raises priority over time
    }
};

struct LaneCompare {
    bool operator()(const Lane& a, const Lane& b) const {
        return a.priority() < b.priority(); // makes priority_queue act as a max-heap
    }
};

int main() {
    std::vector<Lane> lanes = {
        {0, 8, 0},
        {1, 1, 0},   // nearly empty lane — watch what happens to it over time
        {2, 5, 0},
        {3, 3, 0}
    };

    for (int cycle = 1; cycle <= 5; cycle++) {
        std::priority_queue<Lane, std::vector<Lane>, LaneCompare> pq;
        for (auto& lane : lanes) pq.push(lane);

        Lane winner = pq.top();
        std::cout << "Cycle " << cycle << ": Lane " << winner.id
                  << " wins (count=" << winner.vehicleCount
                  << ", priority=" << winner.priority() << ")\n";

        for (auto& lane : lanes) {
            if (lane.id == winner.id) lane.waitTime = 0;
            else lane.waitTime += 5; // every lane that lost waits a bit longer
        }
    }
    return 0;
}
