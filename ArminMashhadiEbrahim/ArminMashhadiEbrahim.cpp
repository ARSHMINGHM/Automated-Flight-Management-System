#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;
//question 1:
int num_flights;
const int MAX_WORD_LEN = 100;
void shift_left(char[][101],int,int);
void print_array(char*[101],int);
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
int list_near_flights_depature2(flights_arrival  [],near_flight [],int ,char []);
int str_2_struct(flights_departure [],char[][101],int);
int str_2_struct2(flights_arrival [],char [][101],int );
int struct_2_file_and_print(near_flight [],int);
int struct_2_file_and_print2(near_flight [],int);
int main_flights_depature_2_near_flights(flights_departure [],char [50]);
int main_flights_arrival_2_near_flights(flights_arrival [],char [50]);

//question 2:

struct passengers_info {
    const char* name;
    const char* id_num;
    const char* bag_weight;
    char sit_num[4];
};
int main_cards_passengers(const char*,passengers_info[],passengers_info[],int&,int&);
int str_2_struct_pass(passengers_info [] ,char*[900],int );
int restricted_over_weight_limit(passengers_info [] , int,passengers_info[],int&);
void weight_distribution(passengers_info [],int);
int str_weight_2_int(const char*);
void shift_left_passenger(passengers_info[],int,int);
void int_2_char(int ,char*);
int flights_between_1_3_hours(flights_departure [],char[50],flights_departure[]);
int give_passenger_card(flights_departure [],passengers_info[],passengers_info[],int,int);
int make_list_card_pass(passengers_info ,flights_departure);
int str_2_int (const char*);
int main(){
    flights_departure flights[100];
    flights_arrival flights2[100];
    flights_departure flights_b13h[20];
    char time_str[50];
    int return_value = 0;
    struct tm *time_info;

    time_t current_time = time(NULL);
    time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y/%m/%d %H:%M", time_info);
    return_value |= main_flights_depature_2_near_flights(flights,time_str);
    return_value |= main_flights_arrival_2_near_flights(flights2,time_str);

    passengers_info *passenger = new passengers_info[100];
    passengers_info *restricted_pass = new passengers_info[100];
    int passenger_id;
    int flights_b13h_num;
    while(1) {
        cout<<"please enter your id:";
        cin>>passenger_id;
        current_time = time(NULL);
        time_info = localtime(&current_time);
        strftime(time_str, sizeof(time_str), "%Y/%m/%d %H:%M", time_info);
        return_value |= main_flights_arrival_2_near_flights(flights2,time_str);
        return_value |= main_flights_depature_2_near_flights(flights,time_str);
        flights_b13h_num = flights_between_1_3_hours(flights,time_str,flights_b13h);
        return_value |= give_passenger_card(flights_b13h,passenger,restricted_pass,flights_b13h_num,passenger_id);
        _sleep(10000);
        if(return_value > 0) {
            return return_value;
        }
    }
    return return_value;
}
//question 2:
int give_passenger_card(flights_departure flights_b13h[],passengers_info passenger[],passengers_info restricted_pass[],int flights_b13h_num,int passenger_id) {
    char flight_file_name [11];
    int return_value = 0 ;
    flight_file_name[0] = '.';
    flight_file_name[1] = '/';
    int num_pass ;
    int num_restericted;
    int temp_id;
    for (int i =0; i < flights_b13h_num;i++) {
        for (int j =0 ; j<7;j++) {
            if(flights_b13h[i].fly_num[j]=='\0') {
                flight_file_name[j+2] = '.';
                flight_file_name[j+3] = 't';
                flight_file_name[j+4] = 'x';
                flight_file_name[j+5] = 't';
                flight_file_name[j+6] = '\0';
                break;
            }
            flight_file_name[j+2] = flights_b13h[i].fly_num[j];
        }
        return_value |= main_cards_passengers(flight_file_name,passenger,restricted_pass,num_pass,num_restericted);
        for(int z = 0 ; z<num_pass;z++) {
            temp_id = str_2_int(passenger[z].id_num);
            if(passenger_id == temp_id) {
                return_value |= make_list_card_pass(passenger[z],flights_b13h[i]);
                break;
            }
        }
        for(int z = 0 ; z<num_restericted-1;z++) {
            temp_id = str_2_int(restricted_pass[z].id_num);
            if(passenger_id == temp_id) {
                return_value |= make_list_card_pass(restricted_pass[z],flights_b13h[i]);
                break;
            }
        }
    }        return 0;
}
int make_list_card_pass(passengers_info passenger ,flights_departure flight_b13h) {
    FILE *f = NULL;
    char temp [15] ;
    for (int i = 0;i<10 ; i++) {
        temp[i] = passenger.id_num[i];
    }
    temp[10] = '.';
    temp[11] = 't';
    temp[12] = 'x';
    temp[13] = 't';
    temp[14] = '\0';
    f = fopen(temp, "w");
    if (!f) {
        printf("cannot open file\n");
        return 1;
    }
    fprintf(f, "%s %s %s %s %s %s \n",passenger.name,flight_b13h.fly_num,flight_b13h.origin,flight_b13h.destination,flight_b13h.take_of,passenger.sit_num);
    fclose(f);
    printf("%s %s %s %s %s %s \n",passenger.name,flight_b13h.fly_num,flight_b13h.origin,flight_b13h.destination,flight_b13h.take_of,passenger.sit_num);
    return 0;
}
int main_cards_passengers(const char* flight,passengers_info passenger[],passengers_info restricted_pass[], int& num_pass,int& num_ress) {
    FILE *f = NULL;
    f = fopen(flight, "r");
    if (!f) {
        printf("can not open file\n");
        return 1;
    }
    char buf[MAX_WORD_LEN + 1];
    auto** sv_buf = new char*[900];
    for(int i=0;i<900;i++) {
        sv_buf[i] = new char[900];
    }
    //delete previous datas
    for(int i=0;i<900;i++) {
        for(int j = 0;j<101;j++) {
            sv_buf[i][j] = '\0';
        }
    }
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
                sv_buf[words][i+1] = '\0';
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
    num_pass = str_2_struct_pass(passenger,sv_buf,words);
    num_pass = restricted_over_weight_limit(passenger , num_pass,restricted_pass,num_ress);
    weight_distribution(passenger,num_pass);

    return 0;
}
void weight_distribution(passengers_info passenger [],int num_pass) {
    //the plane have 43 seats
    int middle = 22;
    int left = middle-1;
    int right =middle+1;
    //there are 7 columns in this airplane
    for(int j = 0 ; j<7 ; j++) {
        passenger[j].sit_num[0] = char(65+j);
        passenger[j].sit_num[1] = char(middle/10 + 48);
        passenger[j].sit_num[2] = char(middle%10 + 48);
        passenger[j].sit_num[3] = '\0';
    }
    for( int i =7; i < num_pass ;i+=14) {
        for(int j = 0 ; j<7 ; j++) {
            if(i+j >= num_pass) {
                break;
            }
            passenger[i+j].sit_num[0] = char(65+j);
            passenger[i+j].sit_num[1] = char(right/10 + 48);
            passenger[i+j].sit_num[2] = char(right%10 + 48);
            passenger[i+j].sit_num[3] = '\0';
        }
        if(i+7 >= num_pass) {
            break;
        }
        for(int j = 0 ; j<7 ; j++) {
            if(i+j >= num_pass) {
                break;
            }
            passenger[i+j+7].sit_num[0] = char(65+j);
            passenger[i+j+7].sit_num[1] = char(left/10 + 48);
            passenger[i+j+7].sit_num[2] = char(left%10 + 48);
            passenger[i+j+7].sit_num[3] = '\0';
        }
        right++;
        left--;
    }
}
int restricted_over_weight_limit(passengers_info passenger [] , int num_pass,passengers_info restricted_pass[],int& num_ress) {
    int weight ;
    int count = 0;
    for(int i =0 ; i<num_pass;i++) {
        //weight limit is 55kg
        weight = str_2_int(passenger[i].bag_weight);
        if (weight>55) {
            shift_left_passenger(passenger,i,num_pass);
            restricted_pass[count].bag_weight=passenger[i].bag_weight;
            restricted_pass[count].id_num=passenger[i].id_num;
            restricted_pass[count].name=passenger[i].name;
            restricted_pass[count].sit_num[0]='N';
            restricted_pass[count].sit_num[1]='A';
            restricted_pass[count].sit_num[2]='N';
            restricted_pass[count].sit_num[3]='\0';
            num_pass--;
            count++;
        }
    }
    num_ress = count;
    return num_pass;
}
void int_2_char(int count,char* count_char) {
    int i =0;
    while(count >0) {
        count_char [i]= (const char)(count%10 +48);
        count/=10;
        i++;
    }
    for(;i<5;i++) {
        count_char[i] = '\0';
    }
}
void shift_left_passenger(passengers_info passenger[],int shift_from_here,int num_pass) {
    for (int i= shift_from_here ; i<num_pass;i++) {
        passenger[i].bag_weight=passenger[i+1].bag_weight;
        passenger[i].id_num=passenger[i+1].id_num;
        passenger[i].name=passenger[i+1].name;
        passenger[i].sit_num[0]=passenger[i+1].sit_num[0];
        passenger[i].sit_num[1]=passenger[i+1].sit_num[1];
        passenger[i].sit_num[2]=passenger[i+1].sit_num[2];
    }
}
int str_2_int(const char* str) {
    int result = 0;
    for (int i= 0;i<101;i++) {
        if(str[i]=='\0') {
          break;
        }
        result = result *10 + (str[i]-48);
    }
    return result;
}
int str_2_struct_pass(passengers_info passenger[] ,char *array[],int size_array ) {
    int counter =0;
    for(int i =0;i<size_array;i+= 3) {
        passenger[counter].name = array[i];
        passenger[counter].id_num = array[i+1];
        passenger[counter].bag_weight = array[i+2];
        counter++;
    }
    return counter;
}
int flights_between_1_3_hours(flights_departure flights[],char time[50],flights_departure flights_b13h[20]) {
    int count = 0;
    const int real_time = str_time_2_int_time(time);
    int flight_time = 0;
    int last_i=0;
    for(int i =0; i < num_flights ; i++) {
        flight_time = const_str_time_2_int_time(flights[i].take_of);
        if((flight_time - real_time >=60 ) && (flight_time - real_time<=180)) {
            flights_b13h[count].take_of = flights[i].take_of;
            flights_b13h[count].date = flights[i].date;
            flights_b13h[count].destination = flights[i].destination;
            flights_b13h[count].flight_time_lenght = flights[i].flight_time_lenght;
            flights_b13h[count].fly_num = flights[i].fly_num;
            flights_b13h[count].origin = flights[i].origin;
            count++;
            last_i=i;
            }
        }
    return count;

}
//question 1:

