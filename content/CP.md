---
title: "CP notes"
date: 2026-01-19T18:28:12-07:00
draft: false
math: true
---

### [Template](https://github.com/h4ck0lympus/CP/blob/main/template.cpp)


A common rule of thumb:
- About **$10^8$ operations per second**

Rough feasibility guide ($n$ = input size):

| $n$ upper bound | Possible complexities |
|-----------------|----------------------|
| $10$           | $O(n!)$, $O(n^7)$, $O(n^6)$   |
| $20$           | $O(2^n \cdot n)$, $O(n^5)$      |
| $80$           | $O(n^4)$                 |
| $400$          | $O(n^3)$                 |
| $7{,}500$        | $O(n^2)$                 |
| $7 \cdot 10^4$      | $O(n \sqrt{n})$               |
| $5 \cdot 10^5$      | $O(n \log n)$            |
| $5 \cdot 10^6$      | $O(n)$                  |
| $10^{18}$         | $O(\log^2 n)$, $O(\log n)$, $O(1)$ |

## Fundamental data structures

1. `vector`
2. `multiset` stores elements in sorted order and allows duplicates.

  * Key properties:
  - Logarithmic insertion and deletion
  - Efficient access to smallest or largest elements
  - Supports queries such as “largest value $\leq X$”

  * Use a multiset when:
    - Order matters
    - Elements are added and removed dynamically
    - You need to repeatedly choose the best valid option

  * for `multiset<int> m`, `m.begin()` will point to first element while, `prev(m.end())` will point to last element. 


## Intutional problems

#### 1. Generating permuations based on relation between 2-3 elements in range of $N$

