#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int count_letters(string input_string);
int count_words(string input_string);
int count_sentences(string input_string);
float calculate_reading_level(int letters_count, int words_count, int sentences_count);
void print_reading_level(float reading_level);
bool is_letter(char c);
bool is_punctuation(char c);

int main(void)
{
    // Get input from user
    string input_string = get_string("Text: ");

    // Compute inputs for Coleman-Liau Index
    int num_letters = count_letters(input_string);
    int num_words = count_words(input_string);
    int num_sentences = count_sentences(input_string);
    
    // Calculate Coleman-Liau Index reading level
    float reading_level = calculate_reading_level(num_letters, num_words, num_sentences);

    print_reading_level(reading_level);
}

int count_letters(string input_string)
{
    int i = 0, letters_count = 0;
    
    // Count all alphabetical characters in input string
    while (input_string[i] != '\0')
    {
        if (is_letter(input_string[i]))
        {
            letters_count++;
        }
        i++;
    }
    return letters_count;
}

int count_words(string input_string, int letters_count)
{
    int i = 0, words_count = 0;
    bool contains_letter = false;
    
    // Count words in input string 
    // Word defined as a substring ended by space or punctuation that contains at least 1 alphabetical character
    // Assumes no typos omitting spaces or leaving off punctuation
    while (input_string[i] != '\0')
    {
        if (is_letter(input_string[i]))
        {
            contains_letter = true;
        }
        if ((input_string[i] == ' ' || is_punctuation(input_string[i])) && contains_letter == true)
        {
            words_count++;
            contains_letter = false;
        }
        i++;
    }
    return words_count;
}

int count_sentences(string input_string)
{
    int i = 0, sentences_count = 0;
    // Count sentences in input string
    // Per problem specifications, sentence defined a substring ended by '.', '!', or '?'
    // Assumes all sentences correctly end with punctuation mark
    while (input_string[i] != '\0')
    {
        if (is_punctuation(input_string[i]))
        {
            sentences_count++;
        }
        i++;
    }
    return sentences_count;
}

float calculate_reading_level(int letters_count, int words_count, int sentences_count)
{
    float L, S;
    
    // Calculate average number of letters per 100 words
    L = ((float) letters_count / (float) words_count) * 100;
    
    // Calculate average number of sentences per 100 words
    S = ((float) sentences_count / (float) words_count) * 100;
    
    // return Coleman-Liau index
    return 0.0588 * L - 0.296 * S - 15.8;
}

void print_reading_level(float reading_level)
{
    // Interpret reading level and print according to problem specifications
    if (reading_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (reading_level >= roundf(16))
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) roundf(reading_level));
    }
}

bool is_letter(char c){
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_punctuation(char c){
    if (c == '.' || c == '!' || c == '?')
    {
        return true;
    }
    else
    {
        return false;
    }
}
