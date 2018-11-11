#include<bits/stdc++.h>
#define debug(x) cout<<"Checkpoint : "<<x<<endl

using namespace std;
using namespace std::chrono; 
int count1=0;
struct node
{
    int data;
    struct node *left,*right;
    int h;
    vector<pair<int,int>> start;
    
    struct node *parent;
    int k;
    int c;
};
bool traverse(struct node* root,int value)
{
    if(root->data==value)
        return true;
    else if(root->left==NULL&&root->right==NULL)
        return false;
    else if(root->left==NULL&&value<root->data)
        return false;
    else if(root->right==NULL&&value>root->data)
        return false;
    else if(value<root->data)
        return traverse(root->left,value);
    else
        return traverse(root->right,value);
}
int height(struct node *root)
{
    if(root==NULL)
    return 0;
    else
    return root->h;
}
int k_cal(struct node *root)
{
    if(root==NULL)
    return 0;
    else
    return root->k;
}
int balance_factor(struct node * root)
{
    int x,y;
    if(root->left!=NULL)
     x=root->left->h;
    else
      x=0;
    if(root->right!=NULL)
       y=root->right->h;
    else
        y=0;
    return x-y;
}

struct node* rotate_left(struct node *root)
{
        struct node *temp,*temp1;
        temp=root->right;
        temp1=root->right->left;
        temp->left=root;
        root->right=temp1;
      root->h = max(height(root->left),height(root->right))+1;
      root->k=k_cal(root->left)+k_cal(root->right)+1;
      temp->h = max(height(temp->left),height(temp->right))+1;
      temp->k=k_cal(temp->left)+k_cal(temp->right)+1;
        return temp;
}
struct node* rotate_right(struct node *root)
{
        struct node *temp,*temp1;
        temp=root->left;
        temp1=root->left->right;
        temp->right=root;
        root->left=temp1;
       
      root->h = max(height(root->left),height(root->right))+1;
      root->k=k_cal(root->left)+k_cal(root->right)+1;
      temp->h = max(height(temp->left),height(temp->right))+1;
      temp->k=k_cal(temp->left)+k_cal(temp->right)+1;
      return temp;
}
struct node* insert(struct node *root,int x,int y,int value)
{

    if(root==NULL)
    {
        struct node *temp;
    temp= new node;
    temp->data=value;
    temp->left=NULL;
    temp->right=NULL;
    temp->h=1;
    temp->k=1;
         temp->start.clear();
        temp->start.push_back(make_pair(x,y));
         temp->c=1;
        return temp;
    }
    if(value==root->data)
    {
        root->start.push_back(make_pair(x,y));
        root->c+=1;
    }
    else if(value<root->data)
           { 
               root->left=insert(root->left,x,y,value);
               root->left->parent=root;
           }
    else
        {
            root->right=insert(root->right,x,y,value);
            root->right->parent=root;
        }
    
    root->h=max(height(root->left),height(root->right))+1;
    root->k=k_cal(root->left)+k_cal(root->right)+1;
    int l=height(root->left);
    int r=height(root->right);
    if(l-r>1)
    {
       
       int l1=balance_factor(root->left);
       if(l1>=0)
       {
              return rotate_right(root);
       }
       else
       {
             root->left=rotate_left(root->left);
             root->left->parent=root;
             return rotate_right(root);
       }
    }
    if(r-l>1)
    {
       
       int l1=balance_factor(root->right);
       if(l1>=0)
       {
               root->right=rotate_right(root->right);
               root->right->parent=root;
             return rotate_left(root);
       }
       else
       {
           return rotate_left(root); 
       }
    }
    return root;
   
 }
void inorder(struct node *head)
{
  if(head==NULL)
    return;
    
  inorder(head->left);
  printf("%d ",head->data);
  inorder(head->right);
}

struct node * inorder_succ(struct node* root)
{
    struct node* temp=root;
    while (temp->left != NULL)
        temp = temp->left;
 
    return temp;
}

struct node* delete1(struct node* root,int start1,int end1, int value)
{
 
    if (root == NULL)
    {
        return root;
    }
    else if ( value < root->data )
        root->left = delete1(root->left,start1,end1,value);
    else if( value > root->data )
        root->right = delete1(root->right,start1,end1,value);
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
           struct node *temp;
          if(root->left==NULL&&root->right==NULL)
          temp=NULL;
          else if(root->left!=NULL)
          temp=root->left;
          else
          temp=root->right;
 
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
             *root = *temp; 
            free(temp);
        }
        else
        {
            struct node* temp = inorder_succ(root->right);
             root->data = temp->data;
             root->start.clear();
             for(int i=0;i<temp->c;i++)
             {
                 root->start.push_back(temp->start[i]);
             }
            root->c=temp->c;
            root->right = delete1(root->right,start1,end1,temp->data);
        }
    }
 
    if (root == NULL)
      return root;
    
 
root->h=max(height(root->left),height(root->right))+1;
    root->k=k_cal(root->left)+k_cal(root->right)+1;
    int l=height(root->left);
    int r=height(root->right);
  if(l-r>1)
  {
       
       int l1=balance_factor(root->left);
       if(l1>=0)
       {
              return rotate_right(root);
       }
       else
       {
             root->left=rotate_left(root->left);
             root->left->parent=root;
             return rotate_right(root);
       }
  }
  if(r-l>1)
  {
       
       int l1=balance_factor(root->right);
       if(l1>=0)
       {
               root->right=rotate_right(root->right);
               root->right->parent=root;
             return rotate_left(root);
       }
       else
       {
           return rotate_left(root); 
       }
  }
  return root;
   
 }

struct node* kthmin(struct node *root,int y)
{
    int t=k_cal(root->left);
   if(t==y-1)
   return root;
   else if(t>y-1)
   {
   return kthmin(root->left,y);
   }
   else
   {
   return kthmin(root->right,y-(t)-1);
   }
   
   
}
int main()
{
    freopen("outputavl.txt", "a", stdout);
    auto start = high_resolution_clock::now(); 
    int n,m,x;
    cin>>n>>m;
    vector<vector<pair<int,int>>> v(100005);
    int visited[100005]={0};
    int w,y,i;
    for(i=0;i<m;i++)
    {
        cin>>x>>y>>w;
        // --x;
        // --y;
        v[x].push_back(make_pair(y,w));
        v[y].push_back(make_pair(x,w));
    }
    int count1=1;
     struct node *root1=NULL;
     root1=insert(root1,0,0,0);
    int sum=0;

    while(count1!=n+1)
    {
           struct node *temp=kthmin(root1,1);
           int r=temp->start[0].first;
           int s=temp->start[0].second;
           
           bool flag=false;
           if(visited[r]==0)
           {
               int n1=v[r].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v[r][i].first]==0)
                 {
                     root1=insert(root1,r,v[r][i].first,v[r][i].second);
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
                     root1=insert(root1,s,v[s][i].first,v[s][i].second);
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
           if(temp->c>1)
           {
               temp->c--;
               temp->start.erase(temp->start.begin());
           }
           else
           {
           root1=delete1(root1,r,s,temp->data);
           }
    }
    // cout<<sum<<endl;
    auto stop = high_resolution_clock::now(); 
  
    auto duration = duration_cast<microseconds>(stop - start); 
    
    cout<< duration.count()<< endl; 
    return 0;
}

