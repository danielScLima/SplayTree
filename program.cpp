// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "splaytree.h"

TEST_CASE( "Testing the insert call in the tree", "[single-file]" )
{	
	SplayTree s;
	NodeOfSplayTree *root = s.getRoot();
	REQUIRE(root == nullptr);
	
	s.insertInterface(50);
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 50);
	REQUIRE(root->left == nullptr);
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(60); //will produce a zag movement (to the left)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 60);
	
	REQUIRE(root->left != nullptr);
	REQUIRE(root->left->data == 50);
	
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(40); //will produce a zig-zig movement (to the right)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 40);
	
	REQUIRE(root->left == nullptr);
	
	REQUIRE(root->right != nullptr);
	REQUIRE(root->right->data == 50);
	
	REQUIRE(root->right->right != nullptr);
	REQUIRE(root->right->right->data == 60);
}

TEST_CASE( "Testing the insert call, case 2 in the tree", "[single-file]" )
{
	SplayTree s;
	NodeOfSplayTree *root = s.getRoot();
	REQUIRE(root == nullptr);
	
	s.insertInterface(60);
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 60);
	REQUIRE(root->left == nullptr);
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(50); //will produce a zig movement (to the right)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 50);
	
	REQUIRE(root->right != nullptr);
	REQUIRE(root->right->data == 60);
	
	REQUIRE(root->left == nullptr);
	
	s.insertInterface(70); //will produce a zag-zag movement (to the left)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 70);
	
	REQUIRE(root->right == nullptr);
	
	REQUIRE(root->left != nullptr);
	REQUIRE(root->left->data == 60);
	
	REQUIRE(root->left->left != nullptr);
	REQUIRE(root->left->left->data == 50);
}

TEST_CASE( "Testing the insert call, case 3, in the tree", "[single-file]" )
{	
	SplayTree s;
	NodeOfSplayTree *root = s.getRoot();
	REQUIRE(root == nullptr);
	
	s.insertInterface(50);
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 50);
	REQUIRE(root->left == nullptr);
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(60); //will produce a zag movement (to the left)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 60);
	
	REQUIRE(root->left != nullptr);
	REQUIRE(root->left->data == 50);
	
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(55); //will produce a zagzig = zag (to left) and zig
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 55);
	REQUIRE(root->left->data == 50);
	REQUIRE(root->right->data == 60);
	
	
}

TEST_CASE( "Testing the insert call, case 4, in the tree", "[single-file]" )
{
	SplayTree s;
	NodeOfSplayTree *root = s.getRoot();
	REQUIRE(root == nullptr);
	
	s.insertInterface(60);
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 60);
	REQUIRE(root->left == nullptr);
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(50); //will produce a zig movement (to the right)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 50);
	
	REQUIRE(root->right != nullptr);
	REQUIRE(root->right->data == 60);
	
	REQUIRE(root->left == nullptr);
	
	s.insertInterface(55); //will produce a zigzag movement
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 55);
	REQUIRE(root->left->data == 50);
	REQUIRE(root->right->data == 60);
}


TEST_CASE( "Testing the remove call in the tree", "[single-file]" )
{	
	SplayTree s;
	NodeOfSplayTree *root = s.getRoot();
	REQUIRE(root == nullptr);
	
	s.insertInterface(50);
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 50);
	REQUIRE(root->left == nullptr);
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(60); //will produce a zag movement (to the left)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 60);
	
	REQUIRE(root->left != nullptr);
	REQUIRE(root->left->data == 50);
	
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(40); //will produce a zig-zig movement (to the right)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 40);
	
	REQUIRE(root->left == nullptr);
	
	REQUIRE(root->right != nullptr);
	REQUIRE(root->right->data == 50);
	
	REQUIRE(root->right->right != nullptr);
	REQUIRE(root->right->right->data == 60);
	
	NodeOfSplayTree *noderem = s.removeInterface(60);//the father become root
	
	REQUIRE(noderem != nullptr);
	REQUIRE(noderem->data == 60);
	delete noderem;
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 50);
	REQUIRE(root->left->data == 40);
	REQUIRE(root->right == nullptr);
}

TEST_CASE( "Testing the remove call, case 2, in the tree", "[single-file]" )
{	
	SplayTree s;
	NodeOfSplayTree *root = s.getRoot();
	REQUIRE(root == nullptr);
	
	s.insertInterface(50);
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 50);
	REQUIRE(root->left == nullptr);
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(60); //will produce a zag movement (to the left)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 60);
	
	REQUIRE(root->left != nullptr);
	REQUIRE(root->left->data == 50);
	
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(40); //will produce a zig-zig movement (to the right)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 40);
	
	REQUIRE(root->left == nullptr);
	
	REQUIRE(root->right != nullptr);
	REQUIRE(root->right->data == 50);
	
	REQUIRE(root->right->right != nullptr);
	REQUIRE(root->right->right->data == 60);
	
	NodeOfSplayTree *noderem = s.removeInterface(50);
	
	REQUIRE(noderem != nullptr);
	REQUIRE(noderem->data == 50);
	delete noderem;
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 40);
	REQUIRE(root->right->data == 60);
	REQUIRE(root->left == nullptr);
}

TEST_CASE( "Testing the search call in the tree", "[single-file]" )
{	
	SplayTree s;
	NodeOfSplayTree *root = s.getRoot();
	REQUIRE(root == nullptr);
	
	s.insertInterface(50);
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 50);
	REQUIRE(root->left == nullptr);
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(60); //will produce a zag movement (to the left)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 60);
	
	REQUIRE(root->left != nullptr);
	REQUIRE(root->left->data == 50);
	
	REQUIRE(root->right == nullptr);
	
	s.insertInterface(40); //will produce a zig-zig movement (to the right)
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 40);
	
	REQUIRE(root->left == nullptr);
	
	REQUIRE(root->right != nullptr);
	REQUIRE(root->right->data == 50);
	
	REQUIRE(root->right->right != nullptr);
	REQUIRE(root->right->right->data == 60);
	
	REQUIRE(s.searchInterface(60));
	
	root = s.getRoot();
	REQUIRE(root != nullptr);
	
	REQUIRE(root->data == 60);
	
	REQUIRE(root->right == nullptr);
	
	REQUIRE(root->left != nullptr);
	REQUIRE(root->left->data == 50);
	
	REQUIRE(root->left->left != nullptr);
	REQUIRE(root->left->left->data == 40);
	
}

TEST_CASE( "Testing the insert of duplicated entries in in the tree", "[single-file]" )
{	
	SplayTree s;	
	REQUIRE(s.insertInterface(50));
	REQUIRE(s.insertInterface(40));
	REQUIRE(s.insertInterface(10));
	REQUIRE(s.insertInterface(20));
	
	REQUIRE(!s.insertInterface(50));
	REQUIRE(!s.insertInterface(40));
	REQUIRE(!s.insertInterface(10));
	REQUIRE(!s.insertInterface(20));
}