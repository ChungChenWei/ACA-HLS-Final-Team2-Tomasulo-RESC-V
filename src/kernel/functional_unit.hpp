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
private:
    __func_unit_finish_task_interface_t result[FUNC_UNIT_ADD_NUM];
    int counter[FUNC_UNIT_ADD_NUM];
    bool busy[FUNC_UNIT_ADD_NUM];

public:
    Adders ();
    void every_cycle (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta);
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
    __func_unit_finish_task_interface_t result[FUNC_UNIT_MUL_NUM];
    int counter[FUNC_UNIT_MUL_NUM];
    bool busy[FUNC_UNIT_MUL_NUM];

public:
    Multipliers ();
    void every_cycle (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta);
};

#endif
