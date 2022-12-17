#include "BVHTree.h"


AABB combineAABBs(const AABB& item1, const AABB& item2)
{
    return item1 + item2;
}

bool isAABBFirstInSecond(const AABB& item1, const AABB& item2) //Is item 1 inside item 2
{
    return(item1.getMin(item1.minX, item2.minX) == item2.minX &&
        item1.getMin(item1.minY, item2.minY) == item2.minY &&
        item1.getMax(item1.maxX, item2.maxX) == item2.maxX &&
        item1.getMax(item1.maxY, item2.maxY) == item2.maxY);
}

void BVHTree::fixAABB(BVHTreeNode*& tempRoot)
{
    if (!tempRoot->isLeaf)
    {
        fixAABB(tempRoot->leftChild);
        fixAABB(tempRoot->rightChild);
        tempRoot->aabb = (tempRoot->leftChild->aabb + tempRoot->rightChild->aabb);

    }

}


void BVHTree::addBVHMemberPriv(BVHTreeNode*& tempRoot, BVHTreeNode*& newMember, BVHTreeNode* prevIter)
{
    if (tempRoot == nullptr)            //case1: tree is empty
    {
        tempRoot = newMember;
    }
    else if (tempRoot->isLeaf == true)  //case2: only one node
    {
        AABB branchAABB = combineAABBs(tempRoot->aabb, newMember->aabb);
        BVHTreeNode* newBranch = new BVHTreeNode(branchAABB, "", false);
        newBranch->leftChild = newMember;
        newBranch->rightChild = tempRoot;
        tempRoot = newBranch;

        newBranch->leftChild->parent = newBranch;
        newBranch->rightChild->parent = newBranch;
        newBranch->parent = prevIter;
    }
    else
    {
        if (tempRoot->isLeaf == false)
        {
            tempRoot->aabb = combineAABBs(newMember->aabb, tempRoot->aabb);

            int increaseInRightTreeSize = AABB::unionArea(newMember->aabb, tempRoot->rightChild->aabb) - tempRoot->rightChild->aabb.getArea();
            int increaseInLeftTreeSize = AABB::unionArea(newMember->aabb, tempRoot->leftChild->aabb) - tempRoot->leftChild->aabb.getArea();
            if (increaseInRightTreeSize < increaseInLeftTreeSize)       //add member to right
            {
                addBVHMemberPriv(tempRoot->rightChild, newMember, tempRoot);
            }
            else
            {
                addBVHMemberPriv(tempRoot->leftChild, newMember, tempRoot);
            }
        }

    }
    //add to hash table
    map[newMember->name] = newMember;
}

void BVHTree::printNode(std::ostream &out, BVHTreeNode *node, int level) {
	if (root == nullptr) return;
	for (int i = 0; i < level; i++) {
		out << "  ";
	}
	if (!node->isLeaf) {
		out << "+ branch || ";
		node->aabb.printAABB(out);
		out << std::endl;
		printNode(out, node->rightChild, level + 1);
		printNode(out, node->leftChild, level + 1);
	}
	else {
		out << "- ";
		if (node->parent) {
			if (node->parent->rightChild == node)
				out << "R ";
			else
				out << "L ";
		}
		out << "- leaf: " << node->name << " || ";
		node->aabb.printAABB(out);
		out << std::endl;
	}
}
void BVHTree::addBVHMember(AABB objectArea, std::string name)
{
    BVHTreeNode* newMember = new BVHTreeNode(objectArea, name, true); //new node as leaf
    addBVHMemberPriv(root, newMember, nullptr);
}

void BVHTree::moveBVHMember(std::string name, AABB newLocation)
{
    BVHTreeNode* nodeToMove = map.at(name);
    if (nodeToMove->parent == nullptr)
    {
        nodeToMove->aabb = newLocation;
    }
    else
    {
        BVHTreeNode* currentParrent = nodeToMove->parent;
        if (currentParrent->rightChild->name == name)
        {//if temp leaf is parent of object to be removed
            if (isAABBFirstInSecond(combineAABBs(currentParrent->leftChild->aabb, newLocation), currentParrent->aabb)) //no need to delete
            {
                currentParrent->rightChild->aabb = newLocation;
            }
            else
            {
                BVHTreeNode* tempNode = new BVHTreeNode(newLocation, name, true);
                removeBVHMember(name);
                addBVHMember(newLocation, name);

            }
        }
        else if (currentParrent->leftChild->name == name)
        {
            if (isAABBFirstInSecond(combineAABBs(currentParrent->rightChild->aabb, newLocation), currentParrent->aabb)) //no need to delete
            {
                currentParrent->leftChild->aabb = newLocation;
            }
            else
            {
                removeBVHMember(name);
                addBVHMember(newLocation, name);

            }
        }
    }
}