int main_flights_arrival_2_near_flights(flights_arrival flights [], char time_str [50]) {
    {
        FILE *f = NULL;
        f = fopen("./flights_arrival.txt", "r");
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
                    sv_buf[words][i+1] = '\0';
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
        num_flights = str_2_struct2(flights,sv_buf,nums_words_cut);
        near_flight near_flights[20];
        int num_near_flights_arrival = list_near_flights_depature2(flights,near_flights,num_flights,time_str);
        struct_2_file_and_print2(near_flights,num_near_flights_arrival);
        return 0;
    }
}
int main_flights_depature_2_near_flights(flights_departure flights [100], char time_str [50]) {
    FILE *f = NULL;
    f = fopen("./flights_depature.txt", "r");
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
                sv_buf[words][i+1] = '\0';
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
    num_flights = str_2_struct(flights,sv_buf,nums_words_cut);
    near_flight near_flights[20];
    int num_near_flights_depature = list_near_flights_depature(flights,near_flights,num_flights,time_str);
    struct_2_file_and_print(near_flights,num_near_flights_depature);
    return 0;
}
int struct_2_file_and_print(near_flight near_flights [], int num_near_flights) {
    FILE *f = NULL;
    f = fopen("near_flights_depature.txt", "w");
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
int struct_2_file_and_print2(near_flight near_flights [], int num_near_flights) {
    FILE *f = NULL;
    f = fopen("near_flights_arrival.txt", "w");
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
    int flight_time ;
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
int list_near_flights_depature2(flights_arrival flights [],near_flight near_flights[],int num_flights,char time[]) {
    int count = 0;
    const int real_time = str_time_2_int_time(time);
    int flight_time ;
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
                flights[counter].flight_time_lenght = "\0";
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
                flights[counter].flight_time_lenght = "\0";
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
                flights[counter].flight_time_lenght = "\0";
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
                flights[counter].flight_time_lenght = "\0";
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
                flights[counter].flight_time_lenght = "\0";
                counter++;
                i+=10;
            }

        }
    }
    return counter;
}
int str_2_struct2(flights_arrival flights[],char array[][101],int size_array) {
    int counter =0;
    for(int i =0;i<size_array;i++) {
        if(strcmp(array[i],"Time")==0) {
            //if there is just on time or plane is waiting for someone
            if(strcmp(array[i+7],"Time")==0||strcmp(array[i+6],"Delayed")==0) {
                flights[counter].destination = "Tehran";
                flights[counter].fly_num = array[i+1];
                flights[counter].origin = array[i+2];
                flights[counter].date = array[i+3];
                flights[counter].take_of = array[i+5];
                flights[counter].flight_time_lenght = "\0";
                counter++;
                i+=5;
            }
            //if the time of the flight is less than hour to take off
            else if(strcmp(array[i+9],"Time")==0||strcmp(array[i+8],"Delayed")==0) {
                flights[counter].destination = "Tehran";
                flights[counter].fly_num = array[i+3];
                flights[counter].origin = array[i+4];
                flights[counter].date = array[i+5];
                flights[counter].take_of = array[i+7];
                flights[counter].flight_time_lenght = "\0";
                counter++;
                i+=7;
            }
            //if the time of the fllight is more than or is a hour to take off
            else if(strcmp(array[i+12],"Time")==0||strcmp(array[i+11],"Delayed")==0) {
                flights[counter].destination = "Tehran";
                flights[counter].fly_num = array[i+6];
                flights[counter].origin = array[i+7];
                flights[counter].date = array[i+8];
                flights[counter].take_of = array[i+10];
                flights[counter].flight_time_lenght = "\0";
                counter++;
                i+=10;
            }
            //if the name has two parts
            else if(strcmp(array[i+13],"Time")==0||strcmp(array[i+12],"Delayed")==0) {
                flights[counter].destination = "Tehran";
                flights[counter].fly_num = array[i+6];
                flights[counter].origin = strcat(array[i+7],array[i+8]);
                flights[counter].date = array[i+9];
                flights[counter].take_of = array[i+11];
                flights[counter].flight_time_lenght = "\0";
                counter++;
                i+=10;
            }
            //if the name has three parts
            else if(strcmp(array[i+14],"Time")==0||strcmp(array[i+13],"Delayed")==0) {
                flights[counter].destination = "Tehran";
                flights[counter].fly_num = array[i+7];
                flights[counter].origin = strcat(array[i+8],array[i+9]);
                flights[counter].date = array[i+10];
                flights[counter].take_of = array[i+12];
                flights[counter].flight_time_lenght = "\0";
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
                array[i][j] = '\0';
                array[i+1][j] = '\0';
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
                array[i][j] = '\0';
            }

        }
    }
}
void print_array(char *array[900], int size_array) {
    for (int i = 0;i < size_array;i++) {
        for( int j = 0;j<101;j++) {
            printf("%c",array[i][j]);
        }
        cout<<endl;
    }
}