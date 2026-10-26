#include<iostream>
#include<vector>
using namespace std;

// hash 1
int h1(string s, int arrSize) {
    ll int hash = 0;
    for (int i = 0; i < s.size(); i++) {
        hash = (hash + ((int)s[i]));
        hash = hash % arrSize;
    }
    return hash;
}

// hash 2
int h2(string s, int arrSize) {
    ll int hash = 1;
    for (int i = 0; i < s.size(); i++) {
        hash = hash + pow(19, i) * s[i];
        hash = hash % arrSize;
    }
    return hash % arrSize;
}

// hash 3
int h3(string s, int arrSize) {
    ll int hash = 7;
    for (int i = 0; i < s.size(); i++) {
        hash = (hash * 31 + s[i]) % arrSize;
    }
    return hash % arrSize;
}

// hash 4
int h4(string s, int arrSize) {
    ll int hash = 3;
    int p = 7;
    for (int i = 0; i < s.size(); i++) {
        hash += hash * 7 + s[0] * pow(p, i);
        hash = hash % arrSize;
    }
    return hash;
}

bool lookup(vector<int>&bitarray,string s,int arrSize){
    int a,b,c;
    a=h1(s,arrsize)
    b=h2(s,arrSize)
    c=h3(s,arrsize)
    d=h4(s,arrsize)
    if(bitarray[a] && bitarray[b] && bitarray[c] && bitarray[d])
    return true;
    else
    return false;

}

void insert(vector<bool>&bitarray,string s,int arrSize){
    int a,b,c,d;
    a=h1(s,arrsize)
    b=h2(s,arrSize)
    c=h3(s,arrsize)
    d=h4(s,arrsize)
    bitarray[a]=true;
    bitarray[b]=true;
    bitarray[c]=true;
    bitarray[d]=true;
    cout<< s <<"insert"<<endl;
}

int main(){
    vector<bool>bitarray(100,false);
    int arrsize=100;
    int arrSize = 100;
    string sarray[33]
        = { "abound",   "abounds",       "abundance",
            "abundant", "accessible",    "bloom",
            "blossom",  "bolster",       "bonny",
            "bonus",    "bonuses",       "coherent",
            "cohesive", "colorful",      "comely",
            "comfort",  "gems",          "generosity",
            "generous", "generously",    "genial",
            "bluff",    "cheater",       "hate",
            "war",      "humanity",      "racism",
            "hurt",     "nuke",          "gloomy",
            "facebook", "geeksforgeeks", "twitter" };
    for (int i = 0; i < 33; i++) {
        insert(bitarray, arrSize, sarray[i]);
    }
    return 0;
}