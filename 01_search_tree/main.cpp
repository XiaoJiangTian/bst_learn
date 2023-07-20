#include <iostream>
#include <queue>
using namespace std;

/*
2023/7/16
二叉搜索树实现
运用递归方法结合new动态创建节点空间（类）包含数据域，和左右孩指针域
熟悉递归的方法
*/
class point
{
public:
    int num_insert;
    point *tree_left = NULL;
    point *tree_right = NULL;
};//以类这种数据结构来实现树节点的数据域，左孩和右孩指针


point * make_new_point(point *p, int num)
{
    p = new point; //开辟新内存用于创建一个新节点，并返回该节点的地址（注意这个地址很关键），返回后通过递归就可以赋值给父节点左孩或右孩指针
    p->num_insert=num;
    p->tree_left=NULL;
    p->tree_right=NULL;
    return p;
}

point * insert(point *root,int num)
{
    if(root==NULL)
        {
        root=make_new_point(root,num);
    }
    else if(num<root->num_insert)
    {
        root->tree_left = insert(root->tree_left,num);//root始终指向根，中途递归改变的是左孩和右孩指针
    }
    else {
        root->tree_right = insert(root->tree_right,num);
    }
    return root;//注意类型一致性，都是一个指向自义定数据类型的指针
}

bool search(point *root, int num)
{
    if(root==NULL)
    {
        return false;
    }
    else if(num==root->num_insert)
    {
        return true;
    }
    else if(num<root->num_insert)return search(root->tree_left,num);
    else if(num>root->num_insert)return search(root->tree_right,num);
}

int findmin(point *root)
{
    if(root==NULL)
    {
        cout << "empty tree!";
        return -1;
    }
    while(root->tree_left!=NULL)
    {
        root = root->tree_left;
    }
    return root->num_insert;
}//利用迭代实现

int findmax(point *root)
{
    if(root==NULL)
    {
        cout<<"empty tree!";
        return -1;
    }
    else if(root->tree_right==NULL)
    {
        return root->num_insert;
    }
    return findmax(root->tree_right);
}//利用递归实现

int findheight(point *root)
{
    if(root == NULL)//当找到叶子节点时返回-1，由叶子节点带来的深度增益为0，因为返回的为-1，因为这里的深度以边定义而不是以节点数定义
        return -1;
    return max(findheight(root->tree_left),findheight(root->tree_right))+1;
}//递归实现


void level_order(point *root)//bst的层次遍历
{
    if(root==NULL)return;
    else if(root!=NULL)
    {
        queue<point*> q;
        q.push(root);
        while (!q.empty()) {
            point * current = q.front();//创建一个临时的
            cout<<current->num_insert<<" "<<endl;//取出值
            if(current->tree_left!=NULL)q.push(current->tree_left);//存入当前结点的左孩指针
            if(current->tree_right!=NULL)q.push(current->tree_right);//存入当前结点的右孩指针
            q.pop();//从队列中删除被访问的节点
        }
    }
}

void preorder(point *root)//前序遍历
{
    if(root==NULL)return;
    cout << root->num_insert <<" "<<endl;
    preorder(root->tree_left);
    preorder(root->tree_right);
}

void inorder(point *root)//中序遍历
{
    if(root==NULL)return;
    inorder(root->tree_left);//注意这里传入的是左右孩的指针
    cout<< root->num_insert <<" "<<endl;//这里是输出对象的值，注意区分
    inorder(root->tree_right);
}

void postorder(point *root)//后序查找.类似于从最低层的叶子节点往上访问
{
    if(root==NULL)return;
    postorder(root->tree_left);
    postorder(root->tree_right);
    cout<< root->num_insert<<" "<<endl;
}

bool bst_judge(point *root, int min,int max)//判断该树是不是一颗  二叉搜索树，二叉搜索树有特定的性质
{
    if(root==NULL)return true;
    if(root->num_insert>min&&root->num_insert<max&&bst_judge(root->tree_left,min,root->num_insert)&&bst_judge(root->tree_right,root->num_insert,max))
        return true;
    else
        return false;
}

bool bst_judge_call(point *root)//判断二叉树的调用接口，只需传入root就行
{
    return bst_judge(root,INT_MIN,INT_MAX);
}


point * search_1(point *root, int num)
{
    if(root==NULL)
    {
        return NULL;
    }
    else if(num==root->num_insert)
    {
        return root;
    }
    else if(num<root->num_insert)return search(root->tree_left,num);
    else if(num>root->num_insert)return search(root->tree_right,num);
}

point *getsuccessor(point *root, int num)//获取二叉树中序的后继节点
{
    point *p_num=search_1(root,num);
    if(p_num==NULL)return NULL;
    if(p_num->tree_right!=NULL)
    {
        while (p_num->tree_left!=NULL) {
            p_num=p_num->tree_left;
        }
        return p_num;
    }
    else
    {
        point *father_p=root;
        point *successor=NULL;
        while(father_p!=p_num)
        {
            if(father_p->num_insert>p_num->num_insert)
            {
                successor = father_p;
                father_p=father_p->tree_left;
            }
            else
            {
                father_p=father_p->tree_right;
            }
            return successor;
        }

    }
}

point *delete_point(point *root,int data)//删除二叉搜索树中的某个节点，注意递归的使用，也要注意递归调用后返回值赋值的对象，被删除的节点存在3种情况，叶子节点，有一个子节点，有两个子节点
{
    if(root==NULL)return root;
    else if(data<root->num_insert)
    {
        root->tree_left=delete_point(root->tree_left,data);
    }
    else if(data>root->num_insert)
    {
        root->tree_right=delete_point(root->tree_right,data);
    }
    else
    {
        if(root->tree_left==NULL&&root->tree_right==NULL)//叶子节点情况，直接将该节点删除，由于每次递归调用都要返回root，所以将该root置null
        {
            delete root;
            root=NULL;
        }
        else if(root->tree_left==NULL)//左叶子为空，先用临时指针保存要删除的节点指针，随后将根节点变化后其右子节点的指针，完成节点移位，最后将原节点内存释放。并返回新指针
        {
            point *temp=root;
            root = root->tree_right;
            delete temp;
        }
        else if(root->tree_right==NULL)
        {
            point *temp=root;
            root = root->tree_left;
            delete temp;
        }
        else//两边都有子节点，找到右子树的最小节点，将其值赋给该节点，原节点值被覆盖，最通过递归将原右树的最小值删除。，最后返回原来的节点，只是其值已被改变，且右树对应该值的节点也被删除。
        {
            int max_right = findmax(root);
            root->num_insert=max_right;
            root->tree_right=delete_point(root->tree_right,max_right);
        }
    }
    return root;
}

int main()
{
    point *root=NULL;
    root = insert(root,15);//递归接收最后的根节点
    root = insert(root,10);
    root = insert(root,20);
    root = insert(root,25);
    root = insert(root,8);
    root = insert(root,12);
    int number=0;
    cout <<"input the num you want to search:"<<endl;
    cin>>number;
    if(search(root,number))
    {
        cout << "got it!";
    }
    else
    {
        cout <<"not found!";
    }
    cout <<endl;
    cout <<"max:"<<findmax(root)<<endl;
    cout <<"min:"<<findmin(root)<<endl;

    cout <<"the height of the bst:"<<findheight(root)<<endl;

    level_order(root);
    cout<<"preorder:"<<endl;
    preorder(root);
    cout << "postorder:"<<endl;
    postorder(root);
    cout << bst_judge_call(root)<<endl;
    delete_point(root,8);
    cout << "new postorder:"<<endl;
    postorder(root);
    return 0;
}
