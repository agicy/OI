#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read(void){
	bool f=false;
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const int MAXSIZE=MAXM*4;

int n,m;

struct Node{
	int val,col;
	int ptr[2];
	inline int getE(void){
		if(!ptr[0])
			return 0;
		else
			return 1;
	}
	inline int getS(void){
		if(ptr[0])
			return 0;
		else
			return 1;
	}
	inline int find(int x){
		if(ptr[0]==x)
			return 0;
		else
			return 1;
	}
};

bool E[MAXN];
int head[MAXN],tail[MAXN];
int tot;
Node chunk[MAXSIZE];

inline void attach(int l_id,int val,int col){

	int id=++tot;
	chunk[id].val=val,chunk[id].col=col;
	chunk[id].ptr[0]=chunk[id].ptr[1]=0;

	if(E[l_id]){

		head[l_id]=tail[l_id]=id;

		chunk[id].ptr[0]=0; //head
		chunk[id].ptr[1]=0; //tail

		E[l_id]=false;
	}

	else{
		int pre=tail[l_id];
		int emp_pid=chunk[pre].getE();
		chunk[pre].ptr[emp_pid]=id;

		chunk[id].ptr[0]=pre;
		
		tail[l_id]=id;
	}
	return;
}

inline int pop(int l_id,int val){

	int res=-1;

	for(int id=tail[l_id];val;id=tail[l_id]){

		if(!id)
			exit(-1);
		
		if(val<chunk[id].val){

			chunk[id].val-=val;
			return chunk[id].col; //res

		}
		else if(val==chunk[id].val){
			chunk[id].val-=val;
			val=0;

			int pre_pid=chunk[id].getS();
			int pre=chunk[id].ptr[pre_pid];
			int res=chunk[id].col;

			//chunk[id].clear();
			
			if(!pre){
				E[l_id]=true;
				head[l_id]=tail[l_id]=0;

				return res;
			}
			else{
				tail[l_id]=pre;
				int pid=chunk[pre].find(id);
				chunk[pre].ptr[pid]=0;

				return res;
			}
		}
		else{
			val-=chunk[id].val;

			int pre_pid=chunk[id].getS();
			int pre=chunk[id].ptr[pre_pid];

			//chunk[id].clear();
			
			if(!pre){
				head[l_id]=tail[l_id]=0;
				return chunk[id].col;

			}
			tail[l_id]=pre;
			int id_pid=chunk[pre].find(id);
			chunk[pre].ptr[id_pid]=0;

		}
	}
	return res;
}

inline void pour(int l_fr,int l_to){
	if(E[l_fr])
		return;
	E[l_fr]=true;

	int h_fr=head[l_fr],t_fr=tail[l_fr];

	if(E[l_to]){
		E[l_to]=false;
		head[l_to]=t_fr;
		tail[l_to]=h_fr;
	}
	else{
		int pre=tail[l_to];
		int pid=chunk[pre].getE();
		chunk[pre].ptr[pid]=t_fr;
		int epid=chunk[t_fr].getE();
		chunk[t_fr].ptr[epid]=pre;
		tail[l_to]=h_fr;
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		E[i]=true;
	for(int i=1;i<=m;++i){
		static char opt[8];
		static int x,y,z,u,v;
		scanf("%s",opt);
		switch(opt[2]){
			case 's':{
				x=read(),y=read(),z=read();
				attach(z,x,y);
				break;
			}
			case 'p':{
				x=read(),z=read();
				int col=pop(z,x);
				printf("%d\n",col);
				break;
			}
			case 't':{
				u=read(),v=read();
				pour(u,v);
				break;
			}
		}
	}
	return 0;
}