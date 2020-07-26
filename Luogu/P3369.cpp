#include <bits/stdc++.h>
using namespace std;
class Treap
{
	//static const std::size_t MaxN=100000+10;
	bool isempty;
	int cnt = 0;
	struct Node
	{
		//static Node *pt;
		int value, tree_size, rand, times;
		Node *lson, *rson;
		Node(void)
		{
			lson = nullptr;
			rson = nullptr;
		}
		/*~Node(void)
		{
			if (lson != nullptr)
				delete lson;
			if (rson != nullptr)
				delete rson;
		}*/
	} *root, *NIL;

  private:
	inline void __update(Node *Object)
	{
		Object->tree_size = Object->lson->tree_size + Object->rson->tree_size + Object->times;
	} //checked
	inline void __right_rotate(Node *&Object)
	{
		if (Object->lson == NIL)
			return;
		Node *p = Object->lson;
		if (p == NIL)
			return;
		Object->lson = p->rson;
		p->rson = Object;
		p->tree_size = Object->tree_size;
		__update(Object);
		Object = p;
	} //checked
	inline void __left_rotate(Node *&Object)
	{
		if (Object->rson == NIL)
			return;
		Node *p = Object->rson;
		if (p == NIL)
			return;
		Object->rson = p->lson;
		p->lson = Object;
		p->tree_size = Object->tree_size;
		__update(Object);
		Object = p;
	} //checked
	inline void __insert(Node *&Object, int value)
	{
		if (Object == nullptr || Object == NIL)
		{
			Object = new Node;
			Object->lson = NIL;
			Object->rson = NIL;
			Object->times = Object->tree_size = 1;
			Object->value = value;
			Object->rand = std::rand();
			return;
		}
		Object->tree_size++; //checked
		if (Object->value == value)
			Object->times++; //checked
		else if (value > Object->value)
		{
			__insert(Object->rson, value);
			if (Object->rson->rand < Object->rand)
				__left_rotate(Object);
		} //checked
		else
		{
			__insert(Object->lson, value);
			if (Object->lson->rand < Object->rand)
				__right_rotate(Object);
		} //checked
	}
	inline void __erase(Node *&Object, int value)
	{
		if (Object == nullptr || Object == NIL)
			return;
		if (Object->value == value)
		{
			if (Object->times > 1)
			{
				Object->times--;
				__update(Object);
				return;
			}
			if ((Object->lson == NIL && Object->rson == NIL) || (Object->lson == nullptr && Object->rson == nullptr))
			{
				Object = NIL;
				return;
			}
			else if ((Object->lson == NIL || Object->lson == nullptr))
				Object = Object->rson;
			else
				Object = Object->lson;

			//checked
			if (Object->lson->rand < Object->rson->rand)
			{
				__right_rotate(Object);
				__erase(Object->rson, value);
			}
			else
			{
				__left_rotate(Object);
				__erase(Object->lson, value);
			}
			//checked
		}
		else if (value > Object->value)
		{
			Object->tree_size--;
			__erase(Object->rson, value);
		}
		else
		{
			Object->tree_size--;
			__erase(Object->lson, value);
		}
	}
	inline int __query_rank(Node *Object, int value)
	{
		if (Object == nullptr || Object == NIL)
			return 0;
		if (Object->value == value)
			return Object->lson->tree_size + 1;
		else if (value > Object->value)
			return Object->lson->tree_size + Object->times + __query_rank(Object->rson, value);
		else
			return __query_rank(Object->lson, value);
	}//checked
	inline int __query_value(Node *Object, int rank)
	{
		if (Object == nullptr || Object == NIL)
			return 0;
		if (rank < Object->lson->tree_size)
			return __query_value(Object->lson, rank);
		else if (rank > Object->lson->tree_size + Object->times)
			return __query_value(Object->rson, rank - Object->lson->tree_size - Object->times);
		else
			return Object->value;
	}//checked
	inline int __query_prev(int now, Node *Object, int value)
	{
		if (Object == nullptr || Object == NIL)
			return now;
		if (Object->value < value)
		{
			now = Object->value;
			now = __query_prev(now, Object->rson, value);
		}
		else
			now = __query_prev(now, Object->lson, value);
		return now;
	}
	inline int __query_next(int now, Node *Object, int value)
	{
		if (Object == nullptr || Object == NIL)
			return now;
		if (Object->value > value)
		{
			now = Object->value;
			now = __query_next(now, Object->lson, value);
		}
		else
			now = __query_next(now, Object->rson, value);
		return now;
	}

  public:
	Treap(void)
	{
		isempty = true;
		NIL = new Node;
		NIL->lson = NIL;
		NIL->rson = NIL;
	}
	~Treap(void)
	{
		if (root != nullptr)
			delete root;
		if (NIL != nullptr)
			delete NIL;
	}
	inline void insert(int value)
	{
		__insert(root, value);
	}
	inline void erase(int value)
	{
		__erase(root, value);
	}
	inline int kth(int value)
	{
		return __query_rank(root, value);
	}
	inline int query(int rank)
	{
		return __query_value(root, rank);
	}
	inline int prev(int value)
	{
		return __query_prev(0, root, value);
	}
	inline int next(int value)
	{
		return __query_next(0, root, value);
	}
} Test;
int main()
{

	std::srand(time(0));
	int tot;
	scanf("%d", &tot);
	for(int i=0;i<tot;i++){
		static int option,num;
		scanf("%d%d",&option,&num);
		if(option==1)
			Test.insert(num);
		else if(option==2)
			Test.erase(num);
		else if(option==3)
			printf("%d\n",Test.kth(num));
		else if(option==4)
			printf("%d\n",Test.query(num));
		else if(option==5)
			printf("%d\n",Test.prev(num));
		else if(option==6)
			printf("%d\n",Test.next(num));
	}
	system("pause");
	return 0;
}