#include <iostream>
#include <stack>
#define VertexType int
#define MAXVertexNum 100
#define INFINITY 100  // 如果边的权值大于等于该值，称该边无穷长
using namespace std;

template <typename MyElement>
struct LinkNode {
    MyElement t;
    LinkNode *next;
};

template <typename MyElement>
struct LinkQueue {
    LinkNode<MyElement> *font, *rear;
};

template <typename MyElement>
void InitLinkQueue(LinkQueue<MyElement> *Q) {
    // Q = new LinkQueue;
    Q->font = nullptr;
    Q->rear = nullptr;
}

template <typename MyElement>
bool LinkQueueEmpty(const LinkQueue<MyElement> *Q) {
    return Q->font == nullptr;
}

template <typename MyElement>
bool EnLinkQueue(LinkQueue<MyElement> *Q, MyElement t) {
    LinkNode<MyElement> *p = new LinkNode<MyElement>;
    if (p == nullptr) return false;
    p->next = nullptr;
    p->t = t;
    if (LinkQueueEmpty(Q)) {
        Q->font = p;
        Q->rear = p;
    } else {
        Q->rear->next = p;
        Q->rear = p;
    }
    return true;
}

template <typename MyElement>
bool DeLinkQueue(LinkQueue<MyElement> *Q) {
    if (LinkQueueEmpty(Q)) return false;
    LinkNode<MyElement> *p = Q->font;
    Q->font = p->next;
    if (Q->rear == p) {
        Q->font = nullptr;
        Q->rear = nullptr;
    }
    delete p;
    return true;
}

template <typename MyElement>
bool DeLinkQueue(LinkQueue<MyElement> *Q, MyElement &e) {
    if (LinkQueueEmpty(Q)) return false;
    LinkNode<MyElement> *p = Q->font;
    Q->font = p->next;
    e = p->t;
    if (Q->rear == p) {
        Q->font = nullptr;
        Q->rear = nullptr;
    }
    delete p;
    return true;
}

// 邻接矩阵
struct MGraph {
    VertexType Vex[MAXVertexNum];          // 顶点
    int Edge[MAXVertexNum][MAXVertexNum];  // 邻接矩阵
    int vernum;                            // 当期顶点树
    int arcnum;                            // 当前边数/弧数
    bool visited[MAXVertexNum] = {false};
    MGraph() : vernum(0), arcnum(0) {
        for (int i = 0; i < MAXVertexNum; i++) {
            Vex[i] = 0;
            for (int j = 0; j < MAXVertexNum; j++) {
                Edge[i][j] = INFINITY;
            }
        }
    }
};

// 邻接表
typedef struct ArcNode {
    int adjvex;  // 边指向哪一个顶点(下一个) 即AdjList[adjvex]
    ArcNode *next;
    int info;  // 权值
    ArcNode() : adjvex(-1), next(nullptr), info(INFINITY){};
} *ArcList;

typedef struct VNode {
    VertexType data;
    ArcList first;  // 第一条边(随便指一条)
    VNode() : data(0), first(nullptr){};
} AdjList[MAXVertexNum];

struct ALGraph {
    AdjList vertices;  // 邻接表
    int vernum;
    int arcnum;
    bool visited[MAXVertexNum] = {false};
    ALGraph() : vernum(0), arcnum(0){};
};

//
struct AcrossAcrNode {
    int tailvex;  // 弧尾点编号
    int headvex;  // 弧头点编号
    int info;
    AcrossAcrNode *hlink;  // 弧尾相同的下一条弧
    AcrossAcrNode *tlink;  // 弧头相同的下一条弧
};

typedef struct AcrossVNode {
    VertexType data;
    AcrossAcrNode *firstin;   // 以该节点为弧头的第一条弧
    AcrossAcrNode *firstout;  // 以该节点为弧尾的第一条弧
} AVList[MAXVertexNum];

struct AcrossGraph {
    AVList vertices;  // 十字链表
    int vernum;
    int arcnum;
};

bool isExistVertex(const MGraph &G, const int &x) {
    if (x < 0 || x >= G.vernum) {
        return false;
    }
    return G.Edge[x][x] == 0;
}

bool isExistVertex(const ALGraph &G, const int &x) {
    if (x < 0 || x >= G.vernum) {
        return false;
    }
    return true;
}

