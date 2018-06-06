#ifndef _kamaz_Postgres_h
#define _kamaz_Postgres_h

using namespace Upp;

#include <PostgreSQL/PostgreSQL.h>

class PostgreSQLTest {
public:
    typedef PostgreSQLTest CLASSNAME;
    bool OpenDB();
protected:
    PostgreSQLSession m_session;
};


#endif
