#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define graph vector<vector<pair<int,int>>>
#define vvi vector<vector<int>>
#define vvl vector<vector<ll>>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>
#define pb push_back
#define eb emplace_back
#define loop(i,n) for(int i = 0; i < n; i++)
#define INF 1e10

#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;
class SegmentTree{
private:
    int n;
    static const int identity=0;
public:
    struct Node{
        int val;
        bool lazy;
        int unprop;
        Node(int num){
            val=num;
            lazy=false;
            unprop=identity;
        }
        Node(){
            val=identity;
            lazy=false;
            unprop=identity;
        }
    };
    vector<Node>tree;
    SegmentTree(int size){
        n=size;
        tree.resize(4*n+1);
    }
    void merge(Node* child1, Node* child2, Node* parent){
        parent->val=child1->val + child2->val;
    }
    void build(vi &arr,int v,int tl,int tr){
       if(tl==tr){
            Node newnode(arr[tl]);
            tree[v]=newnode;
            return;
       }
       int tm=(tl+tr)/2;
       build(arr,2*v,tl,tm);
       build(arr,2*v+1,tm+1,tr);
       Node newnode=Node();
       merge(&tree[2*v],&tree[2*v+1],&newnode);
       tree[v]=newnode;
    }
    void apply(int v,int tl,int tr,int num){
        if(tl!=tr){
            tree[v].lazy=true;
            tree[v].unprop=num;
        }
        tree[v].val=num*(tr-tl+1);
    }
    void pushdown(int v, int tl,int tr){
        if(tree[v].lazy==false)return;
        tree[v].lazy=false;
        int tm=(tl+tr)/2;
        apply(2*v,tl,tm,tree[v].unprop);
        apply(2*v+1,tm+1,tr,tree[v].unprop);
        tree[v].unprop=identity;
    }
    void update(int v,int tl,int tr,int l,int r,int num){
        if(l<=tl && tr<=r){
            apply(v,tl,tr,num);
            return;
        }
        if(tl>r || tr<l)return;
        pushdown(v,tl,tr);
        int tm=(tl+tr)/2;
        update(2*v,tl,tm,l,r,num);
        update(2*v+1,tm+1,tr,l,r,num);
        merge(&tree[2*v],&tree[2*v+1],&tree[v]);
    }
    int query(int v,int tl,int tr,int l,int r){
        if(l<=tl && tr<=r){
            return tree[v].val;
        }
        if(tl>r || tr<l)return identity;
        pushdown(v,tl,tr);
        int tm=(tl+tr)/2;
        int leftans=query(2*v,tl,tm,l,r);
        int rightans=query(2*v+1,tm+1,tr,l,r);
        return leftans+rightans;
    }

    void build(vi &arr){
        build(arr,1,0,n-1);
    }
    void update(int l,int r, int num){
        update(1,0,n-1,l,r,num);
    }
    int query(int l,int r){
        return query(1,0,n-1,l,r);
    }

};
int main(){
    int n=10;
    cout<<"Hello"<<endl;
    vi arr={1,1,1,1,1,1,1,1,1,1};
    SegmentTree st(n);
    st.build(arr);
    cout<<st.query(0,5)<<endl;
    st.update(0,4,2);
    cout<<st.query(3,6)<<endl;
    return 0;
}