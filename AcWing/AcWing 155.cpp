#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000000000+5;
const int MAXT=1000000000+5;
const int MAXM=1000000000+5;
const int MAXP=1000000000+5;

struct Event{
	int mem,time;
	inline Event(void){
		mem=time=0;
		return;
	}
	inline Event(reg int a,reg int b){
		mem=a,time=b;
		return;
	}
};

struct Task{
	int pos,len;
	inline Task(void){
		pos=len=0;
		return;
	}
	inline Task(reg int a,reg int b){
		pos=a,len=b;
		return;
	}
	inline bool operator<(const Task& a)const{
		return pos!=a.pos?pos<a.pos:len<a.len;
	}
};

struct Free_E{
	int time,pos;
	inline Free_E(void){
		time=pos=0;
		return;
	}
	inline Free_E(reg int a,reg int b){
		time=a,pos=b;
		return;
	}
	inline bool operator<(const Free_E& a)const{
		return time<a.time;
	}
	inline bool operator>(const Free_E& a)const{
		return time>a.time;
	}
};

int n,ans,cnt;
set<Task> S;
queue<Event> Q;
priority_queue<Free_E,vector<Free_E>,greater<Free_E>/**/> H;

inline bool Add(reg int t,const Event& E){
	static set<Task>::iterator it,temp;
	for(it=S.begin();it!=S.end();++it){
		temp=it;
		++temp;
		if(temp!=S.end()){
			reg int
			pos=it->pos+it->len,
			len=temp->pos-pos;
			if(E.mem<=len){
				S.insert(Task(pos,E.mem));
				H.push(Free_E(t+E.time,pos));
				return true;
			}
		}
	}
	return false;
}

inline void Free(reg int t){
	reg int time;
	static Free_E temp;
	while(!H.empty()&&H.top().time<=t){
		time=H.top().time;
		while(!H.empty()&&H.top().time<=time){
			temp=H.top();
			H.pop();
			S.erase(S.lower_bound(Task(temp.pos,0)));
		}
		ans=time;
		while(!Q.empty())
			if(Add(time,Q.front()))
				Q.pop();
			else
				break;
	}
	return;
}

int main(void){
	reg int t,m,p;
	n=read();
	S.insert(Task(-1,1)),S.insert(Task(n,1));
	while(t=read(),m=read(),p=read(),t||m||p){
		Free(t);
		if(!Add(t,Event(m,p))){
			++cnt;
			Q.push(Event(m,p));
		}
	}
	Free(MAXT);
	printf("%d\n%d\n",ans,cnt);
	return 0;
}
