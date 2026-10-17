Problem Statement – Collaborative Digital Art Layer Manager
Implement a doubly linked list to manage overlapping design layers in an image editor. Perform insertion of a new layer at the top/bottom, deletion of inactive layers, reordering via pointer manipulation, and sequential traversal to render the final canvas.

Objectives=
To implement a doubly linked list for managing multiple design layers in an image editor.
To perform insertion of new layers at the top and bottom of the layer list.
To perform deletion of inactive or unwanted layers efficiently.
To implement reordering of layers using pointer manipulation.
To perform forward and backward traversal of the linked list for layer management.
To understand the practical application of doubly linked lists in managing dynamic data.


Modified Problem statement -
 a Doubly Linked List (DLL) variation with structural refinements, and a Circular Doubly Linked List (CDLL) variant, which fits graphics loops by letting you cycle from top to bottom seamlessly.

 Objectives -
• Manage Stacking Contexts Flexibly: Implement structural representations of graphic project layers using two alternative approaches: a linear sequence with definite boundaries via a Doubly Linked List (DLL), and a continuous loop environment via a Circular Doubly Linked List (CDLL).
• Optimize Top & Bottom Boundary Access: Ensure instant insertion operations at the absolute background layer depth (O(1) at head) and foreground layout depth (O(1) at tail or head->prev) without sweeping the entire data frame layout.
• Maintain Dynamic Rendering Order: Build standard algorithms to swap node structural pointers, shifting layers forward safely without risking memory isolation bugs or breaking boundary constraints.
• Automate Garbage Deallocation: Identify, detach, and permanently free memory layouts belonging to invisible or muted layers (isActive == false) while keeping tracking integrity stable.
