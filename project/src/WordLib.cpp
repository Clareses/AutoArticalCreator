/*
 * @Description  : �ʿ���ʵ��
 * @Author       : FZU Liao
 * @Date         : 2022-03-07 16:32:56
 * @LastEditors  : Liao
 * @LastEditTime : 2022-03-12 16:30:44
 * @FilePath     : \project\src\WordLib.cpp
 * Copyright 2022 FZU Liao, All Rights Reserved.
 */

#include "../include/WordLib.h"
#include <algorithm>
#include "../include/Artical.h"

WordLib::SuffixNode::SuffixNode() {
    this->suffixStr = "";
    this->numOfOccur = 0;
}

WordLib::SuffixNode::SuffixNode(std::string suffix, int numOfOccur) {
    this->suffixStr = suffix;
    this->numOfOccur = numOfOccur;
}

std::string WordLib::SuffixNode::GetSuffixStr() {
    return this->suffixStr;
}

void WordLib::SuffixNode::UpdateNumOfOccur() {
    this->numOfOccur++;
}

bool WordLib::SuffixNode::operator>(const SuffixNode& otherNode) const {
    if (this->numOfOccur > otherNode.numOfOccur)
        return true;
    else if (this->numOfOccur < otherNode.numOfOccur)
        return false;
    else
        return this->suffixStr > otherNode.suffixStr;
}

std::vector<WordLib::SuffixNode>::iterator WordLib::PrefixNode::GetIterOfSuffix(
    std::string suffixStr) {
    auto iter = suffixList.begin();
    while (iter != suffixList.end() && iter->GetSuffixStr() != suffixStr)
        iter++;
    return iter;
}

WordLib::PrefixNode::PrefixNode() {
    this->prefixStr = "";
}

WordLib::PrefixNode::PrefixNode(std::string prefixStr) {
    this->prefixStr = prefixStr;
}

std::string WordLib::PrefixNode::GetNextSuffix() {
    auto iter = this->suffixList.cend();
    if (this->suffixIter == iter)
        return " ";
    return (this->suffixIter++)->GetSuffixStr();
}

void WordLib::PrefixNode::AddSuffix(std::string suffixStr) {
    auto iter = this->GetIterOfSuffix(suffixStr);
    if (iter == this->suffixList.end()) {
        this->suffixList.push_back(SuffixNode(suffixStr, 1));
    } else {
        iter->UpdateNumOfOccur();
    }
}

void WordLib::PrefixNode::SortSuffixList() {
    std::sort(this->suffixList.begin(), this->suffixList.end(),
              std::greater<SuffixNode>());
    this->suffixIter = this->suffixList.begin();
}

bool WordLib::PrefixNode::operator>(const PrefixNode& otherNode) const {
    return this->prefixStr > otherNode.prefixStr;
}

bool WordLib::PrefixNode::operator==(const PrefixNode& otherNode) const {
    if (this->prefixStr == otherNode.prefixStr)
        return true;
    else
        return false;
}

bool WordLib::PrefixNode::operator<(const PrefixNode& otherNode) const {
    return this->prefixStr < otherNode.prefixStr;
}

WordLib::WordLib() : WordLib(3, 3) {}

WordLib::WordLib(int prefixLength, int suffixLength) {
    this->prefixLength = prefixLength*off_set;
    this->suffixLength = suffixLength*off_set;
    this->prefixSet = new std::set<PrefixNode>;
}

WordLib::WordLib(std::string modelText, int prefixLength, int suffixLength)
    : WordLib(prefixLength, suffixLength) {
    UpdateLib(modelText);
}

void WordLib::UpdateLib(std::string modelText) {
    int textLength = modelText.length();
    std::string prefix;
    std::string suffix;
    std::set<PrefixNode>::iterator iter;
    for (int i = 0; i + prefixLength + suffixLength < textLength; i+= off_set) {
        prefix = modelText.substr(i, prefixLength);
        suffix = modelText.substr(i + prefixLength, suffixLength);
        iter = prefixSet->find(prefix);
        if (iter == prefixSet->end()) {
            PrefixNode newNode(prefix);
            newNode.AddSuffix(suffix);
            prefixSet->insert(newNode);
        } else {
            const_cast<PrefixNode&>(*iter).AddSuffix(suffix);
        }
    }
    for (auto it = prefixSet->begin(); it != prefixSet->end(); it++) {
        const_cast<PrefixNode&>(*it).SortSuffixList();
    }
}

void WordLib::UpdateLib(Artical artical){
    UpdateLib(artical.getContent());
}

std::string WordLib::GetNextWord(std::string prefix) const {
    std::set<PrefixNode>::iterator iter = prefixSet->find(prefix);
    if (iter != prefixSet->end()) {
        return const_cast<PrefixNode&>(*iter).GetNextSuffix();
    } else {
        return " ";
    }
}

int WordLib::GetPrefixLength() const {
    return this->prefixLength;
}

WordLib::~WordLib() {
    delete this->prefixSet;
}