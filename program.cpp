#include "harnus.h"
#include <thread> 

 



void user_input(key_input &input)
{   
    input.input_pause = false;
    while(true)
        while(!input.input_pause)
        {
            std::cin>>input.input_char;
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