void BVHTree::removeBVHMember(std::string name)
{
    BVHTreeNode* tobeDeleted = map.at(name);
    map.erase(name);
    if (tobeDeleted->parent == nullptr)
    {
        BVHTreeNode* oldNode = tobeDeleted;
        tobeDeleted = nullptr;
        delete oldNode;
    }
    else
    {
        BVHTreeNode* currentParrent = tobeDeleted->parent;


        if (currentParrent->leftChild == tobeDeleted) 
        {                                  
            currentParrent->rightChild->parent = currentParrent->parent; //update siblings parrent

            if (currentParrent->parent == nullptr)
            {
                root = currentParrent->rightChild;
            }
            else
            {
                if (currentParrent->parent->rightChild == currentParrent)
                {
                    currentParrent->parent->rightChild = currentParrent->rightChild;
                    map.erase(currentParrent->rightChild->name);
                    map[currentParrent->rightChild->name] = currentParrent->parent->rightChild;
                }
                else
                {
                    currentParrent->parent->leftChild = currentParrent->rightChild;
                    map.erase(currentParrent->rightChild->name);
                    map[currentParrent->rightChild->name] = currentParrent->parent->leftChild;
                }
            }
            delete currentParrent;
        }
        if (currentParrent->rightChild == tobeDeleted) 
        {                                   
            currentParrent->leftChild->parent = currentParrent->parent; //update siblings parrent

            if (currentParrent->parent == nullptr)
            {
                root = currentParrent->leftChild;
            }
            else
            {
                if (currentParrent->parent->rightChild == currentParrent)
                {
                    currentParrent->parent->rightChild = currentParrent->leftChild;
                    map.erase(currentParrent->leftChild->name);
                    map[currentParrent->leftChild->name] = currentParrent->parent->rightChild;
                }
                else
                {
                    currentParrent->parent->leftChild = currentParrent->leftChild;
                    map.erase(currentParrent->leftChild->name);
                    map[currentParrent->leftChild->name] = currentParrent->parent->leftChild;
                }
            }
            delete currentParrent;
        }

        delete tobeDeleted;
        fixAABB(root);
    }
}

void BVHTree::getCollidingObjectspPriv(BVHTreeNode*& tempRoot, AABB object, std::vector<std::string>& collidingObjects)
{
    if (tempRoot->aabb.collide(object))
    {
        if (tempRoot->isLeaf)
        {
            collidingObjects.push_back(tempRoot->name);
        }
        else
        {
            getCollidingObjectspPriv(tempRoot->leftChild, object, collidingObjects);
            getCollidingObjectspPriv(tempRoot->rightChild, object, collidingObjects);
        }
    }
}

std::vector<std::string> BVHTree::getCollidingObjects(AABB object)
{
    std::vector<std::string> collidingObjects;
    getCollidingObjectspPriv(root, object, collidingObjects);
    return collidingObjects;

}

std::ostream &operator<<(std::ostream &out, BVHTree &tree) {
	tree.printNode(out, tree.root, 0);
	return out;
}


BVHTree::BVHTree()
{
    root = nullptr;
}

BVHTree::~BVHTree()
{
    DesBVHTreePriv(root);
}

void BVHTree::DesBVHTreePriv(BVHTreeNode*& tempRoot)
{
    if (tempRoot != nullptr)
    {
        if (tempRoot->isLeaf)
        {
            delete tempRoot;
        }
        else
        {
            DesBVHTreePriv(tempRoot->leftChild);
            DesBVHTreePriv(tempRoot->rightChild);
            delete tempRoot;
        }

    }
}
