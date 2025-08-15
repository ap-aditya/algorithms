#include<bits/stdc++.h>
using namespace std;

class Articulation {
  private:
    vector<bool>visited;
    vector<int>tin,low;
    vector<bool>mark;
    int timer=0;
    void dfs(int node, int parent,vector<int>adj[]){
        visited[node]=true;
        tin[node]=low[node]=timer++;
        int child=0;
        for(auto it:adj[node]){
            if(it==parent)continue;
            if(visited[it]){
                low[node]=min(low[node],tin[it]);
                // See the difference from bridges
                // We do not compare with low
            }
            else{
                child++;
                dfs(it,node,adj);
                low[node]=min(low[node],low[it]);
                if(low[it]>=tin[node] && parent!=-1)mark[node]=true;
            }
        }
        if(parent==-1 && child>1)mark[node]=true;
        return;
    }
  public:
    vector<int> articulationPoints(int V, vector<int> adj[]) {
       visited=vector<bool>(V,false);
       mark=vector<bool>(V,false);
       tin=vector<int>(V);
       low=vector<int>(V);
       dfs(0,-1,adj);
       vector<int>ans;
       for(int i=0;i<V;i++){
           if(mark[i])ans.push_back(i);
       }
       if(ans.size()==0)return vector<int>{-1};
       return ans;
        
    }
};