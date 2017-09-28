#include "word_count.h"

bool startNewWord(std::string::const_iterator &it){
    return (*(it-1) == ' ' && *it != ' ');
}
// implementation details
int word_count(const std::string &line, int start_idx) {
    if (start_idx >= line.length()) {
        return 0;
    }

    int nwords = ((line.at(0) == ' ') ? 0 : 1);

    for (std::string::const_iterator it = line.begin() + start_idx + 1; it < line.end(); it++){
        if (startNewWord(it)){
            nwords ++;
        }
    }

    return nwords;
}