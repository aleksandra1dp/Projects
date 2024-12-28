#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"

using namespace std;





TEST(min_max){
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.min_element(), tree.end());
    ASSERT_EQUAL(tree.max_element(), tree.end());
    tree.insert(6);
    ASSERT_EQUAL(*tree.min_element(), 6);
    ASSERT_EQUAL(*tree.max_element(), 6);
    tree.insert(3);
    ASSERT_EQUAL(*tree.min_element(), 3);
    ASSERT_EQUAL(*tree.max_element(), 6);
    tree.insert(4);
    ASSERT_EQUAL(*tree.min_element(), 3);
    ASSERT_EQUAL(*tree.max_element(), 6);
    tree.insert(1);
    ASSERT_EQUAL(*tree.min_element(), 1);
    ASSERT_EQUAL(*tree.max_element(), 6);
    tree.insert(8);
    ASSERT_EQUAL(*tree.min_element(), 1);
    ASSERT_EQUAL(*tree.max_element(), 8);
    tree.insert(10);
    ASSERT_EQUAL(*tree.min_element(), 1);
    ASSERT_EQUAL(*tree.max_element(), 10);
    tree.insert(12);
    ASSERT_EQUAL(*tree.min_element(), 1);
    ASSERT_EQUAL(*tree.max_element(), 12);
    tree.insert(9);
    ASSERT_EQUAL(*tree.min_element(), 1);
    ASSERT_EQUAL(*tree.max_element(), 12);
    
}


TEST(test_empty) {
    BinarySearchTree<int> empty;
    ASSERT_TRUE(empty.empty());

    BinarySearchTree<int> oneBranch;
    oneBranch.insert(5);
    ASSERT_FALSE(oneBranch.empty());
}

TEST(test_height) {
    BinarySearchTree<int> empty;
    ASSERT_EQUAL(0, empty.height());

    BinarySearchTree<int> oneBranch;
    oneBranch.insert(5);
    ASSERT_EQUAL(1, oneBranch.height());

    BinarySearchTree<int> largeTree;
    largeTree.insert(6);
    largeTree.insert(5);
    largeTree.insert(8);
    largeTree.insert(1);
    largeTree.insert(3);
    largeTree.insert(7);
    largeTree.insert(9);
    ASSERT_EQUAL(4, largeTree.height());

    BinarySearchTree<int> unBalanced;
    unBalanced.insert(6);
    unBalanced.insert(5);
    unBalanced.insert(7);
    unBalanced.insert(1);
    unBalanced.insert(3);
    ASSERT_EQUAL(4, unBalanced.height());
}

TEST(test_size) {
    BinarySearchTree<int> empty;
    ASSERT_EQUAL(0, empty.size());
    ASSERT_TRUE(empty.empty());

    BinarySearchTree<int> oneBranch;
    oneBranch.insert(5);
    ASSERT_EQUAL(1, oneBranch.size());
    ASSERT_FALSE(oneBranch.empty());

    BinarySearchTree<int> largeTree;
    largeTree.insert(6);
    largeTree.insert(5);
    largeTree.insert(8);
    largeTree.insert(1);
    largeTree.insert(3);
    largeTree.insert(7);
    largeTree.insert(9);
    ASSERT_EQUAL(7, largeTree.size());
    ASSERT_FALSE(oneBranch.empty());
}

TEST(test_traversals) {
    BinarySearchTree<int> largeTree;
    largeTree.insert(6);
    largeTree.insert(5);
    largeTree.insert(8);
    largeTree.insert(1);
    largeTree.insert(3);
    largeTree.insert(7);
    largeTree.insert(9);

    std::ostringstream inorder_os; 
    std::ostringstream preorder_os;

    largeTree.traverse_inorder(inorder_os);
    ASSERT_EQUAL(inorder_os.str(), "1 3 5 6 7 8 9 ");

    largeTree.traverse_preorder(preorder_os);
    ASSERT_TRUE(preorder_os.str().find("5 ") == 2);
}

TEST(test_sorting_invariant) {
    BinarySearchTree<int> largeTree;
    largeTree.insert(6);
    largeTree.insert(5);
    largeTree.insert(8);
    largeTree.insert(1);
    largeTree.insert(3);
    largeTree.insert(7);
    largeTree.insert(9);

    ASSERT_TRUE(largeTree.check_sorting_invariant());
}

TEST(test_iterator) {
    BinarySearchTree<int> largeTree;
    largeTree.insert(6);
    largeTree.insert(5);
    largeTree.insert(8);
    largeTree.insert(1);
    largeTree.insert(3);
    largeTree.insert(7);
    largeTree.insert(9);

    std::vector<int> traversed;
    for (int val : largeTree) {
        traversed.push_back(val);
    }
    ASSERT_EQUAL(7, traversed.size());

    auto it = largeTree.begin();
    auto end_it = largeTree.end();
    ASSERT_TRUE(it != end_it);

    //cout << largeTree.to_string() << endl << endl;

    ASSERT_EQUAL(1, *it);
    ++it;
    ASSERT_EQUAL(3, *it);
    ++it;
    ASSERT_EQUAL(5, *it);
    ++it;
    ASSERT_EQUAL(6, *it);
    ++it;
    ASSERT_EQUAL(7, *it);
    
    ASSERT_TRUE(largeTree.check_sorting_invariant());    
    largeTree.insert(2);
    *it = 10;
    //cout << largeTree.to_string() << endl << endl;
    ASSERT_FALSE(largeTree.check_sorting_invariant());   
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant()); 
}

