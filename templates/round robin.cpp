#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_QUERIES 120

// Structure for storing query information
struct Query {
    string queryID;
    int arrivalTime;
    int burstTime;
};

// Function to input queries
void input_queries(vector<Query>& faculty, vector<Query>& student, int& timeQuantum) {
    int totalQueries;
    
    cout << "Enter total number of Queries: ";
    cin >> totalQueries;

    // Validate totalQueries input
    while (totalQueries <= 0 || totalQueries > MAX_QUERIES) {
        cout << "\nQueries cannot be <0 or >120! Enter again: ";
        cin >> totalQueries;
    }

    cout << "Enter Time Quantum for each query: ";
    cin >> timeQuantum;

    // Taking input for all queries
    for (int i = 0; i < totalQueries; i++) {
        int queryType;
        cout << "Enter query " << i + 1 << " details:\n";
        cout << "Type of Query (1 for Faculty, 2 for Student): ";
        cin >> queryType;

        if (queryType == 1) {
            Query q;
            cout << "Enter Query ID: ";
            cin >> q.queryID;
            cout << "Enter Query Arrival Time: ";
            cin >> q.arrivalTime;
            cout << "Enter Query Burst Time: ";
            cin >> q.burstTime;
            faculty.push_back(q);
        } else if (queryType == 2) {
            Query q;
            cout << "Enter Query ID: ";
            cin >> q.queryID;
            cout << "Enter Query Arrival Time: ";
            cin >> q.arrivalTime;
            cout << "Enter Query Burst Time: ";
            cin >> q.burstTime;
            student.push_back(q);
        } else {
            cout << "Invalid Input. Please try again.\n";
            i--;  // Decrement index to redo the input for this query
        }
    }
}

// Function for round-robin scheduling
void round_robin(vector<Query>& faculty, vector<Query>& student, int timeQuantum) {
    vector<Query> allQueries;

    // Merging faculty and student queries into one array
    allQueries.insert(allQueries.end(), faculty.begin(), faculty.end());
    allQueries.insert(allQueries.end(), student.begin(), student.end());

    // Sort queries by arrival time (simple bubble sort)
    sort(allQueries.begin(), allQueries.end(), [](const Query& a, const Query& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int total = allQueries[0].arrivalTime;
    int waitTime = 0;
    int turnAroundTime = 0;
    int i = 0;
    int totalQueries = allQueries.size();

    cout << "Starting Round Robin scheduling...\n";
    cout << "Query ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n";

    while (i < totalQueries) {
        Query& currentQuery = allQueries[i];
        int remainingTime = currentQuery.burstTime;

        if (remainingTime <= timeQuantum && remainingTime > 0) {
            total += remainingTime;
            remainingTime = 0;
        } else if (remainingTime > 0) {
            currentQuery.burstTime -= timeQuantum;
            total += timeQuantum;
        }

        if (remainingTime == 0) {
            int waitingTime = total - currentQuery.arrivalTime - currentQuery.burstTime;
            int turnaroundTime = total - currentQuery.arrivalTime;

            cout << currentQuery.queryID << "\t\t" << currentQuery.arrivalTime << "\t\t" 
                 << currentQuery.burstTime << "\t\t" << waitingTime << "\t\t" 
                 << turnaroundTime << "\t\t" << total << "\n";
            waitTime += waitingTime;
            turnAroundTime += turnaroundTime;
        }

        if (i == totalQueries - 1) {
            i = 0;
        } else if (allQueries[i + 1].arrivalTime <= total) {
            i++;
        } else {
            i = 0;
        }
    }

    // Final Summary
    float avgWaitTime = float(waitTime) / totalQueries;
    float avgTATime = float(turnAroundTime) / totalQueries;

    cout << "\nSummary of Execution: \n";
    cout << "Average Turnaround Time: " << avgTATime << " minutes\n";
    cout << "Average Waiting Time: " << avgWaitTime << " minutes\n";
}

// Main function
int main() {
    vector<Query> faculty, student;
    int timeQuantum;

    input_queries(faculty, student, timeQuantum); // Taking inputs
    round_robin(faculty, student, timeQuantum);   // Running the round robin scheduling

    return 0;
}
