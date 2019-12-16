#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SET_SIZE 100000
typedef struct set{
    int seqlist[SET_SIZE];
    int index;
}set;

set Set;

void set_ini()
{
    memset(Set.seqlist, -1, SET_SIZE);
    Set.index = 0;
}

int set_contain(int val)
{
    int i = 0;
    for (i = 0; i < Set.index; ++i)
    {
        if (Set.seqlist[i] == val)
            return 1;   
    }
    return 0;
}

int set_insert(int val)
{
    if(!set_contain(val))
    {
        Set.seqlist[Set.index++] = val;
        return 1;
    }
    else
        return 0;
}

int main()
{
    set_ini();
    set_insert(1);
    set_insert(2);
    set_insert(3);

    printf("%d\n", set_contain(2));

    printf("%d\n", set_contain(4));
    return 0;
}