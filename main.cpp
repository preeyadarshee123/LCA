#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//#include <functional>
#define pb                    push_back
#define ll                    long long
#define ss                       second
#define ff                        first
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define eps                   0.000000001
#define all(c)               (c).begin(),(c).end()
#define present(c,x)         ((c).find(x) != (c).end())
#define cpresent(c,x)        (find(all(c),x) != (c).end())
//#define pi                   pair<int,int>
#define pll                  pair<ll,ll>
#define endl                 '\n'
#define ull                  unsigned long long
using namespace std;
vector<string> split(const string& s, char c) {
    vector<string> v; stringstream ss(s); string x;
    while (getline(ss, x, c)) v.emplace_back(x); return move(v);
}
template<typename T, typename... Args>
inline string arrStr(T arr, int n) {
    stringstream s; s << "[";
    for(int i = 0; i < n - 1; i++) s << arr[i] << ",";
    s << arr[n - 1] << "]";
    return s.str();
}

#define debug(args...) {__evars_begin(__LINE__); __evars(split(#args, ',').begin(), args);}

inline void __evars_begin(int line) { cerr << "#" << line << ": "; }
template<typename T> inline void __evars_out_var(vector<T> val) { cerr << arrStr(val, val.size()); }
template<typename T> inline void __evars_out_var(T* val) { cerr << arrStr(val, 10); }
template<typename T> inline void __evars_out_var(T val) { cerr << val; }
inline void __evars(vector<string>::iterator it) { cerr << endl; }

template<typename T, typename... Args>
inline void __evars(vector<string>::iterator it, T a, Args... args) {
    cerr << it->substr((*it)[0] == ' ', it->length()) << "=";
    __evars_out_var(a);
    cerr << "; ";
    __evars(++it, args...);
}
//using namespace __gnu_pbds;
//typedef tree<int, null_type, int>, rb_tree_tag,tree_order_statistics_node_update> policy;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef vector< int > vi;
typedef vector< vi > vvi;
int dx[8]={1,-1,0,0,1,1,-1,-1};
int dy[8]={0,0,-1,1,2,-2,2,-2};
vector<int> vis(200010,0),dis(200010,0),par(200010,0),ed(200010,0);
vector<pair<int,int>> adj[200010];
vector<vector<int>> ad;
int myrandom (int i) { return std::rand()%i;}
const int MAX=200010;
const ull inf = 1000000007;
class dsu{
    public :
    vector<int> par,sz;
    void init(int n){
        par.assign(n,0);
        sz.assign(n,1);
        for(int i = 1;i < n;i++){
            par[i] = i;
        }
    }
    int find(int a){
        if(a == par[a])
            return a;
        else
            return par[a] = find(par[a]);
    }
    int uni(int a,int b){
        a = find(a);
        b = find(b);
        if(a == b)
            return 0;
        if(sz[a] < sz[b])
            swap(a,b);
        par[b] = a;
        sz[a] += sz[b];
        return 1;
    }
};
void dfs(int a,int p){
    for(auto i: adj[a]){
        if(i.first != p){
            par[i.first] = a;
            ed[i.first] = i.second;
            dis[i.first] = dis[a] + 1;
            dfs(i.first,a);
        }
    }
}
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
class SegTree{
    public :
    vector<ll> t,a;
    void init(int sz,vector<int> &v){
        t.resize(4*sz);
        a.resize(sz+1);
        for(int i = 1;i <= sz;i++){
            a[i] = v[i];
        }
    }
    void build(int v,int l,int r){
        if(l==r){
            t[v]=a[l];
            return ;
        }
        int mid=(l+r)/2;
        build(2*v,l,mid);
        build(2*v+1,mid+1,r);
        t[v]=max(t[2*v],t[2*v+1]);
    }
    void upd(int v,int l,int r,int id){
        if(l == r){
            t[v]  = a[l];
            //cout<<t[v]<<endl;
            return ;
        }
        int mid = (l+r)/2;
        if(mid < id)
            upd(2*v+1,mid+1,r,id);
        else
            upd(2*v,l,mid,id);
        t[v] = max(t[2*v] , t[2*v+1]);
    }
    ll query(int v,int l,int r,int a,int b){
        if(l > r || l > b || r < a)
            return 0;
        if(l >= a && r <= b){
            return t[v];
        }
        int mid=(l+r)/2;
        return max(query(2*v+1, mid+1, r, a,b),query(2*v, l, mid, a,b));
    }
};
class HLD{
    public :
    vector<int> parent, depth, heavy, head, pos;
    int cur_pos;
    int dfs(int v, vector<vector<int>> const& adj) {
        int size = 1;
        int max_c_size = 0;
        for (int c : adj[v]) {
            if (c != parent[v]) {
                parent[c] = v, depth[c] = depth[v] + 1;
                int c_size = dfs(c, adj);
                size += c_size;
                if (c_size > max_c_size)
                    max_c_size = c_size, heavy[v] = c;
            }        }
        return size;
    }
    void decompose(int v, int h, vector<vector<int>> const& adj) {
        head[v] = h, pos[v] = cur_pos++;
        if (heavy[v] != -1)
            decompose(heavy[v], h, adj);
        for (int c : adj[v]) {
            if (c != parent[v] && c != heavy[v])
                decompose(c, c, adj);
        }
    }
    
