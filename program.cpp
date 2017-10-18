#include "harnus.h"


#include <thread> 
#include <sqlite3.h>  
#include <chrono>     
 



void user_input(key_input &input)
{   
    input.input_pause = false;
    while(true)
        while(!input.input_pause)
        {
            std::cin>>input.input_char;
        } 
}

void add_project()
{
    set_terminal_echo_input(true);
    clear_terminal();
    string name;
    move_cursor_to(0,0);
    write_line("ADDING PROJECT:");
    write_line("What is the project name?");
    move_cursor_to(0,5);
    write_line("Enter '0' and press ENTER to cancel");
    move_cursor_to(0,2);
    refresh_terminal();
    name = trim(read_line());
    if(name != "0")
    {
        add_project_sql(name);
    }
    set_terminal_echo_input(false);
}

void add_subject()
{
    set_terminal_echo_input(true);
    clear_terminal();
    string name;
    move_cursor_to(0,0);
    write_line("ADDING SUBJECT:");
    write_line("What is the subject name?");
    move_cursor_to(0,5);
    write_line("Enter '0' and press ENTER to cancel");
    move_cursor_to(0,2);
    refresh_terminal();
    name = trim(read_line());
    if(name != "0")
    {
        add_project_sql(name);
    }
    set_terminal_echo_input(false);
}

void print_project_menu(table &projects, current_subject &subject)
{
    clear_terminal();
    int no_rows;
    move_cursor_to(0,0);
    if(!subject.project.empty())
    {
        write_line("CURRENT PROJECT IS:" + subject.project);
    }
    write_line("CHOOSE PROJECT:");
    write("\n");
    int idx = projects.rows.size() - projects.offset - 1;
    int limit = idx - 5;
    if(idx < 5)
    {
        limit = 0;
    }

    for(int j = 1; idx > limit; idx--, j++)
    {
        write(to_string(j) + ": ");
        write(projects.rows[idx].entries[1]);
        write("\n");
    }

    write("\n");
    move_cursor_to(0,8);
    if(projects.rows.size() > 5)
    {
        write_line("-: PREVIOUS  |  +: NEXT");
    }
    write_line("*: ADD PROJECT");
    write_line("0: BACK");
    refresh_terminal();
}

void set_project(table projects, current_subject &subject, int idx)
{
    if(idx >= 0)
    {
        subject.project_id = convert_to_integer(projects.rows[idx].entries[0]);
        subject.project = projects.rows[idx].entries[1];
    }
}

bool choose_project(key_input &input, table &projects, current_subject &subject)
{
    print_project_menu(projects, subject);
    int i = projects.rows.size() - projects.offset ;
    switch(input.input_char)
    {
        case '*':
            input.input_pause = true;
            add_project();
            input.input_char = '\0';
            input.input_pause = false;
            return true;
        case '0':
            input.input_char = '\0';
            return true;
        case '1':
            set_project(projects, subject, i - 1);
            input.input_char = '\0';
            return false;
        case '2':
            set_project(projects, subject, i - 2);
            input.input_char = '\0';
            return false;
        case '3':
            set_project(projects, subject, i - 3);
            input.input_char = '\0';
            return false;
        case '4':
            set_project(projects, subject, i - 4);
            input.input_char = '\0';
            return false;
        case '5':
            set_project(projects, subject, i - 5);
            input.input_char = '\0';
            return false;
        case '-':
            projects.offset -= 5;
            if (projects.offset < 0)
            {
                projects.offset = 0;
            }
            input.input_char = '\0';
            return false;
        case '+':
            projects.offset += 5;
            if (projects.offset >= projects.rows.size())
            {
                projects.offset -= 5;
            }
            input.input_char = '\0';
            return false;
        default:
            return false;
    }
}

void choose_subject(key_input &input)
{

}

void print_menu()
{
    clear_terminal();
    move_cursor_to(0,0);
    write_line("1: START TIMER");
    write_line("2: CHANGE PROJECT");
    write_line("3: CHANGE SUBJECT");
    write_line("4: DISPLAY ENTRIES");
    write_line("0: QUIT");
    refresh_terminal();
}

bool menu_action(key_input &input, current_subject &subject)
{

    bool back;
    table projects;
    print_menu();
    switch(input.input_char)
    {
        case '1':
            clear_terminal(); 
            new_timer(input, subject);
            return false;
        case '2':
            input.input_char = '\0';
            projects = get_projects();
            while (back == false)
            {
                back = choose_project(input, projects, subject);
            }
            back = false;
            return false;
        case '3':
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
    current_subject subject;

    setup_tables();
    std::this_thread::sleep_for (std::chrono::seconds(5));

    key_input input;
    input.input_char = '\0';

    setup_terminal();
    thread check_input(user_input, std::ref(input));
    check_input.detach();

    print_menu();
    while(quit == false)
    {
        quit = menu_action(input, subject);
    }

    write(input.input_char);
    end_advanced_terminal();

    return 0;
}
