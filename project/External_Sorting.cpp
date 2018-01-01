#include <iostream>
#include <queue>
#include <regex.h>
#include <fstream>
#define MAX_LENGTH 64
#define MAX_SIZE 25000000
#define INFO_INTERVAL 2000000
#define FatalError(code) fprintf(stderr, code)
#define ORIGINAL_STARTING_VALUE 0
#define STEP_1_FINISHED_VALUE 10
#define CLOCKS_PER_SEC 1000000.0
using namespace std;
char FILENAME[] = "massive_float/clean_data.txt";
char prefix[] = "output/";
int STEP1_STAGE = ORIGINAL_STARTING_VALUE;
int STEP2_STAGE = ORIGINAL_STARTING_VALUE;
int TOTAL_STAGE = ORIGINAL_STARTING_VALUE;
char PATIENT_INFO[] = "-\\|/";
int PATIENT_COUNTER = 0;
queue<int> external_files;




void next_patient_counter(int * patient_counter);
void print_patient_info();
void get_absolute_path(char document[]);
char * get_absolute_filename(const char * PATH, const char * filename);
void read_in(FILE ** fp, const char * PATH, const char * filename);
void write_in(FILE ** fp, const char * PATH, const char * filename);
int is_dirty_data(const char buff[]);
char * get_output_filename(const char * prefix, int number);
double str2double(char str[]);
int step_1(FILE * data, const char * PATH, const char * filename);
void step_1_0(fstream * data, const char * absolute_filename);
void step_2(int file_number_1, int file_number_2, const char * PATH, const char * filename);
void step_2_0(int file_num, const char * PATH, const char * filename);
void step_2_1(int file_num, const char * PATH, const char * filename);




//    while (external_files.size() > 1)
//    {
//        int file_number_1 = external_files.front();
//        external_files.pop();
//        int file_number_2 = external_files.front();
//        external_files.pop();
//        output = get_output_filename(prefix, TOTAL_STAGE);
//        step_2(file_number_1, file_number_2, PATH, output);
//        TOTAL_STAGE++;
//    }
/*
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
        break;
    }
//    output = get_output_filename(prefix, TOTAL_STAGE);
//    step_2_0(TOTAL_STAGE, PATH, output);
//    TOTAL_STAGE++;
    fclose(origin);





    end = clock();
    cout << (double)((end - start) / CLOCKS_PER_SEC) << endl;
	return 0;
}
*/

int main(int argc, char const *argv[])
{
    time_t start, end;
    start = clock();


    argv[0] = "/Users/apple/Documents/Data_Structures/project/External_Sorting";
    char PATH[5 * MAX_LENGTH];
    strcpy(PATH, argv[0]);
    get_absolute_path(PATH);
    char * output;
    fstream origin(get_absolute_filename(PATH, FILENAME), fstream::in);
    while (origin.peek() != EOF)
    {
        output = get_output_filename(prefix, TOTAL_STAGE);
        step_1_0(&origin, get_absolute_filename(PATH, output));
        delete[] output;
        TOTAL_STAGE++;
    }
    output = get_output_filename(prefix, TOTAL_STAGE);
    step_2_1(TOTAL_STAGE, PATH, output);
    TOTAL_STAGE++;
    origin.close();


    end = clock();
    fprintf(stderr, "TOTAL TIME: %lgs\n", (double)((end - start) / CLOCKS_PER_SEC));
    return 0;
}


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


char * get_absolute_filename(const char * PATH, const char * filename)
{
    char * result = new char[5 * MAX_LENGTH];
    strcpy(result, PATH);
    strcat(result, filename);
    return result;
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


void get_clean_data(FILE * data, const char * PATH, const char * filename);
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
            fprintf(out, "%-+17.9E\n", x);
        }
        if ((counter) % 100000 == 0)
            fprintf(stderr, "%d\n", counter);
    }
    fprintf(stderr, "%d\n", counter);
}
//    get_clean_data(origin, PATH, "output/clean_data.txt");


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


char * get_output_filename(const char * prefix, int number)
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
        fprintf(out, "%-+17.9E\n", sorter[_]);
        if (_ % INFO_INTERVAL == 0)
            print_patient_info();
    }
    fprintf(stderr, "\b \b┗Finished [STEP_1: STAGE_%d]\n", STEP1_STAGE);
    external_files.push(TOTAL_STAGE);
    delete[] sorter;
    fclose(out);
    return flag;
}


