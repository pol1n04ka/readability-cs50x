#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Structure to hold overall count of letters/sentences and average per 100
// words.
struct Count {
  float overall;
  float avg;
};

// Utility functions for program
float CountWords(char text[]);
struct Count CountLetters(char text[], float words);
struct Count CountSentences(char text[], float words);
float CountColemanLiauIndex(float letters, float sentences);
void PrintGrade(float index);

// Main function for processing text
void ProcessText(char text[]);

int main() {
  // Grade before 1
  char testText1[] = "One fish. Two fish. Red fish. Blue fish.";

  // Grade 3
  char testText2[] = "Congratulations! Today is your day. You're off to Great "
                     "Places! You're off and away!";

  // Grade 10
  char testText3[] =
      "It was a bright cold day in April, and the clocks were striking "
      "thirteen. Winston Smith, his chin nuzzled into his breast in an effort "
      "to escape the vile wind, slipped quickly through the glass doors of "
      "Victory Mansions, though not quickly enough to prevent a swirl of "
      "gritty dust from entering along with him.";

  char testText4[] =
      "A large class of computational problems involve the determination of "
      "properties of graphs, digraphs, integers, arrays of integers, finite "
      "families of finite sets, boolean formulas and elements of other "
      "countable domains.";

  ProcessText(testText4);

  return 0;
}

float CountWords(char text[]) {
  size_t textSize = strlen(text);
  float count = 0;

  for (size_t i = 0; i <= textSize; i++) {
    if (text[i] == ' ' && text[i + 1] != ' ') {
      count++;
    }
  }

  return count + 1;
}

struct Count CountLetters(char text[], float words) {
  size_t textSize = strlen(text);

  struct Count c;
  c.overall = 0.0;
  c.avg = 0.0;

  for (size_t i = 0; i <= textSize; i++) {
    if (isalpha(text[i])) {
      c.overall += 1;
    }
  }

  if (c.overall > 0) {
    c.avg = (c.overall / words) * 100;
  }

  return c;
}

struct Count CountSentences(char text[], float words) {
  size_t textSize = strlen(text);

  struct Count c;
  c.overall = 0;
  c.avg = 0;

  for (size_t i = 0; i <= textSize; i++) {
    if (text[i] == '.' || text[i] == '?' || text[i] == '!') {
      c.overall += 1;
    }
  }

  if (c.overall > 0) {
    c.avg = (c.overall / words) * 100;
  }

  return c;
}

float CountColemanLiauIndex(float letters, float sentences) {
  float index = 0.0588 * letters - 0.296 * sentences - 15.8;
  return index;
}

void PrintGrade(float index) {
  int roundedIndex = round(index);

  if (roundedIndex < 1) {
    printf("Before grade 1\n");
  } else if (roundedIndex > 16) {
    printf("Grade 16+\n");
  } else {
    printf("Grade %i\n", roundedIndex);
  }
}

void ProcessText(char text[]) {
  float words = CountWords(text);
  struct Count letters = CountLetters(text, words);
  struct Count sentences = CountSentences(text, words);
  float index = CountColemanLiauIndex(letters.avg, sentences.avg);

  printf("In the text is %f words, %f letters and %f average letters per 100 "
         "words\n",
         words, letters.overall, letters.avg);
  printf("There is %f sentences with %f average sentences per 100 words\n",
         sentences.overall, sentences.avg);

  printf("Index is %f\n", index);

  PrintGrade(index);
}
