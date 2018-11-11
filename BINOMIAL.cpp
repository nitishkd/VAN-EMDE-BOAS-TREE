#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono; 
#define debug(x) cout<<"Checkpoint : "<<x<<endl

struct node
{
	int data;
	int degree;
	struct node *child;
	struct node *sibling;
	struct node *parent;
};

class binomialheap
{
	public:
	
	node *head;
	
	binomialheap()
	{
		head=NULL;
	}
	
	node *createnode(int  key)
	{
		node *root;
		root=new node;
		root->child=root->sibling=root->parent=NULL;
		root->degree=0;
		root->data=key;
		return root;
	}
	
	void insert(node *root)
	{
		head=merge(head, root);
		// cout<<"CP1"<<endl;
		head=align(head);
		// cout<<"CP2"<<endl;
	}
	
	int printmin()
	{
		int min;
		node *temp;
		temp=head;
		if(!head)
			return INT_MAX;
		min=head->data;
		head=head->sibling;
		while(head)
		{
			if(head->data<min)
				min=head->data;
			head=head->sibling;
		}
		head=temp;
		return min;
	}
	
	int printheadnode()
	{
		node *temp;
		temp=head;
		if(!head)
			return INT_MAX;
		head=temp;
		return head->data;
	}
	
	node *merge(node *root1, node *root2)
	{
		node *head1;
		node *temp;
		if(!root1)
			return root2;
		if(!root2)
			return root1;
		if(root1->degree<=root2->degree)
		{
			head1=root1;
			root1=root1->sibling;
		}
		else
		{
			head1=root2;
			root2=root2->sibling;
		}
		temp=head1;
		while(root1 && root2)
		{
			if(root1->degree<=root2->degree)
			{
				temp->sibling=root1;
				root1=root1->sibling;
			}
			else
			{
				temp->sibling=root2;
				root2=root2->sibling;
			}
			temp=temp->sibling;
		}
		if(root1)
			temp->sibling=root1;
		else temp->sibling=root2;
		return head1;
	}
	
	node *align(node *root)
	{
		node *temp;
		node *prev;
		node *current;
		node *next;
		node *head1;
		prev=NULL;
		current=root;
		next=current->sibling;
		if(!root->sibling)
			return root;
		while(next)
		{
			if(current->degree!=next->degree)
			{
				if(!prev)
					head1=current;
				prev=current;
				current=next;
				next=next->sibling;
			}
			else
			{
				if(next->sibling && next->sibling->degree==current->degree)
				{
					if(!prev)
						head1=current;
					prev=current;
					current=next;
					next=next->sibling;
				}
				else
				{
					if(current->data>next->data)
					{
						if(prev)
							prev->sibling=next;
						current->sibling=NULL;
						link(next, current);
						current=next;
						next=next->sibling;
					}
					else
					{
						current->sibling=next->sibling;
						next->sibling=NULL;
						link(current, next);
						next=current->sibling;
					}
				}
			}
		}
		if(!prev)
			head1=current;
		return head1;
	}
	
	void link(node *root1, node *root2)
	{
		root1->degree++;
		root2->parent=root1;
		if(!root1->child)
		{
			root1->child=root2;
			return;
		}
		root1=root1->child;
		while(root1->sibling)
			root1=root1->sibling;
		root1->sibling=root2;
	}
	
	node *extractmin()
	{
		node *temp;
		node *x;
		if(!head)
			return NULL;
		getmin(temp);
		if(temp==head)
		{
			head=head->sibling;
			if(!head && temp->degree==0)
				return temp;
		}
		else
		{
			x=head;
			while(x->sibling!=temp)
				x=x->sibling;
			x->sibling=x->sibling->sibling;
		}
		temp->sibling=NULL;
		x=temp->child;
		while(x)
		{
			x->parent=NULL;
			x=x->sibling;
		}
		x=temp->child;
		temp->child=NULL;
		head=merge(head, x);
		head=align(head);
		temp->degree=0;
		return temp;
	}
	
	void getmin(node *&minimum)
	{
		int min;
		node *temp;
		if(head == NULL)
			debug(12384510);
		temp=head;
		min=head->data;
		minimum=head;
		head=head->sibling;
		while(head)
		{
			if(head->data<min)
			{
				min=head->data;
				minimum=head;
			}
			head=head->sibling;
		}
		head=temp;
	}
	
	bool found(node *root, int key)
	{
		if(!root)
			return false;
		while(root)
		{
			if(root->data==key)
			{
				root->data=INT_MIN;
				while(root->parent)
				{
					root->data=root->parent->data;
					root->parent->data=INT_MIN;
					root=root->parent;
				}
				return true;
			}
			else if(root->data<key)
				if(found(root->child, key))
					return true;
			root=root->sibling;
		}
		return false;
	}
	
	bool search(node *root, int key, node *&temp)
	{
		if(!root)
			return false;
		while(root)
		{
			if(root->data==key)
			{
				temp=root;
				root->data=INT_MIN;
				while(root->parent)
				{
					root->data=root->parent->data;
					root->parent->data=INT_MIN;
					root=root->parent;
				}
				return true;
			}
			else if(root->data<key)
				if(found(root->child, key))
					return true;
			root=root->sibling;
		}
		return false;
	}
};


int main()
{
	freopen("outputbino.txt", "a", stdout);
	
	binomialheap bh;
	node *root;	
	auto start = high_resolution_clock::now();
    int n,m,x;
    cin>>n>>m;
    vector<vector<pair<int,int>>> v1(100005);
    vector<vector<pair<int,int>>> v(100005);
    int visited[100005];
    memset(visited, 0, sizeof visited);
    int w,y,i;
    v1[0].push_back({0,0});
    for(i=0;i<m;i++)
    {
        cin>>x>>y>>w;
        // --x; --y;
        v[x].push_back(make_pair(y,w));
        v[y].push_back(make_pair(x,w));
    }
    int count1=1;
    root=bh.createnode(0);
    bh.insert(root);

    int sum=0;
    set<int> KK;
    // d/ebug(0);
    while(count1!=n+1)
    {
    	   // Node *temp = getMin(_heap);
    		// debug(1);

    		node *temp;
           	bh.getmin(temp);   
           int CURR = temp->data;
           int r=v1[temp->data][0].first;
           int s=v1[temp->data][0].second;
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
                    {
                     KK.insert(v[r][i].second);
                    }
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
                    	KK.insert(v[s][i].second);
                    }
                 }
                 
               }
               visited[s]=1;
               flag=true;
           }
           if(flag==true)
        	{
               sum=sum+temp->data;
               count1++;
        	}
        	
           v1[temp->data].erase(v1[temp->data].begin());

           // v1[temp->data].clear();
           if(v1[temp->data].size()==0)
           {	
           		root=bh.extractmin();
           		
           }
           for(auto it = KK.begin(); it != KK.end(); ++it)
	           {
	           		      root=bh.createnode(*it);
						    bh.insert(root);
	           }
	           KK.clear();
    }
    
    // cout<<sum<<endl;
     auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
  
    cout<< duration.count() <<endl;
		
		
	return 0;
}

