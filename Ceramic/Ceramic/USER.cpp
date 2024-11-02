#include "USER.h"
#include <sstream>

USER::USER()
{
}

USER::USER(unit32 username, const std::string name, unit32 password)
        :username(username),name(name),password(password)          //初始化参数列表
{

}

std::string USER::formatInfo()
{
    std::stringstream ss;
    ss<< username <<"\t" << name << "\t" << password<<std::endl;
    return ss.str();
}

USER USER::fromString(const std::string& str)
{
    USER use;
    std::stringstream ss;
    ss >> use.username >> use.name >> use.password;

    return use;
}
