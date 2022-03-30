#ifndef __ADJ_LIST_GRAPH_H__
#define __ADJ_LIST_GRAPH_H__

#include "AdjListUnDirNetworkArc.h"			// �����ڽӱ�ı߽����
#include "AdjListUnDirNetworkVex.h"            // �����ڽӱ�Ķ�������

// ���������ڽӱ���
template <class ElemType, class WeightType>
class AdjListUnDirNetwork
{
protected:
// �ڽӱ�����ݳ�Ա:
	int vexNum, vexMaxNum, arcNum;					// ������Ŀ������Ķ��������Ŀ�ͱ���
	AdjListNetWorkVex<ElemType, WeightType> *vexTable;	// �����
	mutable Status *tag;					        // ��־����				
	WeightType infinity;							// ������ֵ 

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	AdjListUnDirNetwork(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// ������es[]Ϊ��������,�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,
        // infinit��ʾ�����,����Ϊ0������������
	AdjListUnDirNetwork(int vertexMaxNum = DEFAULT_SIZE,
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// ��������Ķ��������ĿΪvertexMaxNum,infinit��ʾ�����,����Ϊ0��������
	~AdjListUnDirNetwork();						 // ��������
	void Clear();			                     // ���������
	bool IsEmpty();                              // �ж��������Ƿ�Ϊ��
	int GetOrder(ElemType &d) const;             // �󶥵�����	
	Status GetElem(int v, ElemType &d) const;    // �󶥵��Ԫ��ֵ	
	Status SetElem(int v, const ElemType &d);    // ���ö����Ԫ��ֵ
	WeightType GetInfinity() const;				 // ȡ������ֵ			 
	int GetVexNum() const;						 // ���������Ķ������
	int GetArcNum() const;						 // ���������ı�������
	int FirstAdjVex(int v) const;				 // ���������ж���v�ĵ�һ���ڽӵ�
	int NextAdjVex(int v1, int v2) const;		 // ���������ж���v1�������v2����һ���ڽӵ�
	void InsertVex(const ElemType &d);			 // ����Ԫ��ֵΪd�Ķ���		 
	void InsertArc(int v1, int v2, WeightType w);// ����Ӷ���Ϊv1��v2��ȨΪw�ı�			 
	void DeleteVex(const ElemType &d);			 // ɾ��Ԫ��ֵΪd�Ķ���			 
	void DeleteArc(int v1, int v2);			     // ɾ���Ӷ���Ϊv1��v2�ı�			 
	WeightType GetWeight(int v1, int v2) const;	 // ��Ӷ���Ϊv1��v2�ıߵ�Ȩֵ
	void SetWeight(int v1, int v2, WeightType w);// ���ôӶ���Ϊv1��v2�ıߵ�Ȩֵ
	Status GetTag(int v) const;				     // �󶥵�v�ı�־		 
	void SetTag(int v, Status tag) const;	     // ���ö���v�ı�־Ϊtag


	// TODO
	int CountDegree(int v) const;
	int ConnectedComponent() const;
	void Prim();     // ��������
	void Kruskal();  // ��������
	void BreakCycle(); // ��Ȧ
	bool hasUniqueMinTree();

	AdjListUnDirNetwork(const AdjListUnDirNetwork<ElemType, WeightType> &copy);	// ���ƹ��캯��
	AdjListUnDirNetwork<ElemType, WeightType> &operator =
		(const AdjListUnDirNetwork<ElemType, WeightType> &copy); // ���ظ�ֵ�����
    void Display();	// ��ʾ�������ڽӱ�
};

// ���������ڽӱ����ʵ�ֲ���
template <class ElemType, class WeightType>
AdjListUnDirNetwork<ElemType, WeightType>::AdjListUnDirNetwork(ElemType es[],
       int vertexNum, int vertexMaxNum, WeightType infinit)
// ������������춥������Ϊes[],������ΪnumVex,�������ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
{
	if (vertexMaxNum < 0)
    	throw Error("����Ķ��������Ŀ����Ϊ��!");        // �׳��쳣

	if (vertexMaxNum < vertexNum)
    	throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!");// �׳��쳣

	vexNum = vertexNum;			
	vexMaxNum = vertexMaxNum; 
	arcNum = 0;
	infinity = infinit;
	
	tag = new Status[vexMaxNum];
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
 
	for (int v = 0; v < vexNum; v++)  {
		tag[v] = UNVISITED;
		vexTable[v].data = es[v];
		vexTable[v].firstarc = NULL;
	}
}

template <class ElemType, class WeightType>
AdjListUnDirNetwork<ElemType, WeightType>::AdjListUnDirNetwork(int vertexMaxNum, WeightType infinit)
// ������������춥�������ĿΪvertexMaxNum,infinit��ʾ�����Ŀ�������
{
	if (vertexMaxNum < 0)
    	throw Error("����Ķ��������Ŀ����Ϊ��!");// �׳��쳣

	vexNum = 0;			
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	infinity = infinit;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
}

template <class ElemType, class WeightType>
AdjListUnDirNetwork<ElemType, WeightType>::~AdjListUnDirNetwork()
// ����������ͷ��ڽӱ���������ռ�ÿռ�
{
    Clear();                                // �ͷű߽��
	delete []tag;							// �ͷű�־
	delete []vexTable;						// �ͷ��ڽӱ�
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::Clear()
// ����������ͷ����еı߽�㣬�����������Ķ������ͱ�������Ϊ0.
{
	AdjListNetworkArc<WeightType> *p;
	for (int v = 0; v < vexNum; v++)	{	// �ͷű߽��
	    p = vexTable[v].firstarc;
	    while (p != NULL) {
			vexTable[v].firstarc = p->nextarc;
			delete p;
			p = vexTable[v].firstarc;
        }	
	}
    vexNum = 0;
	arcNum = 0;	
}

template <class ElemType, class WeightType>
bool AdjListUnDirNetwork<ElemType, WeightType>::IsEmpty()
// ������������������Ϊ�շ���true,���򷵻�false.
{
	return vexNum == 0;
}

template <class ElemType, class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::GetOrder(ElemType &d) const
// ����������󶥵�d�����.�������Ŵ�0��ʼ��ͼ�в����ڶ���dʱ����-1. 
{
    int v;
    for (v = 0; v < vexNum; v++)
        if (d == vexTable[v].data)
           break;
           
	if (v < 0 || v >= vexNum)
		return -1;	// ����d������,����-1
	else
		return v;	// ����d������,����������� 
}	

template <class ElemType, class WeightType>
Status AdjListUnDirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &d) const
// ��������������Ϊv�Ķ���ֵ, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
//	ͨ��dȡ�ö���ֵ��������ENTRY_FOUND������������NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;			// Ԫ�ز�����
	else	{
		d = vexTable[v].data;		// ������v��Ԫ��ֵ����d
		return ENTRY_FOUND;			// Ԫ�ش���
	}
}	

template <class ElemType, class WeightType>
Status AdjListUnDirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &d)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;			// λ�ô�
	else	{
		vexTable[v].data = d;		// ����Ԫ��
		return SUCCESS;				// �ɹ�
	}
}

