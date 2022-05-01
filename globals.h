#pragma once

#include <string>
#include "DB_accounts.h"
#include "DB_students.h"

namespace globals {

    extern std::string filenameAccounts;
    extern std::string filenameStudents;
    extern DB_accounts db_accounts;
    extern DB_students db_students;
}