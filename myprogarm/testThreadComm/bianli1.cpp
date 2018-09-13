http://blog.csdn.net/pi9nc/article/details/13008511
http://blog.csdn.net/pi9nc/article/details/13008511
http://blog.csdn.net/pi9nc/article/details/13008511

typedef struct BTree
{
  char data
  BTree * pLchild, pRchild;
}

void pre_traverse(BTree *pTree)  
{  
    if(pTree)  
    {  
        printf("%c ",pTree->data);  
        if(pTree->pLchild)  
            pre_traverse(pTree->pLchild);  
        if(pTree->pRchild)  
            pre_traverse(pTree->pRchild);      
    }  
}

void in_traverse(BTree *pTree)  
{
    if(pTree)  
    {  
        if(pTree->pLchild)  
            in_traverse(pTree->pLchild);  
        printf("%c ",pTree->data);  
        if(pTree->pRchild)  
            in_traverse(pTree->pRchild);   
    }  
}


void beh_traverse(BTree *pTree)  
{  
    if(pTree)  
    {  
        if(pTree->pLchild)  
            beh_traverse(pTree->pLchild);  
        if(pTree->pRchild)  
            beh_traverse(pTree->pRchild);      
        printf("%c ",pTree->data);  
}  

void AddBTreeNode(BTree* pTree, BTree *newTree)
{
    if(!newNode)return;
    if(pTree)
	{
	    if((pTree->data <= newTree->data) &&
		  (pTree->pLchild !=NULL))
		{
		    AddBTreeNode(pTree->pLchild, newTree);
		}
		elseif((pTree->data <= newTree->data) &&
		  (pTree->pLchild ==NULL))
		{
		    pTree->pLchild = newTree;
		}
		elseif(T->rchild!=NULL)
		{
		    AddBTreeNode(pTree->pRchild, newTree);
		}
		else
		{
		    pTree->pRchild = newTree;
		}
	}
	else
	{
	    pTree = newTree;
	}
}

