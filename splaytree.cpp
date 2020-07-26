#include "splaytree.h"
#include <iostream>
#include <queue>
#include <string>

SplayTree::SplayTree()
{

}

SplayTree::~SplayTree()
{
    if (root != nullptr)
    {
        root->dealockSubTree();
        delete root;
    }
}

void SplayTree::splaying(NodeOfSplayTree* node)
{
    if (root == nullptr)
        return;

    NodeOfSplayTree* current = node;
    while (current != root)
    {
        if (current->father == root)
        {
            //Deve rotacionar o root para direita ou esquerda
            Direction dir = getSideIndicatorOfChildInFather(current);
            if (dir == Direction::Left)
            {
                //fazer rotação para a direita em root (zig)
                zig(root);
            }
            else if (dir == Direction::Right)
            {
                //fazer rotação para a esquerda root (zag)
                zag(root);
            }
            else
                break; //invalid condition
        }
        else
        {
            //Nesse ponto o nó, obrigatoriamente, tem avô
            //O avô pode ser o root
            //Os métodos de zig e zag vão levar isso em consideração

            Direction dirMySelfFather =
                    getSideIndicatorOfChildInFather(current);
            Direction dirfFatherGrandFather =
                    getSideIndicatorOfChildInFather(current->father);

            if (dirMySelfFather == Direction::Left &&
                dirfFatherGrandFather == Direction::Left)
            {
                //Faz zig-zig

                //No avô atual
                zig(current->father->father);

                //No pai (permanece pai)
                zig(current->father);
            }
            else if (dirMySelfFather == Direction::Right &&
                     dirfFatherGrandFather == Direction::Right)
            {
                //Faz zag-zag

                //No avô atual
                zag(current->father->father);

                //No pai (permanece pai)
                zag(current->father);
            }
            else if (dirMySelfFather == Direction::Right &&
                     dirfFatherGrandFather == Direction::Left)
            {
                //faz zag no pai
                zag(current->father);

                //Faz zig no novo pai  (que era avô no inicio)
                zig(current->father);
            }
            else if (dirMySelfFather == Direction::Left &&
                     dirfFatherGrandFather == Direction::Right)
            {
                //faz zig no pai
                zig(current->father);

                //Faz zag no novo pai (que era avô no inicio)
                zag(current->father);
            }
        }
    }
}

struct NodeOfSplayTree* SplayTree::insert(int data)
{
    if (root == nullptr)
    {
        struct NodeOfSplayTree* t = new NodeOfSplayTree(data, nullptr);
        root = t;
        return t;
    }
    else
    {
        struct NodeOfSplayTree* tmp = root;
        while(true)
        {
            if (data < tmp->data) //go to left
            {
                if (tmp->left == nullptr)
                {
                    struct NodeOfSplayTree* t = new NodeOfSplayTree(data, tmp);
                    tmp->left = t;
                    return t;
                }
                else
                {
                    tmp = tmp->left;
                }
            }
            else if (data > tmp->data) //go to right
            {
                if (tmp->right == nullptr)
                {
                    struct NodeOfSplayTree* t = new NodeOfSplayTree(data, tmp);
                    tmp->right = t;
                    return t;
                }
                else
                {
                    tmp = tmp->right;
                }
            }
            else //data == tmp->data
            {
                return nullptr;
            }
        }
    }
}

