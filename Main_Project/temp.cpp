#include <iostream>
#include <ctime>
#include <cstring>
#include <chrono>
using namespace std;
const int MAX_WORD_LEN = 100;
void shift_left(char[][101],int,int);
void print_array(char[][101],int);
int cut_the_end(char[][101],int);
int cut_depatured(char[][101],int);
int str_time_2_int_time(char[]);
int const_str_time_2_int_time(const char []);
struct flights_departure {
    const char* fly_num;
    const char* origin;
    const char* destination;
    const char* date;
    const char* take_of;
    const char* flight_time_lenght;
};
struct flights_arrival {
    const char* fly_num;
    const char* origin;
    const char* destination;
    const char* date;
    const char* take_of;
    const char* flight_time_lenght;
};
struct near_flight {
    const char* fly_num;
    const char* origin;
    const char* destination;
    const char* date;
    const char* take_of;
    const char* flight_time_lenght;
};
int list_near_flights_depature(flights_departure [],near_flight [],int,char []);
int str_2_struct(flights_departure [],char[][101],int);
int struct_2_file_and_print(near_flight [],int);
int main(){
    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    char time_str[50];
    strftime(time_str, sizeof(time_str), "%Y/%m/%d %H:%M", time_info);
    FILE *f = NULL;
    f = fopen("./flights.txt", "r");
    if (!f) {
        printf("cannot open file\n");
        return 1;
    }
    char buf[MAX_WORD_LEN + 1];
    char sv_buf[900][MAX_WORD_LEN + 1];
    int words = 0;
    int is_end =0;
    while (1) {
        int ret = fscanf(f, "%s", buf);
        if (ret != 1) {
            break;
        }
        is_end = 0;
        for(int i = 0; i<100;i++) {
            if(buf[i] == '\0') {
                is_end = 1;
            }
            if(is_end) {
                sv_buf[words][i+1] = NULL;
            }
            else {
                sv_buf[words][i] = buf[i];
            }

        }
        words++;
    }
    if (ferror(f)) {
        printf("error on reading the file\n");
        fclose(f);
        return 1;
    }
    else if (feof(f)) {
        printf("reading the file done\n");
        fclose(f);
    }
    shift_left(sv_buf,words,56);
    int nums_words_cut = cut_the_end(sv_buf,words);
    nums_words_cut = cut_depatured(sv_buf,nums_words_cut);
    flights_departure flights[100];
    flights_arrival flights2[100];
    int num_flights = str_2_struct(flights,sv_buf,nums_words_cut);
    near_flight near_flights[20];
    int num_near_flights_depature = list_near_flights_depature(flights,near_flights,num_flights,time_str);
    struct_2_file_and_print(near_flights,num_near_flights_depature);
return 0;
}
int struct_2_file_and_print(near_flight near_flights [], int num_near_flights) {
    FILE *f = NULL;
    f = fopen("near_flights.txt", "w");
    if (!f) {
        printf("cannot open file\n");
        return 1;
    }
    for (int i = 0; i < num_near_flights; i++) {
        fprintf(f, "%s %s %s %s %s \n",near_flights[i].fly_num,near_flights[i].origin,near_flights[i].destination,near_flights[i].take_of,near_flights[i].flight_time_lenght);
    }
    fclose(f);
    for (int i = 0; i < num_near_flights; i++) {
        printf("%s %s %s %s %s \n",near_flights[i].fly_num,near_flights[i].origin,near_flights[i].destination,near_flights[i].take_of,near_flights[i].flight_time_lenght);
    }
    return 0;
}
int list_near_flights_depature(flights_departure flights [],near_flight near_flights[],int num_flights,char time[]) {
    int count = 0;
    const int real_time = str_time_2_int_time(time);
    int flight_time = 0;
    int last_i=0;
    for(int i =0; i < num_flights ; i++) {
        flight_time = const_str_time_2_int_time(flights[i].take_of);
        if(abs(flight_time - real_time) <=60) {
            near_flights[count].take_of = flights[i].take_of;
            near_flights[count].date = flights[i].date;
            near_flights[count].destination = flights[i].destination;
            near_flights[count].flight_time_lenght = flights[i].flight_time_lenght;
            near_flights[count].fly_num = flights[i].fly_num;
            near_flights[count].origin = flights[i].origin;
            count++;
            last_i=i;
        }
        else {
            last_i=i;
            if(count>0) {
                break;
            }
        }
    }
    for(int i =last_i; i < num_flights ; i++) {
        if(count<5) {
            near_flights[count].take_of = flights[i].take_of;
            near_flights[count].date = flights[i].date;
            near_flights[count].destination = flights[i].destination;
            near_flights[count].flight_time_lenght = flights[i].flight_time_lenght;
            near_flights[count].fly_num = flights[i].fly_num;
            near_flights[count].origin = flights[i].origin;
            count++;
        }
        else{break;}
    }
    return count;
}
int str_time_2_int_time(char time []) {
    int result = 0;
    for (int i = 0; i<18 ; i++) {
        if(time[i]==':') {
            result = result + (time[i-1]-48)*60 + (time[i-2]-48) *600;
            result = result + (time[i+1]-48) * 10 + time[i+2]-48;
        }
    }
    return result;
}
int const_str_time_2_int_time(const char time []) {
    int result = 0;
    for (int i = 0; i<18 ; i++) {
        if(time[i]==':') {
            result = result + (time[i-1]-48)*60 + (time[i-2]-48) *600;
            result = result + (time[i+1]-48) * 10 + time[i+2]-48;
        }
    }
    return result;
}
int str_2_struct(flights_departure flights[],char array[][101],int size_array) {
    int counter =0;
    for(int i =0;i<size_array;i++) {
        if(strcmp(array[i],"Time")==0) {
            //if there is just on time or plane is waiting for someone
            if(strcmp(array[i+7],"Time")==0||strcmp(array[i+6],"Delayed")==0) {
                flights[counter].origin = "Tehran";
                flights[counter].fly_num = array[i+1];
                flights[counter].destination = array[i+2];
                flights[counter].date = array[i+3];
                flights[counter].take_of = array[i+5];
                counter++;
                i+=5;
            }
            //if the time of the flight is less than hour to take off
            else if(strcmp(array[i+9],"Time")==0||strcmp(array[i+8],"Delayed")==0) {
                flights[counter].origin = "Tehran";
                flights[counter].fly_num = array[i+3];
                flights[counter].destination = array[i+4];
                flights[counter].date = array[i+5];
                flights[counter].take_of = array[i+7];
                counter++;
                i+=7;
            }
            //if the time of the fllight is more than or is a hour to take off
            else if(strcmp(array[i+12],"Time")==0||strcmp(array[i+11],"Delayed")==0) {
                flights[counter].origin = "Tehran";
                flights[counter].fly_num = array[i+6];
                flights[counter].destination = array[i+7];
                flights[counter].date = array[i+8];
                flights[counter].take_of = array[i+10];
                counter++;
                i+=10;
            }
            //if the name has two parts
            else if(strcmp(array[i+13],"Time")==0||strcmp(array[i+12],"Delayed")==0) {
                flights[counter].origin = "Tehran";
                flights[counter].fly_num = array[i+6];
                flights[counter].destination = strcat(array[i+7],array[i+8]);
                flights[counter].date = array[i+9];
                flights[counter].take_of = array[i+11];
                counter++;
                i+=10;
            }
            //if the name has three parts
            else if(strcmp(array[i+14],"Time")==0||strcmp(array[i+13],"Delayed")==0) {
                flights[counter].origin = "Tehran";
                flights[counter].fly_num = array[i+7];
                flights[counter].destination = strcat(array[i+8],array[i+9]);
                flights[counter].date = array[i+10];
                flights[counter].take_of = array[i+12];
                counter++;
                i+=10;
            }

        }
    }
    return counter;
}
int cut_depatured(char array[][101], int size_array) {
    int words = 0 ;
    int index = 0;
    for (int i = 0;i < size_array;i++) {
        if(strcmp(array[i] , "Departed") == 0) {
            index = words;
        }
        words++;
    }
    shift_left(array,size_array,index+1);
    return words-index-1;
}
int cut_the_end(char array[][101], int size_array) {
    int is_end = 0;
    int index_end = 100;
    int counter = 0;
    for (int i = 0;i < size_array;i++) {
        if(strcmp(array[i] , "Contact") == 0) {
            if(strcmp(array[i+1] , "us") == 0) {
                if(is_end == 0) {
                    index_end = counter;
                }
                is_end = 1;
            }
        }
        if(is_end) {
            for(int j = 0 ; j<101;j++) {
                array[i][j] = NULL;
                array[i+1][j] = NULL;
            }
        }
        counter ++ ;
    }
    return index_end;
}
void shift_left(char array[][101],int size_array , int shift_lenght) {
    for (int i = 0;i < size_array;i++) {
        for( int j = 0;j<101;j++) {
            if(i + shift_lenght < size_array) {
                array[i][j] = array[i+shift_lenght][j];
            }
            else {
                array[i][j] = NULL;
            }

        }
    }
}
void print_array(char array[][101], int size_array) {
    for (int i = 0;i < size_array;i++) {
        for( int j = 0;j<101;j++) {
            printf("%c",array[i][j]);
        }
        cout<<endl;
    }
}