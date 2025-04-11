#include "HashMap.cpp"
#include <iostream>
#include <chrono>
#include <vector>
#include <random> 
#include <iomanip>

void coreFunctions(){
    HashMap<std::string, int> testMap;
    int value;

    //demostrating the insert method
    std::cout << "insert(): " << std::endl;
    std::cout << "Test 1.1: Inserting ('Calvin', 18): " << (testMap.insert("Calvin", 18) ? "Passed" : "Failed") << std::endl;
    std::cout << "Test 1.2: Inserting ('Matt', 19): " << (testMap.insert("Matt", 19) ? "Passed" : "Failed") << std::endl;
    std::cout << "Test 1.3: Inserting ('Calvin', 7): " << (testMap.insert("Calvin", 7) ? "Passed" : "Failed") << std::endl;

    //demonstarting the remove method
    std::cout << "remove(): " << std::endl;
    std::cout << "Test 2.1: removing 'Calvin': " << (testMap.remove("Calvin") ? "Passed" : "Failed") << std::endl;

    //demonstrating the get method
    std::cout << "get(): " <<std::endl;
    std::cout << "Test 3.1: getting value for 'Matt': ";
    if(testMap.get("Matt", value)){
        std::cout <<value << std::endl;
    } else{
        std::cout << "Failed" <<std::endl;
    }
    std::cout << "Test 3.2: getting value for 'Calvin': ";
    if(testMap.get("Calvin", value)){
        std::cout <<value << std::endl;
    } else{
        std::cout << "Failed" <<std::endl;
    }
}
//clock helper method
template <typename Func>
double clocker(Func&& func){
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() / 1000.0;
}
void performanceTime(){
    int value;
    //random number generator
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(1, 1000000);

    //the for loop tests each size
    for(int size : {100,1000,10000}){
        std::cout << "Size being tested: " << size << std::endl;
        HashMap<int,int> testMap;
        std::vector<int> keys(size);
        //generating random keys
        for(int i=0; i<size; i++){
            keys[i] = dis(gen);
        }
        //measuring the insert time
        double insertTime = clocker([&](){
            for(int i =0; i<size; i++){
                testMap.insert(keys[i],i);
            }
        });
        std::cout << "Insert time: " << insertTime << std::endl;
        //measuring the remove time
        double removeTime = clocker([&](){
            for(int i =0; i<size; i++){
                testMap.remove(keys[i]);
            }
        });
        std::cout << "Remove time: " << removeTime << std::endl;
        //measuring the get time
        double getTime = clocker([&](){
            for(int i =0; i<size; i++){
                testMap.get(keys[i],value);
            }
        });
        std::cout << "Get time: " << getTime << std::endl;
    }
}
int main(){
    coreFunctions();
    performanceTime();
    return 0;
}
