#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;

struct Heap{
	priority_queue<int,vector<int>,greater<int>/**/> A,D;
	inline void push(int x){
		A.push(x);
		return;
	}
	inline void del(int x){
		D.push(x);
		return;
	}
	inline int top(void){
		while(!D.empty()&&A.top()==D.top())
			A.pop(),D.pop();
		return A.top();
	}
	inline void pop(void){
		while(!D.empty()&&A.top()==D.top())
			A.pop(),D.pop();
		D.push(A.top());
		return;
	}
};

int n;
Heap H;
int a[MAXN];

int main(void){
	scanf("%d",&n);
	int tot=0;
	while(n--){
		static string str;
		static int x,k;
		cin>>str;
		if(str=="I"){
			scanf("%d",&x);
			a[++tot]=x;
			H.push(x);
		}
		else if(str=="PM")
			printf("%d\n",H.top());
		else if(str=="DM")
			H.pop();
		else if(str=="D"){
			scanf("%d",&k);
			H.del(a[k]);
		}
		else if(str=="C"){
			scanf("%d%d",&k,&x);
			H.del(a[k]);
			a[k]=x;
			H.push(a[k]);
		}
	}
	return 0;
}
