#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

    void _autocomplete(TrieNode* node, string prefix, vector<string>& results) {
        if (node->isEndOfWord) {
            results.push_back(prefix);
        }
        for (auto& pair : node->children) {
            _autocomplete(pair.second, prefix + pair.first, results);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    vector<string> search(string prefix) {
        TrieNode* node = root;
        vector<string> results;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return results;  
            }
            node = node->children[ch];
        }
        _autocomplete(node, prefix, results);
        return results;
    }
};

int main() {
    Trie trie;
    vector<string> dictionary = {"youtube", "app", "skillfactory", "google", "berry", "baku", "student"};
    for (string word : dictionary) {
        trie.insert(word);
    }

    while (true) {
        string prefix;
        cout << "Введите префикс для автодополнения: ";
        cin >> prefix;

        vector<string> suggestions = trie.search(prefix);
        if (!suggestions.empty()) {
            cout << "Возможные слова:" << endl;
            for (string suggestion : suggestions) {
                cout << suggestion << endl;
            }
        } else {
            cout << "Нет слов, начинающихся с этого префикса." << endl;
        }
    }

    return 0;
}
