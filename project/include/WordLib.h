/*
 * @Description  : �ʿ�������
 * @Author       : FZU Liao
 * @Date         : 2022-03-07 15:10:59
 * @LastEditors  : Liao
 * @LastEditTime : 2022-03-12 16:42:42
 * @FilePath     : \project\include\WordLib.h
 * Copyright 2022 FZU Liao, All Rights Reserved.
 */

/*
 * @note:
 *   �½�һ��WordLib���󣬲��ṩ���ĺ�ѭ������getNextWord���ɡ�
 */

#pragma once

#include <set>
#include <string>
#include <vector>
#include <fstream>

#define off_set 2

//ǰ����������
class Artical;

//�ʿ���
class WordLib {
   private:
    //��׺�ڵ��ڲ���
    class SuffixNode {
       private:
        std::string suffixStr;
        int numOfOccur;  //��¼�˸ú�׺�ڵ�ǰģ�������еĳ��ִ���
       public:
        /**
         * @description: Ĭ�Ϲ��캯��
         * @param *
         * @return *
         * @example:
         */
        SuffixNode();

        /**
         * @description: ���캯��
         * @param suffix string
         * @param numOfOccur int
         * @return *
         * @example:
         */
        SuffixNode(std::string suffix, int numOfOccur);

        /**
         * @description: ���ص�ǰ�ڵ��ڴ洢�ĺ�׺�ַ���
         * @param *
         * @return *
         * @example:
         */
        std::string GetSuffixStr();

        /**
         * @description: ���µ�ǰ�ڵ��׺���ִ�����ʹNumOfOccur++
         * @param *
         * @return *
         * @example:
         */
        void UpdateNumOfOccur();

        /**
         * @description: �������������������
         * @param *
         * @return *
         * @example:
         */
        bool operator>(const SuffixNode& otherNode) const;

        /**
         * @description: Ĭ����������
         * @param *
         * @return *
         * @example:
         */
        ~SuffixNode() = default;
    };

    //ǰ׺�ڵ��ڲ���
    class PrefixNode {
       private:
        std::string prefixStr;
        std::vector<SuffixNode> suffixList;
        //ָ��ǰ���ִ�����൫��δ��ʹ�ù��ĺ�׺�ڵ�ĵ�����
        std::vector<SuffixNode>::iterator suffixIter;

        /**
         * @description: ���ݺ�׺�ַ����ҵ����ں�׺�б��еĵ�����
         * @param suffixStr string
         * @return ��Ӧ��׺�ڵ�ĵ���������û�ҵ�������end()
         * @example:
         */
        std::vector<SuffixNode>::iterator GetIterOfSuffix(
            std::string suffixStr);

       public:
        /**
         * @description: Ĭ�Ϲ��캯��
         * @param *
         * @return *
         * @example:
         */
        PrefixNode();

        /**
         * @description: ���캯��
         * @param prefixStr string
         * @return *
         * @example:
         */
        PrefixNode(std::string prefixStr);

        /**
         * @description: ��ȡ��ǰ����ʵĺ�׺�ַ����������º�׺�б�
         * @param *
         * @return *
         * @example:
         * @note: ȷ�����Ѿ���������
         */
        std::string GetNextSuffix();

        /**
         * @description: ���ýڵ�ά���ĺ�׺�б��м���һ����׺�ַ���
         * @param suffixStf string
         * @return *
         * @example:
         */
        void AddSuffix(std::string suffixStr);

        /**
         * @description: ��ά���ĺ�׺�б���а�Ƶ������
         * @param *
         * @return *
         * @example:
         */
        void SortSuffixList();

        //��������أ�����Ӧstd::set�Ĳ���
        bool operator>(const PrefixNode& otherNode) const;
        //��������أ�����Ӧstd::set�Ĳ���
        bool operator==(const PrefixNode& otherNode) const;
        //��������أ�����Ӧstd::set�Ĳ���
        bool operator<(const PrefixNode& otherNode) const;

        /**
         * @description: ��������
         * @param *
         * @return *
         * @example:
         */
        ~PrefixNode() = default;
    };

    //ǰ׺�ڵ������
    std::set<PrefixNode>* prefixSet;
    //ǰ׺ƥ�䳤��
    int prefixLength;
    //��׺ƥ�䳤��
    int suffixLength;

   public:
    /**
     * @description: ���캯��
     * @param *
     * @return *
     * @example:
     */
    WordLib();

    /**
     * @description: ���캯��
     * @param prefixLength int ǰ׺����
     * @param suffixLength int ��׺����
     * @return *
     * @example:
     */
    WordLib(int prefixLength, int suffixLength);

    /**
     * @description: ���캯��
     * @param modelText string ģ������
     * @param prefixLength int ǰ׺����
     * @param suffixLength int ��׺����
     * @return *
     * @example:
     */
    WordLib(std::string modelText, int prefixLength, int suffixLength);

    /**
     * @description: ����ģ������
     * @param modelText string
     * @return *
     * @example:
     */
    void UpdateLib(std::string modelText);

    /**
     * @description: ����ģ������
     * @param artical Artical
     * @return *
     * @example: 
     */    
    void UpdateLib(Artical artical);

    /**
     * @description: ��ȡ��һ��Ԥ���
     * @param prefix string
     * @return string Ԥ���
     * @example:
     */
    std::string GetNextWord(std::string prefix) const;

    /**
     * @description: ����ǰ׺����
     * @param *
     * @return *
     * @example:
     */
    int GetPrefixLength() const;

    /**
     * @description: ��������
     * @param *
     * @return *
     * @example:
     */
    ~WordLib();

};
