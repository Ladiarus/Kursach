#include "globals.h"
#include <string>
#include "DB_accounts.h"

namespace globals
{
    std::string filenameAccounts = "accounts.txt";
    std::string filenameStudents = "students.txt";
    DB_accounts db_accounts(filenameAccounts);
    DB_students db_students(filenameStudents);
}