#ifndef STRINGSEARCH_H
#define STRINGSEARCH_H
#include <mutex>
using namespace std;
#include <string>

class StringSearch
{
public:
    StringSearch();
    static void brute(string text, string pattern);
    static void boyerMoore(string text, string pattern);
    static void knuthMorrisPratt(string text, string pattern);
    static void lpsCalculation(string pattern, int m, int* lps);


    static int bruteResult;
    static int boyerMooreResult;
    static int knuthMorrisPrattResult;
    static mutex resultMutex;

protected:

private:
};

#endif // STRINGSEARCH_H

