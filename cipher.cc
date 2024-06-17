#include <string>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <cctype>

const int start = 97; // ascii lowercase 'a'
const int end_ = 122; // ascii lowercase 'z' 

using namespace std;

static inline void to_lowercase(string &str) {
    transform(str.begin(), str.end(), str.begin(),[](unsigned char c){ return tolower(c); });
}

static inline bool is_punctuation(char c) {
    if (c == ' ' || c == '.' || c == ',' || c == '!' ||
        c == '?' || c == '\'' || c == '"' || c == ':' || c == ';'
    ) {
        return true;
    } else {
        return false;
    };
}

void encode(string &message, string &key) {
    to_lowercase(key);
    to_lowercase(message);

    uint64_t index = 0;
    for (int i = 0; i < message.size(); i++) {
        if (is_punctuation(message[i])) continue;
        int shift = int(key[i % key.size()]) - start;
        message[i] = char(((int(message[i]) + shift - start) % 26) + start);
    }
}

void decode(string &message, string &key) {
    to_lowercase(key);
    to_lowercase(message);

    uint64_t index = 0;
    for (int i = 0; i < message.size(); i++) {
        if (is_punctuation(message[i])) continue;
        int shift = int(key[i % key.size()]) - start;
        message[i] = char(((message[i]) - start + 26 - shift) % 26 + start);
    }
}

