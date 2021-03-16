#include "treeheader.h"
int main(int argc, char** argv)
{
    if (argc != 2)
    {	
        printf("Please enter in accordance to readme.\n$ make all\n$ ./avltree textfilename.txt\n");
        exit(1);
    }
    avlN* tree = NULL;
    int nodes = 0;
    int size = 0;
    int totalCount = 0;
	char *choice = malloc(sizeof(char) * 10); 
    do
    {
        printf("1. Initialization\n");
        printf("2. Find\n");
        printf("3. Insert\n");
        printf("4. Remove\n");
        printf("5. Check Height, Size and Total Count:\n");
        printf("6. Find All (above a given frequency)\n");
        printf("7. Exit\n");
        printf("avl/> ");
        scanf("%s", choice);
        switch (atoi(choice))
        {
        case 1: //initialize
            tree = inputOne(argv, tree);
            break;
        case 2: //find
            inputTwo(tree);
            break;
        case 3: //insert
            tree = inputThree(tree);
            break;
        case 4: //remove
            tree = inputFour(tree);
            break;
        case 5: //height and size
            inputFive(tree, size, totalCount);
            break;
        case 6: //find all > frequency
            inputSix(tree, nodes);
            break;
        case 7: //quit
            printf("Exiting...\n");
            exit(1);
            break;
        default:
            printf("Error - Invalid input. Please try again.\n");
        }
    } while(atoi(choice) != 7);
    return 0;
}
avlN* insert(avlN* root, char key[1000])
{
    int balanceFactor = 0;
    if (root == NULL)
    {
        return createNode(key); // if empty tree, create the first root
    }
    if (strcmp(key, root->key) < 0)
    {
        root->L  = insert(root->L, key);
    }
    else if (strcmp(key, root->key) > 0)
    {
        root->R = insert(root->R, key);
    }
    else
    {
        root->count++;
        return root;
    }
    root->height = 1 + maxInt(getHeight(root->L), getHeight(root->R)); // update root height

    //balance tree, only if unbalanced (will be difference of L and R heights)
    balanceFactor = getBalance(root);
    if(key != NULL && root->R != NULL && root->L != NULL)
    {
        if ((strcmp(key, root->R->key) > 0) && (balanceFactor < -1))
        {
            return Lrotation(root);
        }
        if ((strcmp(key, root->L->key)) < 0 && balanceFactor > 1 )
        {
            return Rrotation(root);
        }
        if ((balanceFactor < -1) && (strcmp(key, root->R->key) < 0))
        {
            root->R = Rrotation(root->R);
            return Lrotation(root);
        }
        if ((balanceFactor > 1) && (strcmp(key, root->L->key) > 0))
        {
            root->L =  Lrotation(root->L);
            return Rrotation(root);
        }
    }
    return root;
}
int getHeight(avlN* root)
{
    if (root == NULL)
    {
        return 0; //no root means no height
    }
    return root->height;
}
int maxInt(int a, int b) //standard int compare (returns larger)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}


avlN* createNode(char key[1000]) // creates root, allocates memory, and initializes values
{
    avlN* root = (avlN*)malloc(sizeof(avlN));

    strcpy(root->key, key);
    root->count = 1;
    root->height = 1;
    root->L = NULL;
    root->R  = NULL;

    return root;
}

avlN* Rrotation(avlN* root) // R rotation
{
    avlN* L = NULL;
    avlN* LChild = NULL;
    if( root->L != NULL)
    {
        L = root->L;
        LChild = L->R;
        L->R = root;
        root->L = LChild;
        root->height = maxInt(getHeight(root->L), getHeight(root->R));
        L->height = maxInt(getHeight(L->L), getHeight(L->R));
        return L;
    }
    else
    {
        return root;
    }


    return root;
}

avlN* Lrotation(avlN* root) // L rotation
{
    avlN* R = NULL;
    avlN* RChild = NULL;
    if(root->R != NULL)
    {
        R = root->R;
        RChild = R->L;
        R->L = root;
        root->R = RChild;
        root->height = maxInt(getHeight(root->L), getHeight(root->R));
        R->height = maxInt(getHeight(R->L), getHeight(R->R));
        return R;
    }
    else
    {
        return root;
    }

    

    return root;
}

