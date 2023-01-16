//
//  main.cpp
//  Ramsey
//
//  Created by Quinn Robertson on 8/9/22.
//

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <future>
#include <vector>
#include <fstream>

const std::vector<int> D{2,8,32,34,136,144,576,610,2440,2584,10336,10946,43784,46368};
//const int NOTDIV = 6;
const int LOOP_TIMES = 5;

void vecToFile(int valid, int n, int k, std::vector<std::vector<int>> vec){
    std::string filename = "./output" + std::to_string(n) + "x" + std::to_string(k) + ".txt";
    remove(filename.c_str());
    std::ofstream f;
    f.open(filename.c_str());
    f << "Red length: " << n << ", Blue length: " << k << std::endl;
    f << "This is forced at N = " << valid << std::endl;
    if(vec.size() == 0){
        f << "N/A";
        return;
    }
    for(int i = 0; i < vec.size(); i++){
        if(vec[0].size() == 0){
            f << "{}";
        }
        else{
            f << "{";
            for(int j = 0; j < vec[i].size()-1; j++){
                f << vec[i][j] << " ";
            }
            f << vec[i][vec[i].size()-1] << "}" << std::endl;
        }
    }
    f.close();
}

void printVec(std::vector<std::vector<int>> v);
void printVec(std::vector<int> v);

// v is a vector containing all numbers colored blue
// len is the length of a diff sequence to check
bool checkDiffSeq(std::vector<int> v, int len){
    if(len == 0){
        return true;
    }
    if(v.size() < len){
        return false;
    }
    int topB = v[v.size()-1];
    bool diffSeq = false;
    for(long i = v.size()-2; i >= 0; i--){
        if(std::find(D.begin(), D.end(), topB-v[i]) != D.end()){
        //if((topB-v[i] == 2) || (((topB-v[i]) % NOTDIV) != 0)){
            std::vector<int> input(v.begin(), v.begin()+i+1);
            diffSeq = diffSeq | checkDiffSeq(input, len-1);
            if(diffSeq){
                break;
            }
        }
    }

    
    return diffSeq;
}

bool checkArithmeticProgression(std::vector<int> v, int d, int len){
    if(len == 0){
        return true;
    }
    if(v.size() < len){
        return false;
    }
    int arithCheck = v[v.size()-1] - d;
    if(arithCheck < 1) return false;
    for(int i = 0; i < v.size()-1; i++){
        if(v[i] == arithCheck){
            std::vector<int> newV(v.begin(), v.begin() + i+1);
            return checkArithmeticProgression(newV, d, len-1);
        }
    }
    return false;
}

bool checkRed(std::vector<int> v, int k) {
    // false means there is a coloring
    // true means that there is no coloring
    // Take input array which is a coloring,
    // take all blue out
    // get all combinations of length k including end number
    
    std::vector<int> rVec;
    // Convert v to list of indeces
    for(int i = 0; i < v.size(); i++){
        if(v[i] == 0){
            rVec.push_back(i+1);
        }
    }
    
    if(rVec.size() < k) return true;
    /*
    
    // check for arithmetic progression
    // return true if coloring does not exist or false if it does
    int newR = rVec[rVec.size()-1];
    bool arithBool = false;
    for(int i = int(rVec.size())-2; i >= 0; i--){
        int check = rVec[i];
        std::vector<int> input(rVec.begin(), rVec.begin()+i+1);
        //if(std::find(D.begin(), D.end(), newR-check) != D.end()){
        if((newR-check == 2) || (((newR-check) % NOTDIV) != 0)){
            arithBool = checkArithmeticProgression(input, newR - check, k-1) | arithBool;
        }
        if(arithBool) break;
    }
    
    return !arithBool;
    */
    return !checkDiffSeq(rVec, k);
}

bool checkBlue(std::vector<int> v, int k) {
    // false means there is a coloring
    // true means that there is no coloring
    // Take input array which is a coloring,
    // take all blue out
    // get all combinations of length k including end number
    
    std::vector<int> bVec;
    // Convert v to list of indeces
    for(int i = 0; i < v.size(); i++){
        if(v[i] == 1){
            bVec.push_back(i+1);
        }
    }
    
    if(bVec.size() < k) return true;
    
    return !checkDiffSeq(bVec, k);
}

void printVec(std::vector<int> v) {
    if(v.size() == 0){
        std::cout << "{}" << std::endl;
        return;
    }
    std::cout << "{";
    for (int i = 0; i < v.size() - 1; i++) {
        std::cout << v[i] << ',';
    }
    std::cout << v[v.size() - 1] << "}" << std::endl;
}

