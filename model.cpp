#include "model.h"
#include<iostream>
using namespace std;
void model::open()
{
     rc = sqlite3_open("chat.db", &db);
        if( rc ){

          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
          exit(0);
    }
}
int model::checkUser(char *user){
     int id=0;
        sql = "Select id from user where username = ?";
        rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
        if(rc == SQLITE_OK){
            sqlite3_bind_text(stmt,1,user,strlen(user),0);
            while(sqlite3_step(stmt)==SQLITE_ROW){
               id= sqlite3_column_int(stmt,0);
            }
        }
        return id;
}
int model::insertData(char *user, char *pass, char *city){
     sql = "insert into user (username,password,city) values (?,?,?)";
        int rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &tailSql);
        if( rc == SQLITE_OK ) {
            sqlite3_bind_text(stmt, 1, user, strlen(user), 0);
            sqlite3_bind_text(stmt, 2, pass, strlen(pass), 0);
            sqlite3_bind_text(stmt, 3, city, strlen(city), 0);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            cout<<"======dang ki thanh cong======"<<endl;
}
        else{
            cout<<"======dang ki that bai======"<<endl;
        }
}
int model::checkLogin(char *user, char *pass){
     int id=0;
        sql = "select id from user where username = ? and password = ?";
        rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
        if(rc == SQLITE_OK){
            sqlite3_bind_text(stmt,1,user,strlen(user),0);
            sqlite3_bind_text(stmt,2,pass,strlen(pass),0);
          while(sqlite3_step(stmt) == SQLITE_ROW){
                id = sqlite3_column_int(stmt, 0);
          }
          sqlite3_finalize(stmt);
          return id;

      }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);

        }
}
int model::checkFriend(int id1,int id2){
    int id=-1;
        sql = "select id from friend where ((id1 = ? and id2 = ?) or (id1 = ? and id2 = ?))";
        rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
        if(rc == SQLITE_OK){
            sqlite3_bind_int(stmt,1,id1);
            sqlite3_bind_int(stmt,2,id2);
            sqlite3_bind_int(stmt,3,id2);
            sqlite3_bind_int(stmt,4,id1);

            while(sqlite3_step(stmt)==SQLITE_ROW){
                id = sqlite3_column_int(stmt,0);
            }
        }
        sqlite3_finalize(stmt);
        return id;
}
int model::checkBlock(int id1, int id2){
        int id;
        sql = "select id from friend where (id1 = ? and id2 = ?) or (id1 = ? and id2 = ?)";
        rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
        if(rc == SQLITE_OK){
            sqlite3_bind_int(stmt,1,id1);
            sqlite3_bind_int(stmt,2,id2);
            sqlite3_bind_int(stmt,3,id2);
            sqlite3_bind_int(stmt,4,id1);

            while(sqlite3_step(stmt)==SQLITE_ROW){
                id = sqlite3_column_int(stmt,0);
            }
        }
        sqlite3_finalize(stmt);
        return id;
}
void model::addFriend(int id1,int id2){
            sql = "insert into friend(id,id1,id2) values(1,?,?)";
            rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
            if(rc==SQLITE_OK){
            sqlite3_bind_int(stmt,1,id1);
            sqlite3_bind_int(stmt,2,id2);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            cout<<"addfriend sucessfully"<<endl;
            cout<<"=============================="<<endl;

        }
        else{
            cout<<"that bai"<<endl;
        }
}
/*void model::showFriend(int id1){
    sql = "SELECT user2.username, friend.id2 FROM friend inner join user2 on ((friend.id =1 and friend.id1 = ?) or (friend.id =1 and friend.id2 = ? ))where friend.id2 = user2.id";
    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &tailSql);
    if( rc == SQLITE_OK ) {
        sqlite3_bind_int(stmt,1,id1);
        while(sqlite3_step(stmt) == SQLITE_ROW) {
           cout <</* string((const char *) sqlite3_column_text(stmt, 0) << endl;
        }
        sqlite3_finalize(stmt);

            cout <<"-------------------------------------\n";
    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
      }

}*/
void model::block(int id1,int id2){
    if(checkFriend(id1,id2)==1){
            sql = "update friend set id = 0 where (id1= ? and id2 = ?) or (id1= ? and id2=?)";
            rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
            if(rc == SQLITE_OK){
                sqlite3_bind_int(stmt,1,id1);
                sqlite3_bind_int(stmt,2,id2);
                sqlite3_bind_int(stmt,3,id2);
                sqlite3_bind_int(stmt,4,id1);
                sqlite3_step(stmt);
                sqlite3_finalize(stmt);
                cout<<"block sucessfully"<<endl;
                cout<<"==========================================="<<endl;
            }
        }
        else{
            sql = "insert into friend (id,id1,id2) values(0,?,?)";
            rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
            if(rc == SQLITE_OK){
            sqlite3_bind_int(stmt,1,id1);
            sqlite3_bind_int(stmt,2,id2);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            cout<<"block sucessfully"<<endl;
            cout<<"==========================================="<<endl;

        }
        }
}
void model::sendMess(int id1,int id2,char *mess){
       // char *y = new char[mess.length() + 1];
       // strcpy(y, mess.c_str());
        time_t hientai = time(0);
        char* t = ctime(&hientai);
        sql = "insert into mess(id1,id2,mess,time) values(?,?,?,?)";
        rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
        if(rc == SQLITE_OK){
            sqlite3_bind_int(stmt,1,id1);
            sqlite3_bind_int(stmt,2,id2);
            sqlite3_bind_text(stmt,3,mess,strlen(mess),0);
            sqlite3_bind_text(stmt,4,t,strlen(t),0);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            cout<<"gui tin nhan thanh cong"<<endl;
            cout<<"================================="<<endl;
        }
}
void model::showFriendAndId(int id1){
    cout<<"================================ List friend ===================================="<<endl;
        sql = "SELECT user.username, user.id FROM friend inner join user on (((friend.id =1 and friend.id1 = ?) and (friend.id2 = user.id)) or ((friend.id = 1 and friend.id2 = ?) and (friend.id1 = user.id)))";
        rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
        if(rc==SQLITE_OK){
            sqlite3_bind_int(stmt,1,id1);
            sqlite3_bind_int(stmt,2,id1);

            while(sqlite3_step(stmt)==SQLITE_ROW){
                cout<<sqlite3_column_int(stmt,1)<<"\t"<<sqlite3_column_text(stmt,0)<<endl;

            }
        }
        cout<<"===================================================================="<<endl;
         sqlite3_finalize(stmt);
}
void model::showNguoiNhan(int id1){
    sql = "select user.username from mess inner join user on (mess.id1 = ? and mess.id2 = user.id)";
    rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
    if(rc == SQLITE_OK){
        sqlite3_bind_int(stmt,1,id1);
        while(sqlite3_step(stmt)==SQLITE_ROW){
            cout<<sqlite3_column_text(stmt,0)<<endl;
        }
    }
    sqlite3_finalize(stmt);
}
void model::showNguoiGui(int id1){
    sql = "select user.username from mess inner join user on (mess.id2 = ? and mess.id1 = user.id)";
    rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
    if(rc == SQLITE_OK){
        sqlite3_bind_int(stmt,1,id1);
        while(sqlite3_step(stmt)==SQLITE_ROW){
            cout<<sqlite3_column_text(stmt,0)<<endl;
        }
    }
    sqlite3_finalize(stmt);
}
void model::showMessSent(int id1,int id2){
    sql = "select mess,time from mess where id1 = ? and id2 = ?";
        rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
        if(rc == SQLITE_OK){
            sqlite3_bind_int(stmt,1,id1);
            sqlite3_bind_int(stmt,2,id2);
            while(sqlite3_step(stmt)==SQLITE_ROW){
                cout<<sqlite3_column_text(stmt,0)<<"\t"<<sqlite3_column_text(stmt,1)<<endl;
            }
        }
        cout<<"========================================="<<endl;
         sqlite3_finalize(stmt);
}

void model::showMessInbox(int id1,int id2){
    sql = "select mess,time from mess where id1 = ? and id2 = ?";
        rc = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,&tailSql);
        if(rc == SQLITE_OK){
            sqlite3_bind_int(stmt,1,id2);
            sqlite3_bind_int(stmt,2,id1);
            while(sqlite3_step(stmt)==SQLITE_ROW){
                cout<<sqlite3_column_text(stmt,0)<<"\t"<<sqlite3_column_text(stmt,1)<<endl;
            }
        }
        cout<<"========================================="<<endl;
         sqlite3_finalize(stmt);
}

