#ifndef NODEOFSPLAYTREE_H
#define NODEOFSPLAYTREE_H

/*!
 * \brief The NodeOfSplayTree struct
 */
struct NodeOfSplayTree
{
    /*!
     * \brief NodeOfSplayTree
     * \param data
     * \param father
     */
    NodeOfSplayTree(int data, struct NodeOfSplayTree* father):
        data(data), left(nullptr), right(nullptr), father(father)
    {}

    /*!
     * \brief dealockSubTree
     */
    void dealockSubTree()
    {
        if (left != nullptr)
        {
            left->dealockSubTree();
            delete left;
        }

        if (right != nullptr)
        {
            right->dealockSubTree();
            delete right;
        }
    }

    int data = 0;
    int height = 0;
    struct NodeOfSplayTree* left = nullptr;
    struct NodeOfSplayTree* right = nullptr;
    struct NodeOfSplayTree* father = nullptr;
};

#endif // NODEOFSPLAYTREE_H
