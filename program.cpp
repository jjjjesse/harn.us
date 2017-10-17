#include "harnus.h"


#include <thread> 
#include <sqlite3.h>  
#include <chrono>     
 
using namespace std;


void user_input(char &input)
{
    while(true)
    {
        std::cin>>input;
    }   
}

void add_project()
{
    
}

void add_subject()
{

}

void choose_project()
{
    move_cursor_to(0,0);
    write_line("CHOOSE PROJECT:");
    write_line("0: ADD PROJECT");
    refresh_terminal();
}

void choose_subject()
{
    move_cursor_to(0,0);
    write_line("CHOOSE SUBJECT:");
    // Print  
    write_line("0: ADD SUBJECT");
    refresh_terminal();
}

void print_menu()
{
    move_cursor_to(0,0);
    write_line("1: START TIMER");
    write_line("2: CHANGE PROJECT");
    write_line("3: CHANGE SUBJECT");
    write_line("4: DISPLAY ENTRIES");
    write_line("5: QUIT");
    refresh_terminal();
}

bool menu_action(char &input)
{
    switch(input)
    {
        case '1':
            clear_terminal(); 
            new_timer(input);
            return false;
        case '2':
            choose_project();
            return false;
        case '3':
            return false;
        case '4':
            return false;
        case '5':
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
        print_menu();
        quit = menu_action(input);
    }

    write(input);
    end_advanced_terminal();

    return 0;
}
