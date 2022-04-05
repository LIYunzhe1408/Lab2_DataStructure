#include "Assistance.h"					// 辅助软件包
#include "AdjListUnDirNetwork.h"		// 邻接表无向网
#include"Kruskal.h"
#include"Prim.h"
#include"BreakCycle.h"
int main(void)
{
    try									// 用try封装可能出现异常的代码
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
            cout << endl << "1. 无向网清空.";
            cout << endl << "2. 显示无向网.";
            cout << endl << "3. 输出连通分支数.";
            cout << endl << "4. 设置指定顶点的值.";
            cout << endl << "5. 删除顶点.";
            cout << endl << "6. 插入顶点.";
            cout << endl << "7. 删除边.";
            cout << endl << "8. 插入边.";
            cout << endl << "9. 设置指定边的权.";
            cout<<endl<<"a.求最小生成树";
            cout << endl << "b.是否有唯一最小生成树.";
		    cout << endl << "0. 退出";
		    cout << endl << "选择功能(0~b):";
		    cin >> c;
		    switch (c) 		{
			    case '1':
			        net.CountDegree(0);
			        net.Clear();
				    break;
			    case '2':
                    if (net.IsEmpty())
                        cout << "该无向网为空。" << endl;
                    else 
			            net.Display();
				    break;
			    case '3':
		            cout << endl <<"连通分支数为" <<net.ConnectedComponent() ;
			        break;
			    case '4':
			        cout << endl << "输入顶点序号（无向网的顶点序号从0开始）:";
			        cin >> v;
			        cout << endl << "输入" << v <<"号顶点的值:";
			        cin >> e;
		            net.SetElem(v, e);
			        break;
			    case '5':
			        cout << endl << "输入被删除顶点的值:";
			        cin >> e;
		            net.DeleteVex(e);
			        break;
			    case '6':
			        cout << endl << "输入插入顶点的值:";
			        cin >> e;
		            net.InsertVex(e);
			        break;
			    case '7':
			        cout << endl << "输入与被删除边关联的两个顶点值:";
			        cin >> e1 >> e2;
			        v1 = net.GetOrder(e1);
			        v2 = net.GetOrder(e2);
		            net.DeleteArc(v1, v2);
			        break;
			    case '8':
			        cout << endl << "输入与插入边关联的两个顶点值和边的权值:";
			        cin >> e1 >> e2 >> w;
			        v1 = net.GetOrder(e1);
			        v2 = net.GetOrder(e2);
		            net.InsertArc(v1, v2, w);
			        break;
			    case '9':
			        cout << endl << "输入与插入边关联的两个顶点值和边的权值:";
			        cin >> e1 >> e2 >> w;
			        v1 = net.GetOrder(e1);
			        v2 = net.GetOrder(e2);
		            net.SetWeight(v1, v2, w);
			        break;
                case 'a':
                    cout<<"Kruskal算法：最小生成树的边及权值为："<<endl;
                    MiniSpanTreeKruskal(net);
                    cout<<"Prim算法：最小生成树的边及权值为："<<endl;
                    MiniSpanTreePrim(net,0);
                    cout<<"破圈算法：最小生成树的边及权值为："<<endl;
                    MiniSpanTreeBreakCycle(net);
                    break;
                case 'b':
                    cout<<(net.hasUniqueMinTree() ? " 存在" : " 不存在") << "唯一最小生成树";
                    break;
       	      }
         }
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}
	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

