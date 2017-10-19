#include "splashkit.h"

#include <ctime>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

using namespace std;

struct time_record
{
    time_t start_time;
    time_t end_time;
    int seconds;
    int minutes;
    int hours;
};

struct categories
{
    int project_id;
    string project;
    int subject_id;
    string subject;

};

struct row
{
    vector<string> entries;
};

struct table
{
    vector<row> rows;
    int offset;
};

struct key_input
{
    char input_char;
    bool input_pause;
};


//FROM TIMER.CPP
time_t get_current_time();
void seconds_to_hours(double seconds, time_record &timer);
void display_timer(time_record timer);
void ticker(time_record timer);
void print_time(time_t current_time);
void new_timer(key_input &input,categories &current_categories);

//FROM DATABASE.CPP
sqlite3* connect_database();
void create_table(char *sql);
void setup_tables();
table select_data(const char *sql);
table get_projects();
void add_project_sql(string project_name);
void add_subject_sql(string subject_name);
void add_time_record(time_record record, categories &current_categories);