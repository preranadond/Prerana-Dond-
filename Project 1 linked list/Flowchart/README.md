Original: 
flowchart TD
    A([Start]) --> B[Create empty list<br/>Insert 3 sample layers]
    B --> C[/Display menu<br/>Read choice/]
    C --> D{Choice = 7?}

    D -- Yes --> E([Stop])
    D -- No --> F[Perform selected operation:<br/>1. Insert Top<br/>2. Insert Bottom<br/>3. Set Status<br/>4. Delete Inactive<br/>5. Shift Up<br/>6. Render]

    F --> C
    
Modified:
graph TD
    Start([Start]) --> IsEmpty{Is List Empty?}
    
    IsEmpty -- Yes --> NewHead[head = New Node]
    NewHead --> SelfLink[Node links to itself]
    SelfLink --> End1([End])
    
    IsEmpty -- No --> FindTail[Find Tail via head->prev]
    FindTail --> LinkNew[Link New Node next to head<br>Link New Node prev to tail]
    LinkNew --> UpdateNeighbors[Update Tail next to New Node<br>Update Head prev to New Node]
    UpdateNeighbors --> UpdateHead[Update Head Pointer]
    UpdateHead --> End2([End])

    %% Styling Elements %%
    classDef default fill:#1e1e24,stroke:#333,stroke-width:2px,color:#fff;
    classDef decision fill:#ff9f1c,stroke:#d47a00,stroke-width:2px,color:#000;
    classDef terminal  fill:#2ec4b6,stroke:#1fa195,stroke-width:2px,color:#000;
    
    class IsEmpty decision;
    class Start,End1,End2 terminal;
