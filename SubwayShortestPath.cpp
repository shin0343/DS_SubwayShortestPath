#include<iostream>
#include<stack>
using namespace std;

#define INF 10000


class Node
{
public:
	Node(char l = '\0', int n = 0)
	{
		line = l;
		num = n;
	}
	char line; //노선
	int num;//역 번호
};

Node sts[43]; //역 들의 모임. 총 43개 역이 있다.
bool visit[43]; //방문했는지 확인을 위한 배열
double dist[43];//출발역으로부터 모든 역에 대한 최단 경로를 저장하기 위한 배열
int route[43]; //경로 출력을 위해 이용하는 배열
stack<int> stk;
//각 역들간의 시간 비용 담기 위한 인접 행렬
double timecost[43][43] =
{//   a1   a2   a3   a4   a5   a6   a7   a8   a9   a10  a11  a12  a13  a14  a15  a16  a17  a18  a19  a20  b1   b2   b3   b4   b5   b6   b7   b8   b9   b10  c1   c2   c3   c4   c5   c6   c7   c8   c9   c10  c11  c12  c13
	{ 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0.5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0.5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0.5, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0.5, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, 0.5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, 0.5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0.5, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, 0.5, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ 0.5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0.5, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0.5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, 0.5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0, INF },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0, 1.0 },
	{ INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1.0, 0.0 }
};

void graphInit()
{ 
	for (int i = 0; i < 20; i++) //a 노선에 대한 정보 입력
		{
			sts[i].line = 'a';
			sts[i].num = i + 1;
		}
		for (int i = 20; i < 30; i++) //b 노선에 대한 정보 입력
		{
			sts[i].line = 'b';
			sts[i].num = i - 19;
		}
		for (int i = 30; i < 43; i++) //c 노선에 대한 정보 입력
		{
			sts[i].line = 'c';
			sts[i].num = i - 29;
		}
}

int findSt(Node s)
{
	for (int i = 0; i < 43; i++)
	{
		if (sts[i].line == s.line&&sts[i].num == s.num)
		{
			return i;
		}
	}
	return -1; 
}

void sPath(Node s, int n)
{
	//탐색을 진행하기 위한 기본적인 세팅
	for (int i = 0; i < n; i++)
	{
		visit[i] = false;
		dist[i] = timecost[findSt(s)][i]; // 최초 최단거리는 s와의 cost
	}

	for (int i = 0; i < n-1; i++)
	{
		int min = INF + 1;
		int idx = -1;
		for (int j = 0; j < n; j++)
		{
			//기존 정점과 연결된 가장 작은 정점을 찾아서
			if (visit[j] == false && min > dist[j])
			{
				min = dist[j];
				idx = j;
			}
		}

		visit[idx] = true;
		for (int j = 0; j < n; j++)
		{
			if (dist[j] > dist[idx] + timecost[idx][j])
			{
				dist[j] = dist[idx] + timecost[idx][j];
				route[j] = idx;
			}
		}
	}
}

void printPath(Node s, Node e)
{
	//입력 받은 역 정보 범위 확인
	if (findSt(s) == -1 || findSt(e) == -1)
	{
		cout << "존재하지 않는 역을 입력하셨습니다." << endl;
		cout << "프로그램 종료." << endl;
		return;
	}
	sPath(s, 43);

	//시작 노드는 스택을 이용하지 않고 따로 출력
	cout << sts[findSt(s)].line << sts[findSt(s)].num;

	//스택을 이용하여 도착역부터 역으로 추적
	int idx = findSt(e);
	while (idx != 0)
	{
		stk.push(idx);
		idx = route[idx];
	}
	//시작역 다음역부터 도착역까지 출력
	while (!stk.empty())
	{
		cout << " -> " << sts[stk.top()].line << sts[stk.top()].num;
		stk.pop();
	}cout << endl;

	double tmp = 60 * dist[findSt(e)];
	int min = (int)tmp / 60;
	int sec = (int)tmp % 60;
	cout << "소요시간 : " << min << "분 " << sec << "초 " << endl;
}

int main()
{
	graphInit(); //지하철 노선도 초기화

	char start[4], end[4];
	cout << "출발역: ";
	cin >> start;
	cout << "도착역: ";
	cin >> end;
	cout << "================================================================================" << endl;

	//출발 역에 대한 노드, 도착 역에 대한 노드class
	Node s, e;

	//입력 받은 출발역의 정보를 노드s에 입력
	s.line = start[0]; 
	s.num = start[1] - 48;
	if (start[2] >= 48 && start[2] <= 57)
	{
		int tmp = s.num * 10;
		s.num = start[2] - 48;
		s.num += tmp;
	}
	//입력 받은 도착역의 정보를 노드e에 입력
	e.line = end[0];
	e.num = end[1] - 48;
	if (end[2] >= 48 && end[2] <= 57)
	{
		int tmp = e.num * 10;
		e.num = end[2] - 48;
		e.num += tmp;
	}

	printPath(s, e);

	return 0;
}