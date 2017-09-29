#include <gtest/gtest.h>
#include "wordCount.h"

TEST(wordCountTest, wordCount_emptyString_expect0){
    std::string emptyString = "";
    ASSERT_EQ(wordCount::wordCount(emptyString, 0), 0);
}

TEST(wordCountTest, wordCount_emptyString_startIdx1_expect0){
    std::string emptyString = "";
    ASSERT_EQ(wordCount::wordCount(emptyString, 1), 0);
}

TEST(wordCountTest, wordCount_oneWordString_expect1) {
    std::string oneWordString = "one";
    ASSERT_EQ(wordCount::wordCount(oneWordString, 0), 1);
}

TEST(wordCountTest, wordCount_oneWordString_startIdx1_expect1) {
    std::string oneWordString = "one";
    ASSERT_EQ(wordCount::wordCount(oneWordString, 0), 1);
}

TEST(wordCountTest, wordCount_fiveWordsString_expect5){
    std::string fiveWordsString = "one two three four five";
    ASSERT_EQ(wordCount::wordCount(fiveWordsString, 0), 5);
}

TEST(wordCountTest, wordCount_fiveWordsStringStartWithOneSpace_expect5){
    std::string fiveWordsStringStartWithOneSpace = " one two three four five";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringStartWithOneSpace, 0), 5);
}

TEST(wordCountTest, wordCount_fiveWordsStringStartWithTwoSpace_expect5){
    std::string fiveWordsStringStartWithTwoSpace = "  one two three four five";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringStartWithTwoSpace, 0), 5);
}

TEST(wordCountTest, wordCount_fiveWordsStringEndWithOneSpace_expect5){
    std::string fiveWordsStringStartWithOneSpace = "one two three four five ";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringStartWithOneSpace, 0), 5);
}

TEST(wordCountTest, wordCount_fiveWordsStringEndWithTwoSpace_expect5){
    std::string fiveWordsStringStartWithTwoSpace = "one two three four five  ";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringStartWithTwoSpace, 0), 5);
}

TEST(wordCountTest, wordCount_fiveWordsStringStartWithTwoSpaceEndWithTwoSpace_expect5){
    std::string fiveWordsStringStartWithTwoSpaceEndWithTwoSpace = "  one two three four five  ";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringStartWithTwoSpaceEndWithTwoSpace, 0), 5);
}

TEST(wordCountTest, wordCount_fiveWordsStringStartWithOneSpace_startIdx1_expect5){
    std::string fiveWordsStringStartWithOneSpace = " one two three four five";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringStartWithOneSpace, 0), 5);
}

TEST(wordCountTest, wordCount_fiveWordsStringStartWithTwoSpace_startIdx2_expect5){
    std::string fiveWordsStringStartWithTwoSpace = "  one two three four five";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringStartWithTwoSpace, 2), 5);
}

TEST(wordCountTest, wordCount_fiveWordsStringWithTwoSpaceBetweenWords_expect5){
    std::string fiveWordsStringWithTwoSpaceBetweenWords = "one  two  three  four  five";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringWithTwoSpaceBetweenWords, 0), 5);
}

TEST(wordCountTest, wordCount_fiveWordsStringWithThreeSpaceBetweenWords_expect5){
    std::string fiveWordsStringWithThreeSpaceBetweenWords = "one   two   three   four   five";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringWithThreeSpaceBetweenWords, 0), 5);
}

TEST(wordCountTest, wordCount_fiveWordsStringWithSecondWordIndexStartAtIdx4_startIdx4_expect4){
    std::string fiveWordsStringWithSecondWordIndexStartAtIdx4 = "one 2 three four five";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringWithSecondWordIndexStartAtIdx4, 4), 4);
}

TEST(wordCountTest, wordCount_fiveWordsStringWithSecondWordIndexStartAtIdx4EndAtIdx5_startIdx5_expect3){
    std::string fiveWordsStringWithSecondWordIndexStartAtIdx4EndAtIdx5 = "one 2 three four five";
    ASSERT_EQ(wordCount::wordCount(fiveWordsStringWithSecondWordIndexStartAtIdx4EndAtIdx5, 5), 3);
}

