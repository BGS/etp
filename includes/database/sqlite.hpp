#ifndef _H_ETP_SQLITE_WRAPPER_INCLUDED__
#define _H_ETP_SQLITE_WRAPPER_INCLUDED__

#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>


namespace database
{



    using std::cout;
    using std::endl;

    using std::vector;
    using std::string;

    class ETPSqlDatabase
    {
    public:
        ETPSqlDatabase();
        virtual ~ETPSqlDatabase();
        void open(void);
        void close(void);

    private:
       sqlite3* sqldb;

    };
}


#endif
