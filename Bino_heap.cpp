#include<bits/stdc++.h>
using namespace std;
struct node
{
    int data;
    struct node *left;
    struct node* right;
    int deg;
    struct node *parent;
};

list<node*> unionbin(list<node*> base,list<node*> curr )
{
    //kind of merge sort
    list<node*> temp3;
    list<node*>::iterator it=base.begin();
    list<node*>::iterator it1=curr.begin();
    while(it!=base.end()&&it1!=curr.end())
    {
        if((*it)->deg<=(*it1)->deg)
        {
            temp3.push_back(*it);
            it++;
        }
        else
        {
            temp3.push_back(*it1);
            it1++;
        }
    }
    while(it1!=curr.end())
    {
        temp3.push_back(*it1);
        it1++;
    }
    while(it!=base.end())
    {
        temp3.push_back(*it);
        it++;
    }
     return temp3;
     //temp 3 is just collection of dl with non decreasing order of degre of binomial heap
}
node* merge(node *head1,node*head2)
{
    //in order to ensure head1 always less because we are bound to make parent as the one with less value
    if(head2->data<head1->data)
    swap(head1,head2);
     head2->parent=head1;
     //beacuse we are adding head2 at left of head1
     head2->right=head1->left;
     head1->left=head2;
     head1->deg++;
     return head1;
     //kyuki same degree ka ode add kiya therefore degree++
     
}
list<node*> adjust(list<node*> head)
{
    list<node*>::iterator it1=head.begin();
    list<node*>::iterator it2=head.begin();
    list<node*>::iterator it3=head.begin();
    if(head.size()>2)
    {
        it2++;
        it3=it2;
        it3++;
    }
    if(head.size()==2)
    {
        it2++;
        it3=head.end();
    }
    while(it1!=head.end())
    {
        if(it2==head.end())
        {
                it1++;
        }
        else if((*it1)->deg < (*it2)->deg)
        {
            it1++;
            it2++;
            if(it3!=head.end())
            it3++;
        }
        else if((*it1)->deg==(*it2)->deg)
        {
            if(it3!=head.end()&&(*it1)->deg==(*it3)->deg)
            {
                it1++;
                it2++;
                it3++;
            }
            else
            {
                 *it1=merge(*it1,*it2);
                 it2=head.erase(it2);
                 if(it3!=head.end())
                 it3++;
            }
        }
    }
    return head;
}
list<node*> insert(list<node*> head,int x)
{
    node* temp=(node*)malloc(sizeof(node));
    temp->data=x;
    temp->left=NULL;
    temp->right=NULL;
    temp->deg=0;
    temp->parent=NULL;
    list<node*> temp1;
    temp1.push_back(temp);
    temp1=unionbin(head,temp1);
    temp1=adjust(temp1);
    return temp1;
    //head and the current node i.e bascically prev temp1 and new temp1
    

}


////MIN///
node * getmin(list<node*> head)
{
    //get the root of the binomial tree with minimum root value
    //we need to search because we have stored in basis of degree not on basis of data
      node* temp=*head.begin();
      for(auto it=head.begin();it!=head.end();it++)
      {
          if((*it)->data<temp->data)
              temp=*it;
      }
     return temp;
}
list<node*> removemin(node *temp)
{
   list<node*> temp1;
   node*temp2=temp->left;
   node *prev;
   //making collection of all subtree taht came out of deleting the root of the binomial tree taht contain min
   while(temp2)
   {
      prev=temp2;
      temp2=temp2->right;
      prev->right=NULL;
      temp1.push_back(prev);
   }
   return temp1;
}


list<node*> extractmin(list<node*> head)
{
   node *temp=getmin(head);
   list<node*> res;
for(auto it=head.begin();it!=head.end();it++)
{
    if(*it!=temp)
    res.push_back(*it);
}
list<node*> fin=removemin(temp);
res=unionbin(res,fin);
res=adjust(res);
return res;
}


int main()
{
    int n,m,x;
    cin>>n>>m;
    map<int,pair<int,int>> v;

    int visited[100005]={0};
    vector<vector<pair<int,int>>> v1(100005);
    int w,y,i;
    v[0]={0,0};
    for(i=0;i<m;i++)
    {
        cin>>x>>y>>w;
        v[w]=make_pair(y,w);
        v1[x].push_back(make_pair(y,w));
        v1[y].push_back(make_pair(x,w));
    }
    
    int count1=1;
    list<node*> head;
    head=insert(head,0);
    int sum=0;
    while(count1!=n+1)
    {
           node *temp=getmin(head);
           int r=v[temp->data].first;
           int s=v[temp->data].second;
           bool flag=false;
           if(visited[r]==0)
           {
               int n1=v1[r].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v1[r][i].first]==0)
                 {
                     head=insert(head,v1[r][i].second);
                 }
               }
               visited[r]=1;
               flag=true;
               
           }
           if(visited[s]==0)
           {
               int n1=v1[s].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v1[s][i].first]==0)
                 {
                     head=insert(head,v1[s][i].second);
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
          head=extractmin(head);
    }
    cout<<sum<<endl; 
}