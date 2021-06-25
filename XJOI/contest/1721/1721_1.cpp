#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=5e4+5;
const int MAXM=50+5;
const int inf=0x3f3f3f3f;

int n,m,X,A;
int a[MAXN],sum[MAXN];
int b[MAXM],h[MAXM];

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

vector<int> tmp;

inline int getVal(reg int val,reg int id,reg bool flag){
	priority_queue<Node,vector<Node>,less<Node>/**/> Q;
	reg int cnt=0;
	for(reg int i=b[id-1]+1;i<=b[id];++i){
		Q.push(Node(i,a[i]));
		val-=X;
		while(val<0){
			static Node s;
			s=Q.top(),Q.pop();
			++cnt,val+=s.val+X;
			if(flag) tmp.push_back(s.id);
		}
	}
	if(cnt>h[id])
		return -inf;
	else{
		while(cnt<h[id]){
			static Node s;
			s=Q.top(),Q.pop();
			++cnt,val+=s.val+X;
			if(flag) tmp.push_back(s.id);
		}
		return val;
	}
}

int f[MAXM][MAXM];
int from[MAXM][MAXM];

int main(void){
	n=read(),m=read(),X=read(),A=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),sum[i]=sum[i-1]+a[i];
	for(reg int i=1;i<=m;++i)
		b[i]=read(),h[i]=b[i]-b[i-1]-read();
	memset(f,~0x3f,sizeof(f));
	f[0][0]=A;
	for(reg int i=0;i<m;++i)
		for(reg int j=0;j<=i;++j)
			if(f[i][j]>=0){
				reg int val1=f[i][j]+sum[b[i+1]]-sum[b[i]];
				if(f[i+1][j]<val1)
					f[i+1][j]=val1,from[i+1][j]=j;
				reg int val2=getVal(f[i][j],i+1,false);
				if(f[i+1][j+1]<val2)
					f[i+1][j+1]=val2,from[i+1][j+1]=j;
			}
	reg int ptr=-1;
	for(reg int i=m;i>=0;--i)
		if(f[m][i]>=0){
			ptr=i;
			break;
		}
	reg int ans1=ptr;
	vector<int> ans3;
	for(reg int i=m;i>=1;ptr=from[i][ptr],--i)
		if(from[i][ptr]+1==ptr){
			tmp.clear(),tmp.reserve(h[i]);
			getVal(f[i-1][from[i][ptr]],i,true);
			ans3.insert(ans3.end(),tmp.begin(),tmp.end());
		}
		else{
			ans3.reserve(b[i]-b[i-1]);
			for(int j=b[i-1]+1;j<=b[i];++j)
				ans3.push_back(j);
		}
	sort(ans3.begin(),ans3.end());
	write(ans1),putchar('\n'),write(ans3.size()),putchar('\n');
	for(reg int i=0,siz=ans3.size();i<siz;++i)
		write(ans3[i]),putchar(i==siz-1?'\n':' ');
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}