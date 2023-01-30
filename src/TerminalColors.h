//
// Created by nullbyte on 1/29/23.
//

#ifndef PROXYCACHE_TERMINALCOLORS_H
#define PROXYCACHE_TERMINALCOLORS_H


#ifdef __unix

    // Terminal colors
    #define TERMINAL_RESET cout<<"\033[0m"
    #define TERMINAL_BLACK cout<<"\033[30m"        /* Black */
    #define TERMINAL_BLACK_BOLD cout<<"\033[1;30m" /* Bold Black */
    #define TERMINAL_RED cout<<"\033[31m"          /* Red */
    #define TERMINAL_RED_BOLD cout<<"\033[1;31m"   /* Bold Red */
    #define TERMINAL_GREEN cout<<"\033[32m"        /* Green */
    #define TERMINAL_GREEN_BOLD cout<<"\033[1;32m" /* Bold Green */
    #define TERMINAL_YELLOW cout<<"\033[33m"       /* Yellow */
    #define TERMINAL_YELLOW_BOLD cout<<"\033[1;33m" /* Bold Yellow */
    #define TERMINAL_BLUE cout<<"\033[34m"         /* Blue */
    #define TERMINAL_BLUE_BOLD cout<<"\033[1;34m"  /* Bold Blue */
    #define TERMINAL_MAGENTA cout<<"\033[35m"      /* Magenta */
    #define TERMINAL_MAGENTA_BOLD cout<<"\033[1;35m" /* Bold Magenta */
    #define TERMINAL_CYAN cout<<"\033[36m"         /* Cyan */
    #define TERMINAL_CYAN_BOLD cout<<"\033[1;36m"  /* Bold Cyan */
    #define TERMINAL_WHITE cout<<"\033[37m"        /* White */
    #define TERMINAL_WHITE_BOLD cout<<"\033[1;37m" /* Bold White */

#endif // __unix

#ifdef _WIN32

    // Console colors
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #define TERMINAL_RESET SetConsoleTextAttribute(hConsole, 7)
    #define TERMINAL_BLACK SetConsoleTextAttribute(hConsole, 0)
    #define TERMINAL_BLACK_BOLD SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY)
    #define TERMINAL_RED SetConsoleTextAttribute(hConsole, 4)
    #define TERMINAL_RED_BOLD SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY)
    #define TERMINAL_GREEN SetConsoleTextAttribute(hConsole, 2)
    #define TERMINAL_GREEN_BOLD SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY)
    #define TERMINAL_YELLOW SetConsoleTextAttribute(hConsole, 6)
    #define TERMINAL_YELLOW_BOLD SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
    #define TERMINAL_BLUE SetConsoleTextAttribute(hConsole, 1)
    #define TERMINAL_BLUE_BOLD SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY)
    #define TERMINAL_MAGENTA SetConsoleTextAttribute(hConsole, 5)
    #define TERMINAL_MAGENTA_BOLD SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY)
    #define TERMINAL_CYAN SetConsoleTextAttribute(hConsole, 3)
    #define TERMINAL_CYAN_BOLD SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
    #define TERMINAL_WHITE SetConsoleTextAttribute(hConsole, 7)
    #define TERMINAL_WHITE_BOLD SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)


#endif // _WIN32

#endif //PROXYCACHE_TERMINALCOLORS_H
