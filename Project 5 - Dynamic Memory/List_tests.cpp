#include "List.hpp"
#include <iterator>
#include <iostream>
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(empty_constructor) {
    List<int> l1;
    ASSERT_TRUE(l1.empty());
    ASSERT_EQUAL(l1.size(), 0);
    l1.push_front(2);
    l1.push_back(3);
    l1.push_front(1);
    ASSERT_FALSE(l1.empty());
    ASSERT_EQUAL(l1.size(), 3);
    int count = 1;
    for (auto n = l1.begin(); n != l1.end(); n++){
        ASSERT_EQUAL(*n, count);
        count++;
    }

    l1.clear();
    ASSERT_TRUE(l1.empty());
    ASSERT_TRUE(l1.size() == 0);
}

TEST(big_three){
    List<int> l1;
    l1.push_front(2);
    l1.push_back(3);
    l1.push_front(1);
    auto i1 = l1.begin();

    List<int>l2(l1);
    auto i2 = l2.begin();
    ASSERT_FALSE(i1 == i2);
    ASSERT_TRUE(*i1 == *i2);

    ASSERT_FALSE(l2.empty());
    ASSERT_EQUAL(l2.size(), 3);
    int count = 1;
    for (auto n = l2.begin(); n != l2.end(); n++){
        ASSERT_EQUAL(*n, count);
        count++;
    }


    List<int>l3 = l1;
    auto i3 = l3.begin();

    ASSERT_FALSE(i1 == i3);
    ASSERT_TRUE(*i1 == *i3);

    ASSERT_FALSE(l3.empty());
    ASSERT_EQUAL(l3.size(), 3);
    count = 1;
    for (auto n = l3.begin(); n != l3.end(); n++){
        ASSERT_EQUAL(*n, count);
        count++;
    }
}

TEST(list_manip){
    List<int> l1;
    l1.push_front(2);
    auto i = l1.begin();
    i++;
    ASSERT_TRUE(i == l1.end());
    i--;
    ASSERT_TRUE(*i == 2);

    l1.push_back(4);
    i++;
    l1.insert(i, 3);
    ASSERT_EQUAL(*i, 4);
    l1.push_front(1);

    ASSERT_TRUE(l1.size() == 4);
    int count = 0;
    for (auto n = l1.begin(); n != l1.end(); n++){
        count++;
        ASSERT_EQUAL(*n, count);
    }
    ASSERT_EQUAL(count, 4);
    i--;
    i = l1.erase(i);
    i = l1.erase(i);
    ASSERT_TRUE(i == l1.end());
    count = 0;
    for (auto n = l1.begin(); n != l1.end(); n++){
        count++;
        ASSERT_EQUAL(*n, count);
    }
    ASSERT_EQUAL(count, 2);
    i--;

}

TEST(assignment_operator_1){
    List<int> l1;
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(5);
    ASSERT_EQUAL(l1.size(), 3);
    auto ity = l1.begin();
    ASSERT_EQUAL(*ity, 1);
    ++ity;
    ASSERT_EQUAL(*ity, 3);
    ++ity;
    ASSERT_EQUAL(*ity, 5);

    
    List<int> l2; //differnet size from 1
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(6);
    l2.push_back(8);
    l2 = l1; 

    auto it1 = l1.begin();
    auto it2 = l2.begin();
    ASSERT_FALSE(it1 == it2);

    ASSERT_EQUAL(l2.size(), 3);
   
    auto it = l2.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 3);
    it++;
    ASSERT_EQUAL(*it, 5);
    --it;
    ASSERT_EQUAL(*it, 3);
    it--;
    ASSERT_EQUAL(*it, 1);
    
    //Deep copy test
    l1.push_back(7);
    ASSERT_EQUAL(l2.size(), 3);
    ASSERT_EQUAL(l1.size(), 4);
}

TEST (assignment_operator_2){
    
    List<int> l1;
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(5);
    l1.push_back(7);

    List<int> l3;
    l3.push_back(1);
    l3.push_back(2);
    l3 = l1; // should reset l3
    ASSERT_EQUAL(l3.size(), 4);

    List<int> emptyList;
    l3 = emptyList;
    ASSERT_TRUE(l3.empty());
    ASSERT_EQUAL(l3.size(), 0);

    int val[] = {1, 3, 5, 7};
    int i = 0;
    for (auto it = l3.begin(); it != l3.end(); ++it) {
        ASSERT_EQUAL(*it, val[i]);
        i++;
    }
}

