#include<cstdio>
#include<cmath>
#include<algorithm>
using std::sort;

struct Segment{
	double x,y;
	bool operator<(const Segment &a)const{
		return x<a.x;
	}
};

int T,n,L,h,cnt;
Segment S[20005];

int Solve(void);

int main(void){
	register int i;
	scanf("%d",&T);
	while(T--){
		cnt=0;
		scanf("%d%d%d",&n,&L,&h);
		for(i=1;i<=n;++i){
			static int x,r;
			scanf("%d%d",&x,&r);
			if(r<=(h>>1))
				continue;
			S[++cnt].x=x-sqrt(r*r-(h*h/4.0));
			S[cnt].y=x+sqrt(r*r-(h*h/4.0));
		}
		sort(S+1,S+cnt+1);
		printf("%d\n",Solve());
	}
	return 0;
}

int Solve(void){
	register bool flag=true;
	register int ans=0,cur=1;
	double head=0,tail=0;
	while(tail<L){
		++ans;
		head=tail;
		while(cur<=cnt&&S[cur].x<=head){
			if(tail<S[cur].y)
				tail=S[cur].y;
			++cur;
		}
		if(tail==head&&head<L)
			return -1;
	}
	return ans;
}
