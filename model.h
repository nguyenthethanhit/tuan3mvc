#include<iostream>
#include<sqlite3.h>
#include<string>
#include<string.h>
#include<stdlib.h>
using namespace std;
class model
{
    public:
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        const char *sql;
        const char *tailSql;
        sqlite3_stmt *stmt;

        friend class controller;
        void open();
        int checkUser(char *user);
        int insertData(char *user, char *pass,char *city);
        int checkLogin(char *user, char *pass);
        int checkFriend(int id1,int id2);
        int checkBlock(int id1, int id2);
        void addFriend(int id1,int id2);
        void showFriend(int id1);
        void block(int id1,int id2);
        void sendMess(int id1,int id2,char *mess);
        void showFriendAndId(int id1);
        void showMessSent(int id1,int id2);
        void inbox(int id1,int id2);
        void showNguoiNhan(int id1);
        void showNguoiGui(int id1);
        void showMessInbox(int id1,int id2);




    protected:

    private:
};
