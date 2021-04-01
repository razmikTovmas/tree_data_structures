#pragma once

#include <functional>

namespace tree
{

template <class T>
class node
{
public:
    node(const T& value, node<T>* pLeft = nullptr, node<T>* pRight = nullptr) noexcept
        : pLeft(pLeft)
        , pRight(pRight)
        , Value(value)
    { }

    node(const node& other) = delete;
    node(node&& other) = delete;
    node& operator=(const node& other) = delete;
    node& operator=(node&& other) = delete;
    ~node() = default;

    node<T>* pLeft;
    node<T>* pRight;
    T Value;

}; // node

template <class T, class Compare = std::less<T>>
class binary_search_tree
{
public:
    using key_type = T;
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = Compare;
    using value_compare = Compare;
    using reference = value_type&;
    using const_reference = const value_type&;
    using node_type = node<value_type>;

public:
    binary_search_tree() noexcept;
    binary_search_tree(const binary_search_tree& other);
    binary_search_tree(binary_search_tree&& other) noexcept;
    binary_search_tree& operator=(const binary_search_tree& other);
    binary_search_tree& operator=(binary_search_tree&& other) noexcept;
    ~binary_search_tree() noexcept;

private:
    template<class UnaryFunction>
    void inorder(const node_type* pNode, UnaryFunction& f) const;
    template<class UnaryFunction>
    void preorder(const node_type* pNode, UnaryFunction& f) const;
    template<class UnaryFunction>
    void postorder(const node_type* pNode, UnaryFunction& f) const;

    size_type height(const node_type* pNode) const noexcept;
    size_type nodes(const node_type* pNode) const noexcept;
    size_type leaves(const node_type* pNode) const noexcept;
    node_type copy(const node_type* pNode);
    void clean(const node_type* pNode) noexcept;

public:
    template<class UnaryFunction>
    UnaryFunction inorder(UnaryFunction f) const;
    template<class UnaryFunction>
    UnaryFunction preorder(UnaryFunction f) const;
    template<class UnaryFunction>
    UnaryFunction postorder(UnaryFunction f) const;

    size_type height() const noexcept;
    size_type nodes() const noexcept;
    size_type leaves() const noexcept;
    inline bool empty() const noexcept;
    void clean() noexcept;

