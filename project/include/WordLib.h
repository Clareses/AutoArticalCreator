/*
 * @Description  : 词库类声明
 * @Author       : FZU Liao
 * @Date         : 2022-03-07 15:10:59
 * @LastEditors  : Liao
 * @LastEditTime : 2022-03-12 16:42:42
 * @FilePath     : \project\include\WordLib.h
 * Copyright 2022 FZU Liao, All Rights Reserved.
 */

/*
 * @note:
 *   新建一个WordLib对象，并提供范文后循环调用getNextWord即可。
 */

#pragma once

#include <set>
#include <string>
#include <vector>
#include <fstream>

#define off_set 2

//前向引用声明
class Artical;

//词库类
class WordLib {
   private:
    //后缀节点内部类
    class SuffixNode {
       private:
        std::string suffixStr;
        int numOfOccur;  //记录了该后缀在当前模板文章中的出现次数
       public:
        /**
         * @description: 默认构造函数
         * @param *
         * @return *
         * @example:
         */
        SuffixNode();

        /**
         * @description: 构造函数
         * @param suffix string
         * @param numOfOccur int
         * @return *
         * @example:
         */
        SuffixNode(std::string suffix, int numOfOccur);

        /**
         * @description: 返回当前节点内存储的后缀字符串
         * @param *
         * @return *
         * @example:
         */
        std::string GetSuffixStr();

        /**
         * @description: 更新当前节点后缀出现次数，使NumOfOccur++
         * @param *
         * @return *
         * @example:
         */
        void UpdateNumOfOccur();

        /**
         * @description: 重载运算符，用于排序
         * @param *
         * @return *
         * @example:
         */
        bool operator>(const SuffixNode& otherNode) const;

        /**
         * @description: 默认析构函数
         * @param *
         * @return *
         * @example:
         */
        ~SuffixNode() = default;
    };

    //前缀节点内部类
    class PrefixNode {
       private:
        std::string prefixStr;
        std::vector<SuffixNode> suffixList;
        //指向当前出现次数最多但还未被使用过的后缀节点的迭代器
        std::vector<SuffixNode>::iterator suffixIter;

        /**
         * @description: 根据后缀字符串找到它在后缀列表中的迭代器
         * @param suffixStr string
         * @return 对应后缀节点的迭代器，若没找到，返回end()
         * @example:
         */
        std::vector<SuffixNode>::iterator GetIterOfSuffix(
            std::string suffixStr);

       public:
        /**
         * @description: 默认构造函数
         * @param *
         * @return *
         * @example:
         */
        PrefixNode();

        /**
         * @description: 构造函数
         * @param prefixStr string
         * @return *
         * @example:
         */
        PrefixNode(std::string prefixStr);

        /**
         * @description: 获取当前最合适的后缀字符串，并更新后缀列表
         * @param *
         * @return *
         * @example:
         * @note: 确保在已经排序后调用
         */
        std::string GetNextSuffix();

        /**
         * @description: 往该节点维护的后缀列表中加入一个后缀字符串
         * @param suffixStf string
         * @return *
         * @example:
         */
        void AddSuffix(std::string suffixStr);

        /**
         * @description: 对维护的后缀列表进行按频率排序
         * @param *
         * @return *
         * @example:
         */
        void SortSuffixList();

        //运算符重载，以适应std::set的操作
        bool operator>(const PrefixNode& otherNode) const;
        //运算符重载，以适应std::set的操作
        bool operator==(const PrefixNode& otherNode) const;
        //运算符重载，以适应std::set的操作
        bool operator<(const PrefixNode& otherNode) const;

        /**
         * @description: 析构函数
         * @param *
         * @return *
         * @example:
         */
        ~PrefixNode() = default;
    };

    //前缀节点二叉树
    std::set<PrefixNode>* prefixSet;
    //前缀匹配长度
    int prefixLength;
    //后缀匹配长度
    int suffixLength;

   public:
    /**
     * @description: 构造函数
     * @param *
     * @return *
     * @example:
     */
    WordLib();

    /**
     * @description: 构造函数
     * @param prefixLength int 前缀长度
     * @param suffixLength int 后缀长度
     * @return *
     * @example:
     */
    WordLib(int prefixLength, int suffixLength);

    /**
     * @description: 构造函数
     * @param modelText string 模板文章
     * @param prefixLength int 前缀长度
     * @param suffixLength int 后缀长度
     * @return *
     * @example:
     */
    WordLib(std::string modelText, int prefixLength, int suffixLength);

    /**
     * @description: 导入模板文章
     * @param modelText string
     * @return *
     * @example:
     */
    void UpdateLib(std::string modelText);

    /**
     * @description: 导入模板文章
     * @param artical Artical
     * @return *
     * @example: 
     */    
    void UpdateLib(Artical artical);

    /**
     * @description: 获取下一个预测词
     * @param prefix string
     * @return string 预测词
     * @example:
     */
    std::string GetNextWord(std::string prefix) const;

    /**
     * @description: 返回前缀长度
     * @param *
     * @return *
     * @example:
     */
    int GetPrefixLength() const;

    /**
     * @description: 析构函数
     * @param *
     * @return *
     * @example:
     */
    ~WordLib();

};
