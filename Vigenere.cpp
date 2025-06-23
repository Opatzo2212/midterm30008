// COS30008, Midterm, Problem 2, 2022

#include "Vigenere.h"

using namespace std;

void Vigenere::initializeTable() 
{
    for (char row = 0; row < CHARACTERS; row++) 
    {
        char lChar = 'B' + row;
        for (char column = 0; column < CHARACTERS; column++) 
        {
            if (lChar > 'Z')
                lChar = 'A';
            fMappingTable[row][column] = lChar++;
        }
    }
}

Vigenere::Vigenere(const string& aKeyword) 
    : fKeyword(aKeyword), fKeywordProvider(KeyProvider(aKeyword)) 
{
    initializeTable();
}

string Vigenere::getCurrentKeyword() 
{
    string current_keyword;
    for (size_t i = 0; i < fKeyword.length(); i++) 
    {
        current_keyword += *fKeywordProvider;
        fKeywordProvider << *fKeywordProvider;
    }
    return current_keyword;
}

void Vigenere::reset() 
{
    fKeywordProvider.initialize(fKeyword);
}

char Vigenere::encode(char aCharacter) 
{
    if (isalpha(aCharacter)) 
    {
        bool isLower = islower(aCharacter);
        char encoded = fMappingTable[*fKeywordProvider - 'A'][toupper(aCharacter) - 'A'];
        
        fKeywordProvider << aCharacter;
        if (isLower) 
        {
            return static_cast<char>(tolower(encoded));
        }
        return encoded;
    }
    return aCharacter;
}

char Vigenere::decode(char aCharacter) 
{
    if (isalpha(aCharacter)) 
    {
        bool isLower = islower(aCharacter);
        char encoded = static_cast<char>(toupper(aCharacter));
        char decoded = 0;

        for (char column = 0; column < CHARACTERS; column++) 
        {
            if (fMappingTable[*fKeywordProvider - 'A'][column] == encoded) 
            {
                decoded = static_cast<char>(column + 'A');
                break;
            }
        }

        fKeywordProvider << decoded;
        if (isLower) 
        {
            return static_cast<char>(tolower(decoded));
        }
        return decoded;
    }
    return aCharacter;
}

