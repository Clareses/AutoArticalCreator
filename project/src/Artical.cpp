/*
 * @Description  : 文章类实现
 * @Author       : FZU Liao
 * @Date         : 2022-03-12 16:22:00
 * @LastEditors  : Liao
 * @LastEditTime : 2022-03-12 16:41:03
 * @FilePath     : \project\src\Artical.cpp
 * Copyright 2022 FZU Liao, All Rights Reserved.
 */

#include "../include/Artical.h"
#include <fstream>

Artical::Artical() {
    this->fileName = "../res/textResult.txt";
    this->content = "";
}

Artical::Artical(std::string fileName) {
    this->fileName = fileName;
    std::ifstream openFile(fileName);
    openFile >> this->content;
}

void Artical::expand(WordLib lib, int length) {
    int prefixLength = lib.GetPrefixLength();
    if (this->content.length() < prefixLength)
        return;
    while (length--) {
        this->content += lib.GetNextWord(
            this->content.substr(this->content.length() - prefixLength));
    }
}

std::string Artical::getContent() {
    return this->content;
}

void Artical::generateFile() {
    std::ofstream saveFile(this->fileName);
    saveFile<<this->content;
}