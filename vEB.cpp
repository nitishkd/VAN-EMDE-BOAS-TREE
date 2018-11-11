#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; 
#define ll long long
#define MAX 1000007
#define INF 1000000000000000LL
#define MOD 1000000007
#define sd(x) scanf("%d",&x)
#define sll(x) scanf("%lld",&x)
#define PB push_back
#define F first
#define S second
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define dd double
#define PI 3.14159265358979323846
#define debug(x) cout<<"Checkpoint : "<<x<<endl
#define setzero(QQ) memset(QQ, 0, sizeof(QQ))
#define setminus(QQ) memset(QQ, -1, sizeof(QQ))
#define setfalse(QQ) memset(QQ, false, sizeof(QQ))
#define foreach(e, x) for (__typeof(x.begin()) e = x.begin(); e != x.end(); ++e)
#define correct(x, y, n, m) (0 <= x && x < n && 0 <= y && y < m)

const int dx[] = {-1, 0, 1,  0};
const int dy[] = { 0, 1, 0, -1};
const int dxK[] = {-1, -1, 0, 1, 1,  1,  0, -1};
const int dyK[] = { 0,  1, 1, 1, 0, -1, -1, -1};

ll n;

struct VBT
{
	ll u;
	ll minm, maxm;
	VBT *summary;
	VBT **cluster;
};

void BUILD(VBT *V, ll x)
{
	V->u = x;
	V->maxm = -1;
	V->minm = -1;
	if(x == 2)
	{
		V->summary = NULL;
		V->cluster = NULL;
	}
	else
	{

		ll k = (ll)sqrt(x);
		VBT *summ = new VBT;
		BUILD(summ, k);
		V->summary = summ;
		VBT **T = new VBT*[k];
		V->cluster = T;
		for(int i =0; i < k; ++i)
		{
			V->cluster[i] = new VBT;
			BUILD(V->cluster[i], k);
		}	
	}
}

ll VBT_MINM(VBT *&V)
{
	return V->minm;
}

ll VBT_MAXM(VBT *&V)
{
	return V->maxm;
}

void insert_empty(VBT *V, ll x)
{
	V->minm = V->maxm = x;
	return;
}

void insert(VBT *V,ll x)
{
    if(V->minm == -1)
		insert_empty(V, x);
	else
	{
    	if(x < V->minm)
    		swap(x, V->minm);
    	if(V->u > 2)
		{
    		ll k = (ll)sqrt(V->u);         
			if(VBT_MINM(V->cluster[x/k]) == -1)
			{
                insert(V->summary, x/k);
				insert_empty(V->cluster[x/k], x%k);	
			}
			else
            	insert(V->cluster[x/k], x%k);
		}
		if(x > V->maxm)
        	V->maxm = x;
	}		
}	

void print(VBT *V, int tabs=0)
{
	if(V != NULL)
	{
		for(int i =0; i < tabs; ++i)
			cout<<"		";
		cout<<"SUMMARY: "<<V->u<<" ( "<<V->minm<<" , "<<V->maxm<<" ) "<<endl;
		if(V->u != 2)
			print(V->summary, tabs + 1);
		if(V->u != 2)
		{
			for(int i =0; i <= tabs; ++i)
				cout<<" 	";
			cout<<"CLUSTER: "<<V->u<<endl;
			ll k = (ll)sqrt(V->u);
			for(int i =0; i < k; ++i)
				print(V->cluster[i], tabs + 1);
		}
	}
	
}

bool isMember(VBT *V, ll x)
{
	if(x == V->minm or x == V->maxm)
		return true;
	if(V->u == 2)
		return false;
	
	ll k = (ll)sqrt(V->u);
	return isMember(V->cluster[x/k], x%k);
}

ll successor(VBT *V, ll x)
{
	if(V->u == 2)
	{
		if(x == 0 and V->maxm == 1)
			return 1;
		else
			return -1;
	}
	else if(V->minm != -1 and x < V->minm)
		return V->minm;
	else
	{
		ll k = (ll)sqrt(V->u);
		ll max_low = VBT_MAXM(V->cluster[x/k]);
		if(max_low != -1 and x%k < max_low)
		{
			ll offset = successor(V->cluster[x/k], x%k);
			return ((x/k)*k + offset);
		}
		else
		{
			ll succ_cluster = successor(V->summary, x/k);
			if(succ_cluster == -1)
				return -1;
			else
			{
				ll offset = VBT_MINM(V->cluster[succ_cluster]);
				return (succ_cluster*k + offset);
			}
		}
	}	
}


void deletes(VBT *V, ll x)
{
	ll k = (ll)sqrt(V->u);
	if(V->minm == V->maxm)
	{
		V->minm = -1;
		V->maxm = -1;
	}
	else if(V->u == 2)
	{
		if(x == 0)
			V->minm = 1;
		else
			V->minm = 0;
		
		V->maxm = V->minm;
	}
	else
	{
		if(x == V->minm)
		{
			ll first_cluster = VBT_MINM(V->summary);
			x = first_cluster*k + VBT_MINM(V->cluster[first_cluster]);
			V->minm = x;
		}
		deletes(V->cluster[x/k], x%k);
		if(VBT_MINM(V->cluster[x/k]) == -1)
		{
			deletes(V->summary, x/k);
			if(x == V->maxm)
			{
				ll summary_maxm = VBT_MAXM(V->summary);
				if(summary_maxm == -1)
					V->maxm = V->minm;
				else
					V->maxm = summary_maxm * k + VBT_MAXM(V->cluster[summary_maxm]);

			}
		}
		else if(x == V->maxm)
			V->maxm = (x/k)*k + VBT_MAXM(V->cluster[x/k]);
	} 
	
}

int main(int argc, char const *argv[])
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);   
    freopen("outputvb.txt", "a", stdout);
	VBT *V = new VBT;
    VBT *head = V;
    BUILD(head, 65536);
     auto start = high_resolution_clock::now();
    int n,m,x;
    cin>>n>>m;
    vector<vector<pair<int,int>>> v1(100005);
    vector<vector<pair<int,int>>> v(100005);
    int visited[100005]={0};
    int w,y,i;
    v1[0].push_back({0,0});
    for(i=0;i<m;i++)
    {
        cin>>x>>y>>w;
        v[x].push_back(make_pair(y,w));
        v[y].push_back(make_pair(x,w));
    }
    int count1=1;
    insert(V,0);
    struct node *root1=NULL;
    int sum=0;
    while(count1!=n+1)
    {
           int temp=VBT_MINM(V);
           int r=v1[temp][0].first;
           int s=v1[temp][0].second;
           bool flag=false;
           if(visited[r]==0)
           {
               int n1=v[r].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v[r][i].first]==0)
                 {
                    v1[v[r][i].second].push_back(make_pair(r,v[r][i].first));
                    if(v1[v[r][i].second].size()==1)
                     insert(V, v[r][i].second);
                }
               }
               visited[r]=1;
               flag=true;
               
           }
           if(visited[s]==0)
           {
               int n1=v[s].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v[s][i].first]==0)
                 {
                    v1[v[s][i].second].push_back(make_pair(s,v[s][i].first));
                    if(v1[v[s][i].second].size()==1)
                    {
                    insert(V, v[s][i].second);
                    }
                 }
                 
               }
               visited[s]=1;
               flag=true;
           }
           if(flag==true)
        {
               sum=sum+temp;
            count1++;
        }
           v1[temp].erase(v1[temp].begin());
           if(v1[temp].size()==0)
           deletes(V, temp);
    }
    // cout<<sum<<endl;
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    cout<<duration.count()<<endl;
	
}