template <class ElemType, class WeightType>
WeightType AdjListUnDirNetwork<ElemType, WeightType>::GetInfinity() const
// �������������������ֵ 
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::GetVexNum() const
// ������������ض������			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::GetArcNum() const
// ������������ر�������
{
	return arcNum;
}		 

template <class ElemType, class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�һ���ڽӵ�			 
{
	if (v < 0 || v >= vexNum)
       throw Error("v���Ϸ�!");// �׳��쳣

	if (vexTable[v].firstarc == NULL)
	   return -1;              // �������ڽӵ�
	else
	   return vexTable[v].firstarc->adjVex;
}

template <class ElemType, class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�			 
{
	AdjListNetworkArc<WeightType> *p;
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
       throw Error("v1���ܵ���v2!");// �׳��쳣
	
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2)
	    p = p->nextarc;

	if (p == NULL || p->nextarc == NULL)
		return -1;                   // ��������һ���ڽӵ�
	else
		return p->nextarc->adjVex;
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::InsertVex(const ElemType &d)
// ����������ڶ����ı�β����Ԫ��ֵΪd�Ķ��㡣			 
{
	if (vexNum == vexMaxNum)
       throw Error("ͼ�Ķ��������ܳ�������������!");	// �׳��쳣

	vexTable[vexNum].data = d;
	vexTable[vexNum].firstarc = NULL;
	tag[vexNum] = UNVISITED;
    vexNum++;
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)  // 0 1 2
// ������������붥��Ϊv1��v2,ȨΪw�ı�			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
       throw Error("v1���ܵ���v2!");// �׳��쳣
	if (w == infinity)
       throw Error("w����Ϊ�޿մ�!");// �׳��쳣

	AdjListNetworkArc<WeightType> *p, *q, *firstarc;
	p = vexTable[v1].firstarc;
    firstarc = new AdjListNetworkArc<WeightType>(v2, w, p);
    vexTable[v1].firstarc = firstarc;
    q = vexTable[firstarc->adjVex].firstarc;
    vexTable[firstarc->adjVex].firstarc = new AdjListNetworkArc<WeightType>(v1, w, q);
	arcNum += 1;
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::DeleteVex(const ElemType &d)
// ���������ɾ��Ԫ��ֵΪd�Ķ���			 
{
    int v;
    AdjListNetworkArc<WeightType> *p, *q;
    for (v = 0; v < vexNum; v++)
       if	(vexTable[v].data == d)
           break;
	if (v == vexNum)
       throw Error("ͼ�в�����Ҫɾ���Ķ���!");	// �׳��쳣

    for (int u = 0; u < vexNum; u++)           // ɾ������d�Ļ� 
       if (u != v) 
          DeleteArc(u, v); 
          
	p = vexTable[v].firstarc;                  // ɾ����d�����Ļ� 
	while (p != NULL) {
        vexTable[v].firstarc = p->nextarc;
        delete p;    
	    p = vexTable[v].firstarc;
		arcNum--;
	}

    vexNum--;
    vexTable[v].data = vexTable[vexNum].data;
    vexTable[v].firstarc = vexTable[vexNum].firstarc;
    vexTable[vexNum].firstarc = NULL;
    tag[v] = tag[vexNum];

    for (int u = 0; u < vexNum; u++)         
       if (u != v) {
	      p = vexTable[u].firstarc;
	      while (p != NULL) {
             if (p->adjVex == vexNum)
                p->adjVex = v;
             p = p->nextarc;
          }
       }   
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::DeleteArc(int v1, int v2)
// ���������ɾ������Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw
       Error("v1���ܵ���v2!");		// �׳��쳣

	AdjListNetworkArc<WeightType> *p, *q;
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2) {
        q = p;
        p = p->nextarc;
    }
    if (p != NULL) {
	    if (vexTable[v1].firstarc == p)
            vexTable[v1].firstarc = p->nextarc;
        else
            q->nextarc = p->nextarc;
        delete p;    
		arcNum--;
	}
    p = vexTable[v2].firstarc;
    while (p != NULL && p->adjVex != v1) {
        q = p;
        p = p->nextarc;
    }
    if (p != NULL) {
        if (vexTable[v2].firstarc == p)
            vexTable[v2].firstarc = p->nextarc;
        else
            q->nextarc = p->nextarc;
        delete p;
    }
}

