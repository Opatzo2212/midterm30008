#include "iVigenereStream.h"

using namespace std;

iVigenereStream::iVigenereStream(Cipher aCipher, const string& aKeyword, const char* aFileName) 
    : fIStream(ifstream()), fCipherProvider(Vigenere(aKeyword)), fCipher(move(aCipher)) 
{
    if (aFileName != nullptr) 
    {
        open(aFileName);
    }
}

iVigenereStream::~iVigenereStream() 
{
    close();
}

void iVigenereStream::open(const char* aFileName) 
{
    fIStream.open(aFileName, ios::binary);
}

void iVigenereStream::close() 
{
    fIStream.close();
}

void iVigenereStream::reset() 
{
    fCipherProvider.reset();
    seekstart();
}

bool iVigenereStream::good() const 
{
    return fIStream.good();
}

bool iVigenereStream::is_open() const 
{
    return fIStream.is_open();
}

bool iVigenereStream::eof() const 
{
    return fIStream.eof();
}

iVigenereStream& iVigenereStream::operator>>(char& aCharacter) 
{
    aCharacter = fCipher(fCipherProvider, static_cast<char>(fIStream.get()));
    return *this;
}
