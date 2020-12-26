#include "../bst.cpp"
#include "gtest/gtest.h"

using namespace ::testing;

class BSTTest: public Test {
public:
    BST bst;
};

TEST_F(BSTTest, IsEmptyWhenCreated) {
    ASSERT_TRUE(bst.IsEmpty());
}

TEST_F(BSTTest, HasSizeZeroWhenCreated) {
    ASSERT_EQ(bst.Size(), 0);
}
