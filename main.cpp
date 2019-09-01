/* 
 * File:   main.cpp
 * Author: pavelsha
 *
 * Created on 31 августа 2019 г., 17:40
 */

#include <cstdlib>
#include <iostream>
#include <ctime>

const bool TEST = false;
const bool USE_PAUSE = true; // without test
const int ATTEMPTS_COUNT = 4;

const char PERS_PRONOUN_COUNT = 7;
std::string enPersPronoun[PERS_PRONOUN_COUNT] =
    { "I", "you", "you", "we", "he", "she", "they" };
std::string ruPersPronoun[PERS_PRONOUN_COUNT] =
    { "я", "ты", "вы", "мы", "он", "она", "они" };

// 3 forms + present simple + s
const int EN_VERB_COUNT = 10; // expanded
const char EN_VERB_FORMS_COUNT = 4;
std::string enVerbs[EN_VERB_COUNT][EN_VERB_FORMS_COUNT] =
    {
        { "play", "played", "played", "plays" },
        { "love", "loved", "loved", "loves" },
        { "see", "saw", "seen", "sees" },
        { "live", "lived", "lived", "lives" },
        { "work", "worked", "worked", "works" },
        { "open", "opened", "opened", "opens" },
        { "close", "closed", "closed", "closes" },
        { "come", "came", "come", "comes" },
        { "go", "went", "gone", "goes" },
        { "know", "knew", "known", "knows" }
    };

// infinitive + 6 present + 3 psst
const int RU_VERB_COUNT = 1 + EN_VERB_COUNT; // will + expanded
const char RU_VERB_FORMS_COUNT = 10;
std::string ruVerbs[RU_VERB_COUNT][RU_VERB_FORMS_COUNT] =
    {
        { "быть", "буду", "будешь", "будет", "будем", "будете", "будут", "был", "была", "были" },
        { "играть", "играю", "играешь", "играет", "играем", "играете", "играют", "играл", "играла", "играли" },
        { "любить", "люблю", "любишь", "любит", "любим", "любите", "любят", "любил", "любила", "любили" },
        { "видеть", "вижу", "видишь", "видит", "видим", "видете", "видят", "видел", "видела", "видели" },
        { "жить", "живу", "живешь", "живет", "живем", "живете", "живут", "жил", "жила", "жили" },
        { "работать", "работаю", "работаешь", "работает", "работаем", "работаете", "работают", "работал", "работала", "работали" },
        { "открыть", "открываю", "открываешь", "открывает", "открываем", "открываете", "открывают", "открыл", "открыла", "открыли" },
        { "закрыть", "закрываю", "закрываешь", "закрывает", "закрываем", "закрываете", "закрывают", "закрыл", "закрыла", "закрыли" },
        { "приходить", "прихожу", "приходишь", "приходит", "приходим", "приходите", "приходят", "пришел", "пришла", "пришли" },
        { "идти", "иду", "идешь", "идет", "идем", "идете", "идут", "шел", "шла", "шли" },
        { "знать", "знаю", "знаешь", "знает", "знаем", "знаете", "знают", "знал", "знала", "знали" }
    };

bool needS(char p) { return p == 4 || p == 5; }
char persToRuVerb(char p, bool past)
{
    if (past)
    {
        if (p == 0 || p == 1 || p == 4)
            return 7;
        else if (p == 5)
            return 8;
        else
            return 9;
    }
    
    switch(p)
    {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 5;
        case 3:
            return 4;
        case 4:
        case 5:
            return 3;
        case 6:
            return 6;
    }
    return 0;
}

/*
  Params:
    tense: 0 - norm, 1 - ?, 2 - not
    type: 0 - present, 1 - past, 2 - future
 */
void generate(char pers, int verb, char tense, char type)
{
    std::string enSentence, ruSentence;    
    ruSentence += ruPersPronoun[pers];
    if (tense == 1)
    {
        if (type == 2)
            enSentence += "will ";
        else if (type == 1)
            enSentence += "did ";
        else
        {
            if (needS(pers))
                enSentence += "does ";
            else
                enSentence += "do ";
        }
    }
    enSentence += enPersPronoun[pers];
    if (tense == 2)
        ruSentence += " не";
    if (tense != 1 && type == 2)
    {
        if (tense == 0)
            enSentence += " will";
        else
            enSentence += " will not";
    }
    else if (tense == 2)
    {
        if (type == 1)
            enSentence += " didn't";
        else
        {
            if (needS(pers))
                enSentence += " doesn't";
            else
                enSentence += " don't";
        }
    }
    if (type == 2)
        ruSentence += " " + ruVerbs[0][persToRuVerb(pers, false)] +
                      " " + ruVerbs[verb + 1][0];
    else
        ruSentence += " " + ruVerbs[verb + 1][persToRuVerb(pers, type == 1)];
    if (tense == 1)
        ruSentence += "?";
    if (type == 1 && tense == 0)
        enSentence += " " + enVerbs[verb][1];
    else if (type == 0 && tense == 0 && needS(pers))
        enSentence += " " + enVerbs[verb][3];
    else
        enSentence += " " + enVerbs[verb][0];
    if (tense == 1)
        enSentence += "?";

    std::cout << " --------------------- " << std::endl;
    std::cout << "Ru: " << ruSentence << std::endl;
    if (USE_PAUSE)
    {
        char ch;
        std::cin >> ch;
    }
    std::cout << "En: " << enSentence << std::endl;
}

void generate()
{
    char t = std::rand() % 3, tp = std::rand() % 3,
         p = std::rand() % PERS_PRONOUN_COUNT;
    int v = std::rand() % EN_VERB_COUNT;
    generate(p, v, t, tp);
}

void test()
{
    char p, t, tp;
    int v;
    std::cout << "  -- T E S T  -- " << std::endl;
    for (t = 0; t < 3; ++t)
        for (tp = 0; tp < 3; ++tp)
            for (v = 0; v < 1; ++v)
                for (p = 0; p < PERS_PRONOUN_COUNT; ++p)
                    generate(p, v, t, tp);
    std::cout << "  -- T E S T  -- " << std::endl;
}

int main(int argc, char** argv)
{
    if (TEST)
        test();
    else
    {
        int counter = ATTEMPTS_COUNT;
        std::srand(time(NULL));
        if (counter < 0)
            return 0;
        while(counter--)
            generate();
    }
    return 0;
}

