/*
 * @Description  : 文章类声明
 * @Author       : FZU Liao
 * @Date         : 2022-03-12 16:21:53
 * @LastEditors  : Liao
 * @LastEditTime : 2022-03-12 16:27:36
 * @FilePath     : \project\include\Artical.h
 * Copyright 2022 FZU Liao, All Rights Reserved.
 */
#include <string>
#include "WordLib.h"

class Artical {
   private:
    std::string content;
    std::string fileName;
   public:

    /**
     * @description: 默认构造函数
     * @param *
     * @return *
     * @example: 
     */    
    Artical();

    /**
     * @description: 根据文件读入文章
     * @param fileName string 
     * @return *
     * @example: 
     */    
    Artical(std::string fileName);

    /**
     * @description: 扩写函数
     * @param lib WordLib
     * @param length int 扩写长度
     * @return *
     * @example:
     */
    void expand(WordLib lib, int length);

    /**
     * @description: 获取内容
     * @param *
     * @return *
     * @example: 
     */    
    std::string getContent();

    /**
     * @description: 生成文件
     * @param *
     * @return *
     * @example: 
     */    
    void generateFile();
};