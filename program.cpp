#include "splashkit.h"
#include "harnus.h"

#include <iostream>
#include <vector>
#include <math.h> 
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



void choose_project()
{

}

void choose_subject()
{

}

void print_menu()
{
    move_cursor_to(0,0);
    write_line("1: START TIMER");
    write_line("2: QUIT");
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
