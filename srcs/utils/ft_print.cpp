#include "utils.hpp"

void ft_print_logo(void) {
    ft_print_message("  /$$$$$$   /$$          /$$", CYAN);
    ft_print_message(" /$$__  $$ | $$         |__/", CYAN);
    ft_print_message("| $$  \\__//$$$$$$        /$$  /$$$$$$   /$$$$$$$", CYAN);
    ft_print_message("| $$$$   |_  $$_/       | $$ /$$__  $$ /$$_____/", CYAN);
    ft_print_message("| $$_/     | $$         | $$| $$  \\__/| $$      ", CYAN);
    ft_print_message("| $$       | $$ /$$     | $$| $$      | $$      ", CYAN);
    ft_print_message("| $$       |  $$$$/     | $$| $$      |  $$$$$$$", CYAN);
    ft_print_message("|__/        \\___//$$$$$$|__/|__/       \\_______/", CYAN);
    ft_print_message("                |______/\n", CYAN);
    ft_print_message("   === By tkaragoz, fli & mel-habi • v1.0 ===", PURPLE);
    std::cout << std::endl;    
};

void ft_print_message(std::string msg, std::string color) {
    std::cout << BOLD << color << msg << END_COLOR << '\n';
};

void ft_print_success(std::string success) {
    ft_print_message("[SUCCESS]: " + success, GREEN);
};

void ft_print_info(std::string info) {
    ft_print_message("[INFO]: " + info, CYAN);
};

void ft_print_warning(std::string warning) {
    ft_print_message("[WARNING]: " + warning, YELLOW);
};

void ft_print_error(std::string error) {
    ft_print_message("[ERROR]: " + error, RED);
};
