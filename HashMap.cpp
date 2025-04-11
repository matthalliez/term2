#include "KeyValuePair.cpp"
#include <vector>
#include <list>
#include <functional>
#include <cstddef>

template <typename K, typename V>
class HashMap{
    private:
    std::vector<std::list<KeyValuePair<K,V>>> buckets;
    size_t counter; //# of elements in the HashMap
    size_t bucketCounter; //# of buckets in the HashMap
    float loadFactor; //# of elements per bucket

    //method to rehash the hashmap when it gets full
    void rehash(size_t rehashedBuckets){
        auto oldBuckets = buckets;
        buckets.clear();
        buckets.rehash(rehashedBuckets);
        bucketCounter = rehashedBuckets;
        counter = 0;
        for(auto& bucket : oldBuckets){
            for(auto& pair : bucket){
                insert(pair.getKey(), pair.getValue());
            }
        }
    }

    public: 
    //constructors
    HashMap(size_t initialBuckets =16, float initialLoadFactor = 0.75 ) : buckets(initialBuckets), counter(0),bucketCounter(initialBuckets), loadFactor(initialLoadFactor){}
    //destructor
    ~HashMap() {} 

    //methods

    //inserts a key-value pair into the hashmap. if the key already exists, it updates the value
    bool insert(K key, V value){
        //if the hashmap needs to be rehashed from the addition
        if(static_cast<float>(counter+1)/bucketCounter > loadFactor){
            rehash(bucketCounter *2);
        }
        size_t bucketFinder = std::hash<K>{}(key) % bucketCounter;
        //check if the key already exists and sets the new value if it does
        for(auto& pair : buckets[bucketFinder]){
            if(pair.getKey() == key){
                pair.setValue(value);
                return true;
            }
        }
        //if the key doesnt exist then it inserts the new key-value pair
        buckets[bucketFinder].push_back(KeyValuePair<K,V>(key,value));
        counter++;
        return true;
    }

    //removes a key-value pair from the hashmap and returns true/false depending on if the key existed or not
    bool remove(K key){
        
        size_t bucketFinder = std::hash<K>{}(key) % bucketCounter;
        auto& bucket = buckets[bucketFinder];
        for(auto i = bucket.begin(); i != bucket.end(); ++i){
            if(i->getKey() == key){
                bucket.erase(i);
                counter--;
                return true;
            }
        }
        return false;

    }

    //returns the value associated with the key and true/false depending on if the key exists or not. A pointer to the value is returned in the value_out parameter
    bool get(K key, V& value_out){
        size_t bucketFinder = std::hash<K>{}(key) % bucketCounter;
        for(auto& pair : buckets[bucketFinder]){
            if(pair.getKey() == key){
                value_out = pair.getValue();
                return true;
            }
        }
        return false;

    }
};
