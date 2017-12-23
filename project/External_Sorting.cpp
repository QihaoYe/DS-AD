#include <iostream>
#include <regex>
#define MAX_LENGTH 64
#define FatalError(code) fprintf(stderr, code)
char FILENAME[] = "massive_float/test.txt";


using namespace std;


void read_in(FILE ** fp, const char * PATH, const char * filename)
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
    regex reg("^(-?\\d+)(\\.\\d+)?([eE][-+]?\\d+)?\\n$");
    string observe = buff;
    smatch result;
    if (regex_match(observe, result, reg))
        return 0;
    return 1;
}


int main(int argc, char const *argv[])
{
    FILE * fp;
    char buff[MAX_LENGTH];
	argv[0] = "/Users/apple/Documents/Data_Structures/project/External_Sorting";
    read_in(&fp, argv[0], FILENAME);
    int counter = 0;
    while (fgets(buff, MAX_LENGTH, fp))
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
            counter++;
        if ((counter + 1) % 100000 == 0)
            cout << counter << endl;
    }
    cout << counter << endl;
	return 0;
}

//int main()
//{
//    char a[] = "2gj3.234adsf";
//    double b = strtod(a, nullptr);
//    cout <<  << endl;
//    return 0;
//}