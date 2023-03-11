#ifndef _MESSAGE_
#define _MESSAGE_

#include<cstring>
//结构体发送
enum class CMD {
	LOGIN,
	LOGOUT,
	LOGIN_RESULT,
	LOGOUT_RESULT,
	NO_CMD
};

struct Header {
	CMD cmd;
	unsigned dataLen;
	Header() :cmd(CMD::NO_CMD), dataLen(0) {}
	Header(CMD cmd_, unsigned dataLen_) :cmd(cmd_), dataLen(dataLen_) {}
};

struct Login :public Header {
	char userName[32]{};
	char passwd[32]{};
	Login() :Header(CMD::LOGIN, sizeof(Login)), userName{ 0 }, passwd{ 0 } {};
	Login(const char* userName_, const char* passwd_) :Header(CMD::LOGIN, sizeof(Login)) {
		strcpy_s(userName, 32, userName_);
		strcpy_s(passwd, 32, passwd_);
	}
};

struct Logout :public Header {
	unsigned logoutNum;
	Logout() :Header(CMD::LOGOUT, sizeof(Logout)), logoutNum(0) {};
	Logout(unsigned logoutNum_) :Header(CMD::LOGOUT, sizeof(Logout)), logoutNum(logoutNum_) {};
};

struct LoginResult :public Header {
	unsigned loginResultNum;
	LoginResult() :Header(CMD::LOGIN_RESULT, sizeof(LoginResult)), loginResultNum(0) {};
	LoginResult(unsigned loginResultNum_) :Header(CMD::LOGIN_RESULT, sizeof(LoginResult)), loginResultNum(loginResultNum_) {};
};

struct LogoutResult :public Header {
	unsigned logoutResultNum;
	LogoutResult() :Header(CMD::LOGOUT_RESULT, sizeof(LogoutResult)), logoutResultNum(0) {};
	LogoutResult(unsigned logoutResultNum_) :Header(CMD::LOGOUT_RESULT, sizeof(LogoutResult)), logoutResultNum(logoutResultNum_) {};
};

#endif // !_MESSAGE_