TEST(assignment_operator_3){

    List<int> l1;
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(5);
    l1.push_back(7);
    
    List<int> l4;
    l4 = l1;
    ASSERT_EQUAL(l4.size(), 4);


    List<int> l5;
    List<int> l6;
    List<int> l7;
    l7.push_back(10);
    l5 = l6 = l7;
    ASSERT_EQUAL(l5.size(), 1);
    ASSERT_EQUAL(l6.size(), 1);
    ASSERT_EQUAL(l7.size(), 1);
    ASSERT_EQUAL(l5.front(), 10);
    ASSERT_EQUAL(l6.front(), 10);
    ASSERT_EQUAL(l7.back(), 10);

    

    



    
    // List<int> empty;
    // empty = empty;
    // ASSERT_TRUE(empty.empty());
    // ASSERT_EQUAL(empty.size(), 0);

}

TEST(assignment_operator_4){
    List<int> l9;
    l9.push_back(1);
    l9.push_back(2);
    List<int> l10;
    l10.push_back(3);
    l10 = l9;
    l9.push_back(4); //Modify og
    ASSERT_EQUAL(l10.size(), 2);
}


TEST(assignment_operator_5){
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);

    List<int> l3 = l1;

    l1 = l1;

    List<int> l2 = l1;

    ASSERT_EQUAL(l1.front(),l2.front());
    ASSERT_EQUAL(l1.back(),l2.back());

    ASSERT_EQUAL(l1.front(),l3.front());
    ASSERT_EQUAL(l1.back(),l3.back());

    ASSERT_EQUAL(l3.front(),l2.front());
    ASSERT_EQUAL(l3.back(),l2.back());


}

TEST(more_iterator_tests){
    List<int> l1;
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(5);

    auto it1 = l1.begin();
    ASSERT_EQUAL(*it1, 1);
    ++it1;
    ASSERT_EQUAL(*it1, 3);
    --it1;
    ASSERT_EQUAL(*it1, 1);

    auto it2x = l1.begin();
    ASSERT_TRUE(it1 == it2x);
    ++it2x;
    ASSERT_FALSE(it1 == it2x);
    ASSERT_TRUE(it1 != it2x);

    List<int> l3;
    l3.push_back(2);
    l3.push_back(4);

    l3 = l1; 
    auto it3 = l3.begin();
    ASSERT_EQUAL(*it3, 1);
    ++it3;
    ASSERT_EQUAL(*it3, 3);
    
    it1 = l1.begin();
    it3 = l3.begin();
    ASSERT_FALSE(it1 == it3);

    List<string> l2;
    l2.push_back("meow");
    l2.push_back("cat");

    auto it2 = l2.begin();
    ASSERT_EQUAL(*it2, "meow");
    ++it2;
    ASSERT_EQUAL(*it2, "cat");
    auto itx = l2.begin();
    ASSERT_EQUAL(itx->length(), 4);
    ++itx;
    ASSERT_EQUAL(itx->length(), 3);

    List<string> l4(l2);
    ASSERT_EQUAL(l4.front(), "meow");
    ASSERT_EQUAL(l4.back(), "cat");

}

