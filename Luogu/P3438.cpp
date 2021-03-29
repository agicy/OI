#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXW=1e3+5;
const int MAXN=MAXW*MAXW;

struct Node{
	int x,y;
	inline void Read(void){
		x=read()-1,y=read()-1;
		return;
	}
	inline bool operator<(const Node& a)const{
		return y<a.y||(y==a.y&&x<a.x);
	}
};

int w1,w2;
Node st,ed;
int n;
Node p[MAXN];

inline int X(reg int i){
	return p[i].y;
}

int x;

inline int Y(reg int i){
	return p[i].x*p[i].x+p[i].y*p[i].y-2*x*p[i].x;
}

inline bool check1(reg int i,reg int j,reg int k){
	reg int xi=X(i),xj=X(j),xk=X(k);
	reg int yi=Y(i),yj=Y(j),yk=Y(k);
	reg int prex=xj-xi,prey=yj-yi;
	reg int newx=xk-xj,newy=yk-yj;
	return 1ll*newx*prey-1ll*prex*newy>=0;
}

inline bool check2(reg int i,reg int j,reg int k){
	reg int xi=X(i),xj=X(j);
	reg int yi=Y(i),yj=Y(j);
	reg int prex=xj-xi,prey=yj-yi;
	reg int newx=1,newy=k;
	return 1ll*newx*prey-1ll*prex*newy<=0;
}

int dis[MAXW][MAXW];

inline int getId(reg int i,reg int j){
	return i*w2+j;
}

bool vis[MAXW][MAXW];
int _head,_tail;
int Qx[MAXW*MAXW],Qy[MAXW*MAXW];

inline bool check(reg int lim){
	if(dis[st.x][st.y]<lim)
		return false;
	for(reg int i=0;i<w1;++i)
		for(reg int j=0;j<w2;++j)
			vis[i][j]=false;
	_head=_tail=0;
	vis[st.x][st.y]=true,Qx[_tail]=st.x,Qy[_tail]=st.y,++_tail;
	while(_head<_tail){
		reg int x=Qx[_head],y=Qy[_head];
		++_head;
		if(x==ed.x&&y==ed.y)
			return true;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		for(reg int k=0;k<4;++k){
			reg int fx=x+dx[k],fy=y+dy[k];
			if(0<=fx&&fx<w1&&0<=fy&&fy<w2&&!vis[fx][fy]&&dis[fx][fy]>=lim)
				vis[fx][fy]=true,Qx[_tail]=fx,Qy[_tail]=fy,++_tail;
		}
	}
	return false;
}

int Q[MAXN];

int main(void){
	w1=read(),w2=read();
	st.Read(),ed.Read();
	n=read();
	for(reg int i=0;i<n;++i)
		p[i].Read();
	sort(p,p+n);
	vector<int> V;
	V.resize(w1*w2);
	for(reg int i=0;i<w1;++i){
		x=i;
		reg int _head=0,_tail=0;
		for(reg int j=0;j<n;++j){
			while(_tail-_head>1&&check1(Q[_tail-2],Q[_tail-1],j))
				--_tail;
			Q[_tail++]=j;
		}
		for(reg int j=0;j<w2;++j){
			while(_tail-_head>1&&check2(Q[_head],Q[_head+1],2*j))
				++_head;
			dis[i][j]=Y(Q[_head])-2*j*X(Q[_head])+i*i+j*j;
			V[getId(i,j)]=dis[i][j];
		}
	}
	sort(V.begin(),V.end());
	puts("INit");
	reg int l=0,r=w1*w2-1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(V[mid+1]))
			l=mid+1;
		else
			r=mid;
	}
	printf("%d\n",V[l]);
	return 0;
}