TEST(test_min_element) {
    BinarySearchTree<int> largeTree;
    largeTree.insert(6);
    largeTree.insert(5);
    largeTree.insert(8);
    largeTree.insert(1);
    largeTree.insert(3);
    largeTree.insert(7);
    largeTree.insert(9);

    auto it = largeTree.min_element();
    ASSERT_TRUE(it != largeTree.end());
    ASSERT_EQUAL(1, *it);
}

TEST(test_max_element) {
    BinarySearchTree<int> largeTree;
    largeTree.insert(6);
    largeTree.insert(5);
    largeTree.insert(8);
    largeTree.insert(1);
    largeTree.insert(3);
    largeTree.insert(7);
    largeTree.insert(9);

    auto it = largeTree.max_element();
    ASSERT_TRUE(it != largeTree.end());
    ASSERT_EQUAL(9, *it);
}


TEST(test_sorting_invariant_2){
    BinarySearchTree<int> largeTree;
    largeTree.insert(6);
    largeTree.insert(5);
    largeTree.insert(8);
    largeTree.insert(1);
    largeTree.insert(3);
    largeTree.insert(7);
    largeTree.insert(9);
    BinarySearchTree<int>::Iterator it = largeTree.begin();
    for (int x=0;x<6;x++)it++;

    ASSERT_EQUAL(*it, 9);

    *it = 1;

    ASSERT_FALSE(largeTree.check_sorting_invariant());

}

TEST(test_min_greater_than) {
    BinarySearchTree<int> largeTree;
    largeTree.insert(6);
    largeTree.insert(5);
    largeTree.insert(8);
    largeTree.insert(1);
    largeTree.insert(3);
    largeTree.insert(7);
    largeTree.insert(9);

    auto it = largeTree.min_greater_than(4);
    ASSERT_TRUE(it != largeTree.end());
    ASSERT_EQUAL(5, *it);

    it = largeTree.min_greater_than(9);
    ASSERT_TRUE(it == largeTree.end());

    it = largeTree.min_greater_than(0);
    ASSERT_TRUE(it != largeTree.end());
    ASSERT_EQUAL(1, *it);
}

TEST(test_find) {
    BinarySearchTree<int> largeTree;
    largeTree.insert(6);
    largeTree.insert(5);
    largeTree.insert(8);
    largeTree.insert(1);
    largeTree.insert(3);
    largeTree.insert(7);
    largeTree.insert(9);

    ASSERT_TRUE(largeTree.find(3) != largeTree.end());
    ASSERT_TRUE(largeTree.find(7) != largeTree.end());
    ASSERT_TRUE(largeTree.find(1) != largeTree.end());
    //ASSERT_TRUE(largeTree.find(9) == largeTree.end());
    ASSERT_TRUE(largeTree.find(0) == largeTree.end());
}

TEST(test_insert) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_EQUAL(1, tree.size());
    ASSERT_TRUE(tree.find(5) != tree.end());

    tree.insert(3);
    tree.insert(7);
    ASSERT_EQUAL(3, tree.size());
    ASSERT_TRUE(tree.check_sorting_invariant());
}


TEST(test_copy) {
    BinarySearchTree<int> empty;
    BinarySearchTree<int> emptyCopy(empty);
    ASSERT_TRUE(emptyCopy.empty());

    BinarySearchTree<int> original;
    original.insert(1);
    original.insert(4);
    original.insert(8);

    BinarySearchTree<int> copy(original);
    ASSERT_EQUAL(copy.size(), original.size());
    ASSERT_TRUE(copy.check_sorting_invariant());

    original.insert(22);
    ASSERT_EQUAL(original.size(), copy.size() + 1);
}


TEST(invarient_3){
    BinarySearchTree<int> t;
    t.insert(4);
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(8);
    t.insert(6);
    t.insert(5);
    t.insert(7);
    t.insert(9);
    t.insert(10);
    cout << t.to_string() << endl;

    ASSERT_TRUE(t.check_sorting_invariant());
    //1
    auto i = t.begin();
    *i = 99;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 0;
    ASSERT_TRUE(t.check_sorting_invariant());
    *i = 1;

    i++;
    *i = 0;
    //cout << t.to_string() << endl;
    cout << t.to_string() << endl;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 99;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 2;

    i++;
    *i = 0;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 99;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 3;

    i++;
    *i = 0;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 99;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 4;

    i++;
    *i = 0;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 99;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 5;

    i++;
    *i = 0;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 99;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 6;
    
    i++;
    *i = 0;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 99;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 7;

    i++;
    *i = 0;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 99;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 8;

    i++;
    *i = 0;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 99;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 9;

    i++;
    *i = 0;
    ASSERT_FALSE(t.check_sorting_invariant());
    *i = 99;
    ASSERT_TRUE(t.check_sorting_invariant());
    *i = 10;

}

TEST_MAIN()
