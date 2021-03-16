#include "treeheader.h"
avlN* inputOne(char** argv, avlN* tree)
{
    tree = NULL;

    char parsedString[1000];
    int i = 0;
    int j = 0;
    char dataText[50000]; //jeremy us to use a large buffer, so IS THIS OBSCENELY LARGE ENOUGH?
    FILE* fp = NULL;
    fp = fopen(argv[1], "r");
    while (fgets(dataText, 50000, fp))
    {
        i = 0;
        while (dataText[i] != '\n')
        {
            if (isspace(dataText[i]))
            {
                i++;
            }
            else
            {
                while (!isspace(dataText[i]))
                {
                    parsedString[j] = dataText[i];
                    i++;
                    j++;
                }
                tree = insert(tree, parsedString);
                memset(parsedString, 0, 1000); //reset memory block
                j = 0;
            }
        }
    }
    return tree;
}
void inputTwo(avlN* tree)
{
    char key[1000];
    printf("find key: ");
    scanf("%s", key);
    searchNode(tree, key);
}
avlN* inputThree(avlN* tree)
{
    char key[1000];
    printf("insert key: ");
    scanf("%s", key);
    tree = insert(tree, key);
    searchNode(tree, key);
    return tree;
}
avlN* inputFour(avlN* tree) //to remove key, must print 
{
    char key[1000];
    printf("remove key: ");
    scanf("%s", key);
    searchDeleted(tree, key);

    tree = del(tree, key);

    return tree;
}
void inputFive(avlN* tree, int size, int totalCount)
{
    findSize(tree, &size);
    findTotalCount(tree, &totalCount);
    int tempHeight = 0;
    if(totalCount == 0) //hotfix for removing single node'd tree - 
    {
        size = 0;
        printf("height: %d, size: %d, total count: %d\n", tempHeight, size, totalCount);
    }
    else
    {
        printf("height: %d, size: %d, total count: %d\n", getHeight(tree), size, totalCount);
    }
    if(size != 0)
    {
        size = 0;
    }
}
void inputSix(avlN* tree, int nodes)
{
    printf("frequency: ");
    scanf("%d", &nodes);
    findAll(tree, nodes);
}