[2188A](https://codeforces.com/contest/2188/problem/A)

## Greedy algo
1. In greedy string problems, sometimes you have to make the choice out of 2 strings. For example, In lexicographical problems where you only have two choices per step, the greedy choice is almost always: "Pick the smaller of the two resulting strings." Rather than the old string. (see 2180B).

## Binary search on arrays and for answer
## Math

#### Compute answer modulo $1e9 + 7$

## String

#### Circular Problems & The Concat Trick
Concept: To handle circularity in arrays or strings, append the object to itself ($S' = S + S$).

Pros:

* Simplifies logic: Turns circular gaps/patterns into linear ones.

* Eliminates complex `if` statements and modulo arithmetic.

Implementation Tips:

* Limit the Range: Always ensure your results (like max gap length) do not exceed the original length $N$.

* Complexity: Watch for $O(2N)$ memory/time; usually fine for $N \le 10^5$.

Alternative (Index Method): Store indices of key elements (e.g., all 1s).

* Internal gaps: $pos[i+1] - pos[i] - 1$.

* Circular gap: $(N - 1 - pos.back()) + pos[0]$.

Relevant problems: 
1. [2176B](https://codeforces.com/problemset/problem/2176/B) (classic example)

### Array

#### Find median in sliding window in $O(n)$ time


### Graph

#### BFS/DFS

**DFS (recursive)**

```cpp
vector<int> adj[100005];
bool visited[100005];
void dfs(int v) {
  if (visited[v]) return;
  visited[v] = 1;
  for (int neighbour: adj[v]) {
    if (!visited[neighbour]) dfs(neighbour);
  }
}
```

**DFS (iterative)**

>*NOTE:* Most of the times iterative dfs is not reqd.

```cpp
void iterative_dfs(int start) {
  stack<int> st;
  st.push(start);
  visited[start] = 1;

  while (!st.empty()) {
    int v = st.top(); st.pop();
    for (int u : adj[v]) {
      if (!visited[u]) {
        visited[u] = true;
        st.push(u);
      }
    }
  }

}
```

**BFS**

```cpp
vector<int> adj[1000];
bool visited[1000];
int dist[1000][1000];

void bfs(int v) {
  queue<int> q;
  q.push(v);
  dist[v][v] = 0;
  visited[v] = 1;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int e: adj[u]) {
      if (visited[e]) continue;
      visited[e] = 1;
      dist[e] = dist[u] + 1;
      q.push(e);
    }
  }
}
```

**State pruning in BFS**

Sometimes in distance related problem involving BFS, we have to explore all reachable nodes $O(V + E)$. However when single "move" can span multiple cells (like jumping K meters), the number of edges E can explode to $O(V \cdot K)$  . In this situation, there are multiple ways but the core philosophy to tackle is **pruning states** and **skipping redundant edges** to bring the complexity back down to $O(V)$.

#### Multi source BFS

- we can start bfs from multiple sources. Just push multiple sources in the start in the queue.
- Helpful when we need to explore multiple paths from multiple sources at the SAME time.
- Helpful when graph is dynamic, i.e. changes over time.

#### State space BFS

[1063B](https://codeforces.com/contest/1063/problem/B)

#### 0/1 BFS

TODO

#### Bipartite graph

- useful if we need to divide the graph into 2 disjoint independent sets.
- graph not bipartite if we contains odd length cycle
- 

```cpp
vector<int> adj[100005];
int visited[100005]; // use this to store info about color as well as visited or not

bool possible = true;

void dfs(int v, int c) {
  if (visited[v] != -1) return;
  visited[v] = c;

  for (int u: adj[v]){
    if (visited[u] == -1) { // if not visited - visit but with inverted color
      dfs(u, c ^ 1);
    } else if (visited[u] == c)  { // if visited but color is c
      possible = false;
      return;
    }
  }
}

void solve() {
  memset(visited, -1, sizeof(visited));
  ...
  dfs(0, 0); // node 0 with color 0
}
```
* [Building teams](https://cses.fi/problemset/task/1668)
* [NP-Hard-Problem](https://codeforces.com/problemset/problem/687/A)
* [vitaly and cycle](https://codeforces.com/problemset/problem/557/D)
* [alternating paths](https://codeforces.com/problemset/problem/2204/D)
* [Tempe Network Coverage / Cover it](https://codeforces.com/problemset/problem/1176/E)

### Shortest path on weighted edges

TODO

#### Dijkstra

TODO

#### Floyd-Warshal

- useful if we want to find shortest path **among all the edges** in graph.
- time complexity $O(n^3)$

```cpp
// classic floyd-warshal problem
void solve() {
  int n, m, q; cin >> n >> m >> q;
  vector<vector<int>> dist(500, vector<int>(500, INF));
  
  for (int i=0; i < n; i++) dist[i][i] = 0; // distance to itself = 0

  for (int i=0; i < m; i++) {
    int a,b,c; cin >> a >> b >> c;
    --a; --b;
    dist[a][b] = min(dist[a][b], c); // distance to direct neighbour
    dist[b][a] = min(dist[b][a], c); // distance to direct neighbour (if undirected)
  }

  for (int i=0; i < n; i++) { // intermediate
    for (int j=0; j < n; j++) { // source
      for (int k=0; k < n; k++) { // destination
        dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
      }
    }
  }
}
```

[CSES Shortest Route II](https://cses.fi/problemset/task/1672)

### Finding Cycle

#### for undirected graph

in undirected graph, approach is straightforward - when running dfs/bfs, seeing parent is fine, since edges are bidirectional. So the check should be *seeing any other already visited node* if that exists then there is a cycle.

#### for directed graph

in directed graph, we should check if neighbour is visited and exists in current recursion stack. If exists in stack, then visited.

We can also approach this by using 3 states : unvisted, currently exploring, processed.

if visited and currently exploring then it's a cycle. 

TODO

### Topological Sort

**TODO and Practice needed**

### Strongly Connected Components

### 2-Sat

**TODO and Practice needed**

### Minimum Spanning Tree (MST)

**TODO and practice needed**

### DSU (Disjoin set union) / Union find

- stores info about collection of elements in same set. 
- solves the problem of checking if 2 or more nodes in graph exists in same island or not (or similar union finding problems) from O(n) to O(1) (amortized).
- check [DSU.h](https://github.com/h4ck0lympus/CP/blob/main/codeforces/DSU.h) for implementation


## Dynamic Programming

## Range Queries

## Trees

#### Misc coding tips

##### Directional array to reduce code

instead of doing the following and checking each co-ordinate seperately we can just use a loop - much simpler and shorter.

```cpp
int dr[4] = {-1, +1, 0, 0};
int dc[4] = {0, 0, -1, +1};

for (int i=0; i < 4; i++) {
  int nr = cr + dr[i], nc = cc + dc[i];
  if (nr >= 0 && nr < row && nc >= 0 && nc < col)  {
    // do stuff  
  }
}
```

#### Todo
1. Modular arithmetic
