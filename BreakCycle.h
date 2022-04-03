#ifndef TEST_BREAKCYCLE_H
#define TEST_BREAKCYCLE_H
#include"Assistance.h"
#include "AdjListUnDirNetwork.h"
#include <queue>
#include"SeqQueue.h"
template <class ElemType, class WeightType>
class Edge     //��Ȩ����
{
public:
    ElemType vertex1, vertex2;		// �ߵĶ���
    WeightType weight;				// �ߵ�Ȩֵ
    Edge(ElemType v1, ElemType v2, WeightType w);	// ���캯��
    Edge(){};	            // ���캯��
    Edge<ElemType, WeightType> &operator =(const Edge<ElemType, WeightType> &Ed); // ��ֵ�������
    bool operator <=(const Edge<ElemType, WeightType> &Ed);		// ����<=��ϵ����
    bool operator >(const Edge<ElemType, WeightType> &Ed);		// ����>��ϵ����
};

template <class ElemType, class WeightType>
Edge<ElemType, WeightType>::Edge(ElemType v1, ElemType v2, WeightType w)
// �������: �ɶ���v1��v2��Ȩw����ߡ������캯��
{	// ���캯��
    vertex1 = v1;					// ����vertex1
    vertex2 = v2;					// ����vertex2
    weight = w;						// Ȩweight
}

template <class ElemType, class WeightType>
bool Edge<ElemType, WeightType>::operator <= (const Edge<ElemType, WeightType> &Ed)
// �������������<=��ϵ����
{
    return (weight <= Ed.weight);
}

template <class ElemType, class WeightType>
bool Edge<ElemType, WeightType>::operator > (const Edge<ElemType, WeightType> &Ed)
// �������������>��ϵ����
{
    return (weight > Ed.weight);
}


template<class ElemType,  class WeightType>
Edge<ElemType, WeightType> &Edge<ElemType, WeightType>::operator = (const Edge<ElemType, WeightType> &Ed)
// �����������ջcopy��ֵ����ǰջ--��ֵ�������
{
    if (&Ed != this)	{
        vertex1 = Ed.vertex1;					// ����vertex1
        vertex2 = Ed.vertex2;					// ����vertex2
        weight = Ed.weight;						// Ȩweight
    }
    return *this;
}
struct Degree     //��������ṹ��
{
    int d;   //�������
    bool tag;  //��ǵ�ǰ�����Ƿ񱻷��ʹ�
    int nearvex;  //��С�������е�ǰ�������ڱߵ���һ������
};
template <class ElemType, class WeightType>
void MiniSpanTreeBreakCycle(const AdjListUnDirNetwork<ElemType, WeightType> &g)
{
    ElemType v1, v2;
    int vexnum = g.GetVexNum();
    Degree *degree;
    int u, v,k;
    degree=new Degree[vexnum];
    for(v=0;v<vexnum;v++)   //��ʼ����¼��㵱ǰ����������
    {
        degree[v].d=g.CountDegree(v);
        degree[v].nearvex=0;
        degree[v].tag=0;
    }
    Edge<ElemType, WeightType> *edge;   //������Ȩֵ�Ӵ�С������
    Edge<ElemType, WeightType> temp;
    edge=new Edge<ElemType, WeightType>[g.GetArcNum()];
    int edgenum=0;
    bool reach[vexnum][vexnum];  //����һ���ɴ����
    for (v = 0; v < g.GetVexNum(); v++)
        for (u = g.FirstAdjVex(v); u >= 0; u = g.NextAdjVex(v, u))
            if (v < u)
            {	// ��v < u�ı߲���������
                reach[v][u]=reach[u][v]=1;   //�ɴ�����ʼ��
                g.GetElem(v, v1);
                g.GetElem(u, v2);
                edge[edgenum].vertex1 = v1;
                edge[edgenum].vertex2 = v2;
                edge[edgenum].weight = g.GetWeight(v,u);
                edgenum++;
            }
    for(int i=0;i<edgenum-1;i++)  //�Ա����鰴Ȩֵ�Ӵ�С����
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
    for(int i=0;i<edgenum;i++)  //����Ȩֵ�Ӵ�С���еı����μ��������
    {
        e.EnQueue(edge[i]);
    }
    int count=0;  //��ʼ������������¼�ѷ��ʹ��Ķ�����
    SeqQueue<int> queue;  //����һ����Ŷ���Ϊ1�Ķ���Ķ���
    while(count<vexnum)
    {
        for(v=0;v<vexnum;v++)  //���β����Ƿ���ڶ���Ϊ1�Ķ���
        {
            if(degree[v].d==1&&degree[v].tag==0) {
                queue.EnQueue(v);
                degree[v].tag =1;
                k=g.FirstAdjVex(v);
                while(1)  //ѭ�������ҵ���ö����б�������δ�����ʹ��Ķ���
                {
                    if((degree[k].tag==0)&&(reach[v][k]==1))
                        break;
                    k=g.NextAdjVex(v,k);
                }
                degree[v].nearvex=k;
                count++;
            }
        }
        while(!queue.IsEmpty())   //�Զ����еĶ���Ԫ�����γ��Ӳ�����
        {
            queue.DelQueue(v);
            u=degree[v].nearvex;
            degree[u].d-=1;
            g.GetElem(v,v1);
            g.GetElem(u,v2);
            cout << "��:( " << v1 << ", " << v2<< " ) Ȩ:" << g.GetWeight(v,u) << endl ; // ����߼�Ȩֵ
            if(degree[u].d==1)  //�ж�����Ӷ������ڵĶ����ڶ�����1������Ƿ����1
            {
                queue.EnQueue(u);
                degree[u].tag =1;
                count++;
                if(count==vexnum)
                    return;
                k=g.FirstAdjVex(u);
                while(1)  //ѭ�������ҵ���ö����б�������δ�����ʹ��Ķ���
                {
                    if((degree[k].tag==0)&&(reach[u][k]==1))
                        break;
                    k=g.NextAdjVex(u,k);
                }
                degree[u].nearvex=k;
            }
        }
        e.DelQueue(temp);  //��Ȩֵ���ı߳���
        v1 = temp.vertex1;
        v2 = temp.vertex2;
        while((degree[g.GetOrder(v1)].tag==1)&&(degree[g.GetOrder(v2)].tag==1))
        {  //�жϸó��ӵı��Ƿ����ѱ����ʹ��Ķ�����������������ٳ�һ����
            e.DelQueue(temp);
            v1 = temp.vertex1;
            v2 = temp.vertex2;
        }
        degree[g.GetOrder(v1)].d-=1;  //����ñ������Ķ��������1
        degree[g.GetOrder(v2)].d-=1;
        reach[g.GetOrder(v1)][g.GetOrder(v2)]=0;  //����ñ������Ķ����ڿɴ�����ж�Ӧ��ֵ��Ϊ0
        reach[g.GetOrder(v2)][g.GetOrder(v1)]=0;
    }
}
#endif //TEST_BREAKCYCLE_H
