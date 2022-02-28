
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int mod(int a, int b)
{
    if (a >= b)
        return mod(a - b, b);
    if (a < 0)
        return mod(b + a, b);
    return a;
}

void cycleShift(const char* input_arr, char* output_arr, const unsigned int size, const int shift)
{
    for (unsigned int i = 0; i < size; ++i)
        output_arr[i] = input_arr[mod(i + shift, size)];
}

char* cesarEncryption(const char* secret_message, const int key, const char* alphabet, const unsigned int alphabet_size)
{
    char* alphabet_code = (char*)malloc(alphabet_size * sizeof(char));
    cycleShift(alphabet, alphabet_code, alphabet_size, key);

    unsigned int message_len;  
    for (message_len = 0; secret_message[message_len] != '\0'; ++message_len);

    char* cryptogram = (char*)malloc(message_len * sizeof(char));
    for (unsigned int i = 0; i < message_len; ++i)
        cryptogram[i] = alphabet_code[secret_message[i] - 'A'];
    cryptogram[message_len] = '\0';

    free(alphabet_code);
    return cryptogram;
}

char* cesarDecryption(const char* cryptogram, const int key, const char* alphabet, const unsigned int alphabet_size)
{
    char* alphabet_code = (char*)malloc(alphabet_size * sizeof(char));
    cycleShift(alphabet, alphabet_code, alphabet_size, -key);

    unsigned int message_len;  
    for (message_len = 0; cryptogram[message_len] != '\0'; ++message_len);

    char* secret_message = (char*)malloc(message_len * sizeof(char));
    for (unsigned int i = 0; i < message_len; ++i)
        secret_message[i] = alphabet_code[cryptogram[i] - 'A'];
    secret_message[message_len] = '\0';

    free(alphabet_code);
    return secret_message;
}

void task1()
{
    printf("1. Шифрование и расшифровка Цезаря\n\n");

    const unsigned int alphabet_size = 26;
    char* alphabet = (char*)malloc(alphabet_size * sizeof(char));
    alphabet[0] = 'A';
    for (int i = 1; i < alphabet_size; ++i)
        alphabet[i] = alphabet[0] + i;

    printf("Исходное сообщение:\n");
    const unsigned int max_message_size = 500;
    char message[max_message_size] = "THISISASECRETMESSAGEFORCESARENCRYPTION";
    puts(message);

    const int cesar_shift = 3;

    printf("Криптограмма:\n");
    char* cryptogram = cesarEncryption(message, cesar_shift, alphabet, alphabet_size);
    puts(cryptogram);

    printf("Расшифровка:\n");
    char* result = cesarDecryption(cryptogram, cesar_shift, alphabet, alphabet_size);
    puts(result);
    printf("\n");

    free(alphabet);
}

char** init2DArray(const int rows, const int cols)
{
    char** array = (char**)calloc(sizeof(char*), rows);
    for (int i = 0; i < rows; ++i)
        *(array + i) = (char*)calloc(sizeof(char), cols);
    return array;
}

char get2dChar(char** array, const int row, const int col)
{
    return *((*(array + row)) + col);
}

void set2dChar(char** array, const int row, const int col, const char letter)
{
    *((*(array + row)) + col) = letter;
}

char* shuffleEncryption(const char* secret_message, const char* key_word)
{
    unsigned int message_len; 
    for (message_len = 0; secret_message[message_len] != '\0'; ++message_len);

    unsigned int columns_num; 
    for (columns_num = 0; key_word[columns_num] != '\0'; ++columns_num);

    unsigned int rows_num;    
    rows_num = (message_len % columns_num == 0) ? (message_len / columns_num) : (message_len / columns_num + 1);

    char** encoding_array = init2DArray(rows_num, columns_num);
    for (unsigned int i = 0; i < rows_num; ++i)
        for (unsigned int j = 0; j < columns_num; ++j)
            set2dChar(encoding_array, i, j, secret_message[i * columns_num + j]);

    
    char* cryptogram = (char*)malloc(message_len * sizeof(char));
    unsigned int counter = 0;            
    unsigned int idx = 0;               
    char letter = 'A';
    while (counter < columns_num)    
    {
        for (unsigned int j = 0; j < columns_num; ++j)
            if (key_word[j] == letter)    
            {  
                for (unsigned int i = 0; i < rows_num; ++i)
                    cryptogram[idx++] = get2dChar(encoding_array, i, j);
                ++counter;        
                break;
            }
        ++letter;                
    }
    cryptogram[message_len] = '\0';

    for (unsigned int i = 0; i < rows_num; ++i)
        free(encoding_array[i]);
    free(encoding_array);

    return cryptogram;
}

char* shuffleDecryption(const char* cryptogram, const char* key_word)
{
    unsigned int message_len; 
    for (message_len = 0; cryptogram[message_len] != '\0'; ++message_len);

    unsigned int columns_num;
    for (columns_num = 0; key_word[columns_num] != '\0'; ++columns_num);

    unsigned int rows_num;  
    rows_num = (message_len % columns_num == 0) ? (message_len / columns_num) : (message_len / columns_num + 1);

    char** shuffle_array = init2DArray(rows_num, columns_num);
    for (unsigned int i = 0; i < rows_num; ++i)
        for (unsigned int j = 0; j < columns_num; ++j)
            set2dChar(shuffle_array, i, j, cryptogram[i + j * rows_num]);

    char* result = (char*)malloc(message_len * sizeof(char));
    unsigned int counter = 0;           
    char letter = 'A';
    while (counter < columns_num)        
    {
        for (unsigned int j = 0; j < columns_num; ++j)
            if (key_word[j] == letter)
            {
                for (unsigned int i = 0; i < rows_num; ++i)
                    result[i * columns_num + j] = get2dChar(shuffle_array, i, counter);
                ++counter;                
                break;
            }
        ++letter;                         
    }
    result[message_len] = '\0';

    for (unsigned int i = 0; i < rows_num; ++i)
        free(shuffle_array[i]);
    free(shuffle_array);

    return result;
}

void task2()
{
    printf("2. Шифрование и расшифровка перестановками\n\n");

    printf("Исходное сообщение:\n");
    const unsigned int max_message_size = 100;
    char message[max_message_size] = "THISISASECRETMESSAGEFORSHUFFLEENCRYPTION";
    puts(message);

    char key_word[] = "BLACK";

    printf("Криптограмма:\n");
    char* cryptogram = shuffleEncryption(message, key_word);
    puts(cryptogram);

    printf("Разгаданное сообщение:\n");
    char* unraveled_message = shuffleDecryption(cryptogram, key_word);
    puts(unraveled_message);
    printf("\n");
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    task1();
    task2();
    return 0;
}
