#include<iostream>
#include "view.h"
#include "model.h"
#include<string>
#include<string.h>
#include<stdio.h>
using namespace std;
class controller
{
    public:
        int id1 ;
        int id2;
        view v;
        model m;
        void controle();
        int login();
        void signUp();
        void addFriend();
        void loginThanhCong();
        void showFriend();
        void block();
        void test();
        void sendMess();
        void sentMess();
        void inbox();  //virtual ~controller();

    protected:

    private:
};