RemoveReturn SplayTree::remove(int data)
{
    RemoveReturn ret;

    if (root == nullptr)
    {
        ret.toRemoveNode = nullptr;
        ret.newNodeInthePosition = nullptr;
        return ret;
    }

    if (root->data == data)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            root = nullptr;
            ret.toRemoveNode = root;
            ret.newNodeInthePosition = nullptr;
            return ret;
        }
        if (root->left == nullptr)
        {
            ret.toRemoveNode = root;

            root = root->right;
            if (root != nullptr)
                root->father = nullptr;

            ret.newNodeInthePosition = root;
            return ret;
        }
        else if (root->right == nullptr)
        {
            ret.toRemoveNode = root;

            root = root->left;
            if (root != nullptr)
                root->father = nullptr;

            ret.newNodeInthePosition = root;
            return ret;
        }
        else
        {
            struct NodeOfSplayTree* backup = root;
            if (root->left->right == nullptr)
            {
                root = root->left;
                root->right = backup->right;

                ret.toRemoveNode = backup;
                ret.newNodeInthePosition = root;
                return ret;
            }
            else
            {
                NodeOfSplayTree* fatherOfPred = getFatherOfPredecessor(root);
                root = fatherOfPred->right;
                fatherOfPred->right = root->left;
                root->left = backup->left;
                root->right = backup->right;

                ret.toRemoveNode = backup;
                ret.newNodeInthePosition = root;
                return ret;
            }
        }
    }
    else // o root não é o dado
    {
        struct NodeOfSplayTree *tmp = root;
        while (tmp != nullptr)
        {
            if (data < tmp->data) //pesquisar no ramo esquerdo
            {
                if (tmp->left == nullptr)
                {
                    ret.toRemoveNode = nullptr;
                    ret.newNodeInthePosition = nullptr;
                    return ret;
                }
                if (tmp->left->data == data)
                {
                    struct NodeOfSplayTree* father = tmp;
                    struct NodeOfSplayTree* toRemove = tmp->left;
                    struct NodeOfSplayTree* left = toRemove->left;
                    struct NodeOfSplayTree* right = toRemove->right;

                    if (left == nullptr && right == nullptr)
                    {
                        tmp->left = nullptr;
                        ret.toRemoveNode = toRemove;
                        ret.newNodeInthePosition = father;
                        return ret;
                    }
                    else if (left == nullptr)
                    {
                        father->left = right;
                        if (right != nullptr)
                            right->father = father;

                        ret.toRemoveNode = toRemove;
                        ret.newNodeInthePosition = right;
                        return ret;
                    }
                    else if (right == nullptr)
                    {
                        father->left = left;
                        if (left != nullptr)
                            left->father = father;

                        ret.toRemoveNode = toRemove;
                        ret.newNodeInthePosition = left;
                        return ret;
                    }
                    else
                    {
                        NodeOfSplayTree* fatherOfPred = getFatherOfPredecessor(toRemove);
                        NodeOfSplayTree* newNode = fatherOfPred->right;
                        fatherOfPred->right = newNode->left;
                        father->left = newNode;
                        newNode->left = left;
                        newNode->right = right;

                        ret.toRemoveNode = toRemove;
                        ret.newNodeInthePosition = newNode;
                        return ret;
                    }
                }
                else
                    tmp = tmp->left;
            }
            else //pesquisar no ramo direito
            {
                if (tmp->right == nullptr)
                {
                    ret.toRemoveNode = nullptr;
                    ret.newNodeInthePosition = nullptr;
                    return ret;
                }
                if (tmp->right->data == data)
                {
                    struct NodeOfSplayTree* father = tmp;
                    struct NodeOfSplayTree* toRemove = tmp->right;
                    struct NodeOfSplayTree* left = toRemove->left;
                    struct NodeOfSplayTree* right = toRemove->right;

                    if (left == nullptr && right == nullptr)
                    {
                        tmp->right = nullptr;
                        ret.toRemoveNode = toRemove;
                        ret.newNodeInthePosition = father;
                        return ret;
                    }
                    if (left == nullptr)
                    {
                        father->right = right;
                        if (right != nullptr)
                            right->father = father;

                        ret.toRemoveNode = toRemove;
                        ret.newNodeInthePosition = right;
                        return ret;
                    }
                    else if (right == nullptr)
                    {
                        father->right = left;
                        if (left != nullptr)
                            left->father = father;

                        ret.toRemoveNode = toRemove;
                        ret.newNodeInthePosition = left;
                        return ret;
                    }
                    else
                    {
                        NodeOfSplayTree* fatherOfPred = getFatherOfPredecessor(toRemove);
                        NodeOfSplayTree* newNode = fatherOfPred->right;
                        fatherOfPred->right = newNode->left;
                        father->right = newNode;
                        newNode->left = left;
                        newNode->right = right;

                        ret.toRemoveNode = toRemove;
                        ret.newNodeInthePosition = newNode;
                        return ret;
                    }
                }
                else
                    tmp = tmp->right;
            }

        }
    }

    ret.toRemoveNode = nullptr;
    ret.newNodeInthePosition = nullptr;
    return ret;
}

