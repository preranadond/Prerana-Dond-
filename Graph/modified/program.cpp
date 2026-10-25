#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class AdvancedHospitalGraph {
    int V;
    vector<vector<int>> adjList;
    vector<string> deptNames;

public:
    AdvancedHospitalGraph(int vertices) {
        V = vertices;
        adjList.resize(vertices);
        deptNames.resize(vertices);
    }

    void setDepartmentName(int id, string name) {
        if (id >= 0 && id < V)
            deptNames[id] = name;
    }

    void addCorridor(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void analyzeHospitalLayout(int startVertex) {
        vector<bool> visited(V, false);
        vector<int> levels(V, -1);
        queue<int> q;
        vector<int> traversalOrder;

        visited[startVertex] = true;
        levels[startVertex] = 0;
        q.push(startVertex);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            traversalOrder.push_back(current);

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    levels[neighbor] = levels[current] + 1;
                    q.push(neighbor);
                }
            }
        }
        cout << "\n============================================\n";
        cout << "1. BFS TRAVERSAL ORDER FROM: "
             << deptNames[startVertex] << "\n";
        cout << "============================================\n";

        for (size_t i = 0; i < traversalOrder.size(); ++i) {
            cout << i + 1 << ". "
                 << deptNames[traversalOrder[i]] << "\n";
        }

        cout << "\n============================================\n";
        cout << "2. REACHABLE DEPARTMENTS & DISTANCE LEVELS\n";
        cout << "============================================\n";

        int reachableCount = 0;

        for (int i = 0; i < V; ++i) {
            if (visited[i]) {
                reachableCount++;
                cout << "  [OK] " << deptNames[i]
                     << " -> BFS Level (Corridors away): "
                     << levels[i] << "\n";
            }
        }

        cout << "Total Reachable Departments: "
             << reachableCount << "\n";

        cout << "\n============================================\n";
        cout << "3. UNVISITED (UNREACHABLE) DEPARTMENTS\n";
        cout << "============================================\n";

        int unvisitedCount = 0;

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                unvisitedCount++;
                cout << "  [X] " << deptNames[i]
                     << " (Isolated unit)\n";
            }
        }

        if (unvisitedCount == 0) {
            cout << "  None. All hospital departments "
                 << "are fully accessible!\n";
        }

        cout << "============================================\n";
    }
};

int main() {
    int totalDepartments = 7;

    AdvancedHospitalGraph hospital(totalDepartments);

    hospital.setDepartmentName(0, "Main Entrance Lobby");
    hospital.setDepartmentName(1, "Emergency Room (ER)");
    hospital.setDepartmentName(2, "Radiology / MRI Lab");
    hospital.setDepartmentName(3, "General Surgery Theatre");
    hospital.setDepartmentName(4, "Intensive Care Unit (ICU)");
    hospital.setDepartmentName(5, "Infectious Disease Ward A (Isolated)");
    hospital.setDepartmentName(6, "Infectious Disease Ward B (Isolated)");

    hospital.addCorridor(0, 1);
    hospital.addCorridor(0, 2);
    hospital.addCorridor(1, 3);
    hospital.addCorridor(2, 3);
    hospital.addCorridor(3, 4);
    hospital.addCorridor(5, 6);

    int startChoice;

    cout << "================================================\n";
    cout << "     HOSPITAL ROUTING & ACCESSIBILITY AUDIT\n";
    cout << "================================================\n";

    cout << "0. Main Entrance Lobby\n"
         << "1. Emergency Room (ER)\n"
         << "2. Radiology / MRI Lab\n"
         << "3. General Surgery Theatre\n"
         << "4. Intensive Care Unit (ICU)\n"
         << "5. Infectious Disease Ward A (Isolated)\n"
         << "6. Infectious Disease Ward B (Isolated)\n";

    cout << "------------------------------------------------\n";
    cout << "Enter starting department ID (0-6): ";
    cin >> startChoice;

    if (cin.fail() || startChoice < 0 ||
        startChoice >= totalDepartments) {
        cout << "Invalid input ID. Program terminating.\n";
        return 1;
    }

    hospital.analyzeHospitalLayout(startChoice);

    return 0;
}
