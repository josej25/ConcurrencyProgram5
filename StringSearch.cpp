#include "StringSearch.h"
#include <string>
int StringSearch::bruteResult = -1;
int StringSearch::boyerMooreResult = -1;
int StringSearch::knuthMorrisPrattResult = -1;
mutex StringSearch::resultMutex;
StringSearch::StringSearch()
{
    //ctor
}
void StringSearch::brute(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();
    int j;

    for (int i = 0; i <= (n - m); i++) {
        j = 0;
        while ((j < m) && (text[i + j] == pattern[j])) {
            j++;
        }
        if (j == m) {
            resultMutex.lock();
            bruteResult = i;
            resultMutex.unlock();
            return;
        }
    }
    resultMutex.lock();
    bruteResult = -1;
    resultMutex.unlock();
}
static int* buildLast(int last[],string pattern)
{
    for(int i = 0; i<128; i++)
    {
        last[i] = -1;
    }
    for (int i=0; i<pattern.length(); i++)
    {
    last[pattern[i]] = i;
    }
    return last;
}

void StringSearch::boyerMoore(string text, string pattern)
{
    int last[128];
    buildLast(last, pattern);
    int n = text.length();
    int m = pattern.length();

    int i = m - 1;
    if (i > n - 1) {
        resultMutex.lock();
        boyerMooreResult = -1; // If pattern is longer than text, return -1
        resultMutex.unlock();
        return;
    }
    int j = m - 1;

    do
    {
        if (pattern[j] == text[i])
        {
            if (j == 0)
            {
                resultMutex.lock();
                boyerMooreResult = i; // Found a match
                resultMutex.unlock();
                return;
            }
            else
            {
                // Move both pointers backward
                i--;
                j--;
            }
        }
        else
        {
            int lo = last[text[i]]; // Get the last occurrence index of the current character
            i = i + m - min(j, 1 + lo); // Move the text pointer
            j = m - 1; // Reset the pattern pointer
        }
    } while (i <= n - 1);

    resultMutex.lock();
    boyerMooreResult = -1; // No match found
    resultMutex.unlock();
}
void StringSearch::lpsCalculation(string pattern, int m, int* lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void StringSearch::knuthMorrisPratt(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();
    int lps[m];
    lpsCalculation(pattern, m, lps);
    int i = 0;
    int j = 0;
    while ((n - i) >= (m - j)) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            resultMutex.lock();
            knuthMorrisPrattResult = i - j;
            resultMutex.unlock();
            return;
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    resultMutex.lock();
    knuthMorrisPrattResult = -1;
    resultMutex.unlock();
}