NodeOfSplayTree* SplayTree::getFatherOfPredecessor(NodeOfSplayTree * n)
{
    if (n->left->right == nullptr)
        return n;

    NodeOfSplayTree * temp = n->left;

    while (temp->right->right != nullptr)
        temp = temp->right;
    return temp;
}


bool SplayTree::searchInterface(int data)
{
    NodeOfSplayTree* searched = search(data);
    if (searched != nullptr)
    {
        splaying(searched);
        return true;
    }
    else
    {
        return false;
    }
}

NodeOfSplayTree *SplayTree::getRoot()
{
    return this->root;
}

NodeOfSplayTree* SplayTree::search(int data)
{
    struct NodeOfSplayTree* tmp = root;

    while(tmp != nullptr)
    {
        if (tmp->data == data)
            return tmp;
        else
        {
            if (data < tmp->data)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
    }

    return nullptr;
}

bool SplayTree::insertInterface(int data)
{
    struct NodeOfSplayTree* inserted = this->insert(data);
    if (inserted != nullptr)
        splaying(inserted);
    return inserted != nullptr;
}

Direction SplayTree::getSideIndicatorOfChildInFather(NodeOfSplayTree *node)
{
    NodeOfSplayTree* father = node->father;
    if (father == nullptr)
        return Direction::None;
    if (father->left == node)
        return Direction::Left;
    else if (father->right == node)
        return Direction::Right;
    else
        return Direction::None;
}

//the rotation to the left on node
void SplayTree::zag(NodeOfSplayTree* node)
{
    NodeOfSplayTree* left = node->left;
    NodeOfSplayTree* right = node->right;
    if (node == root)
    {
        root = right;
        right->father = nullptr;
        NodeOfSplayTree* backupRightLeft = right->left;
        right->left = node;
        node->father = right; //pai
        node->right = backupRightLeft;
        if (backupRightLeft != nullptr)
            backupRightLeft->father = node; //pai
    }
    else
    {
        NodeOfSplayTree* backupFather = node->father;
        //substituir em backupFather, node por right
        replaceChildInFather(backupFather, node, right);
        right->father = backupFather;
        NodeOfSplayTree* backupRightLeft = right->left;
        right->left = node;
        node->father = right; //pai
        node->right = backupRightLeft;
        if (backupRightLeft != nullptr)
            backupRightLeft->father = node; //pai
    }
}

//the rotation to the right on node
void SplayTree::zig(NodeOfSplayTree* node)
{
    NodeOfSplayTree* left = node->left;
    NodeOfSplayTree* right = node->right;
    if (node == root)
    {
        root = left;
        left->father = nullptr;
        NodeOfSplayTree* backupLeftRight = left->right;
        left->right = node;
        node->father = left; //pai
        node->left = backupLeftRight;
        if (backupLeftRight != nullptr)
            backupLeftRight->father = node; //pai
    }
    else
    {
        NodeOfSplayTree* backupFather = node->father;
        //substituir em backupFather, node por left
        replaceChildInFather(backupFather, node, left);
        left->father = backupFather;
        NodeOfSplayTree* backupLeftRight = left->right;
        left->right = node;
        node->father = left; //pai
        node->left = backupLeftRight;
        if (backupLeftRight != nullptr)
            backupLeftRight->father = node; //pai
    }
}

void SplayTree::replaceChildInFather(NodeOfSplayTree* father, NodeOfSplayTree* old, NodeOfSplayTree* newSon)
{
    if (father->left == old)
        father->left = newSon;
    else if (father->right == old)
        father->right = newSon;
}

NodeOfSplayTree *SplayTree::removeInterface(int data)
{
    RemoveReturn removeReturn = this->remove(data);

    if (removeReturn.toRemoveNode->father != nullptr)
        splaying(removeReturn.toRemoveNode->father);

    return removeReturn.toRemoveNode;
}

const std::string SplayTree::gitDotFileMode2()
{
    std::string textToFile = "digraph g{";
    textToFile += "node [shape=record, height=0.1];";

    if (root == nullptr)
    {
        textToFile += "NULL [label = \"<l> | <m> NULL | <r>\"];Root -> NULL;";
    }
    else
    {
        int count = 0;
        exibirSubArvore2(nullptr, true, root, textToFile, count);
    }

    textToFile += "}";

    return textToFile;
}

const std::string SplayTree::gitDotFileMode1()
{
    std::string textToFile = "digraph g{";
    textToFile += "Root[shape=none fontcolor=blue];";

    if (root == nullptr)
    {
        textToFile += "NULL [ fontcolor=red ];Root -> NULL;";
    }
    else
    {
        int count = 0;
        textToFile += "Root->"+std::to_string(root->data)+";";
        exibirSubArvore1(root, textToFile, count);
    }

    textToFile += "}";

    return textToFile;
}

const std::string SplayTree::preOrder()
{
    std::string content;
    preOrder(root, content);
    return content;
}

const std::string SplayTree::inOrder()
{
    std::string content;
    inOrder(root, content);
    return content;
}

const std::string SplayTree::posOrder()
{
    std::string content;
    posOrder(root, content);
    return content;
}

const std::string SplayTree::inLevelOrder()
{
    std::string content;

    std::queue<NodeOfSplayTree*> queue;

    if (root != nullptr)
        queue.push(root);

    NodeOfSplayTree* node = nullptr;
    while(queue.size() > 0)
    {
        NodeOfSplayTree* node = queue.front(); //acessa o primeiro
        queue.pop(); //remove o primeiro

        content += std::to_string(node->data)+" ";

        if (node->left != nullptr)
            queue.push(node->left);

        if (node->right != nullptr)
            queue.push(node->right);
    }

    return content;
}

void SplayTree::preOrder(struct NodeOfSplayTree* node, std::string& content)
{
    if (node != nullptr)
    {
        content += std::to_string(node->data) + " ";
        preOrder(node->left, content);
        preOrder(node->right, content);
    }
}
void SplayTree::inOrder(struct NodeOfSplayTree* node, std::string& content)
{
    if (node != nullptr)
    {
        inOrder(node->left, content);
        content += std::to_string(node->data) + " ";
        inOrder(node->right, content);
    }
}
void SplayTree::posOrder(struct NodeOfSplayTree* node, std::string& content)
{
    if (node != nullptr)
    {
        posOrder(node->left, content);
        posOrder(node->right, content);
        content += std::to_string(node->data) + " ";
    }
}

void SplayTree::exibirSubArvore1
(
    struct NodeOfSplayTree* n,
    std::string& content,
    int& count
)
{
    //Desenha o dado do nó n
    content += std::to_string(n->data)+";";

    if (n->left == nullptr)
    {
        content += std::to_string(n->data)+"->NULL"+std::to_string(count++)+";";
    }
    else
    {
        content += std::to_string(n->data)+"->"+std::to_string(n->left->data)+";";
        exibirSubArvore1
        (
            n->left,
            content,
            count
        );
    }

    if (n->right == nullptr)
    {
        content += std::to_string(n->data)+"->NULL"+std::to_string(count++)+";";
    }
    else
    {
        content += std::to_string(n->data)+"->"+std::to_string(n->right->data)+";";
        exibirSubArvore1
        (
            n->right,
            content,
            count
        );
    }
}

void SplayTree::exibirSubArvore2
(
    struct NodeOfSplayTree *father,
    bool isLeftSon,
    struct NodeOfSplayTree* n,
    std::string& content,
    int& count
)
{
    //Desenha o dado do nó n
    content += std::to_string(n->data)+" [label = \"<l> | <m> "+std::to_string(n->data)+" | <r>\"];";

    //desenha a ligação entre o pai e ele
    if (father != nullptr)
    {
        if (isLeftSon)
            content += std::to_string(father->data)+":l->"+std::to_string(n->data)+";";
        else
            content += std::to_string(father->data)+":r->"+std::to_string(n->data)+";";
    }
    else
    {
        //é o root
        content += "ROOT[shape=none fontcolor=blue];";
        content += "ROOT->"+std::to_string(n->data)+";";
    }

    if (n->left != nullptr)
    {
        exibirSubArvore2
        (
            n,
            true, //is left
            n->left,
            content,
            count
        );
    }

    if (n->right != nullptr)
    {
        exibirSubArvore2
        (
            n,
            false, //is not left
            n->right,
            content,
            count
        );
    }
}
