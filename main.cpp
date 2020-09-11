class LCA{
    public :
    vector<vector<int>> p,ed;
    vector<int> dis;
    int maxi = 0;
    void build(int n,vector<int> &par,vector<int> &d,vector<int> &edge){
        p.assign(n+1,vector<int> (20,-1));
        ed.assign(n+1,vector<int> (20,-1));
        dis.assign(n+1,0);
        for(int i = 1;i < n;i++){
            p[i][0] = par[i];
            dis[i] = d[i];
            ed[i][0] = edge[i];
        }
        for(int j = 1;j < 20;j++){
            for(int i = 1;i < n;i++){
                if(p[i][j-1] != -1){
                    p[i][j] = p[p[i][j-1]][j-1];
                    ed[i][j] = max(ed[i][j-1],ed[p[i][j-1]][j-1]);
                }
            }
        }
    }
    int lift(int a,int dist){
        for(int i = 0;i < 20;i++){
            if(dist&(1<<i)){
                maxi = max(maxi,ed[a][i]);
                a = p[a][i];
            }
        }
        return a;
    }
    int lca(int a,int b){
        if(dis[a] < dis[b]){
            swap(a,b);
        }
        int diff = dis[a] - dis[b];
        a = lift(a,diff);
        if(a == b){
            return a;
        }
        for(int i = 19; i >= 0;i--){
            if(p[a][i] != p[b][i] ){
                a = p[a][i];
                b = p[b][i];
            }
        }
        return p[a][0];
    }
    int find_max(int a,int l){
        int diff = dis[a] - dis[l];
        maxi = 0;
        lift(a,diff);
        return maxi;
    }
};
