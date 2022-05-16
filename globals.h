#pragma once

#include <string>
#include "DB_accounts.h"
#include "DB_students.h"

namespace globals {

    extern std::string filenameAccounts;//имя файла аккаунтов
    extern std::string filenameStudents;//имя файла студентов
    extern DB_accounts db_accounts;//объект класса работы с аккаунтами
    extern DB_students db_students;//объект класса работы со студентами
}