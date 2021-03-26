#define LAL
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const double eps=1e-4;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

inline double sqr(reg double x){
	return x*x;
}

struct Vector{
	double x,y;
	inline Vector(reg double x=0,reg double y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
	inline Vector operator/(reg double a)const{
		return Vector(x/a,y/a);
	}
	inline double len(void)const{
		return sqrt(sqr(x)+sqr(y));
	}
};

inline double dot(const Vector& a,const Vector& b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}

inline double cross(const Vector& a,const Vector& b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

typedef Vector Point;

inline double getDis(const Point& a,const Point& b){
	return (a-b).len();
}

inline double getAng(const Point& a,const Point& b){
	return atan2(a.y-b.y,a.x-b.x);
}

Point s;

inline bool cmp(const Point& a,const Point& b){
	return sgn(getAng(a,s)-getAng(b,s))==-1||(sgn(getAng(a,s)-getAng(b,s))==0&&sgn(getDis(a,s)-getDis(b,s))==-1);
}

struct Poly{
	int n;
	vector<Point> V;
	inline void Read(void){
		n=read();
		V.resize(n);
		for(reg int i=0;i<n;++i)
			V[i].x=read(),V[i].y=read();
		return;
	}
	inline vector<double> getF(void){
		reg double Max=0;
		s=Point(0,0);
		for(reg int i=0;i<n;++i)
			s=s+V[i];
		s=s/n;
		for(reg int i=0;i<n;++i)
			Max=max(Max,getDis(V[i],s));
		for(reg int i=0;i<n;++i)
			V[i]=(V[i]-s)/Max;
		s=Point(0,0);
		sort(V.begin(),V.end(),cmp);
		vector<double> res;
		res.resize(n<<2);
		for(reg int i=0;i<n;++i){
			reg double len=getDis(V[i],s);
			reg double ang=dot(V[i]-s,V[(i+1)%n]-s)/getDis(V[i],s)/getDis(V[(i+1)%n],s);
			res[i<<1]=len,res[i<<1|1]=ang;
			res[(i<<1)+(n<<1)]=len,res[(i<<1|1)+(n<<1)]=ang;
		}
		return res;
	}
};

inline vector<int> getKMP(const vector<double>& s){
	vector<int> kmp;
	reg int siz=s.size();
	kmp.resize(siz);
	kmp[0]=-1;
	for(reg int i=1,j=-1;i<siz;++i){
		while(j>=0&&sgn(s[i]-s[j+1])!=0)
			j=kmp[j];
		if(sgn(s[i]-s[j+1])==0)
			++j;
		kmp[i]=j;
	}
	return kmp;
}

inline bool check(const vector<double>& s,const vector<double>& t){
	vector<int> kmp=getKMP(t);
	reg int sizt=t.size();
	for(reg int i=0,j=-1,siz=s.size();i<siz;++i){
		while(j>=0&&sgn(t[j+1]-s[i])!=0)
			j=kmp[j];
		if(sgn(s[i]-t[j+1])==0)
			++j;
		if(j==sizt-1)
			return true;
	}
	return false;
}

inline void print(const vector<double>& a){
	for(reg int i=0,siz=a.size();i<siz;++i)
		printf("%.2lf%c",a[i],i==siz-1?'\n':' ');
	return;
}

Poly a,b;

signed main(void){
	a.Read();
	vector<double> s=a.getF();
	//print(s);
	reg int t=read();
	while(t--){
		b.Read();
		if(a.n!=b.n)
			puts("NIE");
		else{
			vector<double> t=b.getF();
			t.resize(b.n<<1);
			reg bool ans=false;
			if(!ans)
				for(reg int i=0,siz=s.size();i+t.size()<siz;++i){
					reg bool flag=true;
					for(reg int j=i;j<i+t.size();++j)
						if(sgn(s[j]-t[j-i])!=0){
							flag=false;
							break;
						}
					if(flag)
						ans=true;
				}
			reverse(t.begin(),t.end());
			if(!ans)
				for(reg int i=0,siz=s.size();i+t.size()<siz;++i){
					reg bool flag=true;
					for(reg int j=i;j<i+t.size();++j)
						if(sgn(s[j]-t[j-i])!=0){
							flag=false;
							break;
						}
					if(flag)
						ans=true;
				}
			if(!ans)
				puts("NIE");
			else
				puts("TAK");
		}
	}
	return 0;
}