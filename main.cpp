#include<bits/stdc++.h>
using namespace std;
//#include <ext/pb_ds/assoc_container.hpp> // Common file
//#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
//using namespace __gnu_pbds; //  order of key(keys strictly less than)  // find_by_order
//typedef tree<long long,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
//typedef tree<long long, null_type, less_equal<>, rb_tree_tag, tree_order_statistics_node_update> indexed_multiset;
//IF WA CHECK FOR : -
// 1 > EDGE CASES LIKE N=1 , N=0
// 2 > SIGNED INTEGER OVERFLOW IN MOD
// 3 > CHECK THE CODE FOR LOGICAL ERRORS AND SEG FAULTS
// 4 > READ THE PS ONCE AGAIN , if having double diff less than 1e-8 is same.
// 5 > You Have got AC .
#define ll long long
#define NUM (ll)998244353
#define inf (long long)(2e18)
#define ff first
#define ss second
#define f(i,a,b) for(ll i=a;(i)<long(b);(i)++)
#define fr(i,a,b) for(ll i=a;(i)>=(long long)(b);(i)--)
#define it(b)  for(auto &it:(b))
#define pb push_back
#define mp make_pair
typedef vector<ll> vll;
typedef pair<ll,ll> pll;
ll binpow( ll base , ll ex,ll mod=NUM) {
    ll ans = 1;base = base % mod;
    if(base==0){
        return 0;
    }
    while (ex > 0) {
        if (ex % 2 == 1) {
            ans = (ans * base) % mod;
        }
        base = (base * base) % mod;
        ex = ex / 2;
    }
    return ans;
}
void read(vll &arr,ll n) {
    if (arr.size() != n) { arr.assign(n, 0); }for (int i = 0; i < n; i++)cin >> arr[i];
}
inline ll min(ll a,ll b){
    if(a>b)return b;return a;
}
inline ll max(ll a, ll b){
    if(a>b)return a;return b;
}
inline ll dif(ll a,ll b) {
    if (a > b)return a - b;return b - a;
}
long long gcd(long long a,long long b) {
    if (b == 0)return a;return gcd(b, a % b);
}
long long lcm(long long a,long long b) {
    long long k = gcd(a, b);
    return (a * b) / k;
}
vector<vll>adj,jump;
vector<ll>in,out,level;
bool mycmp(ll a,ll b){
    return in[a]<=in[b];
}
ll tim = 0;
void dfs(ll curr,ll par,ll lev=0){
    tim++;in[curr]=tim;level[curr]=lev;
    if(curr!=par){
        jump[curr][0]=par;
        for(ll i=1;i<=30;i++){
            ll node_half = jump[curr][i-1];
            ll node_full = jump[node_half][i-1];jump[curr][i]=node_full;
            if(node_full==-1){
                break;
            }
        }
    }
    it(adj[curr]){
        if(it!=par){
            dfs(it,curr,lev+1);
        }
    }
    out[curr]=++tim;
}
ll jump_it(ll a,ll unit){
    for(ll i=30;i>=0;i--){
        ll x = 1<<i;
        if(x<=unit){
            unit-=x;
            a = jump[a][i];
        }
    }
    return a;
}
ll lca(ll a,ll b){
    if(level[a]>level[b]){
        a = jump_it(a,level[a]-level[b]);
    }
    else if(level[b]>level[a]){
        b = jump_it(b,level[b]-level[a]);
    }
    if(a==b){return a;}
    for(int i=30;i>=0;i--){
        if(jump[a][i]!=jump[b][i]){
            a = jump[a][i];b = jump[b][i];
        }
    }
    return jump[a][0];
}
bool anc(ll a,ll b){
    return in[a]<=in[b] and out[a]>=out[b];
}
void solve() {
    int n;cin>>n;
    adj.resize(n+1);in.resize(n+1);out.resize(n+1);
    jump.resize(n+1,vll(31,-1));level=out;
    f(i,0,n-1){
        ll a,b;cin>>a>>b;adj[a].pb(b);adj[b].pb(a);
    }
    dfs(1,1);// for making the in time and out time
    int query;cin>>query;
    while(query--){
        ll k;cin>>k;vector<ll>nodes;set<ll>final_nodes;
        while(k--){
            ll a;cin>>a;nodes.pb(a);final_nodes.insert(a);
        }
        sort(nodes.begin(),nodes.end(),mycmp);
        f(i,1,nodes.size()){
            final_nodes.insert(lca(nodes[i],nodes[i-1]));
        }
        vector<ll>sorted_acc_in_time(final_nodes.begin(),final_nodes.end());
        sort(sorted_acc_in_time.begin(),sorted_acc_in_time.end(),mycmp);
        // we have recieved the final nodes
        stack<ll>s;s.push(sorted_acc_in_time[0]);
        vector<vll>edges;
        f(i,1,sorted_acc_in_time.size()){
            auto it = sorted_acc_in_time[i];
            while(not anc(s.top(),it)){
                // checking if s.top is the ancestor of it or not
                s.pop();
            }
            edges.pb({s.top(), it});s.push(it);
        }
        //edges finally
        it(edges){
            cout<<it[0]<<" "<<it[1]<<endl;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << showpoint;
    cout << setprecision(12);
    long long test_m = 1;
    int k=1;
    //cin >> test_m;
    //WE WILL WIN .
    while (test_m--) {
        //cout<<"Case #"<<k++<<": ";
        solve();
    }
}