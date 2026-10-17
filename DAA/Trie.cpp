#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->children[idx])
                node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEndOfWord;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return true;
    }
};

int main() {
    Trie trie;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("dog");

    cout << trie.search("cat") << "\n";       // 1 (true)
    cout << trie.search("ca") << "\n";        // 0 (false)
    cout << trie.startsWith("ca") << "\n";    // 1 (true)
    cout << trie.search("dog") << "\n";       // 1 (true)
    cout << trie.search("do") << "\n";        // 0 (false)
}