TEST(edge_case_testing){
    List<int> l1; //empty
    ASSERT_TRUE(l1.begin() == l1.end());
 
    l1.push_back(1); // 1 value
    ASSERT_EQUAL(l1.front(), l1.back());
    l1.pop_front();
    ASSERT_TRUE(l1.empty());
    
    l1.push_front(1);//add 1
    l1.push_front(2);// 2
    l1.pop_back(); // only 2 left
    ASSERT_EQUAL(l1.size(), 1);
    ASSERT_EQUAL(l1.front(), 2);

    l1.clear();
    l1.clear();
    ASSERT_TRUE(l1.empty());

    l1.push_back(1);
    auto itx = l1.erase(l1.begin()); //erase 1 value
    ASSERT_TRUE(itx == l1.end());
    ASSERT_TRUE(l1.empty());
    ASSERT_EQUAL(l1.size(), 0);

    l1.push_back(1);
    l1.push_back(5);
    l1.push_back(7);
    itx = l1.erase(l1.begin()); //first
    ASSERT_EQUAL(*itx, 5);
    ASSERT_EQUAL(l1.front(), 5);
    itx = l1.begin();
    ++itx;
    itx = l1.erase(itx); //last
    ASSERT_TRUE(itx == l1.end());
    ASSERT_EQUAL(l1.back(), 5);
    ASSERT_EQUAL(l1.size(), 1);
    
    List<int> l2;

    auto it = l2.insert(l2.begin(), 5); //insert into empty list
    ASSERT_EQUAL(l2.size(), 1);
    ASSERT_EQUAL(l2.front(), 5);
    ASSERT_EQUAL(l2.back(), 5);
    it = l2.insert(l2.begin(), 8); //beginning
    ASSERT_EQUAL(l2.front(), 8);
    ASSERT_EQUAL(*it, 8);
    it = l2.insert(l2.end(), 10); //end
    ASSERT_EQUAL(l2.back(), 10);
    ASSERT_EQUAL(*it, 10);
}

TEST(const_tests){
     List<int> l3 = []() {
        List<int> temp;
        temp.push_back(1);
        temp.push_back(2);
        temp.push_back(3);
        return temp;
    }();
    ASSERT_EQUAL(l3.size(), 3);
    auto it = l3.begin();
    auto end = l3.end();
    int val = 1;
    while(it != end) {
        ASSERT_EQUAL(*it, val);
        ++it;
        //++it;
        ++val;
    }
    
    const List<string> l2 = []() {
        List<string> temp;
        temp.push_back("meow");
        temp.push_back("cat");
        return temp;
    }();

    List<string>::Iterator constIt = l2.begin();  // const iterators
    ASSERT_EQUAL(constIt->length(), 4); 
    ASSERT_EQUAL(*constIt, "meow");    
    const List<string>::Iterator constEnd = l2.end();
    ASSERT_FALSE(constIt == constEnd);

   const List<int> emptyList;
    ASSERT_TRUE(emptyList.empty());
    ASSERT_EQUAL(emptyList.size(), 0);
    
}

TEST(iterator_equality){
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);

    List<int>::Iterator i1 = l1.begin();
    List<int>::Iterator i2 = l1.begin();

    ASSERT_TRUE(i1 == i2);
    ASSERT_FALSE(i1 == l1.end());
    
    i1++;
    ASSERT_FALSE(i1 == i2);
    ++i2;

    ASSERT_TRUE(i1 == i2);
    
    ASSERT_TRUE(i1 == i1);
    ASSERT_TRUE(i2 == i2);
    ASSERT_FALSE(i1 == l1.begin());

    List<int> l2 = l1;
    List<int>::Iterator i3 = l2.begin();
    i1 = l1.begin();

    ASSERT_TRUE(*i1 == *i3);
    ASSERT_FALSE(i1 == i3);
    i1++;
    ASSERT_FALSE(*i1 == *i3);
    ++i3;

    ASSERT_FALSE(i1 == i3);

    

}

TEST(operator_equal_test){
    List<int>::Iterator it1;
    List<int>::Iterator it2;
    List<int> l1; 
    List<int> l2; 
    ASSERT_FALSE(it1 == l1.end());    
    ASSERT_FALSE(l1.end() == it1);
    ASSERT_TRUE(l1.begin() == l1.end());
    ASSERT_FALSE(l1.end() == l2.end());  
    
    l1.push_back(5);
    l2.push_back(5);
    ASSERT_FALSE(l1.begin() == l2.begin());
    ASSERT_FALSE(l1.end() == l2.end());  
    ASSERT_FALSE(it1 == l1.begin());  
    ASSERT_FALSE(it1 == l1.end());
    ASSERT_TRUE(it1 != l1.begin());
    ASSERT_TRUE(it1 != l1.end());

    List<int>::Iterator it3 = l1.begin();
    List<int>::Iterator it4 = it3;
    ASSERT_TRUE(it3 == it4); 
    ASSERT_FALSE(it3 != it4);

    auto itl1 = l1.begin();
    ASSERT_FALSE(itl1 == l1.end());

    auto it = l1.begin();
    ++it;
    ASSERT_TRUE(it == l1.end());
}

TEST_MAIN()
