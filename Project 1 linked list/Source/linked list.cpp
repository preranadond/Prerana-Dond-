//Original code
#include <iostream>
#include <string>

using namespace std;

struct LayerNode {
    int layerId;
    string layerName;
    bool isActive;
    
    LayerNode* prev;
    LayerNode* next;

    LayerNode(int id, string name) {
        layerId = id;
        layerName = name;
        isActive = true; // Layer is active by default upon creation
        prev = nullptr;
        next = nullptr;
    }
};

class DigitalArtCanvasManager {
private:
    LayerNode* head; // Visual Background (Bottom Layer)
    LayerNode* tail; // Visual Foreground (Top Layer)

public:
    DigitalArtCanvasManager() {
        head = nullptr;
        tail = nullptr;
    }
    void insertAtBottom(int id, string name) {
        LayerNode* newLayer = new LayerNode(id, name);
        if (!head) {
            head = tail = newLayer;
        } else {
            newLayer->next = head;
            head->prev = newLayer;
            head = newLayer;
        }
        cout << ">> Success: Layer [" << name << "] inserted at the absolute BOTTOM.\n";
    }

    void insertAtTop(int id, string name) {
        LayerNode* newLayer = new LayerNode(id, name);
        if (!tail) {
            head = tail = newLayer;
        } else {
            tail->next = newLayer;
            newLayer->prev = tail;
            tail = newLayer;
        }
        cout << ">> Success: Layer [" << name << "] inserted at the absolute TOP.\n";
    }


