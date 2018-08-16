#include "controller.h"


//#include "view.h"
//#include "model.h"
using namespace std;
void controller::signUp(){
            v.dangki();
            m.open();
            if(m.checkUser(v.username)>0){
                cout<<"username da co trong he thong, dang ki that bai"<<endl;
            }
            else {
                m.insertData(v.username,v.password,v.city);
            }
}
void controller::test(){
    m.open();
    int id = m.checkFriend(7,1);
    cout<<id;
}
void controller::addFriend(){
    v.addFriend();
    m.open();
    int id = m.checkUser(v.username);
    if(id>=1){
        int id3= m.checkFriend(id1,id);
        /*if(id3 == 1){
            cout<<"username da co trong list friend"<<endl;
        }*/
        if(id3 == 0){
            cout<<"khong the them username nay vao list friend"<<endl;
        }
        else if(id3 == 1){
            cout<<"username da co trong list friend"<<endl;
        }
        else if(id3 = -1){

            m.addFriend(id1,id);
        }

    }
    else {
        cout<<"username khong ton tai trong he thong"<<endl;

    }

}
void controller::showFriend(){
   // v.listFriend();
    m.open();
    m.showFriendAndId(id1);
}
void controller::block(){
    v.block();
    m.open();
    int id = m.checkUser(v.username);
    if(id>0){
        id2 = id;
        m.block(id1,id2);
    }
    else{
        cout<<"username khong ton tai"<<endl;
    }


}
void controller::sendMess(){
    string s;
    v.sendMess();
    m.open();
    int id = m.checkUser(v.username);
    if(id>0){
        if(m.checkFriend(id1,id)==0){
            cout<<"khong the nhan tin cho username nay"<<endl;

        }
        else{
            cout<<"soan tin: ";
            getline(cin,s);
            getline(cin,s);
            v.mess = new char[s.length() + 1];
            strcpy(v.mess, s.c_str());
            m.sendMess(id1,id,v.mess);
        }
    }
    else{
        cout<<"username khong ton tai"<<endl;
    }
}
void controller::sentMess(){
    m.open();
    cout<<"====== gan day ======"<<endl;
    m.showNguoiNhan(id1);
    cout<<"======"<<endl;
    v.sentMess();
    int id=m.checkUser(v.username);
    if(id>0){
        if(m.checkFriend(id1,id)==0){
            cout<<"khong the hien thi tin nhan"<<endl;
        }
        else{
            m.showMessSent(id1,id);
        }
    }
    else{
        cout<<"username khong ton tai"<<endl;
    }
}
void controller::inbox(){
    m.open();
    cout<<"====== gan day ======"<<endl;
    m.showNguoiGui(id1);
    cout<<"======"<<endl;
    v.inbox();
    int id = m.checkUser(v.username);
    if(id>0){
        if(m.checkFriend(id1,id)==0){
            cout<<"khong the hien thi tin nhan"<<endl;
        }
        else{
            m.showMessInbox(id1,id);
        }
    }
    else{
        cout<<"username khong ton tai"<<endl;
    }
}
int controller::login(){
                v.dangnhap();
                m.open();
                int id = m.checkLogin(v.username,v.password);
                if(id>0){
                    cout<<"====== dang nhap thanh cong ======"<<endl;

                    id1 = id;
                    while(1){
                                            v.menu2();
                   cout<<"======"<<endl;
                    nhaplai:cout<<"nhap lua chon: ";
                    int luachon;
                    cin>>luachon;
                    if(luachon<0 || luachon>7){
                        cout<<"lua chon khong hop le, vui long chon lai"<<endl;
                        goto nhaplai;
                    }
                    else{
                        switch(luachon){
                            case 1: addFriend();
                                break;
                            case 2: showFriend();
                                break;
                            case 3: block();
                                break;
                            case 4: sendMess();
                                break;
                            case 5: sentMess();
                                break;
                            case 6: inbox();
                                break;
                            case 7: cout<<"dang xuat thanh cong"<<endl;
                                cout<<"======"<<endl;
                                controle();
                                break;



        }
    }
                    }

                }
                else{
                    cout<<"====== username hoac password khong dung ======"<<endl;
                }
}
void controller::controle()
{   //controller c;
    while(1){
        v.menu1();
        int luachon;
        nhaplai:cout<<"nhap lua chon: ";
        cin>>luachon;
        if(luachon<0 || luachon>3){
        v.nhaplai();
        goto nhaplai;
        }
        else{
        switch(luachon){
            case 1: signUp();

                break;
            case 2: login();

                break;
           case 3: exit(0);
                break;
        }
    }
    }
}

