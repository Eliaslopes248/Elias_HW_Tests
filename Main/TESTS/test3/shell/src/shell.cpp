#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "../include/shell.h"
#include <limits.h> 
#include <ostream>
#include <string>
#include <sys/_types/_pid_t.h>
#include <unistd.h>
#include <pwd.h>
#include <vector>


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
        // remove trailing ".local" in hostname
        std::string unproccessed_hostname = buf.data();
        // set the hostname
        hostname = unproccessed_hostname.substr(0, unproccessed_hostname.length() - 6);
        
    } else 
    {
        perror("gethostname");
    }

    return hostname;
}

std::string SH::get_user()
{ 
    try {
        struct passwd* pw = getpwuid(getuid());
        return pw ? pw->pw_name : "";
        // set value and return
    } catch (...) 
    {
        std::cout << "[ERROR] When getting username" << std::endl;
        return "placeholder";
    }
}

void SH::set_cwd(std::string path)
{
    // handle default cwd
    if (path.size() == 0)
    {
        char* buf = getcwd(nullptr, 0);
        std::string cwd(buf);
        m_current_directory =  buf;

    }else {
        // handle overwritten cwd
        m_current_directory =  path;
    }

}

// ---------------------------------------------------------
void SH::get_prompt(std::string* prompt)
{
    if (!prompt) { return; }
    // make sure values are set
    if (m_current_directory.length() == 0)  { set_cwd(); }
    if (m_host.length() == 0)               { get_host(); }
    if (m_user.length() == 0)               { get_user(); }
    // make sure shell mode is set
    if (m_shell_mode != MODE::INTERACTIVE && m_shell_mode != MODE::SCRIPT)
    { 
        m_shell_mode = MODE::INTERACTIVE; 
    }

    *prompt =  m_user + '@' + m_host + ":~" + m_current_directory + "$ ";
    
}

void SH::print_user(std::string* prompt)
{
    if (prompt == nullptr) { return; }
    // print out the prompt
    std::cout << "--------------------------------------"<< std::endl;
    std::cout << "ELIAS SHELL"<< std::endl;
    std::cout << "--------------------------------------"<< std::endl;
    get_prompt(prompt);
    // print out on same line
    std::cout << *prompt;

}

void SH::cleanup(){}

//------------------------------------------------------------------
std::vector<std::string> SH::command_split(std::string s, const char delimiter)
{
    size_t start=0;
    size_t end=s.find_first_of(delimiter);
    
    std::vector<std::string> output;
    
    while (end <= std::string::npos)
    {
	    output.emplace_back(s.substr(start, end-start));

	    if (end == std::string::npos)
	    	break;

    	start=end+1;
    	end = s.find_first_of(delimiter, start);
    }
    
    return output;
}

void SH::get_input(){
    try{
        // get standard input if in interactive mode
        if (m_shell_mode == MODE::INTERACTIVE)
        {
            std::string cmd;
            // get input line from terminal
            std::getline(std::cin, cmd);
            // split the shell cmds by spaces
            std::vector<std::string> cmds = command_split(cmd, ' ');
            exit(0);
        }else{
            // execute the scripts in the input file
        }
    }catch(...)
    {
        perror("get_input");
        return;
    }
}

int SH::run()
{
    // prompt string used in whole shell
    std::string* prompt = new std::string();
    while (true)
    {
        try 
        {
            // continuosly show user the shell prompt
            print_user(prompt);
            
            // get input and execute commands
            get_input();

            std::cout << '\n';

        } catch (...) 
        {
            std::cout << "SHELL INTERRUPT: Closing shell" << std::endl;
            exit(EXIT_FAILURE);
        }

    }
    // free memory
    delete prompt;
    cleanup();
    return 0;
}