template <class ElemType, class WeightType>
WeightType AdjListUnDirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// ������������ض���Ϊv1��v2�ıߵ�Ȩֵ
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2���Ϸ�!");	// �׳��쳣

	AdjListNetworkArc<WeightType> *p;
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2) 
       p = p->nextarc;
    if (p != NULL)
	   return p->weight;			// ����Ȩֵ
	else
	   return infinity;				// ����ȨֵΪinfinity����ʾ�߲�����
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// ������������ö���Ϊv1��v2�ıߵ�Ȩֵ
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1���Ϸ�!");        // �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2���Ϸ�!");	    // �׳��쳣
	if (v1 == v2)
       throw Error("v1���ܵ���v2!");    // �׳��쳣
	if (w == infinity)
       throw Error("w����Ϊ�޿մ�!");   // �׳��쳣

	AdjListNetworkArc<WeightType> *p;
	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex != v2)
       p = p->nextarc;
    if (p != NULL)
	   p->weight = w;		            // �޸�Ȩֵ
}

template <class ElemType, class WeightType>
Status AdjListUnDirNetwork<ElemType, WeightType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum)
       throw Error("v���Ϸ�!");		// �׳��쳣

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::SetTag(int v, Status val) const
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum)
       throw Error("v���Ϸ�!");		// �׳��쳣

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjListUnDirNetwork<ElemType, WeightType>::AdjListUnDirNetwork(const AdjListUnDirNetwork<ElemType, WeightType> &copy)
// ��������������������ڽӾ���copy���������������ڽӾ���copy�������ƹ��캯��
{
	AdjListNetworkArc<WeightType> *p, *q;
	infinity =copy.infinity;
	vexNum = copy.vexNum;
	vexMaxNum = copy.vexMaxNum;	
	arcNum = copy.arcNum;

	tag = new Status[vexMaxNum];
	vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
	for (int v = 0; v < vexNum; v++)	{
		tag[v] = copy.tag[v];
		vexTable[v].data = copy.vexTable[v].data;
		vexTable[v].firstarc = NULL;
		p = copy.vexTable[v].firstarc;
		while (p != NULL) 
           if (vexTable[v].firstarc == NULL) {
              vexTable[v].firstarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weigth);	
              q = vexTable[v].firstarc;
              p = p->nextarc;
           }
           else {   
              q->nextarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weigth);	
              q = q->nextarc;
              p = p->nextarc;
           }   
	}
}

