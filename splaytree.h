#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include "nodeofsplaytree.h"

/*!
 * \brief The RemoveReturn struct
 */
struct RemoveReturn
{
    NodeOfSplayTree* toRemoveNode = nullptr;
    NodeOfSplayTree* newNodeInthePosition = nullptr;
};

/*!
 * \brief The Direction enum
 */
enum Direction
{
    Left, Right, None
};

/*!
 * \brief The SplayTree class
 */
class SplayTree
{
public:
    /*!
     * \brief SplayTree
     */
    SplayTree();

    ~SplayTree();

    /*!
     * \brief gitDotFileMode1
     * \return
     */
    const std::string gitDotFileMode1();

    /*!
     * \brief gitDotFileMode2
     * \return
     */
    const std::string gitDotFileMode2();

    /*!
     * \brief preOrder
     * \return
     */
    const std::string preOrder();

    /*!
     * \brief inOrder
     * \return
     */
    const std::string inOrder();

    /*!
     * \brief posOrder
     * \return
     */
    const std::string posOrder();

    /*!
     * \brief InLevelOrder
     * \return
     */
    const std::string inLevelOrder();

    /*!
     * \brief insertInterface
     * \param data
     */
    bool insertInterface(int data);

    /*!
     * \brief removeInterface
     * \param data
     * \return
     */
    struct NodeOfSplayTree* removeInterface(int data);

    /*!
     * \brief searchInterface
     * \param data
     * \return
     */
    bool searchInterface(int data);

    /*!
     * \brief getRoot
     * \return
     */
    NodeOfSplayTree* getRoot();
private:
    struct NodeOfSplayTree* root = nullptr;

    /*!
     * \brief exibirSubArvore1
     * \param n
     * \param content
     * \param count
     */
    void exibirSubArvore1(NodeOfSplayTree *n, std::string &content, int& count);

    /*!
     * \brief exibirSubArvore2
     * \param father
     * \param isLeftSon
     * \param n
     * \param content
     * \param count
     */
    void exibirSubArvore2(NodeOfSplayTree *father, bool isLeftSon, NodeOfSplayTree *n, std::string &content, int &count);

    /*!
     * \brief getFatherOfPredecessor
     * \param n
     * \return
     */
    NodeOfSplayTree *getFatherOfPredecessor(NodeOfSplayTree *n);

    /*!
     * \brief preOrder
     * \param node
     * \param content
     */
    void preOrder(NodeOfSplayTree *node, std::string &content);

    /*!
     * \brief inOrder
     * \param node
     * \param content
     */
    void inOrder(NodeOfSplayTree *node, std::string &content);

    /*!
     * \brief posOrder
     * \param node
     * \param content
     */
    void posOrder(NodeOfSplayTree *node, std::string &content);

    /*!
     * \brief splaying
     * \param node
     */
    void splaying(NodeOfSplayTree *node);

    /*!
     * \brief insert
     * \param data
     * \return
     */
    struct NodeOfSplayTree* insert(int data);

    /*!
     * \brief remove
     * \param data
     * \return
     */
    RemoveReturn remove(int data);

    /*!
     * \brief search
     * \param data
     * \return
     */
    NodeOfSplayTree* search(int data);

    /*!
     * \brief getSideIndicatorOfChildInFather
     * \param node
     * \return
     */
    Direction getSideIndicatorOfChildInFather(NodeOfSplayTree *node);

    /*!
     * \brief replaceChildInFather
     * \param father
     * \param old
     * \param newSon
     */
    void replaceChildInFather(NodeOfSplayTree *father, NodeOfSplayTree *old, NodeOfSplayTree *newSon);

    /*!
     * \brief zig
     * \param node
     */
    void zig(NodeOfSplayTree *node);

    /*!
     * \brief zag
     * \param node
     */
    void zag(NodeOfSplayTree *node);
};

#endif // SPLAYTREE_H