    void insert(const T& v);


private:
    node_type* m_pRoot;
    Compare isLess;

}; // binary_search_tree

////////////////////////////////////////////////////////////////////////////////
// Constructors/Destructor
////////////////////////////////////////////////////////////////////////////////
template <class T, class C>
binary_search_tree<T, C>::binary_search_tree() noexcept
    : m_pRoot(nullptr)
{ }

template <class T, class C>
binary_search_tree<T, C>::binary_search_tree(const binary_search_tree& other)
    : m_pRoot(nullptr)
{
    m_pRoot = copy(other.m_pRoot);
}

template <class T, class C>
binary_search_tree<T, C>::binary_search_tree(binary_search_tree&& other) noexcept
    : m_pRoot(other.m_pRoot)
{
    other.m_pRoot = nullptr;
}

template <class T, class C>
binary_search_tree<T, C>& binary_search_tree<T, C>::operator=(const binary_search_tree& other)
{
    m_pRoot = copy(other.m_pRoot);
    return *this;
}

template <class T, class C>
binary_search_tree<T, C>& binary_search_tree<T, C>::operator=(binary_search_tree&& other) noexcept
{
    m_pRoot = other.m_pRoot;
    other.m_pRoot = nullptr;
    return *this;
}

template <class T, class C>
binary_search_tree<T, C>::~binary_search_tree() noexcept
{
    clean();
}

////////////////////////////////////////////////////////////////////////////////
// Private member functions
////////////////////////////////////////////////////////////////////////////////
template <class T, class C>
template <class UF>
void binary_search_tree<T, C>::inorder(const node_type* pNode, UF& f) const
{
    if (nullptr != pNode) {
        inorder(pNode->pLeft, f);
        f(pNode->Value);
        inorder(pNode->pRight, f);
    }
}

template <class T, class C>
template <class UF>
void binary_search_tree<T, C>::preorder(const node_type* pNode, UF& f) const
{
    if (nullptr != pNode) {
        f(pNode->Value);
        preorder(pNode->pLeft, f);
        preorder(pNode->pRight, f);
    }
}

template <class T, class C>
template <class UF>
void binary_search_tree<T, C>::postorder(const node_type* pNode, UF& f) const
{
    if (nullptr != pNode) {
        postorder(pNode->pLeft, f);
        postorder(pNode->pRight, f);
        f(pNode->Value);
    }
}

template <class T, class C>
typename binary_search_tree<T, C>::size_type binary_search_tree<T, C>::height(const node_type* pNode) const noexcept
{
    if (nullptr == pNode) {
        return 0;
    }
    return std::max(height(pNode->pLeft), height(pNode->pRight)) + 1;

}

template <class T, class C>
typename binary_search_tree<T, C>::size_type binary_search_tree<T, C>::nodes(const node_type* pNode) const noexcept
{
    if (nullptr == pNode) {
        return 0;
    }
    return 1 + nodes(pNode->pLeft) + nodes(pNode->pRight);
}

template <class T, class C>
typename binary_search_tree<T, C>::size_type binary_search_tree<T, C>::leaves(const node_type* pNode) const noexcept
{
    if (nullptr == pNode) {
        return 1;
    }
    return leaves(pNode->pLeft) + leaves(pNode->pRight);
}

template <class T, class C>
typename binary_search_tree<T, C>::node_type binary_search_tree<T, C>::copy(const node_type* pNode)
{
    if (nullptr = pNode) {
        return nullptr;
    }
    return new node_type(pNode->Value, copy(pNode->pLeft), copy(pNode->pRight));
}

template <class T, class C>
void binary_search_tree<T, C>::clean(const node_type* pNode) noexcept
{
    if (nullptr != pNode) {
        clean(pNode->pLeft);
        clean(pNode->pRight);
        delete pNode;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Public member functions
////////////////////////////////////////////////////////////////////////////////
template <class T, class C>
template <class UF>
UF binary_search_tree<T, C>::inorder(UF f) const
{
    inorder(m_pRoot, f);
    return f;
}

template <class T, class C>
template <class UF>
UF binary_search_tree<T, C>::preorder(UF f) const
{
    preorder(m_pRoot, f);
    return f;
}

template <class T, class C>
template <class UF>
UF binary_search_tree<T, C>::postorder(UF f) const
{
    postorder(m_pRoot, f);
    return f;
}

template <class T, class C>
typename binary_search_tree<T, C>::size_type binary_search_tree<T, C>::height() const noexcept
{
    return height(m_pRoot);
}

template <class T, class C>
typename binary_search_tree<T, C>::size_type binary_search_tree<T, C>::nodes() const noexcept
{
    return nodes(m_pRoot);
}

template <class T, class C>
typename binary_search_tree<T, C>::size_type binary_search_tree<T, C>::leaves() const noexcept
{
    return leaves(m_pRoot);
}

template <class T, class C>
inline bool binary_search_tree<T, C>::empty() const noexcept
{
    return nullptr == m_pRoot;
}

template <class T, class C>
void binary_search_tree<T, C>::clean() noexcept
{
    clean(m_pRoot);
    m_pRoot = nullptr;
}

template <class T, class C>
void binary_search_tree<T, C>::insert(const T& v)
{
    node_type* pNewNode = new node_type(v);
    if (nullptr == m_pRoot) {
        m_pRoot = pNewNode;
        return;
    }
    node_type* curNode = m_pRoot;
    while (true) {
        if (isLess(v, curNode->Value)) {
            if (nullptr == curNode->pLeft) {
                curNode->pLeft = pNewNode;
                return;
            }
            curNode = curNode->pLeft;
        } else {
            if (nullptr == curNode->pRight) {
                curNode->pRight = pNewNode;
                return;
            }
            curNode = curNode->pRight;
        }
    }
}

} // namespace tree
