#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "logger.h"
using namespace std;

struct  Cmd_writer
{
    bool open_for_write=false;
    int obj_counter;
    vector<string> cmd_buff;
    logger log;
     Cmd_writer(int count) {
         obj_counter=count;
         log.init("");
     }
    void increment_obj_counter(string data){
        if(open_for_write){
            obj_counter++;
        } else {
            obj_counter=1;
            open_for_write=true;
            cmd_buff.clear();
        }
     }
    void decrement_obj_counter(string data){
         obj_counter--;
        if(!open_for_write && obj_counter){
             cmd_buff.push_back(data);
         }
        else if(open_for_write && obj_counter){}
         else {
             obj_counter=3;
             open_for_write=false;
             if (strcmp(data.c_str(),"}")!=0)
                cmd_buff.push_back(data);
             std::string bulk_str="bulk: ";
             for (auto str = cmd_buff.begin(); str != cmd_buff.end(); ++str) {
                 bulk_str=bulk_str+*str;
                 if(str!=cmd_buff.end()-1)
                     bulk_str+=", ";
             }
             std::cout<<bulk_str<<std::endl;
             log.info(bulk_str);
             cmd_buff.clear();
         }
     }
};
int main()
{
    Cmd_writer cmd_writer(3);
    while (1) {
        string cmd;
        std::cin>>cmd;
        if(strcmp(cmd.c_str(),"{")==0){
            cmd_writer.increment_obj_counter(cmd);
        } else if (strcmp(cmd.c_str(),"}")==0) {
             cmd_writer.decrement_obj_counter(cmd);
        } else if (cmd_writer.open_for_write) {
            cmd_writer.cmd_buff.push_back(cmd);
        } else
            cmd_writer.decrement_obj_counter(cmd);
        }
    return 0;
}
