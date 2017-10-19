#include "harnus.h"


#include <thread> 
#include <sqlite3.h>  
#include <chrono>     
 
enum menu
{
    PROJECTS,
    SUBJECTS,
    ENTRIES
};


void user_input(key_input &input)
{   
    input.input_pause = false;
    while(true)
        while(!input.input_pause)
        {
            std::cin>>input.input_char;
        } 
}

void set_category(table projects, categories &currect_categories, int idx, menu &current_menu)
{
    if(idx >= 0)
    {   
        if(current_menu == PROJECTS)
        {
            currect_categories.project_id = convert_to_integer(projects.rows[idx].entries[0]);
            currect_categories.project = projects.rows[idx].entries[1];
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

void print_submenu(table &table_data, categories &currect_categories, menu &current_menu)
{
    clear_terminal();
    int no_rows;
    move_cursor_to(0,0);
    string category_type;
    if (current_menu == PROJECTS)
    {   
        category_type = "PROJECTS";
        if(!currect_categories.project.empty())
        {
            write_line("CURRENT PROJECT IS: " + currect_categories.project);
        }
        else
        {
            write_line("NO PROJECT SELECTED");
        }
    }
    else if (current_menu == SUBJECTS)
    {
        category_type = "SUBJECTS";
        if(!currect_categories.subject.empty())
        {
            write_line("CURRENT SUBJECT IS: " + currect_categories.subject);
        }
        else
        {
            write_line("NO SUBJECT SELECTED");
        }
    }
    else if (current_menu == ENTRIES)
    {
        category_type = "ENTRIES";   
    }
    write_line("CHOOSE " + category_type + ":");
    write("\n");
    print_categories(table_data);
    move_cursor_to(0,9);
    if(table_data.rows.size() > 5)
    {
        write_line("-: PREVIOUS       +: NEXT");
    }
    write_line("*: ADD " + category_type);
    write_line("0: BACK");

    refresh_terminal();
    write(table_data.rows[0].entries[1]);
}

bool submenu_action(key_input &input, table &table_data, categories &currect_categories, menu &current_menu)
{
    print_submenu(table_data, currect_categories, current_menu);
    int i = table_data.rows.size() - table_data.offset ;
    switch(input.input_char)
    {
        case '*':
            input.input_pause = true;
            add_category(current_menu, currect_categories);
            input.input_char = '\0';
            input.input_pause = false;
            return false;
        case '0':
            input.input_char = '\0';
            return true;
        case '1':
            set_category(table_data, currect_categories, i - 1, current_menu);
            input.input_char = '\0';
            return true;
        case '2':
            set_category(table_data, currect_categories, i - 2, current_menu);
            input.input_char = '\0';
            return true;
        case '3':
            set_category(table_data, currect_categories, i - 3, current_menu);
            input.input_char = '\0';
            return true;
        case '4':
            set_category(table_data, currect_categories, i - 4, current_menu);
            input.input_char = '\0';
            return true;
        case '5':
            set_category(table_data, currect_categories, i - 5, current_menu);
            input.input_char = '\0';
            return true;
        case '-':
            table_data.offset -= 5;
            if (table_data.offset < 0)
            {
                table_data.offset = 0;
            }
            input.input_char = '\0';
            return false;
        case '+':
            table_data.offset += 5;
            if (table_data.offset > table_data.rows.size() -1)
            {
                table_data.offset -= 5;
            }
            input.input_char = '\0';
            return false;
        default:
            return false;
    }
}


void print_menu(categories &currect_categories)
{
    clear_terminal();
    if(!currect_categories.project.empty())
    {
        write_line("CURRENT PROJECT IS: " + currect_categories.project);
    }
    else
    {
        write_line("NO PROJECT SELECTED");
    }
    if(!currect_categories.subject.empty())
    {
        write_line("CURRENT SUBJECT IS: " + currect_categories.subject);
    }
    else
    {
        write_line("NO SUBJECT SELECTED");
    }
    move_cursor_to(0,3);
    write_line("1: START TIMER");
    write_line("2: CHOOSE PROJECT");
    write_line("3: CHOOSE SUBJECT");
    write_line("4: DISPLAY ENTRIES");
    write_line("0: QUIT");
    refresh_terminal();
}

bool menu_action(key_input &input, categories &currect_categories)
{
    menu current_menu;
    bool back;
    table table_data;
    print_menu(currect_categories);
    switch(input.input_char)
    {
        case '1':
            clear_terminal(); 
            if(!currect_categories.subject.empty())
            {
                new_timer(input, currect_categories);
            }
            else
            {
                move_cursor_to(0,0);
                input.input_char = '\0';
                while(input.input_char != '1')
                {
                    clear_terminal();
                    write_line("PLEASE CHOOSE PROJECT FIRST");
                    move_cursor_to(0,3);
                    write_line("1: CONTINUE");
                    refresh_terminal();
                }
                input.input_char = '\0';
            }
            return false;
        case '2':
            input.input_char = '\0';
            table_data = get_projects();
            back = false;
            while (back == false)
            {
                current_menu = PROJECTS;
                back = submenu_action(input, table_data, currect_categories, current_menu);
            }
            back = false;
            return false;
        case '3':
            if(currect_categories.project_id)
            {
                input.input_char = '\0';
                table_data = get_subjects(currect_categories);
                back = false;
                while (back == false)
                {
                    current_menu = SUBJECTS;
                    back = submenu_action(input, table_data, currect_categories, current_menu);
                }
            }
            else
            {
                 while(input.input_char != '1')
                {
                    clear_terminal();
                    write_line("PLEASE CHOOSE PROJECT FIRST");
                    move_cursor_to(0,3);
                    write_line("1: CONTINUE");
                    refresh_terminal();
                }
                input.input_char = '\0';
            }
            
            return false;
        case '4':
            return false;
        case '0':
            return true;
        default:
            return false;
    }
}


void setup_terminal()
{
    activate_advanced_terminal();
    set_terminal_colors(color_yellow(), color_dark_blue());
    set_terminal_echo_input(false);
    clear_terminal(); 
}

int main()
{
    bool quit = false;
    categories currect_categories;

    setup_tables();

    key_input input;
    input.input_char = '\0';

    setup_terminal();
    thread check_input(user_input, std::ref(input));
    check_input.detach();

    while(quit == false)
    {
        quit = menu_action(input, currect_categories);
    }

    write(input.input_char);
    end_advanced_terminal();

    return 0;
}
