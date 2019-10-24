#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

struct  Cmd_writer
{
    bool open_for_write=false;
    int obj_counter;
    vector<string> cmd_buff;
     Cmd_writer(int count) {
         obj_counter=count;
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
             for(const string& str : cmd_buff){
                 std::cout<<str<<" ";
             }
             std::cout<<std::endl;
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
