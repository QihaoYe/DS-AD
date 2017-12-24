#include <iostream>
#include <fstream>
#include <regex.h>
#define MAX_LENGTH 64
#define FatalError(code) fprintf(stderr, code)
char FILENAME[] = "massive_float/data.txt";


using namespace std;


void get_absolute_path(char document[])
{
    for (int i=(int)strlen(document) - 1; i >= 0; i--)
    {
        if (document[i] == '/')
            break;
        document[i] = '\0';
    }
}


void read_in(FILE ** fp, const char * PATH, const char * filename)
{
    char document[5 * MAX_LENGTH];
    strcpy(document, PATH);
    get_absolute_path(document);
    strcat(document, filename);
    if (NULL == (*fp = fopen(document,"r")))
        FatalError("Can not open the file!\n");
}
// Use the absolute path of the source document


void merge(double A[], double temp[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;
    while (i != mid + 1 && j != right + 1)
        temp[k++] = A[i] <= A[j] ? A[i++] : A[j++];
    while (i != mid + 1)
        temp[k++] = A[i++];
    while (j != right +1)
        temp[k++] = A[j++];
    for (int _ = left; _ <= right; _++)
        A[_] = temp[_];
}


void merge_sort(double A[], double temp[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        merge_sort(A, temp, left, mid);
        merge_sort(A, temp, mid + 1, right);
        merge(A, temp, left, mid, right);
    }
}


int is_dirty_data(const char buff[])
{
    const char * pattern = "^(-?[0-9]+)([.][0-9]+)?([eE][-+]?[0-9]+)?[\n]$";
    regex_t reg = {};
    int flag = 0;
    regcomp(&reg, pattern, REG_EXTENDED|REG_NOSUB);
    flag = regexec(&reg, buff, 0, NULL, 0);
    regfree(&reg);
    if (flag)
        return 1;
    return 0;
}


void get_clean_data(FILE * data, const char * PATH, const char * filename)
{
    char document[5 * MAX_LENGTH];
    char buff[MAX_LENGTH];
    int counter = 0;
    strcpy(document, PATH);
    get_absolute_path(document);
    strcat(document, filename);
    ofstream out(document);
    while (fgets(buff, MAX_LENGTH, data))
    {
        double x;
        int flag = 0;
        if (is_dirty_data(buff))
            continue;
        flag = sscanf(buff, "%lf\n", &x);
        if (flag != 1)
        {
            cout << buff << endl;
            break;
        }
        else
        {
            counter++;
            out << x << endl;
        }
        if ((counter) % 100000 == 0)
            cout << counter << endl;
    }
    out.close();
    cout << counter << endl;
}

/*
 * abandoned
 * reason: too slow
#include <regex>
int is_dirty_data(const char buff[])
{
    regex reg("^(-?\\d+)(\\.\\d+)?([eE][-+]?\\d+)?\\n$");
    string observer = buff;
    smatch result;
    if (regex_match(observer, result, reg))
        return 0;
    return 1;
}
*/

int main(int argc, char const *argv[])
{
    FILE * fp;
	argv[0] = "/Users/apple/Documents/Data_Structures/project/External_Sorting";
    read_in(&fp, argv[0], FILENAME);
    get_clean_data(fp, argv[0], "output/clean_data.txt");
	return 0;
}

//int main(int argc, char const *argv[])
//{
//    ofstream out("/Users/apple/Documents/Data_Structures/project/output/out.txt");
//    if (out.is_open())
//    {
//        out << "This is a line.\n";
//        out << "This is another line.\n";
//        cout << "ahas" << endl;
//        out.close();
//    }
//    return 0;
//}