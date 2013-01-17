#include "includes/logger/logger.hpp"

using std::fstream;
using std::string;
using std::ios_base;

class debug{

    private:
        fstream logFile;

        time_t rawTime;
        struct tm *localTime;

    public:
        debug(string debugMessage){
            
            logFile.open(EPP_LOG_FILE, ios_base::app | ios_base::out);

            time(&rawTime);
            localTime=localtime(&rawTime);

            logFile<<asctime(localTime)<<debugMessage<<'\n';
            
        }

};

