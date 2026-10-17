Original: 
graph TD
    %% Main Architecture Style
    classDef main fill:#f9f,stroke:#333,stroke-width:2px;
    classDef process fill:#e1f5fe,stroke:#0288d1,stroke-width:1px;
    classDef condition fill:#fff9c4,stroke:#fbc02d,stroke-width:1px;
    classDef finish fill:#c8e6c9,stroke:#388e3c,stroke-width:2px;

    %% 1. Insert at Bottom
    subgraph S1 [1. Insert at Bottom Head]
        A1[Create New Node: active=true] --> B1{Is Head NULL?}
        B1 -- Yes --> C1[head = tail = new node]
        B1 -- No --> D1[new node.next = head<br>head.prev = new node]
        D1 --> E1[head = new node]
        C1 --> F1([Stop])
        E1 --> F1
    end

    %% 2. Insert at Top
    subgraph S2 [2. Insert at Top Tail]
        A2[Create New Node: active=true] --> B2{Is Tail NULL?}
        B2 -- Yes --> C2[head = tail = new node]
        B2 -- No --> D2[tail.next = new node<br>new node.prev = tail]
        D2 --> E2[tail = new node]
        C2 --> F2([Stop])
        E2 --> F2
    end

    %% 3. Set Layer Status
    subgraph S3 [3. Set Layer Status]
        A3[temp = head] --> B3{temp != NULL?}
        B3 -- Yes --> C3{temp.layerId == id?}
        C3 -- Yes --> D3[temp.isActive = status<br>Display Success] --> E3([Stop])
        C3 -- No --> F3[temp = temp.next] --> B3
        B3 -- No --> G3[Display 'Layer not found'] --> E3
    end

    %% 4. Delete Inactive Layers
    subgraph S4 [4. Delete Inactive Layers]
        A4{head == NULL?} -- Yes --> B4[Display 'Canvas is empty'] --> C4([Stop])
        A4 -- No --> D4[current = head<br>count = 0]
        D4 --> E4{current != NULL?}
        E4 -- Yes --> F4[nextNode = current.next]
        F4 --> G4{current.isActive == false?}
        G4 -- Yes --> H4{Check Current Position}
        H4 -- current == head --> I4[head = current.next<br>if head exists, head.prev = NULL]
        H4 -- current == tail --> J4[tail = current.prev<br>if tail exists, tail.next = NULL]
        H4 -- Else --> K4[current.prev.next = current.next<br>current.next.prev = current.prev]
        I4 --> L4[Delete current<br>count++<br>current = nextNode]
        J4 --> L4
        K4 --> L4
        L4 --> E4
        G4 -- No --> M4[current = nextNode] --> E4
        E4 -- No --> N4{head == NULL?}
        N4 -- Yes --> O4[tail = NULL] --> P4[Display count] --> C4
        N4 -- No --> P4
    end

    %% 5. Shift Layer Up
    subgraph S5 [5. Shift Layer Up]
        A5{List Empty or size == 1?} -- Yes --> B5([Stop])
        A5 -- No --> C5[Traverse from head for node 'current']
        C5 --> D5{Found?}
        D5 -- No --> E5[Display Error] --> B5
        D5 -- Yes --> F5{current == tail?}
        F5 -- Yes --> G5[Display 'Already at top'] --> B5
        F5 -- No --> H5["Set pointers:<br>targetNext = current.next<br>beforeCurrent = current.prev<br>afterTarget = targetNext.next"]
        H5 --> I5{beforeCurrent exists?}
        I5 -- Yes --> J5[beforeCurrent.next = targetNext]
        I5 -- No --> K5[head = targetNext]
        J5 --> L5{afterTarget exists?}
        K5 --> L5
        L5 -- Yes --> M5[afterTarget.prev = current]
        L5 -- No --> N5[tail = current]
        M5 --> O5["Update linkages:<br>targetNext.prev = beforeCurrent<br>targetNext.next = current<br>current.prev = targetNext<br>current.next = afterTarget"]
        N5 --> O5
        O5 --> P5[Display Success] --> B5
    end

    %% 6. Render Canvas
    subgraph S6 [6. Render Canvas]
        A6{head == NULL?} -- Yes --> B6[Display 'Canvas is empty'] --> C6([Stop])
        A6 -- No --> D6[temp = head<br>index = 0]
        D6 --> E6{temp != NULL?}
        E6 -- Yes --> F6[Display current layer specs<br>index++<br>temp = temp.next] --> E6
        E6 -- No --> G6[Display 'Render complete'] --> C6
    end

    %% Apply Classes
    class F1,F2,E3,C4,B5,C6 finish;
    class B1,B2,B3,C3,A4,E4,G4,N4,A5,D5,F5,I5,L5,A6,E6 condition;

    Modified:  
    graph TD
    classDef finish fill:#c8e6c9,stroke:#388e3c,stroke-width:2px;
    classDef condition fill:#fff9c4,stroke:#fbc02d,stroke-width:1px;

    %% Insertion Block
    subgraph Insertion [Core Step: Insertion at Top Head]
        A1[Create new node N] --> B1{Is head NULL?}
        B1 -- Yes --> C1["N.next = N<br>N.prev = N<br>head = N"]
        B1 -- No --> D1[Find tail: tail = head.prev]
        D1 --> E1["N.next = head<br>N.prev = tail"]
        E1 --> F1["tail.next = N<br>head.prev = N"]
        F1 --> G1[head = N]
        C1 --> H1([Stop])
        G1 --> H1
    end

    %% Deletion Block
    subgraph Deletion [Core Step: Deletion of a Layer]
        A2{Is head NULL?} -- Yes --> B2([Return])
        A2 -- No --> C2[Locate target node T]
        C2 --> D2{Is T the only node?}
        D2 -- Yes --> E2[head = NULL] --> F2[Deallocate memory for T]
        D2 -- No --> G2["T.prev.next = T.next<br>T.next.prev = T.prev"]
        G2 --> H2{Does T == head?}
        H2 -- Yes --> I2[head = T.next] --> F2
        H2 -- No --> F2
        F2 --> J2([Stop])
    end

    %% Forward Traversal
    subgraph Traversal [Core Step: Forward Traversal Render]
        A3{Is head NULL?} -- Yes --> B3([Stop])
        A3 -- No --> C3[Start at current = head]
        C3 --> D3[Print / Process current node details]
        D3 --> E3[Move current = current.next]
        E3 --> F3{Does current == head?}
        F3 -- No --> D3
        F3 -- Yes --> G3([Stop Render])
    end

    class H1,J2,B3,G3 finish;
    class B1,A2,D2,H2,A3,F3 condition;
