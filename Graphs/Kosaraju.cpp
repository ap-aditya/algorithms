#include<bits/stdc++.h>
using namespace std;
class SCC {
  private:
    stack<int>s;
    vector<bool>visited;
    void dfs(int node,vector<vector<int>> &adj){
        visited[node]=true;
        for(auto it:adj[node]){
            if(visited[it])continue;
            dfs(it,adj);
        }
        s.push(node);
        return;
    }
    void dfsK(int node, vector<vector<int>>&adj,vector<int>&t){
        visited[node]=true;
        t.push_back(node);
        for(auto it:adj[node]){
            if(visited[it])continue;
            dfsK(it,adj,t);
        }
        return;
    }
  public:
    int kosaraju(vector<vector<int>> &adj) {
        int n=adj.size();
        visited=vector<bool>(n,false);
        for(int i=0;i<n;i++){
            if(!visited[i])dfs(i,adj);
        }
        visited=vector<bool>(n,false);
        vector<vector<int>>revadj(n);
        for(int i=0;i<n;i++){
            for(auto it:adj[i]){
                revadj[it].push_back(i);
            }
        }
        vector<vector<int>>ans;
        while(!s.empty()){
            int node=s.top();
            s.pop();
            if(visited[node])continue;
            vector<int>t;
            dfsK(node,revadj,t);
            ans.push_back(t);
        }
        return ans.size();
        
    }
};