bool isExistVertex(const AcrossGraph &G, const int &x) {
    if (x < 0 || x >= G.vernum) {
        return false;
    }
    return true;
}

//
// 判断是否存在边<x,y>
//
bool Adjacent(const MGraph &G, const int &x, const int &y) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y)) {
        return false;
    }
    if (x == y) {
        return false;
    }

    return G.Edge[x][y] < INFINITY;
}

bool Adjacent(const ALGraph &G, const int &x, const int &y) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y)) {
        return false;
    }
    if (x == y) {
        return false;
    }

    VNode a = G.vertices[x], b = G.vertices[y];
    ArcList arc = a.first;
    while (arc != nullptr) {
        if (arc->adjvex == y) {
            return arc->info < INFINITY;
        }

        arc = arc->next;
    }

    return false;
}

//
// 判断是否存在边|x->y|
//
bool Adjacent(const AcrossGraph &G, const int &x, const int &y) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y)) {
        return false;
    }
    if (x == y) {
        return false;
    }

    AcrossVNode a = G.vertices[x], b = G.vertices[y];
    auto arc = a.firstout;
    while (arc != nullptr) {
        if (arc->tailvex == y) {
            return arc->info < INFINITY;
        }

        arc = arc->tlink;
    }

    return false;
}

//
// 求图G中顶点x的第一个邻接点，若有则返回顶点号。若x没有邻接点
// 或图中不存在x，则返回-1。
//
int FirstNeighbor(const MGraph &G, const int &x) {
    if (!isExistVertex(G, x)) {
        return -1;
    }

    for (int i = 0; i < G.vernum; i++) {
        if (i == x || !isExistVertex(G, i)) {
            continue;
        }

        if (Adjacent(G, x, i)) {
            return i;
        }
    }

    return -1;
}

int FirstNeighbor(const ALGraph &G, const int &x) {
    if (!isExistVertex(G, x) || G.vertices[x].first == nullptr) {
        return -1;
    }

    return G.vertices[x].first->adjvex;
}

//
// 假设图G中顶点y是顶点x的一个邻接点，返回除y之外顶点x的下一个邻接点的顶点号，若y是x的最后一个邻接点，则返回-1
//
int NextNeighbor(const MGraph &G, const int &x, const int &y) {
    if (!isExistVertex(G, x)) {
        return -1;
    }

    for (int i = y + 1; i < G.vernum; i++) {
        if (i == x || !isExistVertex(G, i)) {
            continue;
        }

        if (Adjacent(G, x, i)) {
            return i;
        }
    }

    return -1;
}

int NextNeighbor(const ALGraph &G, const int &x, const int &y) {
    VNode a = G.vertices[x];
    ArcList arc = a.first;
    while (arc != nullptr) {
        if (arc->adjvex != y) {
            arc = arc->next;
            continue;
        }
        if (arc->next == nullptr) {
            return -1;
        }

        return arc->next->adjvex;
    }
    return -1;
}

bool InsertVertex(MGraph &G, const int &x, const VertexType &value) {
    return false;
}

bool DeleteVertex(MGraph &G, const int &x) { return false; }

bool AddEdge(MGraph &G, const int &x, const int &y) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y) || Adjacent(G, x, y)) {
        return false;
    }

    G.Edge[x][y] = 1;
    G.arcnum++;
    return true;
}

bool AddEdge(ALGraph &G, const int &x, const int &y, int info) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y) || Adjacent(G, x, y)) {
        return false;
    }

    info = (info > INFINITY) ? (INFINITY) : (info);

    // 头插法
    ArcNode *p = new ArcNode;
    p->adjvex = y;
    p->next = G.vertices[x].first;
    p->info = info;
    G.vertices[x].first = p;
    G.arcnum++;
    return true;
}

bool RemoveEdgeAddEdge(MGraph &G, const int &x, const int &y) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y) || !Adjacent(G, x, y)) {
        return false;
    }

    G.Edge[x][y] = INFINITY;
    G.Edge[y][x] = INFINITY;
    G.arcnum--;
    return true;
}

bool RemoveEdgeAddEdge(ALGraph &G, const int &x, const int &y) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y) || !Adjacent(G, x, y)) {
        return false;
    }

    // 暂时不能删除
    return false;
}

