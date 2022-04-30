#include "globals.h"
#include <string>
#include "DB_accounts.h"

std::string globals::filenameAccounts = "accounts.txt";
DB_accounts globals::db_accounts(filenameAccounts);