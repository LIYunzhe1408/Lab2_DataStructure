#ifndef TEST_BREAKCYCLE_H
#define TEST_BREAKCYCLE_H
#include"Assistance.h"
#include "AdjListUnDirNetwork.h"
#include <queue>
#include"SeqQueue.h"
template <class ElemType, class WeightType>
class Edge     //带权边类
{
public:
    ElemType vertex1, vertex2;		// 边的顶点
    WeightType weight;				// 边的权值
    Edge(ElemType v1, ElemType v2, WeightType w);	// 构造函数
    Edge(){};	            // 构造函数
    Edge<ElemType, WeightType> &operator =(const Edge<ElemType, WeightType> &Ed); // 赋值语句重载
    bool operator <=(const Edge<ElemType, WeightType> &Ed);		// 重载<=关系运算
    bool operator >(const Edge<ElemType, WeightType> &Ed);		// 重载>关系运算
};

template <class ElemType, class WeightType>
Edge<ElemType, WeightType>::Edge(ElemType v1, ElemType v2, WeightType w)
// 操作结果: 由顶点v1、v2和权w构造边——构造函数
{	// 构造函数
    vertex1 = v1;					// 顶点vertex1
    vertex2 = v2;					// 顶点vertex2
    weight = w;						// 权weight
}

template <class ElemType, class WeightType>
bool Edge<ElemType, WeightType>::operator <= (const Edge<ElemType, WeightType> &Ed)
// 操作结果：重载<=关系运算
{
    return (weight <= Ed.weight);
}

template <class ElemType, class WeightType>
bool Edge<ElemType, WeightType>::operator > (const Edge<ElemType, WeightType> &Ed)
// 操作结果：重载>关系运算
{
    return (weight > Ed.weight);
}


template<class ElemType,  class WeightType>
Edge<ElemType, WeightType> &Edge<ElemType, WeightType>::operator = (const Edge<ElemType, WeightType> &Ed)
// 操作结果：将栈copy赋值给当前栈--赋值语句重载
{
    if (&Ed != this)	{
        vertex1 = Ed.vertex1;					// 顶点vertex1
        vertex2 = Ed.vertex2;					// 顶点vertex2
        weight = Ed.weight;						// 权weight
    }
    return *this;
}
struct Degree     //顶点度数结构体
{
    int d;   //顶点度数
    bool tag;  //标记当前顶点是否被访问过
    int nearvex;  //最小生成树中当前顶点所在边的另一个顶点
};
template <class ElemType, class WeightType>
void MiniSpanTreeBreakCycle(const AdjListUnDirNetwork<ElemType, WeightType> &g)
{
    ElemType v1, v2;
    int vexnum = g.GetVexNum();
    Degree *degree;
    int u, v,k;
    degree=new Degree[vexnum];
    for(v=0;v<vexnum;v++)   //初始化记录结点当前度数的数组
    {
        degree[v].d=g.CountDegree(v);
        degree[v].nearvex=0;
        degree[v].tag=0;
    }
    Edge<ElemType, WeightType> *edge;   //构建边权值从大到小的数组
    Edge<ElemType, WeightType> temp;
    edge=new Edge<ElemType, WeightType>[g.GetArcNum()];
    int edgenum=0;
    bool reach[vexnum][vexnum];  //创建一个可达矩阵
    for (v = 0; v < g.GetVexNum(); v++)
        for (u = g.FirstAdjVex(v); u >= 0; u = g.NextAdjVex(v, u))
            if (v < u)
            {	// 将v < u的边插入数组中
                reach[v][u]=reach[u][v]=1;   //可达矩阵初始化
                g.GetElem(v, v1);
                g.GetElem(u, v2);
                edge[edgenum].vertex1 = v1;
                edge[edgenum].vertex2 = v2;
                edge[edgenum].weight = g.GetWeight(v,u);
                edgenum++;
            }
    for(int i=0;i<edgenum-1;i++)  //对边数组按权值从大到小排序
    {
        for(int j=0;j<edgenum-i-1;j++)
        {
            if(edge[j]<=edge[j+1])
            {
                temp=edge[j];
                edge[j]=edge[j+1];
                edge[j+1]=temp;
            }
        }

    }
    SeqQueue<Edge<ElemType, WeightType>> e;
    for(int i=0;i<edgenum;i++)  //将按权值从大到小排列的边依次加入队列中
    {
        e.EnQueue(edge[i]);
    }
    int count=0;  //初始化计数器，记录已访问过的顶点数
    SeqQueue<int> queue;  //创建一个存放度数为1的顶点的队列
    while(count<vexnum)
    {
        for(v=0;v<vexnum;v++)  //依次查找是否存在度数为1的顶点
        {
            if(degree[v].d==1&&degree[v].tag==0) {
                queue.EnQueue(v);
                degree[v].tag =1;
                k=g.FirstAdjVex(v);
                while(1)  //循环遍历找到与该顶点有边相邻且未被访问过的顶点
                {
                    if((degree[k].tag==0)&&(reach[v][k]==1))
                        break;
                    k=g.NextAdjVex(v,k);
                }
                degree[v].nearvex=k;
                count++;
            }
        }
        while(!queue.IsEmpty())   //对队列中的顶点元素依次出队并访问
        {
            queue.DelQueue(v);
            u=degree[v].nearvex;
            degree[u].d-=1;
            g.GetElem(v,v1);
            g.GetElem(u,v2);
            cout << "边:( " << v1 << ", " << v2<< " ) 权:" << g.GetWeight(v,u) << endl ; // 输出边及权值
            if(degree[u].d==1)  //判断与出队顶点相邻的顶点在度数减1后度数是否等于1
            {
                queue.EnQueue(u);
                degree[u].tag =1;
                count++;
                if(count==vexnum)
                    return;
                k=g.FirstAdjVex(u);
                while(1)  //循环遍历找到与该顶点有边相邻且未被访问过的顶点
                {
                    if((degree[k].tag==0)&&(reach[u][k]==1))
                        break;
                    k=g.NextAdjVex(u,k);
                }
                degree[u].nearvex=k;
            }
        }
        e.DelQueue(temp);  //将权值最大的边出队
        v1 = temp.vertex1;
        v2 = temp.vertex2;
        while((degree[g.GetOrder(v1)].tag==1)&&(degree[g.GetOrder(v2)].tag==1))
        {  //判断该出队的边是否与已被访问过的顶点相连，如果是则再出一条边
            e.DelQueue(temp);
            v1 = temp.vertex1;
            v2 = temp.vertex2;
        }
        degree[g.GetOrder(v1)].d-=1;  //将与该边所连的顶点度数减1
        degree[g.GetOrder(v2)].d-=1;
        reach[g.GetOrder(v1)][g.GetOrder(v2)]=0;  //将与该边所连的顶点在可达矩阵中对应的值置为0
        reach[g.GetOrder(v2)][g.GetOrder(v1)]=0;
    }
}
#endif //TEST_BREAKCYCLE_H
