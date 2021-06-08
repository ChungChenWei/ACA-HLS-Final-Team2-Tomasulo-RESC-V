#ifndef __FUNCTIONAL_UNIT_HPP__
#define __FUNCTIONAL_UNIT_HPP__

#include "common.hpp"

class Adders_status {
private:
    bool busy[FUNC_UNIT_ADD_NUM];

public:
    Adders_status ();
    bool get_busy (int &index_o);
    void set_busy (int index);
    void unset_busy (int index);
    void print_debug ();
};

class Adders {
public:
    Adders ();
    void run_task (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta);
};

class Multipliers_status {
private:
    bool busy[FUNC_UNIT_MUL_NUM];

public:
    Multipliers_status ();
    bool get_busy (int &index_o);
    void set_busy (int index);
    void unset_busy (int index);
    void print_debug ();
};

class Multipliers {
private:
    bool busy[FUNC_UNIT_MUL_NUM];

public:
    Multipliers ();
    void run_task (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta);
};

#endif
