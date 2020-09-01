#include "SerializableDeserializableTrie.h"
using namespace serializabledeserializabletrie;


/*
//Just a basic test case, can be used to verify the code
void basic_testing() {
    vector<string> words = {"trie", "is", "a", "beautiful", "datastructure"};
    vector<string> words2 = {"aac", "ab", "abde", "abdf", "beab", "bead"};
    vector<string> words3 = {"ab", "abc", "bac", "bad"};

    Trie t(words3);
    t.printTrie();

    cout << "words with prefix ab are ";
    cout << t.wordCountWithPrefix("ab") << endl;

    cout << "words with prefix abc are ";
    cout << t.wordCountWithPrefix("abc") << endl;

    cout << "words with prefix ba are ";
    cout << t.wordCountWithPrefix("ba") << endl;

    string res = t.serializeTheTrieIntoString();
    cout << "serialized string is " << res << endl;

    Trie nt = t.deserializeStringToTrie(res);
    nt.printTrie();
    cout << nt.totalWordsCount() << endl;

    cout << "words with prefix ab are ";
    cout << nt.wordCountWithPrefix("ab") << endl;

    cout << "words with prefix abc are ";
    cout << nt.wordCountWithPrefix("abc") << endl;

    cout << "words with prefix ba are ";
    cout << nt.wordCountWithPrefix("ba") << endl;

    if (nt.searchWord("aac")) {
        cout << "word aac exists" << endl;
    }
}
*/

void Serialization() {
#ifndef ONLINE_JUDGE
    freopen("test_strings_data_input.txt", "r", stdin);
    freopen("test_serialized_data_output.txt", "w", stdout);
#endif

    string word;
    cin >> word;
    vector<string> words;
    do {
        words.push_back(word);
        cin >> word;
    } while (word != "#END#");

    Trie original_trie(words);
    string serialized_trie = original_trie.serializeTheTrieIntoString();
    cout << serialized_trie << endl;
}

void Deserialization() {
#ifndef ONLINE_JUDGE
    freopen("test_serialized_data_output.txt", "r", stdin);
    freopen("test_deserialized_data_output.txt", "w", stdout);
#endif

    string serializedTrie;
    cin >> serializedTrie;
    Trie trie;
    Trie new_trie = trie.deserializeStringToTrie(serializedTrie);
    new_trie.printTrie();
    // cout << new_trie.totalWordsCount() << endl;
}

int main() {
    // basic_testing();

    //to run and test the trie follow these steps
    //1. First make all text files with same names and fill the data in the first input file.
    //2. First execute the program for Serialization
    //3. Then again execute for Deserilization.
    //(or you can use File Handling in a some other way to do it in one go).

    // Serialization();
    // Deserialization();

    return 0;
}