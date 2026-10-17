Original:
graph TD
    Start([Start]) --> CreateNode[Create Node 'tmp' with flags<br>lthread=true, rthread=true]
    CreateNode --> CheckRoot{Is root == nullptr?}
    
    CheckRoot -- Yes --> RootEmpty[root = tmp] --> RetRoot1[Return root] --> End1([End])
    
    CheckRoot -- No --> InitPtrs[Set ptr = root, parent = nullptr]
    
    InitPtrs --> CheckPtr{Is ptr == nullptr?}
    
    CheckPtr -- No --> SetParent[Set parent = ptr]
    
    SetParent --> MatchKey{Compare key and ptr->data}
    MatchKey -- "key == ptr->data" --> PrintDup[Print 'Duplicate'] --> End2([End])
    
    MatchKey -- "key < ptr->data" --> CheckLThread{Is lthread false?}
    CheckLThread -- Yes --> GoLeft[ptr = ptr->left] --> CheckPtr
    CheckLThread -- No --> AttachStep
    
    MatchKey -- "key > ptr->data" --> CheckRThread{Is rthread false?}
    CheckRThread -- Yes --> GoRight[ptr = ptr->right] --> CheckPtr
    CheckRThread -- No --> AttachStep

    CheckPtr -- Yes --> AttachStep
    
    AttachStep{Is key < parent->data?}
    
    AttachStep -- Yes --> AttachLeft[tmp->left = parent->left<br>tmp->right = parent<br>parent->lthread = false<br>parent->left = tmp]
    AttachLeft --> RetRoot2[Return root] --> End3([End])
    
    AttachStep -- No --> AttachRight[tmp->left = parent<br>tmp->right = parent->right<br>parent->rthread = false<br>parent->right = tmp]
    AttachRight --> RetRoot3[Return root] --> End4([End])

    Modified:
    graph TD
    Start([Start]) --> CreateNode[Create Node 'tmp' with flags<br>lthread=true, rthread=true]
    CreateNode --> CheckRoot{Is root == nullptr?}
    
    CheckRoot -- Yes --> RootEmpty[root = tmp] --> RetRoot1[Return root] --> End1([End])
    
    CheckRoot -- No --> InitPtrs[Set ptr = root, parent = nullptr]
    
    InitPtrs --> CheckPtr{Is ptr == nullptr?}
    
    CheckPtr -- No --> SetParent[Set parent = ptr]
    
    SetParent --> MatchKey{Compare key and ptr.data}
    MatchKey -- "key == ptr.data" --> PrintDup[Print 'Duplicate'] --> End2([End])
    
    MatchKey -- "key < ptr.data" --> CheckLThread{Is lthread false?}
    CheckLThread -- Yes --> GoLeft[ptr = ptr.left] --> CheckPtr
    CheckLThread -- No --> BreakToAttach
    
    MatchKey -- "key > ptr.data" --> CheckRThread{Is rthread false?}
    CheckRThread -- Yes --> GoRight[ptr = ptr.right] --> CheckPtr
    CheckRThread -- No --> BreakToAttach

    CheckPtr -- Yes --> AttachStep
    BreakToAttach[Break to Attach] --> AttachStep
    
    AttachStep[Attach Step] --> CheckDir{Is key < parent.data?}
    
    CheckDir -- Yes --> AttachLeft[tmp.left = parent.left<br>tmp.right = parent<br>parent.lthread = false<br>parent.left = tmp]
    AttachLeft --> RetRoot2[Return root] --> End3([End])
    
    CheckDir -- No --> AttachRight[tmp.left = parent<br>tmp.right = parent.right<br>parent.rthread = false<br>parent.right = tmp]
    AttachRight --> RetRoot3[Return root] --> End4([End])
