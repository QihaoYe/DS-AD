#include <iostream>
#include <fstream>
#include <regex.h>
#define MAX_LENGTH 64
#define MAX_SIZE 25000000
#define INFO_INTERVAL 2000000
#define FatalError(code) fprintf(stderr, code)
char FILENAME[] = "massive_float/clean_data.txt";
int STEP1_STAGE = 0;
char PATIENT_INFO[] = "-\\|/";
int PATIENT_COUNTER = 0;


using namespace std;


void next_patient_counter(int * patient_counter)
{
    *(patient_counter) = (*(patient_counter) + 1) % 4;
}


void print_patient_info()
{
    fprintf(stderr, "\b \b");
    fprintf(stderr, "%c", PATIENT_INFO[PATIENT_COUNTER]);
    next_patient_counter(&PATIENT_COUNTER);
}


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
    strcat(document, filename);
    if (NULL == (*fp = fopen(document,"r")))
        FatalError("Can not open the file!\n");
}


void write_in(FILE ** fp, const char * PATH, const char * filename)
{
    char document[5 * MAX_LENGTH];
    strcpy(document, PATH);
    strcat(document, filename);
    if (NULL == (*fp = fopen(document,"w")))
        FatalError("Can not open the file!\n");
}


/*
 * state : abandoned
 * reason: too slow
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
*/


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
    FILE * out;
    write_in(&out, PATH, filename);
    char buff[MAX_LENGTH];
    int counter = 0;
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
            fprintf(out, "%lG\n", x);
        }
        if ((counter) % 100000 == 0)
            cout << counter << endl;
    }
    cout << counter << endl;
}


/*
 * state : abandoned
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


int step_1(FILE * data, const char * PATH, const char * filename)
{
    STEP1_STAGE++;
    cout << "Running  [STEP_1: " << "STAGE_" << STEP1_STAGE << "]" << endl;
    FILE * out;
    write_in(&out, PATH, filename);
    int counter = 0;
    double * sorter = new double[MAX_SIZE];
    int flag = 0;
    cout << "Reading in..." << endl;
    while (!feof(data))
    {
        double x;
        flag = fscanf(data, "%lf\n", &x);
        if (flag != 1)
            break;
        sorter[counter++] = x;
        if (MAX_SIZE == counter)
        {
            flag = 2;
            break;
        }
        if (counter % INFO_INTERVAL == 0)
            print_patient_info();
    }
    cout << endl << "Sorting..." << endl;
    sort(sorter, sorter + MAX_SIZE);
    cout << "Storing..." << endl;
    for (int _ = 0; _ < MAX_SIZE; _++)
    {
        fprintf(out, "%lG\n", sorter[_]);
        if (_ % INFO_INTERVAL == 0)
            print_patient_info();
    }
    cout << endl << "Finished " << "[STEP_1: " << "STAGE_" << STEP1_STAGE << "]" << endl;
    delete[] sorter;
    return flag;
}


//    get_clean_data(fp, PATH, "output/clean_data.txt");
int main(int argc, char const *argv[])
{
    time_t start, end;
    start = clock();


    FILE * fp;
	argv[0] = "/Users/apple/Documents/Data_Structures/project/External_Sorting";
    char PATH[5 * MAX_LENGTH];
    strcpy(PATH, argv[0]);
    get_absolute_path(PATH);

    read_in(&fp, PATH, FILENAME);

    step_1(fp, PATH, "output/001.txt");
    step_1(fp, PATH, "output/002.txt");
//    remove("/Users/apple/Documents/Data_Structures/project/output/001.txt");


    end = clock();
    cout << (double)((end - start) / CLOCKS_PER_SEC) << endl;
	return 0;
}
