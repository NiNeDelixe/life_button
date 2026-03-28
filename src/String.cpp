#include "utils/String.hpp"

uint8_t string::encodeChar(char c)
{
    switch (c)
    {
        case '0': return SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F;
        case '1': return SEG_B|SEG_C;
        case '2': return SEG_A|SEG_B|SEG_D|SEG_E|SEG_G;
        case '3': return SEG_A|SEG_B|SEG_C|SEG_D|SEG_G;
        case '4': return SEG_B|SEG_C|SEG_F|SEG_G;
        case '5': return SEG_A|SEG_C|SEG_D|SEG_F|SEG_G;
        case '6': return SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
        case '7': return SEG_A|SEG_B|SEG_C;
        case '8': return SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
        case '9': return SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G;

        case 'A': case 'a': return SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
        case 'B': case 'b': return SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
        case 'C': case 'c': return SEG_A|SEG_D|SEG_E|SEG_F;
        case 'D': case 'd': return SEG_B|SEG_C|SEG_D|SEG_E|SEG_G;
        case 'E': case 'e': return SEG_A|SEG_D|SEG_E|SEG_F|SEG_G;
        case 'F': case 'f': return SEG_A|SEG_E|SEG_F|SEG_G;
        case 'G': case 'g': return SEG_A|SEG_C|SEG_D|SEG_E|SEG_F;
        case 'H': case 'h': return SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
        case 'I': case 'i': return SEG_B|SEG_C;
        case 'J': case 'j': return SEG_B|SEG_C|SEG_D|SEG_E;
        case 'K': case 'k': return SEG_E|SEG_F|SEG_G;
        case 'L': case 'l': return SEG_D|SEG_E|SEG_F;
        case 'M': case 'm': return SEG_A|SEG_C|SEG_E|SEG_G;
        case 'N': case 'n': return SEG_C|SEG_E|SEG_G;
        case 'O': case 'o': return SEG_C|SEG_D|SEG_E|SEG_G;
        case 'P': case 'p': return SEG_A|SEG_B|SEG_E|SEG_F|SEG_G;
        case 'Q': case 'q': return SEG_A|SEG_B|SEG_C|SEG_F|SEG_G;
        case 'R': case 'r': return SEG_E|SEG_G;
        case 'S': case 's': return SEG_A|SEG_C|SEG_D|SEG_F|SEG_G;
        case 'T': case 't': return SEG_D|SEG_E|SEG_F|SEG_G;
        case 'U': case 'u': return SEG_C|SEG_D|SEG_E;
        case 'V': case 'v': return SEG_C|SEG_D|SEG_E;
        case 'W': case 'w': return SEG_B|SEG_D|SEG_F;
        case 'X': case 'x': return SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
        case 'Y': case 'y': return SEG_B|SEG_C|SEG_D|SEG_F|SEG_G;
        case 'Z': case 'z': return SEG_A|SEG_B|SEG_D|SEG_E|SEG_G;

        case 'А': case 'а': return SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
        case 'Б': case 'б': return SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
        case 'В': case 'в': return SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
        case 'Г': case 'г': return SEG_A|SEG_E|SEG_F;
        case 'Д': case 'д': return SEG_B|SEG_C|SEG_D|SEG_E|SEG_G;
        case 'Е': case 'е': return SEG_A|SEG_D|SEG_E|SEG_F|SEG_G;
        case 'Ё': case 'ё': return SEG_A|SEG_D|SEG_E|SEG_F|SEG_G;
        case 'Ж': case 'ж': return SEG_A|SEG_G|SEG_D;
        case 'З': case 'з': return SEG_A|SEG_B|SEG_C|SEG_D|SEG_G;
        case 'И': case 'и': return SEG_C|SEG_E|SEG_G;
        case 'Й': case 'й': return SEG_C|SEG_E|SEG_G;
        case 'К': case 'к': return SEG_E|SEG_F|SEG_G;
        case 'Л': case 'л': return SEG_D|SEG_E|SEG_F;
        case 'М': case 'м': return SEG_A|SEG_C|SEG_E|SEG_G;
        case 'Н': case 'н': return SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
        case 'О': case 'о': return SEG_C|SEG_D|SEG_E|SEG_G;
        case 'П': case 'п': return SEG_A|SEG_B|SEG_C|SEG_E|SEG_F;
        case 'Р': case 'р': return SEG_A|SEG_B|SEG_E|SEG_F|SEG_G;
        case 'С': case 'с': return SEG_A|SEG_D|SEG_E|SEG_F;
        case 'Т': case 'т': return SEG_D|SEG_E|SEG_F|SEG_G;
        case 'У': case 'у': return SEG_B|SEG_C|SEG_D|SEG_F|SEG_G;
        case 'Ф': case 'ф': return SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
        case 'Х': case 'х': return SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
        case 'Ц': case 'ц': return SEG_C|SEG_D|SEG_E;
        case 'Ч': case 'ч': return SEG_B|SEG_C|SEG_G;
        case 'Ш': case 'ш': return SEG_B|SEG_C|SEG_D|SEG_E|SEG_F;
        case 'Щ': case 'щ': return SEG_B|SEG_C|SEG_D|SEG_E|SEG_F;
        case 'Ъ': case 'ъ': return SEG_C|SEG_D|SEG_E|SEG_F;
        case 'Ы': case 'ы': return SEG_B|SEG_C|SEG_D|SEG_F|SEG_G;
        case 'Ь': case 'ь': return SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
        case 'Э': case 'э': return SEG_A|SEG_B|SEG_C|SEG_D|SEG_G;
        case 'Ю': case 'ю': return SEG_B|SEG_C|SEG_D|SEG_E|SEG_G;
        case 'Я': case 'я': return SEG_A|SEG_B|SEG_C|SEG_F|SEG_G;

        case '-': return SEG_G;
        case ' ': return 0;

        default: return 0;
    }
}

void string::encodeString(const char *str, uint8_t *out, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        if (str[i] == '\0')
            out[i] = 0;
        else
            out[i] = encodeChar(str[i]);
    }
}