int GetEdgeValue(const MGraph &G, const int &x, const int &y) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y)) {
        return INFINITY;
    }

    return G.Edge[x][y];
}

int GetEdgeValue(const ALGraph &G, const int &x, const int &y) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y) || !Adjacent(G, x, y)) {
        return INFINITY;
    }

    VNode a = G.vertices[x];
    ArcList arc = a.first;
    while (arc != nullptr) {
        if (arc->adjvex == y) {
            break;
        }
        arc = arc->next;
    }
    return arc->info;
}

bool SetEdgeValue(MGraph &G, const int &x, const int &y, int value) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y) || !Adjacent(G, x, y)) {
        return false;
    }

    value = (value > INFINITY) ? (INFINITY) : (value);
    G.Edge[x][y] = value;
    return true;
}

bool SetEdgeValue(ALGraph &G, const int &x, const int &y, int info) {
    if (!isExistVertex(G, x) || !isExistVertex(G, y) || !Adjacent(G, x, y)) {
        return false;
    }

    VNode a = G.vertices[x];
    ArcList arc = a.first;
    while (arc != nullptr) {
        if (arc->adjvex == y) {
            break;
        }
        arc = arc->next;
    }
    info = (info > INFINITY) ? (INFINITY) : (info);
    arc->info = info;
    return true;
}

void BFSTraverse(MGraph &G) {
    void BSF(MGraph & G, const int &x, LinkQueue<int> *Q);

    cout << "BFSTraverse" << endl;
    for (int i = 0; i < G.vernum; ++i) {
        G.visited[i] = false;
    }
    LinkQueue<int> *Q = new LinkQueue<int>;
    InitLinkQueue(Q);
    for (int i = 0; i < G.vernum; ++i) {
        if (!G.visited[i]) {
            BSF(G, i, Q);
            cout << endl;
        }
    }
    delete Q;
}

void BFSTraverse(ALGraph &G) {
    void BSF(ALGraph & G, const int &x, LinkQueue<int> *Q);

    cout << "BFSTraverse" << endl;
    for (auto &&i : G.visited) {
        i = false;
    }
    LinkQueue<int> *Q = new LinkQueue<int>;
    InitLinkQueue(Q);
    for (int i = 0; i < G.vernum; ++i) {
        if (!G.visited[i]) {
            BSF(G, i, Q);
            cout << endl;
        }
    }
    delete Q;
}

void BSF(MGraph &G, const int &x, LinkQueue<int> *Q) {
    void visit(const MGraph &G, const int &x);
    visit(G, x);
    G.visited[x] = true;
    EnLinkQueue(Q, x);  // x入队
    while (!LinkQueueEmpty(Q)) {
        DeLinkQueue(Q);
        for (auto w = FirstNeighbor(G, x); w >= 0; w = NextNeighbor(G, x, w)) {
            if (G.visited[w]) {
                continue;
            }
            visit(G, w);
            G.visited[w] = true;
            EnLinkQueue(Q, w);
        }
    }
}

void BSF(ALGraph &G, const int &x, LinkQueue<int> *Q) {
    void visit(const ALGraph &G, const int &x);
    visit(G, x);
    G.visited[x] = true;
    EnLinkQueue(Q, x);  // x入队
    while (!LinkQueueEmpty(Q)) {
        DeLinkQueue(Q);
        for (auto w = FirstNeighbor(G, x); w >= 0; w = NextNeighbor(G, x, w)) {
            if (G.visited[w]) {
                continue;
            }
            visit(G, w);
            G.visited[w] = true;
            EnLinkQueue(Q, w);
        }
    }
}

void visit(const MGraph &G, const int &x) { cout << G.Vex[x]; }

void visit(const ALGraph &G, const int &x) { cout << G.vertices[x].data; }

