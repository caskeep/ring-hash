// ring_hash.cpp : Defines the entry point for the application.
//

#include "ring_hash.h"
#include "ring_hash_imp.h"
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
    HashRing < size_t, size_t> ring(3);
    ring.AddNode(10);
    ring.AddNode(11);
    ring.AddNode(12);
    ring.AddNode(13);
    auto ringMap = ring.GetRingMap();
    for (auto it = ringMap.begin(); it != ringMap.end(); ++it)
    {
        cout << it->first << " -> " << it->second << endl;
    }
    for (size_t data = 0; data < 1000; data += 100)
    {
        auto node = ring.GetNode(data);
        if (nullptr != node)
        {
            cout << " data:" << data << " -> " << *node << endl;
        }
    }
	return 0;
}
