Original: 
Algorithm
Collaborative Digital Art Layer Manager (Doubly Linked List)
Each layer is a node with: layerId, layerName, isActive, prev, next. head = bottom layer, tail = top layer.
1. Insert at Bottom (Head)
Step 1: Create a new node with the given ID and name; isActive = true.
Step 2: If head is NULL, set head = tail = new node.
Step 3: Otherwise, set new node's next = head and head's prev = new node.
Step 4: Set head = new node.
Step 5: Stop.
2. Insert at Top (Tail)
Step 1: Create a new node with the given ID and name; isActive = true.
Step 2: If tail is NULL, set head = tail = new node.
Step 3: Otherwise, set tail's next = new node and new node's prev = tail.
Step 4: Set tail = new node.
Step 5: Stop.
3. Set Layer Status (Active / Inactive)
Step 1: Set temp = head.
Step 2: Repeat while temp is not NULL:
If temp's layerId = id, set isActive = status, display message and stop.
Otherwise, move temp = temp's next.
Step 3: If not found, display "Layer not found".
Step 4: Stop.
4. Delete Inactive Layers
Step 1: If head is NULL, display "Canvas is empty" and stop.
Step 2: Set current = head and count = 0.
Step 3: Repeat while current is not NULL:
Save nextNode = current's next.
If current is inactive:
(a) If current = head: set head = current's next; if head exists, head's prev = NULL.
(b) Else if current = tail: set tail = current's prev; if tail exists, tail's next = NULL.
(c) Else: current's prev → next = current's next, and current's next → prev = current's prev.
Delete current and increase count by 1.
Set current = nextNode.
Step 4: If head is NULL, set tail = NULL.
Step 5: Display count and stop.
5. Shift Layer Up (Swap with Next Layer)
Step 1: If the list is empty or has only one node, stop.
Step 2: Search for the node 'current' with layerId = id by traversing from head.
Step 3: If not found, display error and stop.
Step 4: If current = tail, display "Already at top" and stop.
Step 5: Set targetNext = current's next, beforeCurrent = current's prev, afterTarget = targetNext's next.
Step 6: If beforeCurrent exists, set its next = targetNext; else set head = targetNext.
Step 7: If afterTarget exists, set its prev = current; else set tail = current.
Step 8: Set targetNext's prev = beforeCurrent and targetNext's next = current.
Step 9: Set current's prev = targetNext and current's next = afterTarget.
Step 10: Display success message and stop.
6. Render Canvas (Bottom to Top)
Step 1: If head is NULL, display "Canvas is empty" and stop.
Step 2: Set temp = head and index = 0.
Step 3: Repeat while temp is not NULL: display index, layerId, layerName and status; increase index; set temp = temp's next.
Step 4: Display "Render complete" and stop.
7. Main Program
Step 1: Create the manager object and insert the three sample layers at the top.
Step 2: Display the menu (1–7) and read choice.
Step 3: If choice = 7, exit the program.
Step 4: Otherwise, perform the matching operation:
1 → Insert at Top, 2 → Insert at Bottom, 3 → Set Status, 4 → Delete Inactive, 5 → Shift Up, 6 → Render Canvas; any other → show invalid message.
Step 5: Go back to Step 2.

 Modified:  
. Layer Representation (Node Structure)

Each node contains:
• layerID (Integer)
• name (String)
• isVisible (Boolean)
• next (Pointer to the next layer above)
• prev (Pointer to the previous layer below)
2. Core Operational Steps

• Initialization: Set head = NULL.
• Insertion at Top (Head):
	1. Create a new node N.
	2. If head is NULL, point N's next and prev to itself, then set head = N.
	3. If head exists, find the last node (tail = head->prev).
	4. Set N → next = head, N → prev = tail.
	5. Update tail → next = N and head → prev = N.
	6. Update head = N.
• Deletion of a Layer:
	1. If the list is empty, return.
	2. Locate the target node T. If it's the only node, set head = NULL.
	3. Otherwise, set T → prev → next = T → next.
	4. Set T → next → prev = T → prev.
	5. If T == head, move head to T → next.
	6. Deallocate memory for T.
• Forward Traversal (Render Canvas):
	1. Start at head.
	2. Loop, printing/processing each node's details.
	3. Move to current->next. Stop when current == head again.