template <class ElemType, class WeightType>
AdjListUnDirNetwork<ElemType, WeightType> &AdjListUnDirNetwork<ElemType, WeightType>::operator =(const AdjListUnDirNetwork<ElemType, WeightType> &copy)
// ��������������������ڽӾ���copy��ֵ����ǰ���������ڽӾ��󡪡���ֵ�������
{
	if (&copy != this)
	{
        Clear();                                    // �ͷŵ�ǰ�������߽��
	    delete []tag;								// �ͷŵ�ǰ��������־����
	    delete []vexTable;							// �ͷŵ�ǰ�����������

	    AdjListNetworkArc<WeightType> *p, *q;
	    infinity =copy.infinity;
	    vexNum = copy.vexNum;
	    vexMaxNum = copy.vexMaxNum;	
	    arcNum = copy.arcNum;

	    tag = new Status[vexMaxNum];
	    vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
	    for (int v = 0; v < vexNum; v++)	{
		   tag[v] = copy.tag[v];
		   vexTable[v].data = copy.vexTable[v].data;
		   vexTable[v].firstarc = NULL;
		   p = copy.vexTable[v].firstarc;
		   while (p != NULL) 
               if (vexTable[v].firstarc == NULL) {
                  vexTable[v].firstarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weigth);	
                  q = vexTable[v].firstarc;
                  p = p->nextarc;
               }
               else {   
                  q->nextarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weigth);	
                  q = q->nextarc;
                  p = p->nextarc;
               }   
	   }
    }
	return *this;
}

template <class ElemType, class WeightType>
void AdjListUnDirNetwork<ElemType, WeightType>::Display()
// �������: ��ʾ�ڽӾ���������
{
	AdjListNetworkArc<WeightType> *p;
    cout << "����������" << vexNum << "�����㣬" << arcNum << "���ߡ�" << endl;
	for (int v = 0; v < vexNum; v++)	{	// ��ʾ��v���ڽ�����
		cout << v << ":\t" << vexTable[v].data;				// ��ʾ�����
	    p = vexTable[v].firstarc;
	    while (p != NULL) {
        	cout << "-->(" << p->adjVex << "," << p->weight << ")";
            p = p->nextarc; 
		}
		cout << endl; 
	}
}

template<class ElemType,class WeightType>
int AdjListUnDirNetwork<ElemType, WeightType>::CountDegree(int v) const
{
    AdjListNetworkArc<WeightType> *p;
    int cnt = 0;
    cout << v << ":\t" << vexTable[v].data;				// ��ʾ�����
    p = vexTable[v].firstarc;
    while (p != NULL)
    {
        p = p->nextarc;
        ++cnt;
    }
    cout << "'s degree = " << cnt << endl;
    return cnt;
}

#endif