double str2double(char str[])
{
    double x = 0;
    int exp = (str[14] - '0') * 10 + str[15] - '0';
    if (str[16] != ' ')
        exp = exp * 10 + str[16] - '0';
    for (int i = 11; i >=3; i--)
    {
        x = x * 0.1 + str[i] - '0';
    }
    x = x * 0.1 + str[1] - '0';
    if (str[13] == '+')
    {
        while (exp > 100)
        {
            x *= 1e100;
            exp -= 100;
        }
        while (exp > 10)
        {
            x *= 1e10;
            exp -= 10;
        }
        while (exp > 0)
        {
            x *= 1e1;
            exp--;
        }
    }
    if (str[13] == '-')
    {
        while (exp > 100)
        {
            x /= 1e100;
            exp -= 100;
        }
        while (exp > 10)
        {
            x /= 1e10;
            exp -= 10;
        }
        while (exp > 0)
        {
            x /= 1e1;
            exp--;
        }
    }
    if (str[0] == '-')
        x = -x;
    return x;
}


void step_1_0(fstream * data, const char * absolute_filename)
{
    time_t start, end, mid;
    start = clock();


    STEP1_STAGE++;
    fprintf(stderr, "┏Running  [STEP_1: STAGE_%d]\n", STEP1_STAGE);
    fstream out(absolute_filename, fstream::out);
    int counter = 0;
    double * sorter = new double[MAX_SIZE];
    int flag = 0;
    fprintf(stderr, "┃Reading in...\n");
    while ((*data).peek() != EOF)
    {
        char temp[18];
        flag = (*data).read(temp, 18);
        if (flag != 1)
            break;
        sorter[counter++] = str2double(temp);
        if (MAX_SIZE == counter)
        {
            flag = 2;
            break;
        }
        if (counter % INFO_INTERVAL == 0)
            print_patient_info();
    }
    end = clock();
    fprintf(stderr, "\b \b┃Time: %lgs\n", (double)((end - start) / CLOCKS_PER_SEC));

    fprintf(stderr, "┃Sorting...\n");
    mid = clock();
    sort(sorter, sorter + counter);
    end = clock();
    fprintf(stderr, "┃Time: %lgs\n", (double)((end - mid) / CLOCKS_PER_SEC));

    fprintf(stderr, "┃Storing...\n");
    mid = clock();
    for (int _ = 0; _ < counter; _++)
    {
        char temp[18];
        sprintf(temp, "%-+17.9E\n", sorter[_]);
        out.write(temp, 18);
        if (_ % INFO_INTERVAL == 0)
            print_patient_info();
    }
    end = clock();
    fprintf(stderr, "\b \b┃Time: %lgs\n", (double)((end - mid) / CLOCKS_PER_SEC));
    fprintf(stderr, "┗Finished [STEP_1: STAGE_%d]  Time spent:%lgs\n", STEP1_STAGE, (double)((end - start) / CLOCKS_PER_SEC));
    delete[] sorter;
    out.close();
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
            fprintf(out, "%-+17.9E\n", x1);
            flag = 1;
        }
        else
        {
            fprintf(out, "%-+17.9E\n", x2);
            flag = 2;
        }
        counter++;
        if (counter % INFO_INTERVAL == 0)
            print_patient_info();
    }
    while (!feof(data_1))
    {
        fscanf(data_1, "%lf\n", &x1);
        fprintf(out, "%-+17.9E\n", x1);
        counter++;
        if (counter % INFO_INTERVAL == 0)
            print_patient_info();
    }
    fclose(data_1);
    while (!feof(data_2))
    {
        fscanf(data_2, "%lf\n", &x2);
        fprintf(out, "%-+17.9E\n", x2);
        counter++;
        if (counter % INFO_INTERVAL == 0)
            print_patient_info();
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


// multi-way merge
void step_2_0(int file_num, const char * PATH, const char * filename)
{
    FILE * data[file_num];
    int i;
    for (i = 0; i < file_num; i++)
        read_in(&data[i], PATH, get_output_filename(prefix, i));
    STEP2_STAGE++;
    fprintf(stderr, "┏Running  [STEP_2]\n");
    FILE * out;
    write_in(&out, PATH, filename);
    fprintf(stderr, "┃Comparing & Storing... \n");
    int counter = 0;
    double x[file_num];
    int flag = -1;
    int finish_flag = 0;
    int finished[file_num];
    memset(finished, 0, sizeof(finished));
    while (1)
    {
        for (i = 0; i < file_num; i++)
            if (finished[i]);
            else if (feof(data[i]))
            {
                finished[i] = 1;
                finish_flag++;
            }
        if (finish_flag >= file_num - 1)
            break;
        if (flag == -1)
            for (i = 0; i < file_num; i++)
                fscanf(data[i], "%lf\n", &x[i]);
        for (i = 0; i < file_num; i++)
            if (flag == i)
                fscanf(data[i], "%lf\n", &x[i]);
        double m = 1e+308;
        for (i = 0; i < file_num; i++)
        {
            if (finished[i])
                continue;
            else if (x[i] <= m)
            {
                m = x[i];
                flag = i;
            }
        }
        fprintf(out, "%-+17.9E\n", x[flag]);
        counter++;
        if (counter % INFO_INTERVAL == 0)
            print_patient_info();
    }
    for (i = 0; i < file_num; i++)
    {
        while (!feof(data[i]))
        {
            fscanf(data[i], "%lf\n", &x[i]);
            fprintf(out, "%-+17.9E\n", x[i]);
            counter++;
            if (counter % INFO_INTERVAL == 0)
                print_patient_info();
        }
    }
    for (i = 0; i < file_num; i++)
    {
        fclose(data[i]);
        char file_name[5 * MAX_LENGTH];
        strcpy(file_name, PATH);
        strcat(file_name, get_output_filename(prefix, i));
        remove(file_name);
    }
    fclose(out);
    fprintf(stderr, "\b \b┃Removed intermediate file\n");
    fprintf(stderr, "┗Finished [STEP_2]\n");
}


void step_2_1(int file_num, const char * PATH, const char * filename)
{
    time_t start, end;
    start = clock();


    fstream * data = new fstream[file_num];
    int i;
    for (i = 0; i < file_num; i++)
        (data[i]).open(get_absolute_filename(PATH, get_output_filename(prefix, i)), fstream::in);
    STEP2_STAGE++;
    fprintf(stderr, "┏Running  [STEP_2]\n");
    fstream out(get_absolute_filename(PATH, filename), fstream::out);
    fprintf(stderr, "┃Comparing & Storing... \n");
    int counter = 0;
    char * temp[file_num];
    for (i = 0; i < file_num; i++)
        temp[i] = new char[18];
    double x[file_num];
    int flag = -1;
    int finish_flag = 0;
    int finished[file_num];
    memset(finished, 0, sizeof(finished));
    while (1)
    {
        for (i = 0; i < file_num; i++)
            if (finished[i]);
            else if ((data[i]).peek() == EOF)
            {
                finished[i] = 1;
                finish_flag++;
            }
        if (finish_flag >= file_num - 1)
            break;
        if (flag == -1)
            for (i = 0; i < file_num; i++)
            {
                (data[i]).read(temp[i], 18);
                x[i] = str2double(temp[i]);
            }
        for (i = 0; i < file_num; i++)
            if (flag == i)
            {
                (data[i]).read(temp[i], 18);
                x[i] = str2double(temp[i]);
            }
        double m = 1e+308;
        for (i = 0; i < file_num; i++)
        {
            if (finished[i])
                continue;
            else if (x[i] <= m)
            {
                m = x[i];
                flag = i;
            }
        }
        out.write(temp[flag], 18);
        counter++;
        if (counter % INFO_INTERVAL == 0)
            print_patient_info();
    }
    for (i = 0; i < file_num; i++)
    {
        while ((data[i]).peek() != EOF)
        {
            (data[i]).read(temp[i], 18);
            out.write(temp[i], 18);
            counter++;
            if (counter % INFO_INTERVAL == 0)
                print_patient_info();
        }
    }
    for (i = 0; i < file_num; i++)
    {
        (data[i]).close();
        char file_name[5 * MAX_LENGTH];
        strcpy(file_name, PATH);
        strcat(file_name, get_output_filename(prefix, i));
        remove(file_name);
    }
    for (i = 0; i < file_num; i++)
        delete[] temp[i];
    delete[] data;
    out.close();
    fprintf(stderr, "\b \b┃Removed intermediate file\n");
    end = clock();
    fprintf(stderr, "┗Finished [STEP_2] Time spent:%lgs\n", (double)((end - start) / CLOCKS_PER_SEC));
}
