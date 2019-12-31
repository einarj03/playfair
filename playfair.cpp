#include "playfair.h"
using namespace std;

void prepare(const char* input, char* output) {
    int in_len = strlen(input);
    int count = 0;
    for (int i = 0; i < in_len - 1; ++i) {
        if (isalnum(input[i]) != 0) {
            output[count] = toupper(input[i]);
            ++count;
        }
    }
    if (count % 2 != 0) {
        output[count] = 'X';
    }
}


void grid(const char* codeword, char square[6][6]) {
    int codeword_len = strlen(codeword);
    int grid_count = 0;

    for (int i = 0; i < codeword_len; ++i) {
        if (!occurs_before(codeword, codeword[i], i)) {
            int col = grid_count / 6;
            int row = grid_count % 6;
            square[col][row] = codeword[i];
            ++grid_count;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        if (!occurs_before(codeword, ch, codeword_len)) {
            int col = grid_count / 6;
            int row = grid_count % 6;
            square[col][row] = ch;
            ++grid_count;
        }
    }

    for (char ch = '0'; ch <= '9'; ++ch) {
        if (!occurs_before(codeword, ch, codeword_len)) {
            int col = grid_count / 6;
            int row = grid_count % 6;
            square[col][row] = ch;
            ++grid_count;
        }
    }
}

bool occurs_before(const char str[], char letter, int pos) {
    for (int i = 0; i < pos; ++i) {
        if (str[i] == letter)
            return true;
    }
    return false;
}

void bigram(const char square[6][6], const char inchar1, const char inchar2, char &outchar1, char &outchar2) {
    int row1, col1, row2, col2;
    find_pos(square, inchar1, row1, col1);
    find_pos(square, inchar2, row2, col2);

    outchar1 = square[row1][col2];
    outchar2 = square[row2][col1];
}

void find_pos(const char square[6][6], char ch, int &row, int &col) {
    for (row = 0; row < 6; ++row) {
        for (col = 0; col < 6; ++col) {
            if (square[row][col] == ch)
                return;
        }
    }
}

void encode(const char square[6][6], const char* prepared, char* encoded) {
    int msg_len = strlen(prepared);
    if (msg_len == 0)
        return;    

    bigram(square, prepared[0], prepared[1], encoded[0], encoded[1]);
    encode(square, prepared+2, encoded+2);
    return;
}

void decode(const char square[6][6], const char* encoded, char* decoded) {
    int msg_len = strlen(encoded);
    if (msg_len == 0)
        return;

    bigram(square, encoded[1], encoded[0], decoded[1], decoded[0]);
    decode(square, encoded+2, decoded+2);
    return;
}