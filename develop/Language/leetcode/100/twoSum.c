/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**
 * 解题思路: 二叉树 
 * 目标数中间截断 , 必有一个小于等于截断数的左侧 和 大于等于截断数的右侧.
 * (因此把所有数都 * 10了,不想用浮点数)
 * 左右侧的数与截断数的差值相等.
 * 所以主要耗时在二叉树查找速度, logn ,找不到相同的就插入到合适地方.
 * 最差情况 最后两个数 为目标数 耗时 nlogn;
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int Value;
    short int Positive;
    short int Negative;
}Node;

struct Tree{
    Node NodeValue;
    struct Tree *Left;
    struct Tree *Right;
};



void InitTreeNode(struct Tree *pTreeNode, int Value, int Offset)
{
    pTreeNode->Left = NULL;
    pTreeNode->Right = NULL;

    if (0 > Value)
    {
        pTreeNode->NodeValue.Value = -(Value);
        pTreeNode->NodeValue.Negative = Offset;
        pTreeNode->NodeValue.Positive = -1; 
    }
    else
    {
        pTreeNode->NodeValue.Value = Value;
        pTreeNode->NodeValue.Positive = Offset; 
        pTreeNode->NodeValue.Negative = -1; 
    }
}

void InitTree(struct Tree *pTree, int Target)
{
    pTree->NodeValue.Value = 0;
    pTree->NodeValue.Positive = -1;
    pTree->NodeValue.Negative = -1;

    pTree->Left = NULL;
    pTree->Right = NULL;
}

struct Tree* FindTarget(struct Tree *pTree, int TargetValue)
{
    if (0 < (TargetValue - pTree->NodeValue.Value))
    {
        if (NULL != pTree->Right)
        {
            return FindTarget(pTree->Right, TargetValue);
        }
    }
    else if (0 > (TargetValue - pTree->NodeValue.Value))
    {
        if (NULL != pTree->Left)
        {
            return FindTarget(pTree->Left, TargetValue);
        }
    }
	
    return pTree;
}

struct Tree * AddToTree(struct Tree *pTree, struct Tree *Insert)
{
	int Result = -1;
    if (pTree->NodeValue.Value == Insert->NodeValue.Value)
    {
        if (0 == Insert->NodeValue.Value)
            return NULL;
        
        if (Insert->NodeValue.Negative == -1)
        {
            if (pTree->NodeValue.Negative != -1)
                Insert->NodeValue.Negative = pTree->NodeValue.Negative;
        }
        
        if (Insert->NodeValue.Positive == -1)
        {
            if (pTree->NodeValue.Positive != -1)
                Insert->NodeValue.Positive = pTree->NodeValue.Positive;
        }

        if (Insert->NodeValue.Negative != -1
            && Insert->NodeValue.Positive != -1)
        {
            return NULL;
        }
    }
    else
    {
        if (pTree->NodeValue.Value > Insert->NodeValue.Value)
        {
            pTree->Left = Insert;
        }
        else
        {
            pTree->Right = Insert;
        }
    }
	return Insert;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{

    struct Tree HeaderNode;
    struct Tree AllNode[numsSize];

    *returnSize = 2;
	target *= 5;

    InitTree(&HeaderNode, target);
    int Equl = 0;
    int *pBuffer;
    pBuffer = (int*)malloc(sizeof(int) * 2);

    int i = 0;

    while (i < numsSize)
    {
        nums[i] *= 10;
        InitTreeNode(&AllNode[i], nums[i] - target, i);

        struct Tree* pTemp = FindTarget(&HeaderNode, AllNode[i].NodeValue.Value);

        if (NULL == AddToTree(pTemp, &AllNode[i]))
        {

            if (0 != AllNode[i].NodeValue.Value)
            {
                pBuffer[0] = (int)AllNode[i].NodeValue.Positive;
                pBuffer[1] = (int)AllNode[i].NodeValue.Negative;
		        return pBuffer;
            }
            else
            {
                if (0 == Equl)
                {
                    pBuffer[0] = (int)AllNode[i].NodeValue.Positive;
                    Equl++;
                }
                else
                {
                    pBuffer[1] = (int)AllNode[i].NodeValue.Positive;
                    return pBuffer;
                }	    
            }
        }

        i++;
    }
	return NULL;
}
