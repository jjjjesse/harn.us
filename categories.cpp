#include "harnus.h"

void set_category(table projects, categories &currect_categories, int idx, menu &current_menu)
{
    if(idx >= 0)
    {   
        if(current_menu == PROJECTS)
        {
            currect_categories.project_id = convert_to_integer(projects.rows[idx].entries[0]);
            currect_categories.project = projects.rows[idx].entries[1];
            currect_categories.subject_id = 0;
            currect_categories.subject = '\0';
        }
        else if (current_menu == SUBJECTS)
        {
            currect_categories.subject_id = convert_to_integer(projects.rows[idx].entries[0]);
            currect_categories.subject = projects.rows[idx].entries[1];
        }
    }
}


void add_category(menu &current_menu, categories &currect_categories)
{
    set_terminal_echo_input(true);
    clear_terminal();
    string name;
    string category_type;
    if (current_menu == PROJECTS)
    {
        category_type = "project";
    }
    else if (current_menu == SUBJECTS)
    {
        category_type = "subject";
    }
    move_cursor_to(0,0);
    write_line("ADDING " + to_uppercase(category_type) + ":");
    write_line("What is the " + category_type + " name?");
    move_cursor_to(0,5);
    write_line("Enter '0' and press ENTER to cancel");
    move_cursor_to(0,2);
    refresh_terminal();
    name = trim(read_line());
    if(name != "0")
    {
        if (current_menu == PROJECTS)
        {
            add_project_sql(name);
        }
        else if (current_menu == SUBJECTS)
        {
            add_subject_sql(name, currect_categories);
        }
    }
    set_terminal_echo_input(false);
}

void print_categories(table &table_data)
{
    int idx = table_data.rows.size() - table_data.offset - 1;
    int limit = idx - 5;
    if(idx < 5)
    {
        limit = -1;
    }

    for(int j = 1; idx > limit; idx--, j++)
    {
        write(to_string(j) + ": ");
        write(table_data.rows[idx].entries[1]);
        write("\n");
    }

    write("\n");
}

void print_timestamps(table &table_data)
{
    write_line("TIME RECORDS");
    move_cursor_to(0,3);
    int idx = table_data.rows.size() - table_data.offset - 1;
    int limit = idx - 5;
    if(idx < 5)
    {
        limit = -1;
    }
    for(int j = 1 + table_data.offset; idx > limit; idx--, j++)
    {
        write(to_string(j) + ": ");
        write("TIME: ");
        write(table_data.rows[idx].entries[0]);
        write("      ");
        write(table_data.rows[idx].entries[1]);
        write(" | ");
        write(table_data.rows[idx].entries[2]);

        write("\n");
    }

}