#include <iostream>
#include <queue>
#include <string>
#include <regex.h>
#define MAX_LENGTH 64
#define MAX_SIZE 25000000
#define INFO_INTERVAL 2000000
#define FatalError(code) fprintf(stderr, code)
using namespace std;
char FILENAME[] = "massive_float/clean_data.txt";
char prefix[] = "output/";
int STEP1_STAGE = 0;
int STEP2_STAGE = 0;
int TOTAL_STAGE = 0;
char PATIENT_INFO[] = "-\\|/";
int PATIENT_COUNTER = 0;
queue<int> external_files;


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
            fprintf(stderr, "%s\n", buff);
            break;
        }
        else
        {
            counter++;
            fprintf(out, "%lG\n", x);
        }
        if ((counter) % 100000 == 0)
            fprintf(stderr, "%d\n", counter);
    }
    fprintf(stderr, "%d\n", counter);
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


char * get_output_filename(const char * prefix, const int number)
{
    char * result = new char[5 * MAX_LENGTH];
    strcpy(result, prefix);
    strcat(result, to_string(number).c_str());
    strcat(result, ".txt");
    return result;
}


int step_1(FILE * data, const char * PATH, const char * filename)
{
    STEP1_STAGE++;
    fprintf(stderr, "┏Running  [STEP_1: STAGE_%d]\n", STEP1_STAGE);
    FILE * out;
    write_in(&out, PATH, filename);
    int counter = 0;
    double * sorter = new double[MAX_SIZE];
    int flag = 0;
    fprintf(stderr, "┃Reading in...\n");
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
    fprintf(stderr, "\b \b┃Sorting...\n");
    sort(sorter, sorter + MAX_SIZE);
    fprintf(stderr, "┃Storing...\n");
    for (int _ = 0; _ < MAX_SIZE; _++)
    {
        fprintf(out, "%lG\n", sorter[_]);
        if (_ % INFO_INTERVAL == 0)
            print_patient_info();
    }
    fprintf(stderr, "\b \b┗Finished [STEP_1: STAGE_%d]\n", STEP1_STAGE);
    external_files.push(TOTAL_STAGE);
    delete[] sorter;
    fclose(out);
    return flag;
}


void step_2(int file_number_1, int file_number_2, const char * PATH, const char * filename)
{
    FILE * data_1;
    FILE * data_2;
    read_in(&data_1, PATH, get_output_filename(prefix, file_number_1));
    read_in(&data_2, PATH, get_output_filename(prefix, file_number_2));
    STEP2_STAGE++;
    fprintf(stderr, "┏Running  [STEP_2: STAGE_%d]\n", STEP2_STAGE);
    FILE * out;
    write_in(&out, PATH, filename);
    fprintf(stderr, "┃Comparing & Storing... \n");
    int counter = 0;
    double x1 = 0.0, x2 = 0.0;
    int flag = 0;
    while (!feof(data_1) && !feof(data_2))
    {
        if (flag == 0)
        {
            fscanf(data_1, "%lf\n", &x1);
            fscanf(data_2, "%lf\n", &x2);
        }
        if (flag == 1)
            fscanf(data_1, "%lf\n", &x1);
        if (flag == 2)
            fscanf(data_2, "%lf\n", &x2);
        if (x1 <= x2)
        {
            fprintf(out, "%lG\n", x1);
            flag = 1;
        }
        else
        {
            fprintf(out, "%lG\n", x2);
            flag = 2;
        }
        counter++;
        if (counter % INFO_INTERVAL == 0)
            print_patient_info();
    }
    while (!feof(data_1))
    {
        fscanf(data_1, "%lf\n", &x1);
        fprintf(out, "%lG\n", x1);
        counter++;
        if (counter % INFO_INTERVAL == 0)
        {
            fprintf(stderr, "ttt1\n");
            print_patient_info();
        }
    }
    fclose(data_1);
    while (!feof(data_2))
    {
        fscanf(data_2, "%lf\n", &x2);
        fprintf(out, "%lG\n", x2);
        counter++;
        if (counter % INFO_INTERVAL == 0)
        {
            fprintf(stderr, "ttt2\n");
            print_patient_info();
        }
    }
    fclose(data_2);
    fclose(out);
    char file_name_1[5 * MAX_LENGTH];
    char file_name_2[5 * MAX_LENGTH];
    strcpy(file_name_1, PATH);
    strcpy(file_name_2, PATH);
    strcat(file_name_1, get_output_filename(prefix, file_number_1));
    strcat(file_name_2, get_output_filename(prefix, file_number_2));
    remove(file_name_1);
    remove(file_name_2);
    fprintf(stderr, "\b \b┃Removed intermediate file\n");
    external_files.push(TOTAL_STAGE);
    fprintf(stderr, "┗Finished [STEP_2: STAGE_%d]\n", STEP2_STAGE);
}


//    get_clean_data(fp, PATH, "output/clean_data.txt");
int main(int argc, char const *argv[])
{
    time_t start, end;
    start = clock();




    FILE * origin;
	argv[0] = "/Users/apple/Documents/Data_Structures/project/External_Sorting";
    char PATH[5 * MAX_LENGTH];
    strcpy(PATH, argv[0]);
    get_absolute_path(PATH);
    read_in(&origin, PATH, FILENAME);
    char * output;
    while (!feof(origin))
    {
        output = get_output_filename(prefix, TOTAL_STAGE);
        step_1(origin, PATH, output);
        delete[] output;
        TOTAL_STAGE++;
    }
    while (external_files.size() > 1)
    {
        int file_number_1 = external_files.front();
        external_files.pop();
        int file_number_2 = external_files.front();
        external_files.pop();
        output = get_output_filename(prefix, TOTAL_STAGE);
        step_2(file_number_1, file_number_2, PATH, output);
        TOTAL_STAGE++;
    }
    fclose(origin);





    end = clock();
    cout << (double)((end - start) / CLOCKS_PER_SEC) << endl;
	return 0;
}
