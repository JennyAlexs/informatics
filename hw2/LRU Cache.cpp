#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) {
        maxCapacity = capacity;
    }

    int get(int key) {
        if (cacheMap.count(key) == 0) {
            return -1;
        } else {
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            return cacheMap[key]->second;
        }
    }

    void put(int key, int value) {
        if (cacheMap.count(key) == 0) {
            if (cacheList.size() == maxCapacity) {
                cacheMap.erase(cacheList.back().first);
                cacheList.pop_back();
            }
            cacheList.push_front(make_pair(key, value));
            cacheMap[key] = cacheList.begin();
        } else {
            cacheMap[key]->second = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        }
    }

private:
    int maxCapacity;
    list<pair<int, int>> cacheList;
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;
};

int main()
{
    vector<int> v;
    cout << "Initial capacity: " << v.capacity() << endl;

    for(int i=0; i<20; i++)
    {
        v.push_back(i);

        if(v.capacity() > v.size())
        {
            cout << "Capacity increased at: " << v.capacity() << endl;
        }
    }

    cout << "Final capacity: " << v.capacity() << endl;

    vector<int> v1;
    v1.reserve(1000);
    cout << "Capacity after reserve: " << v1.capacity() << endl;

    vector<int> v2(10000000);
    cout << "Capacity of large vector: " << v2.capacity() << endl;

    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;  // returns 1
    cache.put(3, 3);
    cout << cache.get(2) << endl;  // returns -1
    cache.put(4, 4);  
    cout << cache.get(1) << endl;  // returns -1
    cout << cache.get(3) << endl;  // returns 3
    cout << cache.get(4) << endl;  // returns 4

    return 0;
}
