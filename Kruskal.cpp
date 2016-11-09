//�ú�ѧϰ �������� Ҫ��ѧ���е�ѧ�� ŶҲ --���� May 08 2015 һ�����ʵ�������������һ���������д���С��ԭ���Ǵ������˶��Ⱦ�
#include<iostream>  
#include<cstring>  
#include<algorithm>  
#include<cstdlib>  
#include<cmath>  
#include<vector>  
#include<unordered_map>  
#include<random>
#include<math.h>

using namespace std;
default_random_engine e(22180204);
uniform_real_distribution<double> u(0, 1);



//uniform_real_distribution<double> u(0, 1);

struct Edge {
	char vertex1;
	char vertex2;
	int weight;
	Edge(char v1, char v2, int w):vertex1(v1), vertex2(v2), weight(w) {}
};

struct Graph {
	vector<char> vertice;
	vector<Edge> edges;
};

unordered_map<char, char> PARENT;
unordered_map<char, int> RANK;

char find(char vertex) {
	if (PARENT[vertex] == vertex) 
		return PARENT[vertex];
	else
		return find(PARENT[vertex]);	
}

void MST(Graph& g) {
	vector<Edge> res;

	for (auto c : g.vertice) {
		PARENT[c] = c;
		RANK[c] = 0;
	}

	sort(g.edges.begin(), g.edges.end(), [](Edge x, Edge y) {return x.weight < y.weight;});   // O(E*log(E))

	for (Edge e : g.edges) {         // O(E)
		char root1 = find(e.vertex1);  // O(E) worst case
		char root2 = find(e.vertex2);
		if (root1 != root2) {
			res.push_back(e);
			if (RANK[root1] > RANK[root2]) {
				PARENT[root2] = root1;
				RANK[root1]++;
			} else {
				PARENT[root1] = root2;
				RANK[root2]++;
			}
		}
	}

	for (Edge e : res) {
		cout << e.vertex1 << " -- " << e.vertex2 << "  " << e.weight << endl;
	}
}

void Union( char vertex_1, char vertex_2 ) {

}

struct ZaiQu {
	int x;
	int y;
	int demand;
};

int main() {
	int BianChang_of_area = 100;//����߳���С
	const int number_of_ZaiQu = 10;//��������
	//int ZaiQu_location[number_of_ZaiQu][number_of_ZaiQu];//��������
	ZaiQu ZaiQu_location[number_of_ZaiQu];
	int Maxdemand = 3;//����̶�
	int i, j, k,i1,j1;
	FILE* location;
	location = fopen("ZaiQu_location.txt", "w");
	for (i = 0; i < number_of_ZaiQu; i++)
	{
		ZaiQu_location[i].x = floor(u(e)*BianChang_of_area);//���������������
		ZaiQu_location[i].y = floor(u(e)*BianChang_of_area);
		ZaiQu_location[i].demand = ceil(u(e)*Maxdemand);//�����ʵ�����̶�
		fprintf(location, "%d\t%d\n", ZaiQu_location[i].x, ZaiQu_location[i].y);
		cout << i << "\t" << ZaiQu_location[i].x << "\t" << ZaiQu_location[i].y << "\t" << ZaiQu_location[i].demand<<endl;
	}
	fclose(location);
	int ZaiQu_distance_number = number_of_ZaiQu*(number_of_ZaiQu - 1) / 2;//������������Ļ�����������Cn2
	double ZaiQu_distance[number_of_ZaiQu][number_of_ZaiQu];
	double ZaiQu_distance_based_on_demand[number_of_ZaiQu][number_of_ZaiQu];//��������;���Ȩ���Ȩ�ؾ���
	cout << "Distance" << endl;
	for (i = 0; i < number_of_ZaiQu; i++)
	{
		for (j = 0; j < number_of_ZaiQu; j++)
		{
			if (i == j)ZaiQu_distance[i][j] = 0;
			else
			{
				ZaiQu_distance[i][j] = sqrt(abs((ZaiQu_location[i].x - ZaiQu_location[j].x)*(ZaiQu_location[i].x - ZaiQu_location[j].x)) + abs((ZaiQu_location[i].y - ZaiQu_location[j].y)*(ZaiQu_location[i].y - ZaiQu_location[j].y)));
				//	cout << "diff\t" << (ZaiQu_location[i].x - ZaiQu_location[j].x)*(ZaiQu_location[i].x - ZaiQu_location[j].x) << "\t" << (ZaiQu_location[i].y - ZaiQu_location[j].y)*(ZaiQu_location[i].y - ZaiQu_location[j].y) << endl;
				ZaiQu_distance_based_on_demand[i][j] = ZaiQu_distance[i][j] / (ZaiQu_location[i].demand + ZaiQu_location[j].demand);
			}
			cout << i << "\t" << j << "\t" << ZaiQu_distance[i][j] << "\t" << ZaiQu_distance_based_on_demand[i][j] <<endl;
		}//��������֮��ľ���
	}

	char t[] = {'a', 'b', 'c', 'd', 'e', 'f','g','h','i','j'};//��������a��j���

	Graph g;
	g.vertice = vector<char>(t, t + sizeof(t)/sizeof(t[0]));
	cout << "Vertice"<<sizeof(g.vertice)<<endl;
	for (i = 0; i < number_of_ZaiQu; i++)
	{
		for (j = 0; j < number_of_ZaiQu; j++)
		{
			g.edges.push_back(Edge(t[i], t[j], ZaiQu_distance_based_on_demand[i][j]));//��������Ϣ�ŵ�ͼ����
		}
	}

	MST(g);//��minimum spanning tree

	return 0;
}

