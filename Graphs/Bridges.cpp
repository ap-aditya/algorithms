#include<bits/stdc++.h>
using namespace std;

class Bridges {
private:
vector<bool>visited;
vector<int>tin,low;
int timer=1;
void dfs(int node, int parent, vector<vector<int>>&ans,vector<vector<int>>&adj){
    visited[node]=true;
    tin[node]=low[node]=timer++;
    for(auto it:adj[node]){
        if(it==parent)continue;
        if(visited[it]){
            low[node]=min(low[node],low[it]);
        }
        else{
            dfs(it,node,ans, adj);
            low[node]=min(low[node],low[it]);
            if(low[it]>tin[node]){
                ans.push_back({node,it});
            }
        }
    }
    return;
}
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>>adj(n);
        for(auto it:connections){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        visited=vector<bool>(n,false);
        tin=vector<int>(n);
        low=vector<int>(n);
        vector<vector<int>>ans;
        dfs(0,-1,ans,adj);
        return ans;

    }
};