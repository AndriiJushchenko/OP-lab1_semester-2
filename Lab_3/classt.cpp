#include "classt.h"


Text :: Text() {
    text = "";
}

void Text :: text_append(string str) {
    text += str;
}

int Text :: countDoubleCharOccurrences() {
    int count = 0;
    for (int i = 1; i < text.length(); ++i) {
        if (text[i] == text[i - 1] && text[i] != text[i + 1] && text[i] != text[i - 2]) {
            ++count;
        }
    }
    return count;
}

void Text :: print() {
    cout << text << endl;
}