void printVec(std::vector<std::vector<int>> v) {
    if(v.size() == 0){
        std::cout << "{}" << std::endl;
        return;
    }
    std::cout << "{";
    std::vector<int> x;
    for (int i = 0; i < v.size() - 1; i++) {
        x = v[i];
        if (x.size() == 0) {
            std::cout << "{},";
        } else {
            std::cout << "{";
            for (int j = 0; j < x.size() - 1; j++) {
                std::cout << x[j] << ',';
            }
            std::cout << x[x.size() - 1] << "},";
        }
    }
    x = v[v.size() - 1];
    if (x.size() == 0) {
        std::cout << "{}";
    } else {
        std::cout << "{";
        for (int j = 0; j < x.size() - 1; j++) {
            std::cout << x[j] << ',';
        }
        std::cout << x[x.size() - 1] << "}";
    }
    std::cout << "}" << std::endl;
}

int checkSafeEmpty(std::vector<std::vector<int>> &safe) {
    for (int i = int(safe.size()) - 1; i >= 0; i--) {
        if (!safe[i].empty()) {
            return i;
        }
    }
    return -1;
}

void appendMaxColorings(std::vector<std::vector<int>> &returnVec, std::vector<int> vec) {
    if (returnVec.empty()) {
        returnVec.push_back(vec);
    } else {
        size_t vecLen = returnVec[0].size();
        if (vec.size() > vecLen) {
            // std::cout << vec.size() << std::endl;
            returnVec.clear();
            returnVec.push_back(vec);
            return;
        } else if (vec.size() == vecLen) {
            returnVec.push_back(vec);
            return;
        } else {
            return;
        }
    }
}

int runBlueRed(int n, int k, std::vector<std::vector<int>> &returnVec) {
    // This is to pass length of n and k
    // as n-1 and k-1 gaps in the progression
    // or diff-sequences
    n = n-1;
    k = k-1;
    
    std::vector<int> coloring{};
    std::vector<std::vector<int>> safe{};
    while(true){
        std::vector<int> coloring_r(coloring.begin(), coloring.end());
        coloring_r.push_back(0);
        std::vector<int> coloring_b(coloring.begin(), coloring.end());
        coloring_b.push_back(1);
        
        auto asyncRed = std::async(checkRed, coloring_r, n);
        //bool redOk = checkRed(coloring_r, n);
        bool blueOk = checkBlue(coloring_b, k);
        
        bool redOk = asyncRed.get();
        
        if (redOk) {
            coloring = coloring_r;
        } else if (blueOk) {
            coloring = coloring_b;
        }
        
        if (redOk && blueOk) {
            safe.push_back({1});
        }
        if ((redOk && !blueOk) || (!redOk && blueOk)) {
            safe.push_back({});
        }
        
        coloring_r.clear();
        coloring_r.shrink_to_fit();
        coloring_b.clear();
        coloring_b.shrink_to_fit();
        
        int allEmpty = checkSafeEmpty(safe);
        
        
        if (!redOk && !blueOk && (allEmpty == -1)) {
            return int(returnVec[0].size()) + 1;
        }
        
        else if (!redOk && !blueOk && (allEmpty != -1)) {
            // Modify safe and repeat
            coloring.erase(coloring.begin() + allEmpty, coloring.end());
            coloring.push_back(safe[allEmpty][0]);
            safe[allEmpty].erase(safe[allEmpty].begin());
            safe.erase(safe.begin() + allEmpty + 1, safe.end());
            // appendMaxColorings(returnVec, coloring);
            
        }
        appendMaxColorings(returnVec, coloring);
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    for(int n = 4; n <= LOOP_TIMES; n++){
        for(int k = 4; k <= LOOP_TIMES; k++){
            std::cout << "n,k : " << n << "," << k << std::endl;
            std::vector<std::vector<int>> returnVec{};
            int nValid = runBlueRed(n, k, returnVec);
            std::cout << "N: " << std::to_string(nValid) << std::endl;
            std::cout << "Safe colorings outputted to output" + std::to_string(n) + "x" + std::to_string(k) + ".txt" << std::endl;
            vecToFile(nValid, n, k, returnVec);
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    int seconds = duration.count() % 60;
    int minutes = ((duration.count() / 60) % 60);
    long long hours = (duration.count() / 3600);
    std::cout << "Runtime (hh:mm:ss) : " << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds << std::endl;
}
