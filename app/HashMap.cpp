#include "HashMap.hpp"

 

HashMap::HashMap()
    : hasher{hashFunction}, bucketSize{initialBucketCount}, totalInput{0}
    {
        buckets = new Node*[bucketSize];
        for (int n = 0; n < bucketSize; n++)
        {
            buckets[n] = nullptr;
        }
    }

HashMap::HashMap(HashFunction hasher)
    : hasher{hasher}, bucketSize{initialBucketCount}, totalInput{0}
    {
        buckets = new Node*[bucketSize];
        for (int n = 0; n < bucketSize; n++)
        {
            buckets[n] = nullptr;
        }
    }

HashMap::HashMap(const HashMap& hm)
    : hasher{hm.hasher}, bucketSize{hm.bucketSize},
      totalInput{hm.totalInput}, buckets{new Node*[hm.bucketSize]}
    {
        bucketsCopy(buckets, hm.buckets, bucketSize);
    }

HashMap::~HashMap()
{
    for (int n = 0; n < bucketSize; n++)
    {
        if (buckets[n] == nullptr){}
        else
        {
            Node* node = buckets[n];
            Node* nextNode = node;
            while (nextNode != nullptr)
            {
                node = nextNode;
                nextNode = node->next;
                delete node;
            }
        }
    }
    delete[] buckets;
}


HashMap& HashMap::operator=(const HashMap& hm)
{
    if (this != &hm)
    {
        int beforeBucketSize = bucketSize;
        Node** beforeBuckets = buckets;
        bucketSize = hm.bucketSize;
        totalInput = hm.totalInput;
        hasher = hm.hasher;

        buckets = new Node*[bucketSize];
        bucketsCopy(buckets, hm.buckets, bucketSize);

        for (int n = 0; n < beforeBucketSize; n++)
        {
            if (beforeBuckets[n] == nullptr){}
            else
            {
                Node* node = beforeBuckets[n];
                Node* nextNode = node;
                while (nextNode != nullptr)
                {
                    node = nextNode;
                    nextNode = node->next;
                    delete node;
                }
            }
        }
        delete[] beforeBuckets;
    }
    return *this;
}

void HashMap::add(const std::string& key, const std::string& value)
{
    int bucketNum = (hasher(key)) % bucketSize;
    Node* lastNode = buckets[bucketNum];
    Node* node = lastNode;
    while (node != nullptr)
    {
        if ((node->key) == key)
        {
            return;
        }
        else
        {
            lastNode = node;
            node = node->next;
        }
    }

    totalInput = totalInput + 1;
    Node* addedNode = new Node;
    addedNode->key = key;
    addedNode->value = value;
    addedNode->next = nullptr;

    if (lastNode != nullptr)
    {
        lastNode->next = addedNode;
    }
    else
    {
        buckets[bucketNum] = addedNode;
    }

    double lFactor = loadFactor();
    if (lFactor > 0.8)
    {
        increaseHashTable();
    }
}

void HashMap::remove(const std::string& key)
{
    int bucketNum = (hasher(key)) % bucketSize;
    Node* lastNode = buckets[bucketNum];
    Node* node = lastNode;
    while (node != nullptr)
    {
        if (node->key == key)
        {
            if (lastNode->key == node->key)
            {
                buckets[bucketNum] = node->next;
                delete node;
            }
            else
            {
                lastNode->next = node->next;
                delete node;
            }
            totalInput = totalInput-1;
            break;
        }
        else
        {
            lastNode = node;
            node = node->next;
        }
    }
}

bool HashMap::contains(const std::string& key) const
{
    int bucketNum = (hasher(key)) % bucketSize;
    if (buckets[bucketNum] == nullptr)
    {
        return false;
    }
    else
    {
        Node* node = buckets[bucketNum];
        while (node != nullptr)
        {
            if (node->key == key)
            {
                return true;
            }
            else
            {
                node = node->next;
            }
        }
        return false;
    }
}

std::string HashMap::value(const std::string& key) const
{
    int bucketNum = (hasher(key)) % bucketSize;
    Node* node = buckets[bucketNum];
    while (node != nullptr)
    {
        if (node->key == key)
        {
            return node->value;
        }
        else
        {
            node = node->next;
        }
    }
    return "";
}

unsigned int HashMap::size() const
{
    return totalInput;
}

unsigned int HashMap::bucketCount() const
{
    return bucketSize;
}

double HashMap::loadFactor() const
{
    return ((totalInput+0.0) / bucketSize);
}

unsigned int HashMap::maxBucketSize() const
{
    int max = bucketMemberCount(buckets[0]);
    for (int n = 1; n < bucketSize; n++)
    {
        int current = bucketMemberCount(buckets[n]);
        if (current > max)
        {
            max = current;
        }
    }
    return max;
}


void HashMap::bucketsCopy(Node** target, Node** source, unsigned int bSize)
{
    for (int n = 0; n < bSize; n++)
    {
        if (source[n] == nullptr)
        {
            target[n] = nullptr;
        }
        else
        {
            Node* node = new Node;
            Node* t = node;
            Node* s = source[n];
            while (s != nullptr)
            {
                node->key = s->key;
                node->value = s->value;
                if (s->next == nullptr)
                {
                    node->next = nullptr;
                    s = s->next;
                }
                else
                {
                    node->next = new Node;
                    node = node->next;
                    s = s->next;
                }
            }
            target[n] = t;
        }
    }
}

void HashMap::increaseHashTable()
{
    int beforeBucketSize = bucketSize; 
    totalInput = 0;
    bucketSize = ((bucketSize * 2) + 1); 
    Node **beforeBuckets = buckets; 

    buckets = new Node* [bucketSize]; 
    for(int n = 0; n < bucketSize; n++)
    {
        buckets[n] = nullptr; 
    }

    for(int n = 0; n < beforeBucketSize; n++)
    {
        Node *node = beforeBuckets[n]; 
        if(node == nullptr) 
        {
            buckets[n] = nullptr;
        }
        else
        {       
            while(node != nullptr)
            {
                add(node->key,node->value); 
                node = node->next; 
            }
        }
    }

    for (int n = 0; n < beforeBucketSize; n++)
    {
        if (beforeBuckets[n] == nullptr){}
        else
        {
            Node* node = beforeBuckets[n];
            Node* nextNode = node;
            while (nextNode != nullptr)
            {
                node = nextNode;
                nextNode = node->next;
                delete node;
            }
        }
    }
    delete[] beforeBuckets;    
}

int HashMap::bucketMemberCount(const Node* bucket) const
{
    int count = 0;
    while (bucket != nullptr)
    {
        count = count + 1;
        bucket = bucket->next;
    }
    return count;
}