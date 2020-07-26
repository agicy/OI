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

const int MAXSIZE=7;

const char dic[]="ABCDEFGH";

struct Node{
	int a[MAXSIZE][MAXSIZE];
	inline void Read(void){
		a[0][2]=read();
		if(a[0][2]==0)
			exit(0);
		a[0][4]=read();
		a[1][2]=read();
		a[1][4]=read();
		for(reg int i=0;i<MAXSIZE;++i)
			a[2][i]=read();
		a[3][2]=read();
		a[3][4]=read();
		for(reg int i=0;i<MAXSIZE;++i)
			a[4][i]=read();
		a[5][2]=read();
		a[5][4]=read();
		a[6][2]=read();
		a[6][4]=read();
		return;
	}
	inline int GetVal(void){
		int T[4];
		memset(T,0,sizeof(T));
		++T[a[2][2]],++T[a[2][3]],++T[a[2][4]];
		++T[a[3][2]],++T[a[3][4]];
		++T[a[4][2]],++T[a[4][3]],++T[a[4][4]];
		reg int Max=0,pos=-1;
		for(reg int i=1;i<=3;++i)
			if(T[i]>Max){
				Max=T[i],pos=i;
			}
		reg int res=0;
		for(reg int i=1;i<=3;++i)
			if(i!=pos)
				res+=T[i];
		return res;
	}
	inline void change(reg int i){
		reg int temp;
		switch(i){
			case 0:
				temp=a[0][2];
				for(reg int j=0;j<MAXSIZE-1;++j)
					a[j][2]=a[j+1][2];
				a[MAXSIZE-1][2]=temp;
				break;
			case 1:
				temp=a[0][4];
				for(reg int j=0;j<MAXSIZE-1;++j)
					a[j][4]=a[j+1][4];
				a[MAXSIZE-1][4]=temp;
				break;
			case 2:
				temp=a[2][MAXSIZE-1];
				for(reg int j=MAXSIZE-1;j>0;--j)
					a[2][j]=a[2][j-1];
				a[2][0]=temp;
				break;
			case 3:
				temp=a[4][MAXSIZE-1];
				for(reg int j=MAXSIZE-1;j>0;--j)
					a[4][j]=a[4][j-1];
				a[4][0]=temp;
				break;
			case 4:
				temp=a[MAXSIZE-1][4];
				for(reg int j=MAXSIZE-1;j>0;--j)
					a[j][4]=a[j-1][4];
				a[0][4]=temp;
				break;
			case 5:
				temp=a[MAXSIZE-1][2];
				for(reg int j=MAXSIZE-1;j>0;--j)
					a[j][2]=a[j-1][2];
				a[0][2]=temp;
				break;
			case 6:
				temp=a[4][0];
				for(reg int j=0;j<MAXSIZE-1;++j)
					a[4][j]=a[4][j+1];
				a[4][MAXSIZE-1]=temp;
				break;
			case 7:
				temp=a[2][0];
				for(reg int j=0;j<MAXSIZE-1;++j)
					a[2][j]=a[2][j+1];
				a[2][MAXSIZE-1]=temp;
				break;
			default:
				break;
		}
		return;
	}
};

Node a;
int id;
char ans[1048576];
int last;

inline bool DFS(reg int dep,Node a){
	if(dep+a.GetVal()>id+1){
		return false;
	}
	if(dep==id+1){
		if(a.GetVal()==0){
			last=a.a[2][2];
			return true;
		}
		return false;
	}
	for(reg int i=0;i<8;++i){
		Node temp=a;
		temp.change(i);
		ans[dep]=dic[i];
		if(DFS(dep+1,temp))
			return true;
	}
	return false;
}

int main(void){
	while(true){
		memset(ans,0,sizeof(ans));
		a.Read();
		for(reg int i=0;;++i){
			id=i;
			if(DFS(1,a)){
				if(i==0){
					puts("No moves needed");
					printf("%d\n",last);
				}
				else{
					puts(ans+1);
					printf("%d\n",last);
				}
				break;
			}
		}
	}
	return 0;
}
