#include <array>
#include <cstdlib>
#include <iostream>
#include "../include/shell.h"
#include <limits.h> 
#include <string>
#include <unistd.h>
// --------------------------------------------------------------------
// shell class implementation
// --------------------------------------------------------------------
#define SH shell


SH::shell()
{
    // set mode & mode map values
    m_shell_mode = MODE::INTERACTIVE;
    mode_map = {
        {MODE::INTERACTIVE, "[Interactive Mode]"}, 
        {MODE::SCRIPT, "[Script Mode]"}
    };

    // set the host name
    m_host = get_host();

    // set user name
    m_user = get_user();

    // get init cwd
    set_cwd();

}
SH::~shell() {}

// ---------------------------------------------------------
std::string SH::get_mode(){ return mode_map[this->m_shell_mode ]; };

std::string SH::get_host()
{
    std::array<char, 255> buf{};
    std::string hostname = "";

    if (gethostname(buf.data(), buf.size()) == 0) 
    {
        // set the hostname
        hostname = buf.data();
    } else 
    {
        perror("gethostname");
    }

    return hostname;
}

std::string SH::get_user(){ return "placeholder";}

void SH::set_cwd(std::string path)
{
    char buffer[PATH_MAX];

    // handle default cwd
    if (path.size() == 0)
    {
        if (getcwd(buffer, sizeof(buffer)) != nullptr){
            m_current_directory = new std::string(buffer);
        }else {
            perror("getcwd");
        }

    }else {
        // handle overwritten cwd
    
    }

}

// ---------------------------------------------------------
void SH::prompt_user()
{
    // print out the prompt
    std::cout << "Host:" << m_host << std::endl;
    std::cout << "User:" << m_user << std::endl;
    std::cout << "CWD:" << m_current_directory << std::endl;
    exit(0);
}

int SH::run()
{
    while (true)
    {
        try 
        {
            // continuosly show user the shell prompt
            prompt_user();
        } catch (...) 
        {
            std::cout << "SHELL INTERRUPT: Closing shell" << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    return 0;
}