int getBalance(avlN* root) // determines balance factor for a root
{
    int balanceFactor = 0;
    if (root == NULL)
    {
        return 0;
    }

    balanceFactor = (getHeight(root->L) - getHeight(root->R));
    return balanceFactor;
}

void searchNode(avlN* root, char key[1000])
{
    avlN* temp = root;
    if (temp == NULL)
    {
        printf("no_such_key\n");
        return;
    }

    while (strcmp(key, temp->key) != 0)
    {
        if (temp->L == NULL && temp->R == NULL)
        {
            printf("no_such_key\n");
            return;
        }
        if (strcmp(key, temp->key) > 0)
        {
            temp = temp->R;
        }
        else
        {
            temp = temp->L;
        }
    }
    printf("key: %s, frequency: %d\n", key, temp->count);
    return;
}

avlN* smallestNode(avlN* root)
{
    avlN* temp = root;

    while (temp->L != NULL) //Because tree is balanced (and sorted by value of string), left side will contain "smallest"
    {
        temp = temp->L;
    }
    return temp;
}
avlN* del(avlN* delNode, char* delItem)
{
    if (!(delNode)) //if tree is empty, :thinking:
    {
        return delNode; // >>cant delete something that doesnt exist (☞ﾟヮﾟ)☞
    }
    if (strcmp(delItem, delNode->key) < 0)
    {
        delNode->L = del(delNode->L, delItem);
    }
    else
    {
        if (strcmp(delItem, delNode->key) > 0)
        {
            delNode->R = del(delNode->R, delItem); //the two cases above are for traversal^^, after this the keys match
        }
        else 
        {
            if ((delNode->count > 1)) //now that the key to delete and node key are matched, if freq > 1, just decrement + return
            {
                delNode->count--;
                return delNode;
            }
            // else if ((delNode->count == 1))
            // {
            //     delNode->count--;
            // }
            avlN* oTree = delNode; //dummy, dont want to break the tree
            if ((delNode->L) && (delNode->R)) //if both children aren't empty,
            {
                avlN* parent = delNode->R; //temp assigned n->right
                delNode = parent->L; //go to left node (of initial right)
                if (delNode) //if left of initial right isnt null
                {
                    while(delNode->L)
                    {
                        parent = delNode;
                        delNode = delNode->L;
                    }
                    parent->L = delNode->R; // {redux}
                    delNode->R = oTree->R;
                }
                else
                {
                    delNode = parent;
                }
                delNode->L = oTree->L;
            }
            else
            {
                if (delNode->L)
                {
                    delNode = delNode->L;
                }
                else
                {
                    delNode = delNode->R;
                }
            }
            free(oTree);
        }
    }
    return delNode;
}
void findSize(avlN* root, int* size) //traversing and totalling node count
{
    if (root != NULL)
    {
		(*size) = (*size) + 1;
        findSize(root->L, size);
        findSize(root->R, size);
    }
    return;
}
void findAll(avlN* root, int count) 
{
    if (root != NULL)
    {
        if (count <= root->count)
        {
            printf("key: %s, frequency: %d\n", root->key, root->count);
        }
        findAll(root->L, count);
        findAll(root->R, count); //traverses and prints out everything
    }
    return;
}
void searchDeleted(avlN* tree, char key[1000])
{
    avlN* temp = tree;
    if (temp == NULL)
    {
        printf("no_such_key\n");
        return;
    }

    while (strcmp(key, temp->key) != 0)
    {
        if (temp->L == NULL && temp->R == NULL)
        {
            printf("no_such_key\n");
            return;
        }
        if (strcmp(key, temp->key) > 0)
        {
            temp = temp->R;
        }
        else
        {
            temp = temp->L;
        }
    }
    printf("key: %s, frequency: %d\n", key, temp->count - 1);
    return;
}
void findTotalCount(avlN* root, int* totalCount)
{
    if (root != NULL)
    {
        (*totalCount) += root->count;
        findTotalCount(root->L, totalCount);
        findTotalCount(root->R, totalCount);
    }
    return;
}
