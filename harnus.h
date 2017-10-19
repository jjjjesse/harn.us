#include "splashkit.h"

#include <ctime>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

using namespace std;

enum menu
{
    PROJECTS,
    SUBJECTS,
    ENTRIES
};

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

//FROM MENUS.CPP
void print_submenu(table &table_data, categories &currect_categories, menu &current_menu);
bool submenu_action(key_input &input, table &table_data, categories &currect_categories, menu &current_menu);
bool menu_action(key_input &input, categories &currect_categories);
void print_menu(categories &currect_categories);

//FROM TIMER.CPP
time_t get_current_time();
void seconds_to_hours(double seconds, time_record &timer);
void display_timer(time_record timer);
void ticker(time_record timer);
void print_time(time_t current_time);
void new_timer(key_input &input,categories &current_categories);

//FROM CATEGORIES.CPP
void set_category(table projects, categories &currect_categories, int idx, menu &current_menu);
void add_category(menu &current_menu, categories &currect_categories);
void print_categories(table &table_data);
void print_timestamps(table &table_data);

//FROM DATABASE.CPP
sqlite3* connect_database();
void create_table(char *sql);
void setup_tables();
table select_data(const char *sql);
table get_subjects(categories current_categories);
table get_projects();
table get_records();
void add_project_sql(string project_name);
void add_subject_sql(string subject_name, categories &currect_categories);
void add_time_record(time_record record, categories &current_categories);