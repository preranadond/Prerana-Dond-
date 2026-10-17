Original :  
1. Allocate Memory: Create a new node tmp with its value set to key. Initialize both lthread and rthread to true (indicating they point to threads).
2. Handle Empty Tree: If root is nullptr, assign root = tmp and terminate.
3. Locate Target Position: Set a current pointer ptr = root and an tracking parent pointer parent = nullptr.
4. Tree Search Loop: Loop while ptr is not null:
	• Assign parent = ptr.
	• If key == ptr->data, terminate (duplicate key detected).
	• If key < ptr->data, move left: if ptr->lthread is false, update ptr = ptr->left; else break loop.
	• If key > ptr->data, move right: if ptr->rthread is false, update ptr = ptr->right; else break loop.
5. Attach Left Child: If key < parent->data:
	• Set tmp->left = parent->left (inherits parent's predecessor link).
	• Set tmp->right = parent (successor becomes parent).
	• Toggle parent->lthread = false.
	• Assign parent->left = tmp.
6. Attach Right Child: If key > parent->data:
	• Set tmp->left = parent (predecessor becomes parent).
	• Set tmp->right = parent->right (inherits parent's successor link).
	• Toggle parent->rthread = false.
	• Assign parent->right = tmp.
7. Return: Output the updated root node pointer.

Modified:
1. Node Allocation: Allocate memory for node tmp. Assign tmp->data = key, tmp->left = nullptr, tmp->right = nullptr, and set both lthread and rthread flags to true.
2. Base Condition: If root equals nullptr, point root to tmp. Print root setup metrics, run verifyThreads(tmp), and return root.
3. Traverse Matrix: Set crawler index ptr = root and companion pointer parent = nullptr.
4. Position Match Loop: Execute while ptr != nullptr:
	• Set parent = ptr.
	• If key == ptr->data, notify user of duplicate drop, clean up tmp memory, and return root.
	• If key < ptr->data: If ptr->lthread == false, step left (ptr = ptr->left). Else, exit the loop.
	• If key > ptr->data: If ptr->rthread == false, step right (ptr = ptr->right). Else, exit the loop.
5. Left Border Placement: If key < parent->data:
	• Point tmp->left to parent->left (inherits predecessor context).
	• Point tmp->right to parent (sets parent as its successor target).
	• Toggle parent->lthread = false (parent left link converts into an explicit child node pointer).
	• Assign parent->left = tmp.
	• Print structural adjustments text block to screen.
6. Right Border Placement: If key > parent->data:
	• Point tmp->left to parent (sets parent as its predecessor target).
	• Point tmp->right to parent->right (inherits successor context).
	• Toggle parent->rthread = false (parent right link converts into an explicit child node pointer).
	• Assign parent->right = tmp.
	• Print structural adjustments text block to screen.
7. Automated Validation Invocations:
	• Invoke verifyThreads(tmp, "Newly Inserted Node Validation").
	• Invoke verifyThreads(parent, "Parent Node Link Validation").
8. Exit Routine: Return the updated root memory address.
9.
