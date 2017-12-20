#include <iostream>
#include <cmath>
#include <map>
#define MAX_LENGTH 64
#define FatalError(code) fprintf(stderr, code)
using namespace std;


typedef struct frequency_group
{
    int frequency_1;
    int frequency_2;
    frequency_group()
    {
        this->frequency_1 = 0;
        this->frequency_2 = 0;
    }
    frequency_group(int frequency_1, int frequency_2)
    {
        this->frequency_1 = frequency_1;
        this->frequency_2 = frequency_2;
    }
}frequency_group;


double norm(const int * p, int n)
{
    int norm = 0;
    for (int i = 0; i < n; i++)
        norm += p[i] * p[i];
    return sqrt(norm);
}


double similarity(int * p1, int * p2, int n)
{
    double cos = 0.0;
    for (int i = 0; i < n; i++)
        cos += p1[i] * p2[i];
    cos /= (norm(p1, n) * norm(p2, n));
    return cos;
}


void read_in(FILE ** fp, const char * PATH, char * filename)
{
    char document[5 * MAX_LENGTH];
    strcpy(document, PATH);
    for (int i=(int)strlen(document) - 1; i >= 0; i--)
    {
        if (document[i] == '/')
            break;
        document[i] = '\0';
    }
    strcat(document, filename);
    if (NULL == (*fp = fopen(document,"r")))
        FatalError("Can not open the file!\n");
}
// Use the absolute path of the source document

void cut_head(FILE ** fp, char symbol)
{
    char cmp;
    int flag = 0;
    while (!feof(*fp))
    {
        fscanf(*fp, "%c", &cmp);
        while (cmp == symbol)
        {
            fscanf(*fp, "%c", &cmp);
            flag = 1;
        }
        if (flag)
            break;
    }
}
// ignore the head of the source document

int main(int argc, char const *argv[])
{
    FILE * fp;
    map<string, int> word_list;
    map<string, frequency_group> temp;
    int * common_words[2];

    char filename[] = "source2_keywords.txt";
    read_in(&fp, argv[0], filename);
    cut_head(&fp, '-');
    int max_fre = 100000;
    int if_max = 1;
    while (!feof(fp))
    {
        char buff[MAX_LENGTH];
        int frequency;
        int flag;
        string word;
        flag = fscanf(fp, "%d %s", &frequency, buff);
        if (if_max)
        {
            max_fre = frequency;
            if_max = 0;
        }
        if (flag != 2)
            break;
        if (frequency < max_fre / 100)
            break;
        if (strlen(buff) < 5)
            continue;
        word = buff;
        word_list[word] = frequency;
    }
    // read in source2 and create a map of word and frequency

    strcpy(filename, "source1_keywords.txt");
    cout << "Common words\tFrequency in source1\tFrequency in source2" << endl;
    read_in(&fp, argv[0], filename);
    cut_head(&fp, '-');
    max_fre = 100000;
    if_max = 1;
    while (!feof(fp))
    {
        char buff[MAX_LENGTH];
        int frequency;
        int flag;
        int previous_fre;
        string word;
        flag = fscanf(fp, "%d %s", &frequency, buff);
        if (if_max)
        {
            max_fre = frequency;
            if_max = 0;
        }
        if (flag != 2)
            break;
        if (frequency < max_fre / 100)
            break;
        if (strlen(buff) < 5)
            continue;
        word = buff;
        if ((previous_fre = word_list[word]) > 0)
        {
            printf("%12s\t%12d%8s\t%12d%8s\n", word.c_str(), frequency, "", word_list[word], "");
            temp[word] = frequency_group(frequency, previous_fre);
        }
    }
    // read in source2 and pick up the common words between source1 and source2

    int length = (int)temp.size();
    common_words[0] = new int[length];
    common_words[1] = new int[length];
    int index = 0;
    for (map<string, frequency_group>::iterator iter = temp.begin(); iter != temp.end(); iter++)
    {
        common_words[0][index] = iter->second.frequency_1;
        common_words[1][index] = iter->second.frequency_2;
        index++;
    }
    // create arrays of frequency

    double result;
    result = similarity(common_words[0], common_words[1], length);
    // calculate the similarity

    printf("\nSimilarity of these two sources is %g\n", result);
    if (result > 0.5)
        cout << "They are very alike!" << endl;
    else
        cout << "It seems that they are not so similar!" << endl;
    delete common_words[0];
    delete common_words[1];
	return 0;
}
