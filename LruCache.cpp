//
// Created by tenghuanhe on 2016/9/27.
//

#include <iostream>
#include <unordered_map>

using namespace std;

struct LruCacheNode {
    int key;
    int value;
    LruCacheNode *prev;
    LruCacheNode *next;

    LruCacheNode() : key(0), value(0), prev(NULL), next(NULL) {}
};

class LruCache {
private:
    unordered_map<int, LruCacheNode *> map;
    LruCacheNode *head;
    LruCacheNode *tail;
    int capacity;
    int count;

public:
    LruCache(int capacity);

    ~LruCache();

    int get(int key);

    void set(int key, int value);

private:
    void removeLruNode();

    void detachNode(LruCacheNode *node);

    void insertFront(LruCacheNode *node);
};

LruCache::LruCache(int capacity) {
    this->capacity = capacity;
    this->count = 0;
    head = new LruCacheNode;
    tail = new LruCacheNode;
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;

}

LruCache::~LruCache() {
    delete head;
    delete tail;
}

int LruCache::get(int key) {
    if (map.find(key) == map.end())
        return -1;
    else {
        LruCacheNode *node = map[key];
        detachNode(node);
        insertFront(node);
        return node->value;
    }
}

void LruCache::set(int key, int value) {
    if (map.find(key) == map.end()) {
        LruCacheNode *node = new LruCacheNode;
        if (count == capacity) {
            removeLruNode();
        }

        node->key = key;
        node->value = value;
        map[key] = node;
        insertFront(node);
        count++;
    } else {
        LruCacheNode *node = map[key];
        detachNode(node);
        node->value = value;
        insertFront(node);
    }
}

void LruCache::removeLruNode() {
    LruCacheNode *node = tail->prev;
    detachNode(node);
    map.erase(node->key);
    --count;
}

void LruCache::detachNode(LruCacheNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LruCache::insertFront(LruCacheNode *node) {
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
    node->prev = head;
}
