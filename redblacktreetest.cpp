#include <vector>
#include "UnitTest++.h"
#include "redblacktree.h"

SUITE(singleRbt)
{
    struct rbtFixture {
        void multipleInsert(redBlackTree& r, std::vector<int>& v) {
            for (unsigned int i = 0; i < v.size(); ++i) {
                r.rbInsert(v.at(i));
            }
        }
        void multipleDelete(redBlackTree& r, std::vector<int>& v) {
            for (unsigned int i = 0; i < v.size(); ++i) {
                r.rbDelete(v.at(i));
            }
        }
    };

    TEST(rbDefaultCtor)
    {
        std::cout << "TEST rbDefaultCtor:" << std::endl;
        redBlackTree rbt;
        Node* n = (rbt.getAlloc()).allocate(1);
        n->parent = NULL;
        n->left = NULL;
        n->right = NULL;
        n->data = 0;
        n->color = BLACK;

        CHECK_EQUAL(rbt.getRoot(), rbt.getNil());

        CHECK_EQUAL((rbt.getNil())->parent, n->parent);
        CHECK_EQUAL((rbt.getNil())->left, n->left);
        CHECK_EQUAL((rbt.getNil())->right, n->right);
        CHECK_EQUAL((rbt.getNil())->data, n->data);
        CHECK_EQUAL((rbt.getNil())->color, n->color);

        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST_FIXTURE(rbtFixture, rbDtor1)
    {
        std::cout << "TEST rbDtor1:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,3,2,100,4,10,7,27,199,28,28,8,9,12,167,11,29 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        rbt.~redBlackTree();
        rbt.rbPrint();
    }

    TEST(rbInsert1)
    {
        std::cout << "TEST rbInsert1:" << std::endl;
        redBlackTree rbt;
        rbt.rbInsert(1);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbInsert2)
    {
        std::cout << "TEST rbInsert2:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v = { 5,1,10 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbInsert3)
    {
        std::cout << "TEST rbInsert3:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,3,2,4,10,11,8 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbInsert4)
    {
        std::cout << "TEST rbInsert4:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,4,3,2,1,5,4,3,2,1 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete1)
    {
        std::cout << "TEST rbDelete1:" << std::endl;
        redBlackTree rbt;
        rbt.rbInsert(20);
        rbt.rbPrint();
        rbt.rbDelete(20);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete2)
    {
        std::cout << "TEST rbDelete2:" << std::endl;
        redBlackTree rbt;
        rbt.rbInsert(20);
        rbt.rbPrint();
        rbt.rbDelete(5);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete3)
    {
        std::cout << "TEST rbDelete3:" << std::endl;
        redBlackTree rbt;
        rbt.rbInsert(20);
        rbt.rbPrint();
        rbt.rbDelete(20);
        rbt.rbPrint();
        rbt.rbInsert(20);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete4)
    {
        std::cout << "TEST rbDelete4:" << std::endl;
        redBlackTree rbt;
        rbt.rbInsert(2);
        rbt.rbInsert(1);
        rbt.rbInsert(3);
        rbt.rbPrint();
        rbt.rbDelete(2);
        rbt.rbPrint();
        std::cout << std::endl;
    }


    TEST(rbDelete5)
    {
        std::cout << "TEST rbDelete5:" << std::endl;
        redBlackTree rbt;
        rbt.rbInsert(2);
        rbt.rbInsert(1);
        rbt.rbInsert(3);
        rbt.rbPrint();
        rbt.rbDelete(1);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete6)
    {
        std::cout << "TEST rbDelete6:" << std::endl;
        redBlackTree rbt;
        rbt.rbInsert(2);
        rbt.rbInsert(1);
        rbt.rbInsert(3);
        rbt.rbPrint();
        rbt.rbDelete(3);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete7)
    {
        std::cout << "TEST rbDelete7:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,3,2,4,10,7,8,9,12,11 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        rbt.rbDelete(7);
        rbt.rbPrint();
        rbt.rbDelete(10);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete8)
    {
        std::cout << "TEST rbDelete8:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,3,2,100,4,10,7,27,199,28,28,8,9,12,167,11 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        rbt.rbDelete(7);
        rbt.rbPrint();
        rbt.rbDelete(10);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete9)
    {
        std::cout << "TEST rbDelete9:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,3,2,100,4,10,7,27,199,28,28,8,9,12,167,11,29 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        rbt.rbDelete(5);
        rbt.rbPrint();
        rbt.rbInsert(100);
        rbt.rbInsert(400);
        rbt.rbInsert(300);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete10)
    {
        std::cout << "TEST rbDelete10:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,3,2,100,4,10,7,27,199,28,28,8,9,12,167,11,29 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        rbt.rbDelete(10);
        rbt.rbPrint();
        rbt.rbInsert(100);
        rbt.rbInsert(400);
        rbt.rbInsert(300);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete11)
    {
        std::cout << "TEST rbDelete11:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,3,2,100,4,10,7,27,199,28,28,8,9,12,167,11,29 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        rbt.rbDelete(167);
        rbt.rbPrint();
        rbt.rbInsert(100);
        rbt.rbInsert(400);
        rbt.rbInsert(300);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete12)
    {
        std::cout << "TEST rbDelete12:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,3,2,100,4,10,7,27,199,28,28,8,9,12,167,11,29 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        rbt.rbDelete(28);
        rbt.rbPrint();
        rbt.rbInsert(100);
        rbt.rbInsert(400);
        rbt.rbInsert(300);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete13)
    {
        std::cout << "TEST rbDelete13:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,3,2,100,4,10,7,27,199,28,28,8,9,12,167,11,29 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        rbt.rbDelete(199);
        rbt.rbPrint();
        rbt.rbInsert(100);
        rbt.rbInsert(400);
        rbt.rbInsert(300);
        rbt.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbDelete14)
    {
        std::cout << "TEST rbDelete14:" << std::endl;
        redBlackTree rbt;
        rbtFixture f;
        std::vector<int> v { 5,3,2,100,4,10,7,27,199,28,28,8,9,12,167,11,29 };
        f.multipleInsert(rbt, v);
        rbt.rbPrint();
        f.multipleDelete(rbt, v);
        rbt.rbPrint();
        std::cout << std::endl;
    }

//////////////////////////////////////////////////////////////////////////////////////////
// the following tests involve at least two red-black trees
    TEST(rbCopyCtor1)
    {
        std::cout << "TEST rbCopyCtor1:" << std::endl;
        redBlackTree rbt1;
        redBlackTree rbt2(rbt1);

        Node* n = (rbt2.getAlloc()).allocate(1);
        n->parent = NULL;
        n->left = NULL;
        n->right = NULL;
        n->data = 0;
        n->color = BLACK;

        CHECK_EQUAL(rbt2.getRoot(), rbt2.getNil());

        CHECK_EQUAL((rbt2.getNil())->parent, n->parent);
        CHECK_EQUAL((rbt2.getNil())->left, n->left);
        CHECK_EQUAL((rbt2.getNil())->right, n->right);
        CHECK_EQUAL((rbt2.getNil())->data, n->data);
        CHECK_EQUAL((rbt2.getNil())->color, n->color);
    }


    TEST(rbCopyCtor2)
    {
        std::cout << "TEST rbCopyCtor2:" << std::endl;
        redBlackTree rbt1;
        rbt1.rbInsert(10);
        redBlackTree rbt2(rbt1);
        rbt2.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbCopyCtor3)
    {
        std::cout << "TEST rbCopyCtor3:" << std::endl;
        redBlackTree rbt1;
        rbtFixture f;
        std::vector<int> v { 5,3,2,100,4,10,7,27,199,28,28,8,9,12,167,11,29 };
        f.multipleInsert(rbt1, v);
        rbt1.rbPrint();
        redBlackTree rbt2(rbt1);
        rbt2.rbPrint();
        std::cout << std::endl;
    }

    TEST(rbAssign1)
    {
        std::cout << "TEST rbAssign1:" << std::endl;
        redBlackTree rbt1;
        redBlackTree rbt2;
        rbt1.rbInsert(10);
        rbt2 = rbt1;
        rbt1.rbPrint();
        rbt2.rbPrint();
    }

    TEST(rbAssign2)
    {
        std::cout << "TEST rbAssign2:" << std::endl;
        redBlackTree rbt1;
        rbtFixture f;
        std::vector<int> v { 5,3,2,100,4,10,7,27,199,28,28,8,9,12,167,11,29,1000 };
        f.multipleInsert(rbt1, v);
        rbt1.rbDelete(1000);
        redBlackTree rbt2;
        rbt2 = rbt1;
        rbt1.rbPrint();
        rbt2.rbPrint();
    }
}

