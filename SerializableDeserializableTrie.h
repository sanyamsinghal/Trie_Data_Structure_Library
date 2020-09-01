#pragma once
#include <bits/stdc++.h>
using namespace std;
/*
 this is basically a preprocessor directive (which give instructions to the
 compiler to preprocess the information before actual compilation starts.)
 pragma once allows file to be included only once even if two cpp files uses
 this header file - It increases the speed and less code.
*/

namespace serializabledeserializabletrie {

// structure of the nodes in the trie.
struct TrieNode {
    char data;
    map<char, TrieNode *> children;

    //we can have multiple similar words, so keeping count of them
    int wordsEndingHere;

    // used to represent if the word ending at this node is a valid word.
    bool isTerminal;

    TrieNode(int data) {
        this->data = data;
        isTerminal = false;
        wordsEndingHere = 0;
    }
};

class Trie {
   private:
    TrieNode *root;
    int totalWords;

    //Depth First Search Traversal to traverse the complete tree.
    void dfs(TrieNode *node, string &curr) {
        curr.push_back(node->data);

        if (node->isTerminal) {
            std::cout << curr << endl;
        }

        for (auto &it : node->children) {
            TrieNode *child = it.second;
            dfs(child, curr);
        }

        curr.pop_back();
    }

    //helper function for converting the trie into a string
    void buildSerializedTrie(TrieNode *node, string &serializedTrie) {
        if (node->isTerminal) {  //if this is a valid word
            //storing the count with word.
            //for eg:- Hello is present 4 times then will be added as "Hello[4]"
            serializedTrie += "[" + to_string(node->wordsEndingHere) + "]";
            //"#" is used as a seperator between two words
        }

        auto &child_map = node->children;
        for (auto &child : child_map) {
            TrieNode *currentNode = child.second;
            serializedTrie.push_back(currentNode->data);
            buildSerializedTrie(currentNode, serializedTrie);
            // serializedTrie.pop_back();
        }
        serializedTrie.push_back('<');
    }

    int extractCount(string &serialTrie, int &idx) {
        string count = "";
        for (int i = idx; i < serialTrie.size(); i++) {
            if (serialTrie[i] == '[')
                continue;
            else if (serialTrie[i] == ']')
                break;
            else
                count += serialTrie[i];
        }

        idx += 2 + count.size();
        return stoi(count);
    }

    int buildDeserializedTrie(TrieNode *root, string &serialTrie, int &idx, int &wordCount) {
        int wordsSeen = 0;
        if (serialTrie[idx] == '[') {
            //this function call will findout the word ending with prefix till current node and update the index
            int wordsEndingAtCurrentNode = extractCount(serialTrie, idx);
            root->isTerminal = true;
            root->wordsEndingHere = wordsEndingAtCurrentNode;
            wordsSeen++;

            //updating the totalWordsCount for the trie
            wordCount++;
        }

        auto &child_map = root->children;
        while (idx < serialTrie.size() && serialTrie[idx] != '<') {
            char ch = serialTrie[idx++];
            child_map[ch] = new TrieNode(ch);

            wordsSeen += buildDeserializedTrie(child_map[ch], serialTrie, idx, wordCount);
        }
        root->wordsEndingHere = wordsSeen;
        idx++;
        return wordsSeen;
    }

   public:
    // Constructor for empty trie
    Trie() {
        // initializing root node with Null character
        root = new TrieNode('\0');
        totalWords = 0;
    }

    // initialize trie with words
    Trie(vector<string> &words) {  //calling the default constructor
        root = new TrieNode('\0');
        totalWords = 0;
        for (auto &w : words) {
            insertWordIntoTrie(w);
        }
    }

    //create a trie with given some given Trie
    Trie(TrieNode *root_node, int totalWords) {
        root = root_node;
        this->totalWords = totalWords;
    }

    void insertWordIntoTrie(string &word) {
        TrieNode *temp = root;
        for (int i = 0; i < word.size(); i++) {
            auto &child_map = temp->children;

            if (child_map.find(word[i]) == child_map.end()) {  // checking if already present in the map or not
                child_map[word[i]] = new TrieNode(word[i]);
            }
            temp = child_map[word[i]];
            temp->wordsEndingHere += 1;
        }
        // mark the node for a valid word
        temp->isTerminal = true;
        totalWords++;
    }

    //function used to check if given word is present in the trie or not
    bool searchWord(string word) {
        TrieNode *temp = root;

        for (int i = 0; i < word.size(); i++) {
            if (temp->children.count(word[i]) == 0)
                return false;
            temp = temp->children[word[i]];
        }

        return true;
    }

    //second variable - present is just to determine if this word is valid word or not.
    int wordCountWithPrefix(string word) {
        if (root == NULL)
            return 0;
        TrieNode *currentNode = root;

        for (int i = 0; i < word.size(); i++) {
            auto &child_map = currentNode->children;
            if (child_map.find(word[i]) == child_map.end())
                return 0;
            currentNode = child_map[word[i]];
        }

        return currentNode->wordsEndingHere;
    }

    void printTrie() {
        TrieNode *temp = root;
        string curr = "";
        for (auto &it : temp->children) {
            dfs(it.second, curr);
        }
    }

    string serializeTheTrieIntoString() {
        string serializedTrie;
        buildSerializedTrie(root, serializedTrie);
        return serializedTrie;
    }

    Trie deserializeStringToTrie(string word) {
        TrieNode *root = new TrieNode('\0');
        int idx = 0, wordCount = 0;

        //deserializing the trie
        buildDeserializedTrie(root, word, idx, wordCount);

        //making a trie object
        Trie deserialized(root, wordCount);
        return deserialized;
    }

    int totalWordsCount() {
        return totalWords;
    }
};

}  // namespace serializabledeserializabletrie