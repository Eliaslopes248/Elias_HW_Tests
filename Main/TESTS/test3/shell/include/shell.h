#include <unistd.h>
#include <string>
#include <map>


/**
defines mode for shell:
    - interactive mode expects written out scripts
    - script mode expects a path to a file
*/
enum MODE{ INTERACTIVE, SCRIPT };


//--------------------------------------
class shell
{
private:
MODE            m_shell_mode           = MODE::INTERACTIVE;
std::map<MODE, std::string> mode_map;
std::string     m_host;
std::string     m_user;
std::string*    m_current_directory;


// --------------------------------------
std::string get_mode();
std::string get_host();
std::string get_user();
void set_cwd(std::string path="");

public:

shell();
~shell();

// ------------------------------------
int run();

// ------------------------------------
void change_mode(const std::string mode); // change from interactive mode to script mode
void prompt_user();                       // displays the shell prompt
};