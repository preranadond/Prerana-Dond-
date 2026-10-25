## Algorithm -

1.Start.

2.Input the number of hospital departments and their names.

3.Create a graph using an adjacency list to represent departments and corridors.

4.Enter the starting department.

5.Initialize the visited array as false and create an empty queue.

6.Mark the starting department as visited and add it to the queue.

7.Repeat the following steps while the queue is not empty:

•Remove the front department from the queue.

•Display the department.

•Visit all its unvisited neighbouring departments.

•Mark each neighbour as visited and add it to the queue.

8.Display all reachable departments in BFS traversal order.

9.Enter another department to check its reachability.

10.If the department is visited, display "Target is reachable." Otherwise, display "Target is not reachable."

11.Stop.