//
// Prim最小生成树
//
template <typename MyGraph>
int Prim(const MyGraph &G) {
    int result = 0, vernum = G.vernum;
    if (vernum <= 0) {
        return result;
    }

    bool *isJoin = new bool[vernum];
    int *lowCost = new int[vernum], *vers = new int[vernum];
    for (int i = 0; i < vernum; i++) {
        isJoin[i] = false;
        lowCost[i] = INFINITY;
        vers[i] = -1;
    }
    isJoin[0] = true, lowCost[0] = 0, vers[0] = 0;
    int len = 1;
    while (true) {
        // 更新lowCost数组
        for (int i = 0; i < vernum; i++) {
            if (isJoin[i]) {
                continue;
            }

            for (int j = 0; j < len; j++) {
                int info = GetEdgeValue(G, vers[j], i);
                lowCost[i] = min(lowCost[i], info);
            }
        }
        // 选择最新的lowCost加入点集
        int min = INFINITY, minIndex = -1;
        for (int i = 0; i < vernum; i++) {
            if (isJoin[i] || min <= lowCost[i]) {
                continue;
            }

            minIndex = i;
            min = lowCost[i];
        }
        if (minIndex != -1) {
            vers[len] = minIndex;
            len++;
            isJoin[minIndex] = true;
            continue;
        }

        for (int i = 0; i < len; i++) {
            result += lowCost[vers[i]];
        }
        break;
    }

    cout << "prim ans: ";
    for (int i = 0; i < len; i++) {
        cout << lowCost[i] << "\t";
    }
    cout << endl;
    delete[] lowCost;
    delete[] vers;
    delete[] isJoin;
    return result;
}

template <typename MyGraph>
int Kruskal(const MyGraph &G) {
    return 0;
}

//
// Dijkstra寻找有向图最短路径
//
template <typename MyGraph>
void DJL(const MyGraph &G, const int &x) {
    int vernum = G.vernum;
    // dist[i] 由点x到点i的最近距离
    // path[i] 由点path[i]是离点i最近的点
    int *dist = new int[vernum], *path = new int[vernum];
    bool *found = new bool[vernum];

    dist[x] = 0, path[x] = -1, found[x] = true;
    // 初始化赋值
    for (int i = 0; i < vernum; i++) {
        if (i == x) {
            continue;
        }
        dist[i] = GetEdgeValue(G, x, i);
        found[i] = false;
        if (dist[i] < INFINITY) {
            path[i] = x;
        } else {
            path[i] = -1;
        }
    }
    // 寻找不在关于x的生成树的生成子图的点， 选择与x相距最近的点
    for (int i = 0; i < vernum; i++) {
        if (found[i]) {
            continue;
        }
        int minDist = INFINITY, minIndex = x;
        for (int j = 0; j < vernum; j++) {
            if (found[j]) {
                continue;
            }
            if (minDist > dist[j]) {
                minDist = dist[j];
                minIndex = j;
            }
        }
        // 将寻找到的点加入生成子图中，并且更新不在生成子图中的点i的dist[i]
        found[minIndex] = true;
        for (int j = 0; j < vernum; j++) {
            if (found[j]) {
                continue;
            }
            if (minDist + GetEdgeValue(G, minIndex, j) >= dist[j]) {
                continue;
            }

            dist[j] = minDist + GetEdgeValue(G, minIndex, j);
            path[j] = minIndex;
        }
    }
    cout << "Dijkstra ans: " << endl;
    for (int i = 0; i < vernum; i++) {
        cout << x << "->" << i << " distance: " << dist[i] << "\t";
        int p = path[i];
        cout << "path: " << i;
        while (p != -1) {
            cout << "<-" << p;
            if (p < 0) {
                break;
            }

            p = path[p];
        }
        cout << endl;
    }
    delete[] found, dist, path;
}

