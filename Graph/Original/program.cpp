#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class HospitalGraph {
    int V;
    vector<vector<int>> adjList; 
    vector<string> deptNames;

public:
    HospitalGraph(int vertices) {
        V = vertices;
        adjList.resize(vertices);
        deptNames.resize(vertices);
    }

    void setDepartmentName(int id, string name) {
        if (id >= 0 && id < V) {
            deptNames[id] = name;
        }
    }

    void addCorridor(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<bool> performBFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        cout << "\n--- BFS Traversal Order From " << deptNames[startVertex] << " ---\n";

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << " -> " << deptNames[current] << " (ID: " << current << ")\n";

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "-------------------------------------------\n";
        return visited;
    }

    void displayDepartments() {
        cout << "\nAvailable Hospital Departments:\n";
        for (int i = 0; i < V; ++i) {
            cout << i << ". " << deptNames[i] << "\n";
        }
    }

    string getDeptName(int id) {
        return deptNames[id];
    }
};

int main() {
    int totalDepartments = 6;
    HospitalGraph hospital(totalDepartments);

    hospital.setDepartmentName(0, "Emergency Room");
    hospital.setDepartmentName(1, "Radiology / X-Ray");
    hospital.setDepartmentName(2, "Intensive Care Unit (ICU)");
    hospital.setDepartmentName(3, "Outpatient Pharmacy");
    hospital.setDepartmentName(4, "Pediatrics Ward");
    hospital.setDepartmentName(5, "Isolation Unit"); 

    hospital.addCorridor(0, 1);
    hospital.addCorridor(0, 2);
    hospital.addCorridor(1, 3); 
    hospital.addCorridor(2, 3);
    hospital.addCorridor(3, 4);

    hospital.displayDepartments();

    int startDept;
    cout << "\nEnter the ID of the starting department for BFS: ";
    cin >> startDept;

    if (startDept < 0 || startDept >= totalDepartments) {
        cout << "Invalid Department ID.\n";
        return 1;
    }

    vector<bool> reachabilityMap = hospital.performBFS(startDept);

    int targetDept;
    cout << "\nEnter the ID of another department to check its reachability: ";
    cin >> targetDept;

    if (targetDept < 0 || targetDept >= totalDepartments) {
        cout << "Invalid Department ID.\n";
        return 1;
    }

    if (reachabilityMap[targetDept]) {
        cout << "\n[SUCCESS] " << hospital.getDeptName(targetDept) 
             << " IS reachable from " << hospital.getDeptName(startDept) << ".\n";
    } else {
        cout << "\n[UNREACHABLE] " << hospital.getDeptName(targetDept) 
             << " IS NOT reachable from " << hospital.getDeptName(startDept) 
             << " (Corridor broken or isolated unit).\n";
    }

    return 0;
}