    void init(vector<vector<int>> const& adj) {
        int n = adj.size();
        parent = vector<int>(n);
        depth = vector<int>(n);
        heavy = vector<int>(n, -1);
        head = vector<int>(n);
        pos = vector<int>(n);
        cur_pos = 1;
        
        dfs(1, adj);
        decompose(1, 1, adj);
    }
    int query(int a, int b,SegTree &s) {
        int res = 0;
        int n = (int)parent.size();
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            int cur_heavy_path_max = s.query(1,1,n-1,pos[head[b]], pos[b]);
            res = max(res, cur_heavy_path_max);
        }
        if (depth[a] > depth[b])
            swap(a, b);
        int last_heavy_path_max = s.query(1,1,n-1,pos[a], pos[b]);
        res = max(res, last_heavy_path_max);
        return res;
    }
    
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //ifstream fin;
    //ofstream fout;
    //fin.open("input.txt");
    //fout.open("output.txt");
    //clock_t launch=clock();
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> v(n);
        for(int i = 0;i < n;i++){
            cin>>v[i];
        }
        int maxi = INT_MIN, mini = INT_MAX;
        for(int i = 0;i < n;i++){
            int cnt = 1;
            int max_speed = v[i],min_speed = v[i];
            for(int j = 0;j < i;j++){
                max_speed = max(max_speed , v[j]);
            }
            for(int j = i+1;j < n;j++){
                min_speed = min(min_speed, v[j]);
            }
            for(int j = 0;j < i;j++){
                if(v[j] > min_speed){
                    cnt++;
                }
            }
            for(int j = i+1 ; j < n;j++){
                if(v[j] < max_speed){
                    cnt++;
                }
            }
            maxi = max(maxi,cnt);
            mini = min(mini,cnt);
        }
        cout<<mini<<" "<<maxi<<endl;
    }
    /*
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<vector<int>> edge;
        ad.assign(n+1,vector<int> ());
        for(int i = 1;i < n;i++){
            int a,b,c;
            cin>>a>>b>>c;
            adj[a].pb({b,c});
            adj[b].pb({a,c});
            ad[a].pb(b);
            ad[b].pb(a);
            edge.pb({a,b,c});
        }
        dfs(1,-1);
        LCA l;
        l.build(n+1,par,dis,ed);
        HLD h;
        h.init(ad);
        SegTree s;
        vector<int> a(n+1);
        for(int i = 1;i <= n;i++){
            a[h.pos[i]] = ed[i];
        }
        s.init(n,a);
        s.build(1,1,n);
        while(1){
            string str;
            cin>>str;
            if(str == "DONE")
                break;
            if(str == "QUERY"){
                int a,b;
                cin>>a>>b;
                int lca = l.lca(a,b);
                int he = h.depth[lca];
                if(lca == a){
                    int node2 = l.lift(b,l.dis[b] - he - 1);
                    int maxi = h.query(b,node2,s);
                    cout<<maxi<<endl;
                }
                else if(lca == b){
                    int node1 = l.lift(a,l.dis[a] - he - 1);
                    int maxi = h.query(a,node1,s);
                    cout<<maxi<<endl;
                }
                else{
                    int node1 = l.lift(a,l.dis[a] - he - 1);
                    int node2 = l.lift(b,l.dis[b] - he - 1);
                    int maxi = max(h.query(a,node1,s),h.query(b,node2,s));
                    cout<<maxi<<endl;
                }
                
            }
            else{
                int i,j;
                cin>>i>>j;
                int node1 = edge[i-1][0],node2 = edge[i-1][1];
                if(h.parent[node1] == node2){
                    int p = h.pos[node1];
                    cout<<p<<endl;
                    s.a[p] = j;
                    s.upd(1,1,n,p);
                }
                else{
                    int p = h.pos[node2];
                    s.a[p] = j;
                    s.upd(1,1,n,p);
                }
            }
        }
    }
     */
}
