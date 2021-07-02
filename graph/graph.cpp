#include <iostream>
#include <typeinfo>
using namespace std;

#define VertexType int
#define MAXVertexNum 100
#define INFINITY 100 //如果边的权值大于等于该值，称该边无穷长
struct MGraph
{
    VertexType Vex[MAXVertexNum];         //顶点
    int Edge[MAXVertexNum][MAXVertexNum]; //邻接矩阵
    int vexnum;                           //当期顶点树
    int arcnum;                           //当前边数/弧数
};

//
typedef struct ArcNode
{
    int adjvex; //边指向哪一个顶点(下一个) 即AdjList[adjvex]
    ArcNode *next;
    int info; //权值
} ArcList;

typedef struct VNode
{
    VertexType data;
    ArcList first; //第一条边(随便指一条)
} AdjList[MAXVertexNum];

struct ALGraph
{
    AdjList vertices; //邻接表
    int vernum;
    int arcnum;
};

//
struct AcrossAcrNode
{
    int tailvex; //弧尾点编号
    int headvex; //弧头点编号
    int info;
    AcrossAcrNode *hlink; //弧尾相同的下一条弧
    AcrossAcrNode *tlink; //弧头相同的下一条弧
};

typedef struct AcrossVNode
{
    VertexType data;
    AcrossAcrNode *firstin;  //以该节点为弧头的第一条弧
    AcrossAcrNode *firstout; //以该节点为弧尾的第一条弧
} AVList[MAXVertexNum];

struct AcrossGraph
{
    AVList vertices; //十字链表
    int vernum;
    int arcnum;
};

template <typename Graph, typename Vertex>
bool Adjacent(const Graph &G, const Vertex &x, const Vertex &y);
int main()
{
    MGraph MG = {{0}, {0}, 0, 0};
    Adjacent(MG, 1, 2);
    ALGraph AG;
    return 0;
}

template <typename Graph, typename Vertex>
bool Adjacent(const Graph &G, const Vertex &x, const Vertex &y)
{
    MGraph MG;
    cout << (typeid(G).name() == typeid(MG).name());
    return true;
}

void BFSTraverse(G)
{
    for (int i = 0; i<G.vexnum; ++i>)
    {
        G.visited[i] = false;
    }
    InitQueue(Q);
    for (int i = 0; i<G.vexnum; ++i>)
    {
        if (!G.visited[i])
        {
            BSF(G, i);
        }
    }
}

void BSF(G, x)
{
    visit(G, x);
    G.visited[x] = true;
    Enqueue(Q, x); //x入队
    while (!isEmpty(Q))
    {
        DeQueue(Q, x, e); //e可有可无
        for (w = FirstNeighbor(G, x); w >= 0; w = NextNeighbor(G, v, w))
        {
            if (G.visited[w])
            {
                continue;
            }
            visit(w);
            G.visit[w] = true;
            EnQueue(Q, w)
        }
    }
}