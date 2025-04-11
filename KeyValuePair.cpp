template <typename K, typename V>
class KeyValuePair{
    private:
    K key;
    V value;

    public:
    //constructors
    KeyValuePair(){}
    KeyValuePair(const K& k, const V& v): key(k), value(v) {}
    //destrcutor
    ~KeyValuePair(){}

    //gets the key
    K getKey() const{
        return key;
    }
    //gets the value
    V getValue() const{
        return value;
    }
    //sets a new value
    void setValue(const V& v){
        value = v;
    }
};
