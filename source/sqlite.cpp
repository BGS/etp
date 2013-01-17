#include "includes/database/sqlite.hpp"
#include "includes/database/exceptions.hpp"
#include "includes/defines.hpp"




database::ETPSqlDatabase::ETPSqlDatabase()
{

}
database::ETPSqlDatabase::~ETPSqlDatabase()
{

}
void database::ETPSqlDatabase::open( void )
{
    if (sqlite3_open(EPP_MAIN_DATABASE, &sqldb) != SQLITE_OK)
    {
        #if EPP_DEBUG
           cout << "!! Error opening database: " << EPP_MAIN_DATABASE << endl;
        #endif
        return;

    }

}


void database::ETPSqlDatabase::close()
{
    sqlite3_close(sqldb);
}
