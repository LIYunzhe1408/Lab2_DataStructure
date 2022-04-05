#include "Assistance.h"					// ���������
#include "AdjListUnDirNetwork.h"		// �ڽӱ�������
#include"Kruskal.h"
#include"Prim.h"
#include"BreakCycle.h"
int main(void)
{
    try									// ��try��װ���ܳ����쳣�Ĵ���
	{
		int infity = DEFAULT_INFINITY;
		char vexs[] = {'A', 'B', 'C', 'D','E','F'};
		int m[6][6] = {
			{0, 34, 46, infity,infity,19},
			{34, 0, infity, infity,12,infity},
			{46, infity, 0, 17,infity,25},
			{infity, infity, 17, 0,38,25},
            {infity,12,infity,38,0,26},
            {19,infity,25,25,26,0}
		};
		char c = 'a', e, e1, e2;
		int n = 6, v, v1, v2, w;

		AdjListUnDirNetwork<char, int> net(vexs, n);

		for (int v = 0; v < n; v++)
			for (int u = v; u < n; u++)
				if (m[v][u] != infity&&m[v][u]!=0) net.InsertArc(v, u, m[v][u]);

	    while (c != '0')	{
            cout << endl << "1. ���������.";
            cout << endl << "2. ��ʾ������.";
            cout << endl << "3. �����ͨ��֧��.";
            cout << endl << "4. ����ָ�������ֵ.";
            cout << endl << "5. ɾ������.";
            cout << endl << "6. ���붥��.";
            cout << endl << "7. ɾ����.";
            cout << endl << "8. �����.";
            cout << endl << "9. ����ָ���ߵ�Ȩ.";
            cout<<endl<<"a.����С������";
            cout << endl << "b.�Ƿ���Ψһ��С������.";
		    cout << endl << "0. �˳�";
		    cout << endl << "ѡ����(0~b):";
		    cin >> c;
		    switch (c) 		{
			    case '1':
			        net.CountDegree(0);
			        net.Clear();
				    break;
			    case '2':
                    if (net.IsEmpty())
                        cout << "��������Ϊ�ա�" << endl;
                    else 
			            net.Display();
				    break;
			    case '3':
		            cout << endl <<"��ͨ��֧��Ϊ" <<net.ConnectedComponent() ;
			        break;
			    case '4':
			        cout << endl << "���붥����ţ��������Ķ�����Ŵ�0��ʼ��:";
			        cin >> v;
			        cout << endl << "����" << v <<"�Ŷ����ֵ:";
			        cin >> e;
		            net.SetElem(v, e);
			        break;
			    case '5':
			        cout << endl << "���뱻ɾ�������ֵ:";
			        cin >> e;
		            net.DeleteVex(e);
			        break;
			    case '6':
			        cout << endl << "������붥���ֵ:";
			        cin >> e;
		            net.InsertVex(e);
			        break;
			    case '7':
			        cout << endl << "�����뱻ɾ���߹�������������ֵ:";
			        cin >> e1 >> e2;
			        v1 = net.GetOrder(e1);
			        v2 = net.GetOrder(e2);
		            net.DeleteArc(v1, v2);
			        break;
			    case '8':
			        cout << endl << "���������߹�������������ֵ�ͱߵ�Ȩֵ:";
			        cin >> e1 >> e2 >> w;
			        v1 = net.GetOrder(e1);
			        v2 = net.GetOrder(e2);
		            net.InsertArc(v1, v2, w);
			        break;
			    case '9':
			        cout << endl << "���������߹�������������ֵ�ͱߵ�Ȩֵ:";
			        cin >> e1 >> e2 >> w;
			        v1 = net.GetOrder(e1);
			        v2 = net.GetOrder(e2);
		            net.SetWeight(v1, v2, w);
			        break;
                case 'a':
                    cout<<"Kruskal�㷨����С�������ı߼�ȨֵΪ��"<<endl;
                    MiniSpanTreeKruskal(net);
                    cout<<"Prim�㷨����С�������ı߼�ȨֵΪ��"<<endl;
                    MiniSpanTreePrim(net,0);
                    cout<<"��Ȧ�㷨����С�������ı߼�ȨֵΪ��"<<endl;
                    MiniSpanTreeBreakCycle(net);
                    break;
                case 'b':
                    cout<<(net.hasUniqueMinTree() ? " ����" : " ������") << "Ψһ��С������";
                    break;
       	      }
         }
	}
	catch (Error err)					// ��׽�������쳣
	{
		err.Show();						// ��ʾ�쳣��Ϣ
	}
	system("PAUSE");					// ���ÿ⺯��system()
	return 0;							// ����ֵ0, ���ز���ϵͳ
}