    void toggleLayerStatus(int id, bool status) {
        LayerNode* temp = head;
        while (temp) {
            if (temp->layerId == id) {
                temp->isActive = status;
                cout << ">> Layer ID " << id << " status updated to: " << (status ? "ACTIVE" : "INACTIVE") << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << ">> Error: Layer ID " << id << " not found.\n";
    }

    void deleteInactiveLayers() {
        if (!head) {
            cout << ">> Canvas is completely empty.\n";
            return;
        }

        LayerNode* current = head;
        int deleteCount = 0;

        while (current != nullptr) {
            LayerNode* nextNode = current->next; 

            if (!current->isActive) {
                deleteCount++;

                if (current == head) {
                    head = current->next;
                    if (head) head->prev = nullptr;
                }
                else if (current == tail) {
                    tail = current->prev;
                    if (tail) tail->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                cout << ">> Discarding Inactive Layer: [" << current->layerName << "]\n";
                delete current; // Free system heap memory safely
            }
            current = nextNode;
        }
        
        // Final sanity update if everything was cleaned out
        if (!head) tail = nullptr;

        cout << ">> Total inactive layers cleaned up: " << deleteCount << "\n";
    }

    void shiftLayerUp(int id) {
        if (!head || head == tail) return; // Nothing to reorder

        LayerNode* current = head;
        while (current) {
            if (current->layerId == id) {
                break;
            }
            current = current->next;
        }

        if (!current) {
            cout << ">> Error: Target reorder Layer ID " << id << " not found.\n";
            return;
        }
        if (current == tail) {
            cout << ">> Notice: Layer is already at the absolute TOP (Foreground).\n";
            return;
        }
        LayerNode* targetNext = current->next;
        LayerNode* beforeCurrent = current->prev;
        LayerNode* afterTarget = targetNext->next;

        if (beforeCurrent) beforeCurrent->next = targetNext;
        else head = targetNext; // Head tracking pointer updates

        if (afterTarget) afterTarget->prev = current;
        else tail = current; // Tail tracking pointer updates

        targetNext->prev = beforeCurrent;
        targetNext->next = current;
        current->prev = targetNext;
        current->next = afterTarget;

        cout << ">> Reorder Success: Shifted Layer ID " << id << " up by 1 position.\n";
    }

    void renderCanvas() {
        if (!head) {
            cout << "\n========================================\n";
            cout << "       CANVAS IS CURRENTLY EMPTY        \n";
            cout << "========================================\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "     SEQUENTIAL CANVAS RENDERING PIPELINE \n";
        cout << "       (Stacking Context: Bottom -> Top)  \n";
        cout << "========================================\n";
        
        LayerNode* temp = head;
        int renderIndex = 0;
        
        while (temp) {
            cout << " Layer Depth [" << renderIndex++ << "] -> ID: " << temp->layerId 
                 << " | Name: \"" << temp->layerName << "\" | Status: " 
                 << (temp->isActive ? " [ACTIVE]" : " [INACTIVE - Muted]") << "\n";
            temp = temp->next;
        }
        cout << "----------------------------------------\n";
        cout << ">> Render Complete: Final canvas output generated successfully.\n\n";
    }
};

int main() {
    DigitalArtCanvasManager editor;
    int choice, id;
    string name;
    int statusChoice;

    editor.insertAtTop(101, "Background Sketch Fill");
    editor.insertAtTop(102, "Character Vector Lineart");
    editor.insertAtTop(103, "Dynamic Light Overlay FX");

    while (true) {
        cout << "\n--- COLLABORATIVE DIGITAL ART LAYER MANAGER ---\n";
        cout << "1. Insert New Layer at TOP (Foreground)\n";
        cout << "2. Insert New Layer at BOTTOM (Background)\n";
        cout << "3. Toggle Layer Visibility (Active / Inactive Flags)\n";
        cout << "4. Flush & Delete Inactive Design Layers\n";
        cout << "5. Reorder Layers (Shift Targeted Layer Upwards)\n";
        cout << "6. Render Graphic Canvas (Sequential Traversal)\n";
        cout << "7. Close Editor & Exit Program\n";
        cout << "Enter selection choice (1-7): ";
        cin >> choice;

        if (choice == 7) {
            cout << "Exiting the Digital Art Layer Manager workspace. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter unique layer ID (int): ";
                cin >> id;
                cout << "Enter friendly layer name: ";
                cin.ignore();
                getline(cin, name);
                editor.insertAtTop(id, name);
                break;

            case 2:
                cout << "Enter unique layer ID (int): ";
                cin >> id;
                cout << "Enter friendly layer name: ";
                cin.ignore();
                getline(cin, name);
                editor.insertAtBottom(id, name);
                break;

            case 3:
                cout << "Enter target layer ID to edit: ";
                cin >> id;
                cout << "Set structural layer state (1 = Active, 0 = Inactive/Hidden): ";
                cin >> statusChoice;
                editor.toggleLayerStatus(id, (statusChoice == 1));
                break;

            case 4:
                editor.deleteInactiveLayers();
                break;

            case 5:
                cout << "Enter layer ID you want to shift up towards foreground: ";
                cin >> id;
                editor.shiftLayerUp(id);
                break;

            case 6:
                editor.renderCanvas();
                break;

            default:
                cout << ">> Invalid input option! Please input a valid menu item entry code.\n";
        }
    }
    return 0;
}

//Modified code:
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct LayerNode {
    int layerId;
    string layerName;
    bool isActive;

    LayerNode(int id, string name) {
        layerId = id;
        layerName = name;
        isActive = true; 
    }
};
class DigitalArtCanvasManager {
private:
 
    vector<LayerNode*> layerStack; 
    
    queue<LayerNode*> trashDeallocationQueue;

public:
    ~DigitalArtCanvasManager() {
        // Cleanup active layers
        for (auto layer : layerStack) {
            delete layer;
        }
      
        while (!trashDeallocationQueue.empty()) {
            delete trashDeallocationQueue.front();
            trashDeallocationQueue.pop();
        }
    }

    void insertAtTop(int id, string name) {
        LayerNode* newLayer = new LayerNode(id, name);
        layerStack.push_back(newLayer); // Stack Push operation
        cout << ">> Success: Layer [" << name << "] pushed to the absolute TOP (Foreground Stack).\n";
    }

    void insertAtBottom(int id, string name) {
        LayerNode* newLayer = new LayerNode(id, name);
        layerStack.insert(layerStack.begin(), newLayer); // Insert at bottom of stack
        cout << ">> Success: Layer [" << name << "] inserted at the absolute BOTTOM (Background Base).\n";
    }


    void toggleLayerStatus(int id, bool status) {
        for (auto layer : layerStack) {
            if (layer->layerId == id) {
                layer->isActive = status;
                cout << ">> Layer ID " << id << " status updated to: " << (status ? "ACTIVE" : "INACTIVE") << "\n";
                return;
            }
        }
        cout << ">> Error: Layer ID " << id << " not found.\n";
    }

    void deleteInactiveLayers() {
        if (layerStack.empty()) {
            cout << ">> Canvas Stack is completely empty.\n";
            return;
        }

        vector<LayerNode*> activeLayers;
        int movedToTrashCount = 0;

      
        for (auto layer : layerStack) {
            if (!layer->isActive) {
                trashDeallocationQueue.push(layer); 
                movedToTrashCount++;
                cout << ">> Enqueuing Inactive Layer to Trash Queue: [" << layer->layerName << "]\n";
            } else {
                activeLayers.push_back(layer);
            }
        }

        layerStack = move(activeLayers);
        cout << ">> Total layers sent to Garbage Queue: " << movedToTrashCount << "\n";

        int cleanCount = 0;
        while (!trashDeallocationQueue.empty()) {
            LayerNode* targetTrash = trashDeallocationQueue.front(); 
            trashDeallocationQueue.pop();                            
            
            cout << ">> [FIFO Cleanup] Safely freeing heap memory for: [" << targetTrash->layerName << "]\n";
            delete targetTrash;
            cleanCount++;
        }
        cout << ">> Memory Garbage Queue successfully processed. Total freed nodes: " << cleanCount << "\n";
    }

    void shiftLayerUp(int id) {
        if (layerStack.size() < 2) return; 

        for (size_t i = 0; i < layerStack.size(); ++i) {
            if (layerStack[i]->layerId == id) {
                if (i == layerStack.size() - 1) {
                    cout << ">> Notice: Layer is already at the absolute TOP stack limits.\n";
                    return;
                }

                swap(layerStack[i], layerStack[i + 1]);
                cout << ">> Reorder Success: Shifted Layer ID " << id << " up by 1 stack index depth.\n";
                return;
            }
        }
        cout << ">> Error: Target reorder Layer ID " << id << " not found.\n";
    }

    void renderCanvas() {
        if (layerStack.empty()) {
            cout << "\n========================================\n";
            cout << "       CANVAS STACK IS CURRENTLY EMPTY  \n";
            cout << "========================================\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "     SEQUENTIAL CANVAS RENDERING PIPELINE \n";
        cout << "       (Stacking Context: Bottom -> Top)  \n";
        cout << "========================================\n";
        

        for (size_t i = 0; i < layerStack.size(); ++i) {
            cout << " Layer Depth [" << i << "] -> ID: " << layerStack[i]->layerId 
                 << " | Name: \"" << layerStack[i]->layerName << "\" | Status: " 
                 << (layerStack[i]->isActive ? " [ACTIVE]" : " [INACTIVE - Muted]") << "\n";
        }
        cout << "----------------------------------------\n";
        cout << ">> Render Complete: Final Stack output generated successfully.\n\n";
    }
};

int main() {
    DigitalArtCanvasManager editor;
    int choice, id;
    string name;
    int statusChoice;

    editor.insertAtTop(101, "Background Sketch Fill");
    editor.insertAtTop(102, "Character Vector Lineart");
    editor.insertAtTop(103, "Dynamic Light Overlay FX");

    while (true) {
        cout << "\n--- COLLABORATIVE DIGITAL ART LAYER MANAGER (STACK & QUEUE) ---\n";
        cout << "1. Push New Layer to TOP (Foreground Stack)\n";
        cout << "2. Insert New Layer at BOTTOM (Base Background)\n";
        cout << "3. Toggle Layer Visibility (Active / Inactive Flags)\n";
        cout << "4. Flush & Process Inactive Layers (Queue Deallocation)\n";
        cout << "5. Reorder Layers (Shift Layer Upwards)\n";
        cout << "6. Render Graphic Canvas (Bottom-to-Top Traversal)\n";
        cout << "7. Close Editor & Exit Program\n";
        cout << "Enter selection choice (1-7): ";
        cin >> choice;

        if (choice == 7) {
            cout << "Exiting workspace. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter unique layer ID (int): ";
                cin >> id;
                cout << "Enter friendly layer name: ";
                cin.ignore();
                getline(cin, name);
                editor.insertAtTop(id, name);
                break;
            case 2:
                cout << "Enter unique layer ID (int): ";
                cin >> id;
                cout << "Enter friendly layer name: ";
                cin.ignore();
                getline(cin, name);
                editor.insertAtBottom(id, name);
                break;
            case 3:
                cout << "Enter target layer ID to edit: ";
                cin >> id;
                cout << "Set structural layer state (1 = Active, 0 = Inactive): ";
                cin >> statusChoice;
                editor.toggleLayerStatus(id, (statusChoice == 1));
                break;
            case 4:
                editor.deleteInactiveLayers();
                break;
            case 5:
                cout << "Enter layer ID you want to shift up: ";
                cin >> id;
                editor.shiftLayerUp(id);
                break;
            case 6:
                editor.renderCanvas();
                break;
            default:
                cout << ">> Invalid input option!\n";
        }
    }
    return 0;
}
