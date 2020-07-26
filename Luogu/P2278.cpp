#include <cstdio>
#include <queue>
using std::priority_queue;
#define max(a, b) ((a) > (b) ? (a) : (b))

struct Node{
	int ID, arrive, time, IM;
	bool operator<(const Node &a)const{
		if(IM==a.IM)
			return IM > a.IM;
		else
			return arrive < a.arrive;
	}
};

int ID, arrive, time, IM;
int now;
Node temp;
priority_queue<Node> Q;

int main(void){
	while (~scanf("%d%d%d%d", &ID, &arrive, &time, &IM)){
		temp.ID = ID;
		temp.arrive = arrive;
		temp.time = time;
		temp.IM = IM;
		Q.push(temp);
	}
	while(!Q.empty()){
		temp = Q.top();
		Q.pop();
		now = max(now, temp.arrive);
		now += temp.time;
		printf("%d %d\n", temp.ID, now);
	}
	return 0;
}