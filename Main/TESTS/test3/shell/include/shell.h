#include <unistd.h>
#include <string>
#include <map>


/**
defines mode for shell:
    - interactive mode expects written out scripts
    - script mode expects a path to a file
*/
enum MODE{ INTERACTIVE, SCRIPT };


// ------------------------------------------------------------------------------------
class shell
{
private:
MODE            m_shell_mode           = MODE::INTERACTIVE;
std::map<MODE, std::string> mode_map;
std::string     m_host;
std::string     m_user;
std::string     m_current_directory;

// ------------------------------------------------------------------------------------
// gathering user info
std::string get_mode();
std::string get_host();
std::string get_user();
void        set_cwd(std::string path="");
// stdin methods
void get_prompt(std::string* prompt);
void get_input();
std::vector<std::string> command_split(std::string s, const char delimiter);

public:

shell();
~shell();

// ------------------------------------------------------------------------------------
int run();
void cleanup();
// ------------------------------------------------------------------------------------
void change_mode(const std::string mode); // change from interactive mode to script mode
void print_user(std::string* prompt);                       // displays the shell prompt
};

// ------------------------------------------------------------------------------------
// Commands will be placed into a TREE data structure ordered by command precedence
// ------------------------------------------------------------------------------------
struct command_node {
    std::string     data;
    command_node*   left;
    command_node*   right;
};

class command_tree {
public:
private:
};

