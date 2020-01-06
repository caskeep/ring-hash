#pragma once

#include <map>
#include <iostream>

template <class Node, class Data, typename Hash = std::hash<Data>, size_t seed = 67672385>
class HashRing
{
    typedef std::map<size_t, Node> RingMap;
public:
    HashRing(size_t repicas) : repicas_(repicas) {}
    HashRing(size_t repicas, Hash hash) : repicas_(repicas), hash_ (hash) {}
    void AddNode(const Node& node);
    void RemoveNode(const Node& node);
    Node* GetNode(const Data& data);
    const RingMap& GetRingMap() { return ring_; }
private:
    const size_t repicas_;
    RingMap ring_;
    Hash hash_;
};

template<class Node, class Data, typename Hash, size_t seed>
inline void HashRing<Node, Data, Hash, seed>::AddNode(const Node& node)
{
    for (size_t i = 0; i < repicas_; ++i)
    {
        size_t hash = hash_(node + i * seed);
        ring_[hash] = node;
        std::cout << "add " << hash << " node:" << node << std::endl;
    }
}

template<class Node, class Data, typename Hash, size_t seed>
inline void HashRing<Node, Data, Hash, seed>::RemoveNode(const Node& node)
{
    for (size_t i = 0; i < repicas_; ++i)
    {
        size_t hash = hash_(node + r * seed);
        ring_.erase(hash);
    }
}

template<class Node, class Data, typename Hash, size_t seed>
inline Node* HashRing<Node, Data, Hash, seed>::GetNode(const Data& data)
{
    if (ring_.empty())
    {
        return nullptr;
    }
    auto it = ring_.lower_bound(hash_(data));
    if (it == ring_.end())
    {
        return &(ring_.begin()->second);
    }
    return &it->second;
}
