# Performance Analysis and Optimization Project

## Problem Description

We have a directed graph with $n$ nodes. The graph nodes are labelled with numbers $0, 1, \dots, n - 1$. There is a directed edge between each pair of nodes. The cost of the edge between nodes $i$ and $j$ is $d_{ij}$. We will assume that $d_{ij}$ is a non-negative real number. For convenience, we write $d_{ii}=0$ for each node $i$.

However, the costs do not necessarily satisfy the triangle inequality. We might have an edge of cost $d_{ij}=10$ from node $i$ to $j$, but there might be an intermediate node $k$ with $d_{ik}=2$ and $d_{kj}=3$. Then we can follow the route $i \rightarrow k \rightarrow j$ at a total cost of $2 + 3 = 5$, while the direct route $i \rightarrow j$ would cost $10$.

Our task is to find for all $i$ and $j$ what is the cost of getting from $i$ to $j$ by taking **at most two edges**. If we write $r_{ij}$ for the result, then clearly

$$r_{ij} = \min_k (d_{ik} + d_{kj}),$$

where $k$ ranges over $0, 1, \dots, n - 1$. Note that routes such as $i \rightarrow i \rightarrow j$ will also be considered, hence a path of one edge will be found if it happens to be the cheapest.

## Results

| Implementation                 | N = 100 | N = 200 | N = 500 | N = 1000 |  N = 2000 |   N = 5000 |
| :----------------------------- | ------: | ------: | ------: | -------: | --------: | ---------: |
| [Naive](Naive)                 |    0 ms |    5 ms |   70 ms | 1 065 ms | 40 961 ms | 974 426 ms |
| [NaiveOpenMP](NaiveOpenMP)     |   20 ms |   20 ms |   45 ms |   315 ms |  8 667 ms | 172 436 ms |
| [Cached](Cached)               |    0 ms |    2 ms |   33 ms |   265 ms |  2 888 ms |  41 513 ms |
| [CachedOpenMP](CachedOpenMP)   |   30 ms |   30 ms |   30 ms |    71 ms |    672 ms |  13 703 ms |
| [SIMD](SIMD)                   |    0 ms |    5 ms |   50 ms |   317 ms |  3 213 ms |  42 535 ms |
| [SIMDOpenMP](SIMDOpenMP)       |   30 ms |   30 ms |   40 ms |   127 ms |    596 ms |   9 735 ms |
| [OpenCL](OpenCL)               |    0 ms |    0 ms |    6 ms |    59 ms |  1 823 ms |  40 173 ms |
| [OpenCLSwapped](OpenCLSwapped) |    0 ms |    0 ms |    1 ms |    31 ms |    290 ms |   4 672 ms |
