#  Performance Analysis and Optimization Project

We have a directed graph with $n$ nodes. The nodes of the graph are labeled with numbers $0, 1, \dots, n − 1$. There is a directed edge between each pair of the nodes. The cost of the edge between nodes $i$ and $j$ is $d_{ij}$. We will assume that $d_{ij}$ is a non-negative real number. For convenience, we write $d_{ii}=0$ for each node $i$.

However, the costs do not necessarily satisfy the triangle inequality. We might have an edge of cost $d_{ij}=10$ from node $i$ to $j$, but there might be an intermediate node $k$ with $d_{ik}=2$ and $d_{kj}=3$. Then we can follow the route $i \rightarrow k \rightarrow j$ at a total cost of $2 + 3 = 5$, while the direct route $i \rightarrow j$ would cost $10$.

Our task is to find for all $i$ and $j$ what is the cost of getting from $i$ to $j$ by taking **at most two edges**. If we write $r_{ij}$ for the result, then clearly

$$r_{ij} = \min_k (d_{ik} + d_{kj}),$$

where $k$ ranges over $0, 1, \dots, n − 1$. Note that we will also consider here e.g. the route $i \rightarrow i \rightarrow j$, and hence we will also find a path of one edge if it happens to be cheapest.
