#include<cstdio>
#include<algorithm>
using std::sort;

const int MAXN=1000+5;

struct Node{
	int s,f;
	void Read(void){
		scanf("%d%d",&s,&f);
		return;
	}
	bool operator<(const Node &a)const{
		return f<a.f;
	}
};

int n;
Node E[MAXN];

int main(void){
	register int i,t,ans=1;
	scanf("%d",&n);
	for(i=1;i<=n;++i)
		E[i].Read();
	sort(E+1,E+n+1);
	t=E[1].f;
	for(i=2;i<=n;++i){
		if(E[i].s>=t){
			++ans;
			t=E[i].f;
		}
	}
	printf("%d\n",ans);
	return 0;
}