//
// Floyd寻找有向图最短路径
//
template <typename MyGraph>
void Floyd(const MyGraph &G) {
    int vernum = G.vernum;
    int **dp = new int *[vernum], **path = new int *[vernum];
    for (int i = 0; i < vernum; i++) {
        dp[i] = new int[vernum];
        path[i] = new int[vernum];
        for (int j = 0; j < vernum; j++) {
            if (i == j) {
                dp[i][j] = 0;
                path[i][j] = -1;
                continue;
            }
            dp[i][j] = GetEdgeValue(G, i, j);
            if (dp[i][j] < INFINITY) {
                path[i][j] = i;
            } else {
                path[i][j] = -1;
            }
        }
    }
    for (int i = 0; i < vernum; i++) {
        for (int j = 0; j < vernum; j++) {
            for (int k = 0; k < vernum; k++) {
                if (dp[i][j] > (dp[i][k] + dp[k][j])) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    cout << "Floyd ans point0 : " << endl;
    for (int i = 0; i < vernum; i++) {
        cout << 0 << "->" << i << " distance: " << dp[0][i] << "\t";
        int p = path[0][i];
        cout << "path: " << i;
        while (p != -1) {
            cout << "<-" << p;
            if (p < 0) {
                break;
            }

            p = path[0][p];
        }
        cout << endl;
    }
}

//
// 获得有向图G点x的入度
//
template <typename MyOrientedGraph>
int GetInDegree(const MyOrientedGraph &G, const int &x) {
    if (!isExistVertex(G, x)) {
        return 0;
    }

    int inDegree = 0;
    for (int i = 0; i < G.vernum; i++) {
        if (!Adjacent(G, i, x)) {
            continue;
        }
        inDegree++;
    }

    return inDegree;
}

//
// 获得有向图G所有点的入度
//
template <typename MyOrientedGraph>
int *GetInDegree(const MyOrientedGraph &G) {
    int vernum = G.vernum;
    int *inDegree = new int[vernum];
    for (int i = 0; i < vernum; i++) {
        inDegree[i] = 0;
    }

    for (int i = 0; i < vernum; i++) {
        for (auto w = FirstNeighbor(G, i); w >= 0; w = NextNeighbor(G, i, w)) {
            inDegree[w]++;
        }
    }

    return inDegree;
}

//
// 获得有向图G所有点的出度
//
template <typename MyOrientedGraph>
int *GetOutDegree(const MyOrientedGraph &G) {
    int vernum = G.vernum;
    int *outDegree = new int[vernum];
    for (int i = 0; i < vernum; i++) {
        outDegree[i] = 0;
    }

    for (int i = 0; i < vernum; i++) {
        for (auto w = FirstNeighbor(G, i); w >= 0; w = NextNeighbor(G, i, w)) {
            outDegree[i]++;
        }
    }

    return outDegree;
}

//
// 拓扑排序
//
template <typename MyOrientedGraph>
bool TopologicalSort(const MyOrientedGraph &G) {
    int vernum = G.vernum, count = 0;
    int *inDegree = GetInDegree(G);

    LinkQueue<int> *Q = new LinkQueue<int>;
    InitLinkQueue(Q);
    for (int i = 0; i < vernum; i++) {
        if (inDegree[i]) {
            continue;
        }

        EnLinkQueue(Q, i);
    }

    cout << "TopologicalSort:";
    while (!LinkQueueEmpty(Q)) {
        int k;
        DeLinkQueue(Q, k);
        count++;
        cout << k << "\t";
        for (auto w = FirstNeighbor(G, k); w >= 0; w = NextNeighbor(G, k, w)) {
            inDegree[w]--;
            if (!inDegree[w]) {
                EnLinkQueue(Q, w);
            }
        }
    }

    delete[] inDegree;
    return count == vernum;
}

//
// 逆拓扑排序
//
template <typename MyOrientedGraph>
bool InverseTopologicalSort(const MyOrientedGraph &G) {
    int vernum = G.vernum, count = 0;
    int *outDegree = GetOutDegree(G);

    LinkQueue<int> *Q = new LinkQueue<int>;
    InitLinkQueue(Q);

    for (int i = 0; i < vernum; i++) {
        if (outDegree[i]) {
            continue;
        }
        EnLinkQueue(Q, i);
    }

    cout << "InverseTopologicalSort:";
    while (!LinkQueueEmpty(Q)) {
        int k;
        DeLinkQueue(Q, k);
        count++;
        cout << k << "\t";
        for (int i = 0; i < vernum; i++) {
            for (auto w = FirstNeighbor(G, i); w >= 0;
                 w = NextNeighbor(G, i, w)) {
                if (w != k) {
                    continue;
                }
                outDegree[i]--;
                if (!outDegree[i]) {
                    EnLinkQueue(Q, i);
                }
            }
        }
    }

    delete[] outDegree;
    return count == vernum;
}

template <typename MyOrientedGraph>
void topoDFS(MyOrientedGraph &G, const int &x, int &count) {
    for (auto w = FirstNeighbor(G, x); w >= 0; w = NextNeighbor(G, x, w)) {
        if (G.visited[w]) {
            continue;
        }

        topoDFS(G, w, count);
    }

    G.visited[x] = true;
    cout << x << '\t';
    count++;
}

//
// 逆拓扑排序DFS实现
//
template <typename MyOrientedGraph>
bool InverseTopologicalSortByDFS(MyOrientedGraph &G) {
    for (int i = 0; i < G.vernum; ++i) {
        G.visited[i] = false;
    }
    int count = 0;

    cout << "InverseTopologicalSortByDFS:";
    for (int i = 0; i < G.vernum; i++) {
        if (G.visited[i]) {
            continue;
        }

        topoDFS(G, i, count);
    }
    return count == G.vernum;
}

//
// 拓扑排序
// T为逆拓扑排序
//
template <typename MyOrientedGraph>
bool TopologicalSort(const MyOrientedGraph &G, stack<int> &T) {
    int vernum = G.vernum, count = 0;
    int *inDegree = GetInDegree(G);
    for (int i = 0; i < vernum; i++) {
        inDegree[i] = GetInDegree(G, i);
    }

    stack<int> S;
    for (int i = 0; i < vernum; i++) {
        if (inDegree[i]) {
            continue;
        }

        S.push(i);
    }

    cout << "TopologicalSort: ";
    while (!S.empty()) {
        int k = S.top();
        S.pop();
        T.push(k);
        count++;
        cout << k << "->";
        for (auto w = FirstNeighbor(G, k); w >= 0; w = NextNeighbor(G, k, w)) {
            inDegree[w]--;
            if (!inDegree[w]) {
                S.push(w);
            }
        }
    }

    cout << endl << "Inverse: ";
    while (!T.empty()) {
        int k = T.top();
        T.pop();
        cout << k << "->";
    }
    delete[] inDegree;
    return count == vernum;
}

//
// AOE网关键路径
//
template <typename MyOrientedGraph>
void CriticalPath(const MyOrientedGraph &G) {
    if (!TopologicalSort(G)) {
        return;
    }
    cout << endl;
    // start: AOE网的起点 end: AOE网的终点
    int vernum = G.vernum, start = -1, end = -1;
    // verE[i]: 事件点i的最早开始时间 verL[i]: 事件点i的最晚开始时间
    // inDegree[i]: 事件点i的入度
    int *verE = new int[vernum], *verL = new int[vernum],
        *inDegree = GetInDegree(G);
    stack<int> topo, reverseTopo;
    for (int i = 0; i < vernum; i++) {
        verE[i] = 0;
        verL[i] = INT_MAX;
    }
    // 寻找起点 入度为0的点
    for (int i = 0; i < vernum; i++) {
        if (inDegree[i]) {
            continue;
        }

        topo.push(i);
        start = i;
        verE[i] = 0;  // AOE网的起点的最早开始时间为0
        break;
    }
    // 获得拓扑排序和逆拓扑排序 以正拓扑排序获得verE
    while (!topo.empty()) {
        int k = topo.top();
        topo.pop();
        reverseTopo.push(k);
        // 更新以事件点k为起点的所有活动的终点的verE的值
        for (auto w = FirstNeighbor(G, k); w >= 0; w = NextNeighbor(G, k, w)) {
            // 对有向边i->j verE[j] = max{verE[i] + GetEdgeValue(G, i, j)}
            // i in [Adjacent(G, i, j) == true]
            if (GetEdgeValue(G, k, w) + verE[k] > verE[w]) {
                verE[w] = GetEdgeValue(G, k, w) + verE[k];
            }
            inDegree[w]--;
            if (!inDegree[w]) {
                topo.push(w);
            }
        }
    }

    end = reverseTopo.top();
    verL[end] = verE[end];  // 终点的最晚开始时间等于最早开始时间
    // 逆拓扑排序获得verL
    while (!reverseTopo.empty()) {
        int k = reverseTopo.top();
        reverseTopo.pop();
        for (int i = 0; i < vernum; i++) {
            for (auto w = FirstNeighbor(G, i); w >= 0;
                 w = NextNeighbor(G, i, w)) {
                if (w != k) {
                    continue;
                }
                // 对有向边i->j verL[i] = min{verL[j] - GetEdgeValue(G, i, j)}
                // i in [Adjacent(G, i, j) == true]
                if (verL[k] - GetEdgeValue(G, i, k) < verL[i]) {
                    verL[i] = verL[k] - GetEdgeValue(G, i, k);
                }
                break;
            }
        }
    }

    cout << "CriticalPath: ";
    int w = start;
    cout << w << "->";
    while (w >= 0) {
        for (int i = FirstNeighbor(G, w); i >= 0; i = NextNeighbor(G, w, i)) {
            if (verE[w] == verL[i] - GetEdgeValue(G, w, i)) {
                w = i;
                cout << w << "->";
                break;
            }
        }
        if (w == end) {
            break;
        }
    }
    delete[] verE, verL, inDegree;
}

void CreateTestMGraph(MGraph &G) {
    // 6 6 11 22 33 44 55 66 0 1 6 0 2 3 0 3 9 2 4 7 2 3 4 3 5 8
    // int verNum, edgeNum;
    // cout << "Ipnut VerTex Number: " << endl;
    // cin >> verNum;
    // cout << "Ipnut Edge Number: " << endl;
    // cin >> edgeNum;
    // cout << "Ipnut VerTex Info: " << endl;
    // for (int i = 0; i < verNum; i++) {
    //     cin >> G.Vex[i];
    //     G.Edge[i][i] = 0;
    // }
    // G.vernum = verNum;
    // cout << "Ipnut Edge Info. x y" << endl;
    // for (; G.arcnum < edgeNum;) {
    //     int x, y, weigth;
    //     cin >> x >> y >> weigth;
    //     AddEdge(G, x, y);
    // }

    int ver[7] = {0, 1, 2, 3, 4, 5, 6};
    int edge1[11] = {0, 0, 1, 1, 1, 2, 3, 3, 4, 4, 5};
    int edge2[11] = {1, 3, 3, 2, 4, 4, 4, 5, 5, 6, 6};
    int info[11] = {7, 5, 9, 8, 7, 5, 15, 6, 8, 9, 11};
    for (int i = 0; i < 7; i++) {
        G.Edge[i][i] = 0;
        G.Vex[i] = i;
    }
    G.vernum = 7;
    // 无向图
    for (int i = 0; i < 11; i++) {
        AddEdge(G, edge1[i], edge2[i]);
        AddEdge(G, edge2[i], edge1[i]);
        G.arcnum--;
        SetEdgeValue(G, edge1[i], edge2[i], info[i]);
        SetEdgeValue(G, edge2[i], edge1[i], info[i]);
    }
}

//
// 创建无向图
//
void CreateTestALGraph01(ALGraph &G) {
    int ver[7] = {0, 1, 2, 3, 4, 5, 6};
    int edge1[11] = {0, 0, 1, 1, 1, 2, 3, 3, 4, 4, 5};
    int edge2[11] = {1, 3, 3, 2, 4, 4, 4, 5, 5, 6, 6};
    int info[11] = {7, 5, 9, 8, 7, 5, 15, 6, 8, 9, 11};
    for (int i = 0; i < 7; i++) {
        G.vertices[i].data = i;
    }
    G.vernum = 7;
    // 无向图
    for (int i = 0; i < 11; i++) {
        AddEdge(G, edge1[i], edge2[i], info[i]);
        AddEdge(G, edge2[i], edge1[i], info[i]);
        G.arcnum--;
    }
}

//
// 创建AOV网
//
void CreateTestALGraph02(ALGraph &G) {
    bool AddEdge(ALGraph & G, const int &x, const int &y, int info);

    int ver[7] = {0, 1, 2, 3, 4, 5, 6};
    int edge1[7] = {0, 1, 2, 3, 4, 4, 5};
    int edge2[7] = {6, 0, 1, 5, 1, 3, 0};
    int info[7] = {1, 1, 1, 1, 1, 1, 1};
    for (int i = 0; i < 7; i++) {
        G.vertices[i].data = i;
    }
    G.vernum = 7;
    for (int i = 0; i < 7; i++) {
        AddEdge(G, edge1[i], edge2[i], info[i]);
    }
}

//
// 创建AOE网
//
void CreateTestALGraph03(ALGraph &G) {
    bool AddEdge(ALGraph & G, const int &x, const int &y, int info);

    int ver[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int edge1[] = {0, 0, 0, 0, 0, 0, 1, 2, 3, 3,  3,  4,
                   4, 5, 5, 6, 7, 8, 8, 8, 9, 10, 11, 11};
    int edge2[] = {1, 2, 3,  4, 5, 6, 7,  7,  7,  9,  11, 8,
                   9, 8, 12, 8, 9, 7, 10, 11, 12, 11, 9,  12};
    int info[] = {1,  6,  3,  4, 3, 1, 6, 2, 7,  8, 6, 5,
                  11, 10, 21, 6, 8, 4, 9, 4, 10, 9, 3, 12};
    for (int i = 0; i < 13; i++) {
        G.vertices[i].data = i;
    }
    G.vernum = 13;
    for (int i = 0; i < 24; i++) {
        AddEdge(G, edge1[i], edge2[i], info[i]);
    }
    for (int i = 0; i < 24; i++) {
        cout << edge1[i] + 1 << '\t';
    }
    cout << endl;
    for (int i = 0; i < 24; i++) {
        cout << edge2[i] + 1 << '\t';
    }
    cout << endl;
    for (int i = 0; i < 24; i++) {
        cout << info[i] << '\t';
    }
    cout << endl;
    cout << endl;
}

//
// 邻接矩阵表示无向图的测试
//
void testMGraph() {
    cout << "MGraph" << endl;
    MGraph MG;
    CreateTestMGraph(MG);
    for (int i = 0; i < MG.vernum; i++) {
        for (int j = 0; j < MG.vernum; j++) {
            cout << MG.Edge[i][j] << "\t";
        }
        cout << endl;
    }

    BFSTraverse(MG);
    cout << Prim(MG) << endl;
    DJL(MG, 0);
    Floyd(MG);
}

//
// 邻接表表示无向图的测试
//
void testALGraph01() {
    cout << "ALGraph" << endl;
    ALGraph AG;
    CreateTestALGraph01(AG);
    for (int i = 0; i < AG.vernum; i++) {
        int vex = i;
        cout << AG.vertices[vex].data << "\t";
        ArcList p = AG.vertices[i].first;
        while (p != nullptr) {
            vex = p->adjvex;
            cout << AG.vertices[vex].data << "\t";
            p = p->next;
        }
        cout << endl;
    }
    BFSTraverse(AG);
    cout << Prim(AG) << endl;
    DJL(AG, 0);
    Floyd(AG);
}

//
// 邻接表表示AOV网测试
//
void testALGraph02() {
    cout << "ALGraph AOV" << endl;
    ALGraph AG;
    CreateTestALGraph02(AG);
    for (int i = 0; i < AG.vernum; i++) {
        int vex = i;
        cout << AG.vertices[vex].data << "\t";
        ArcList p = AG.vertices[i].first;
        while (p != nullptr) {
            vex = p->adjvex;
            cout << AG.vertices[vex].data << "\t";
            p = p->next;
        }
        cout << endl;
    }
    BFSTraverse(AG);
    auto canTopo = TopologicalSort(AG);
    cout << endl << "canTopo " << canTopo << endl;
    canTopo = InverseTopologicalSort(AG);
    cout << endl << "canTopo " << canTopo << endl;
    canTopo = InverseTopologicalSortByDFS(AG);
    cout << endl << "canTopo " << canTopo << endl;
    stack<int> t;
    canTopo = TopologicalSort(AG, t);
    cout << endl << "canTopo " << canTopo << endl;
    // CriticalPath();
}

//
// 邻接表表示AOE网测试
//
void testALGraph03() {
    cout << "ALGraph AOE" << endl;
    ALGraph AG;
    CreateTestALGraph03(AG);
    for (int i = 0; i < AG.vernum; i++) {
        int vex = i;
        cout << AG.vertices[vex].data << "\t";
        ArcList p = AG.vertices[i].first;
        while (p != nullptr) {
            vex = p->adjvex;
            cout << AG.vertices[vex].data << "\t";
            p = p->next;
        }
        cout << endl;
    }
    BFSTraverse(AG);
    auto canTopo = TopologicalSort(AG);
    cout << endl << "canTopo " << canTopo << endl;
    canTopo = InverseTopologicalSort(AG);
    cout << endl << "canTopo " << canTopo << endl;
    canTopo = InverseTopologicalSortByDFS(AG);
    cout << endl << "canTopo " << canTopo << endl;
    stack<int> t;
    canTopo = TopologicalSort(AG, t);
    cout << endl << "canTopo " << canTopo << endl;
    CriticalPath(AG);
}

int main() {
    testMGraph();
    testALGraph01();
    testALGraph02();
    testALGraph03();

    return 0;
}