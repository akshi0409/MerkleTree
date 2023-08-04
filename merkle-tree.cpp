#include <iostream>
#include <bits/stdc++.h>
#include <bitset>
#include "picosha2.h"
using namespace std;
struct node{
    string value;
    string key;
    struct node* left;
    struct node* right;
};
inline std::string hash_sha256(std::string src_str)
{
    std::string hash_hex_str = picosha2::hash256_hex_string(src_str);
    return hash_hex_str;
}
void printInorder(struct node* root)
{
    if (root == NULL)
        return;
    printInorder(root->left);
    cout << root->value << " ";
    printInorder(root->right);
}
int main()
{
    int n;
    cout<<"Enter the number of elements: ";
    cin>>n;
    string leaves[n];
    for(int i=0;i<n;i++)
    {
        cout<<"Enter element: ";
        cin>>leaves[i];
    }
    vector<node*>q;
    for(int i=0;i<n;i++)
    {
        node* hash=new node();
        hash->value=leaves[i];
        hash->key=hash_sha256(leaves[i]);
        hash->left=NULL;
        hash->right=NULL;
        q.push_back(hash);
    }
    while(q.size()!=1)
    {
        vector<node*>temp;
        for(int i=0;i<=q.size()-2;i=i+2)
        {
            node* t=new node();
            t->value = q[i]->value +q[i + 1]->value;
            t->key=hash_sha256(q[i]->key+q[i+1]->key);
            t->left=q[i];
            t->right=q[i+1];
            temp.push_back(t);
        }
        if(q.size()%2!=0)
        {
            node *t = new node();
            t->value = q[q.size()-1]->value;
            t->key=hash_sha256(q[q.size()-1]->key);
            t->left = q[q.size()-1];
            t->right = NULL;
            temp.push_back(t);
        }
        q.clear();
        q=temp;
        temp.clear();
    }
    struct node* root=q[0];
    cout<<root->value<<endl;
    cout<<root->key<<endl;
    printInorder(root);
    return 0;
}