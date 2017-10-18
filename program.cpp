#include "harnus.h"


#include <thread> 
#include <sqlite3.h>  
#include <chrono>     
 



void user_input(char &input)
{
    while(true)
    {
        std::cin>>input;
        std::this_thread::sleep_for (std::chrono::seconds(1));
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

void print_project_menu(table projects)
{
    clear_terminal();
    move_cursor_to(0,0);
    write_line("CHOOSE PROJECT:");
    write("\n");
    for(int i = projects.rows.size(); i > 0; i--)
    {
        write(1 + ": ");
        write(projects.rows[i].entries[1]);
        write("\n");
    }
    write("\n");
    write_line("*: ADD PROJECT");
    write_line("0: BACK");
    refresh_terminal();
}

bool choose_project(char &input, table projects)
{
    print_project_menu(projects);
    switch(input)
    {
        case '*':
            add_project();
            input = '\0';
            return true;
        case '0':
            return false;
        case '1':
            return false;
        case '2':
            return false;
        case '3':
            return false;
        case '4':
            return false;
        case '5':
            return false;
        case '-':
            return false;
        case '+':
            return false;
        default:
            return false;
    }
}

void choose_subject(char &input)
{

}

void print_menu()
{
    move_cursor_to(0,0);
    write_line("1: START TIMER");
    write_line("2: CHANGE PROJECT");
    write_line("3: CHANGE SUBJECT");
    write_line("4: DISPLAY ENTRIES");
    write_line("0: QUIT");
    refresh_terminal();
}

bool menu_action(char &input, current_subject &subject)
{

    bool back;
    table projects;
    print_menu();
    switch(input)
    {
        case '1':
            clear_terminal(); 
            new_timer(input, subject);
            return false;
        case '2':
            input = '\0';
            projects = get_projects();
            while (back == false)
            {
                back = choose_project(input, projects);
            }
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

    char input;
    input = '\0';

    setup_terminal();
    thread check_input(user_input, std::ref(input));
    check_input.detach();

    print_menu();
    while(quit == false)
    {
        quit = menu_action(input, subject);
    }

    write(input);
    end_advanced_terminal();

    return 0;
}
