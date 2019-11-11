//
// Created by Sascha Roth on 03.11.19.
//

#pragma once

#include <ios>
#include <ostream>
#include <istream>

class HexDump {

public:
    template<class Elem, class Traits>
    static inline void hex_dump(const void* aData, std::size_t aLength, std::basic_ostream<Elem, Traits>& aStream, std::size_t aWidth = 16)
    {
        const char* const start = static_cast<const char*>(aData);
        const char* const end = start + aLength;
        const char* line = start;
        while (line != end)
        {
            aStream.width(4);
            aStream.fill('0');
            aStream << std::hex << line - start << " : ";
            std::size_t lineLength = std::min(aWidth, static_cast<std::size_t>(end - line));
            for (std::size_t pass = 1; pass <= 2; ++pass)
            {
                for (const char* next = line; next != end && next != line + aWidth; ++next)
                {
                    char ch = *next;
                    switch(pass)
                    {
                        case 1:
                            aStream << (ch < 32 ? '.' : ch);
                            break;
                        case 2:
                            if (next != line)
                                aStream << " ";
                            aStream.width(2);
                            aStream.fill('0');
                            aStream << std::hex << std::uppercase << static_cast<int>(static_cast<unsigned char>(ch));
                            break;
                    }
                }
                if (pass == 1 && lineLength != aWidth)
                    aStream << std::string(aWidth - lineLength, ' ');
                aStream << " ";
            }
            aStream << std::endl;
            line = line + lineLength;
        }
    }
};
