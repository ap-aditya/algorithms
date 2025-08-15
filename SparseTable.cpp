#include<bits/stdc++.h>
using namespace std;
class SparseTable{
private:
    int nmax;
    vector<int>lg;
    vector<vector<int>>st;
    void computelg(int n){
        lg.resize(n+1);
        lg[1]=0;
        for(int i=2;i<=n;i++){
            lg[i]=lg[i/2]+1;
        }
    }
public:
    void build(vector<int>&arr){
        nmax=arr.size();
        computelg(nmax);
        int k=lg[nmax]+1;
        st=vector<vector<int>>(k,vector<int>(nmax));
        copy(arr.begin(),arr.end(),st[0].begin());
        for(int i=1;i<k;i++){
            for(int j=0;j+(1<<i)<=nmax;j++){
                st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
        return;
    }
    int query(int l,int r){
        int len=r-l+1;
        int k=lg[len];
        return min(st[k][l],st[k][r-(1<<k)+1]);
    }

};
int main(){
    vector<int>arr={1,2,3,4,5,6,7,-1,9,10};
    SparseTable st;
    st.build(arr);
    cout<<st.query(0,4)<<endl;
    cout<<st.query(5,9)<<endl;
    return 0;
}