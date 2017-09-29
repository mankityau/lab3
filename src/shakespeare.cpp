#include <map>
#include <string>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

#include "wordCount.h"

/**
 * Checks if the line specifies a character's dialogue, returning
 * the index of the start of the dialogue.  If the
 * line specifies a new character is speaking, then extracts the
 * character's name.
 *
 * Assumptions: (doesn't have to be perfect)
 *     Line that starts with exactly two spaces has
 *       CHARACTER. <dialogue>
 *     Line that starts with exactly four spaces
 *       continues the dialogue of previous character
 *
 * @param line line to check
 * @param character extracted character name if new character,
 *        otherwise leaves character unmodified
 * @return index of start of dialogue if a dialogue line,
 *      -1 if not a dialogue line
 */
int is_dialogue_line(const std::string &line, std::string &character) {

    // new character
    if (line.length() >= 3 && line[0] == ' '
        && line[1] == ' ' && line[2] != ' ') {
        // extract character name

        int start_idx = 2;
        int end_idx = 3;
        while (end_idx <= line.length() && line[end_idx - 1] != '.') {
            ++end_idx;
        }

        // no name found
        if (end_idx >= line.length()) {
            return 0;
        }

        // extract character's name
        character = line.substr(start_idx, end_idx - start_idx - 1);
        return end_idx;
    }

    // previous character
    if (line.length() >= 5 && line[0] == ' '
        && line[1] == ' ' && line[2] == ' '
        && line[3] == ' ' && line[4] != ' ') {
        // continuation
        return 4;
    }

    return 0;
}

/**
 * Reads a file to count the number of words each actor speaks.
 *
 * @param filename file to open
 * @param mutex mutex for protected access to the shared wcounts map
 * @param wcounts a shared map from character -> word count
 */
void count_character_words(const std::string &filename,
                           std::mutex &mutex,
                           std::map<std::string, int> &wcounts) {

    //===============================================
    //  IMPLEMENT THREAD SAFETY IN THIS METHOD
    //===============================================

    std::string line;  // for storing each line read from the file
    std::ifstream file(filename);

    // read contents of file if open
    if (file.is_open()) {

        std::string character = "";  // empty character to start

        // line by line
        while (std::getline(file, line)) {

            int idx = is_dialogue_line(line, character);
            if (idx > 0 && !character.empty()) {

                int nwords = wordCount::wordCount(line, idx);
                {
                    std::lock_guard<std::mutex> wcountLock(mutex);
                    if (wcounts.find(character) == wcounts.end()) {
                        wcounts.insert({character, nwords});
                    } else {
                        wcounts[character] += nwords;
                    }
                }


            } else {
                character = "";  // reset character
            }

        }
        file.close();  // close file
    }

}

/**
 * Comparator, order by alphabet, then by length.
 * Example
 *  s1 = aa, s2 = ab, return true
 *  s1 = ab, s2 = aa, return false
 *  s1 = aa, s2 = aaa, return true
 *  s1 = aaa, s2 = aa, return false
 *  @pre s1, and s2 must be different
 * @param s1
 * @param s2
 * @return
 */
bool nameGreaterThan(const std::string &s1, const std::string &s2) {
    for (int idx = 0; idx < s1.length() && idx < s2.length(); ++idx) {
        if (s1.at(idx) < s2.at(idx)) {
            return true;
        } else if (s2.at(idx) < s1.at(idx)) {
            return false;
        }
    }
    return (s1.length() < s2.length());
}

/**
 * Comparator, orders by number decreasing, then by name
 * @param p1 first pair
 * @param p2 second pair
 * @return true if p1 should come before p2, false otherwise
 */
bool wc_greater_than(std::pair<std::string, int> &p1, std::pair<std::string, int> &p2) {
    if (p1.second > p2.second) {
        return true;
    } else if (p1.second == p2.second) {
        return nameGreaterThan(p1.first, p2.first);
    } else {
        return false;
    }
};


/**
 * Sorts characters in descending order by word count
 *
 * @param wcounts a map of character -> word count
 * @return sorted vector of {character, word count} pairs
 */
std::vector<std::pair<std::string, int>> sort_characters_by_wordcount(
        const std::map<std::string, int> &wcounts) {

    std::vector<std::pair<std::string, int>> out;
    out.reserve(wcounts.size());   // reserve memory for efficiency

    // sort characters by words descending
    for (const auto &pair : wcounts) {
        out.push_back(pair);
    }
    std::sort(out.begin(), out.end(), wc_greater_than);

    return out;
}

int main() {

    // map and mutex for thread safety
    std::mutex mutex;
    std::map<std::string, int> wcounts;

    std::vector<std::string> filenames = {
            "data/shakespeare_antony_cleopatra.txt",
            "data/shakespeare_hamlet.txt",
            "data/shakespeare_julius_caesar.txt",
            "data/shakespeare_king_lear.txt",
            "data/shakespeare_macbeth.txt",
            "data/shakespeare_merchant_of_venice.txt",
            "data/shakespeare_midsummer_nights_dream.txt",
            "data/shakespeare_much_ado.txt",
            "data/shakespeare_othello.txt",
            "data/shakespeare_romeo_and_juliet.txt",
    };

    std::vector<std::thread> threads;

    for (std::vector<std::string>::iterator filenameIterator = filenames.begin(); filenameIterator != filenames.end(); filenameIterator ++) {
        threads.push_back(std::thread(count_character_words, *filenameIterator, std::ref(mutex), std::ref(wcounts)));
    }

    for (std::vector<std::thread>::iterator threadIt = threads.begin(); threadIt != threads.end(); ++threadIt) {
        threadIt->join();
    }

    auto sorted_wcounts = sort_characters_by_wordcount(wcounts);

    // results
    for (const auto &entry : sorted_wcounts) {
        std::cout << entry.first << "\t" << entry.second << std::endl;
    }

    std::cout << std::endl << "Press ENTER to continue..." << std::endl;
    std::cin.get();

    return 0;
}
