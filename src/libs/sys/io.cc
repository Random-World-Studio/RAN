/**
 * @file io.cc
 * @author pointer-to-bios
 * @brief 输入输出库
 * @version 0.0
 * @date 2022-05-14
 *
 * @copyright Copyright (c) 2022 Random World Studio
 *
 */

#include "../../rancinterface/type.hh"

struct file
{
    /*权限*/
    static const ranuint read = 0;  //读权限
    static const ranuint write = 1; //写权限
    static const ranuint exec = 2;  //运行权限

    ranuint pfile = 0; //文件指针

    static const ranuint sof = 0; //文件开头
    ranuint eof;                  //文件结尾

    ranstr openfile; //打开文件的路径

    /**
     * @brief 打开文件函数
     *
     * @param path 文件的路径
     * @param permission 打开的权限
     */
    void open(ranstr path, ranuint permission);
    /**
     * @brief 关闭文件函数
     */
    void close();

    /**
     * @brief 获得count字节文件内容
     * 从文件指针处读取，读一字节将文件指针增加一字节
     * 返回已经读取的字节数，可以用此返回值判断是否到达文件结尾还没有读完
     *
     * @param count 要读取的字节数
     *
     * @return str 返回读到的字节序列
     * @return uint 返回已经读取的字节数
     */
    ranstr popbyte(ranuint count, ranuint *return1);

    /**
     * @brief 定位文件指针
     *
     * @param location 相对于sof的位置
     */
    void seek__t__2__(ranuint location);
    /**
     * @brief 定位文件指针
     *
     * @param relofst 相对偏移
     * @param org 计算相对偏移的起始位置
     */
    void seek__t__23__(ranint relofst, ranuint org);

    /**
     * @brief 判断文件是否打开
     *
     * @return bool true-已经打开文件;false-没有打开文件
     */
    bool is_open();
    /**
     * @brief 判断文件是否关闭
     *
     * @return bool 与上个函数相反
     */
    bool is_close();

    /**
     * @brief 获得打开的文件
     *
     * @return str 返回文件名
     */
    ranstr get_openfile();
};
