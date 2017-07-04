#include <bits/stdc++.h>
using namespace std;

template <class T>
class _set {
public:
	struct Node {
		T val;
		int size, priority;
		Node *left, *right;
		Node(T val):val(val),size(1),priority(rand()),left(0),right(0){}
		void setleft(Node *v) {
			left = v;
			size = 1;
			if (left != 0)
				size += left->size;
			if (right != 0)
				size += right->size;
		}
		void setright(Node *v) {
			right = v;
			size = 1;
			if (left != 0)
				size += left->size;
			if (right != 0)
				size += right->size;
		}
	};

	Node *root;
	_set():root(0){}
	pair<Node*, Node*> split(Node *root, T val) {
		if (root == 0)
			return{ 0,0 };
		if (root->val < val) {
			pair<Node*, Node*> ret = split(root->right, val);
			root->setright(ret.first);
			return{ root,ret.second };
		}
		pair<Node*, Node*> ret = split(root->left, val);
		root->setleft(ret.second);
		return{ ret.first,root };
	}
	Node* insert(Node* root, Node *node) {
		if (root == 0)
			return node;
		if (node->priority > root->priority) {
			pair<Node*, Node*> ret = split(root, node->val);
			node->setleft(ret.first);
			node->setright(ret.second);
			return node;
		}
		if (root->val < node->val)
			root->setright(insert(root->right, node));
		else
			root->setleft(insert(root->left, node));
		return root;
	}
	void insert(T val) {
		root = insert(root, new Node(val));
	}
	Node* merge(Node *a, Node *b) {
		if (a == 0)
			return b;
		if (b == 0)
			return a;
		if (a->priority < b->priority) {
			if (b->val < a->val) {
				b->setright(merge(a, b->right));
				return b;
			}
			b->setleft(merge(a, b->left));
			return b;
		}
		if (a->val < b->val) {
			a->setright(merge(a->right, b));
			return a;
		}
		a->setleft(merge(a->left, b));
		return a;
	}
	Node *erase(Node *root, T val) {
		if (root == 0)
			return 0;
		if (root->val == val) {
			Node *ret = merge(root->left, root->right);
			delete root;
			return ret;
		}
		if (root->val < val)
			root->setright(erase(root->right, val));
		else
			root->setleft(erase(root->left, val));
		return root;
	}
	void erase(T val){
		root=erase(root,val);
	}
	bool find(Node *root, T val) {
		if (root == 0)
			return false;
		if (root->val == val)
			return true;
		if (root->val < val)
			return find(root->right, val);
		return find(root->left, val);
	}
	bool find(T val) {
		return find(root, val);
	}
	int countLessThan(Node *root, T key) {
		if (root == NULL)
			return 0;
		if (root->val <= key)
			return countLessThan(root->right, key);
		int rs = (root->right ? root->right->size : 0);
		return rs + 1 + countLessThan(root->left, key);
	}
	int countLessThan(T key){
		return countLessThan(root,key);
	}
};
_set<int> tree[100005];
int n,m;
void update(int idx,int val){
	idx++;
	while(idx<100005){
		tree[idx].insert(val);
		idx+=idx&(-idx);
	}
}
void erase(int idx,int val){
	idx++;
	while(idx<100005){
		tree[idx].erase(val);
		idx+=idx&(-idx);
	}
}
int query(int idx,int val){
	int ret=0;
	idx++;
	while(idx){
		ret+=tree[idx].countLessThan(val);
		idx-=idx&(-idx);
	}
	return ret;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
		int in;
		scanf("%d",&in);
		update(i,in);
    }
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		printf("%d\n", query(b,c)-query(a-1,c));
	}
    return 0;
}