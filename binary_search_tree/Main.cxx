#include <iostream>

#include "binary_search_tree.hxx"

int main()
{
    tree::binary_search_tree<int> tree;
    std::cout << "empty: " << tree.empty() << std::endl;
    std::cout << "\ninserting" << std::endl;
    tree.insert(0);
    tree.insert(-2);
    tree.insert(2);
    tree.insert(-1);
    tree.insert(-3);
    tree.insert(1);
    tree.insert(3);
    std::cout << "inorder: ";
    tree.inorder([](int v) { std::cout << v << " ";});
    std::cout << std::endl;
    std::cout << "preorder: ";
    tree.preorder([](int v) { std::cout << v << " ";});
    std::cout << std::endl;
    std::cout << "postorder: ";
    tree.postorder([](int v) { std::cout << v << " ";});
    std::cout << std::endl;

    std::cout << "empty: " << tree.empty() << std::endl;
    std::cout << "height: " << tree.height() << std::endl;
    std::cout << "nodes: " << tree.nodes() << std::endl;
    std::cout << "leaves: " << tree.leaves() << std::endl;

    std::cout << "\ncleaning" << std::endl;
    tree.clean();
    std::cout << "empty: " << tree.empty() << std::endl;
    std::cout << "height: " << tree.height() << std::endl;
    std::cout << "nodes: " << tree.nodes() << std::endl;
    std::cout << "leaves: " << tree.leaves() << std::endl;

    return 0;
}
