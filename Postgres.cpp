#include "kamaz.h"

bool PostgreSQLTest::OpenDB()
{
    if(!m_session.Open("host=172.16.49.171 dbname=puma user=comis password=1234"))
    {
        //Exclamation(Format("Error in open: %s", DeQtf(m_session.GetLastError())));
        return false;
    }

#ifdef _DEBUG
	m_session.SetTrace();
#endif

	SQL = m_session;
	return true;
}
