#include "harnus.h"


#include <thread> 
#include <sqlite3.h>  
#include <chrono>     
 



void user_input(char &input)
{
    while(true)
    {
        std::cin>>input;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
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

}

void print_project_menu(vector<vector<string>> projects)
{
    move_cursor_to(0,0);
    write_line("CHOOSE PROJECT:");
    for(int i = 0; i < projects.size(); i++)
    {
        for(int j = 0; j < projects[i].size(); j++)
        {
            write(projects[i][j] + " ");
        }
        write("\n");
    }
    write_line("*: ADD PROJECT");
    write_line("0: BACK");
    refresh_terminal();
}

bool choose_project(char &input, vector<vector<string>> projects)
{
    print_project_menu(projects);
    switch(input)
    {
        case '*':
            add_project();
            input = '\0';
            return false;
        default:
            return false;
    }
}

void choose_subject(char &input)
{
    move_cursor_to(0,0);
    write_line("CHOOSE SUBJECT:");
   
    write_line("*: ADD SUBJECT");
    refresh_terminal();
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

bool menu_action(char &input)
{
    bool back;
    vector<vector<string>> projects;
    print_menu();
    switch(input)
    {
        case '1':
            clear_terminal(); 
            new_timer(input);
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
        quit = menu_action(input);
    }

    write(input);
    end_advanced_terminal();

    return 0;
}
