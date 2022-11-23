// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len){

    BitLen = len;
    MemLen = (len / sizeof(TELEM) * 8) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {

        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf){ // конструктор копирования

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {

        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField(){

    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const{ // индекс Мем для бита n
    
    if ((n >= 0) && (n < BitLen)) {

        int index = n / (sizeof(TELEM) * 8);
        return index;
    }
    else throw "error";
}

TELEM TBitField::GetMemMask(const int n) const{ // битовая маска для бита n

    if ((n >= 0) && (n < BitLen)) {

        TELEM mask = n % (sizeof(TELEM) * 8);
        return (TELEM)1 << mask;
    }
    else throw "error";
}

// доступ к битам битового поля

int TBitField::GetLength(void) const{ // получить длину (к-во битов)

  return BitLen;
}

void TBitField::SetBit(const int n){ // установить бит

    if ((n >= 0) && (n < BitLen)) {

        int index = GetMemIndex(n);
        TELEM mask = GetMemMask(n);
        pMem[index] = pMem[index] | mask;
    }
    else throw "error";
}

void TBitField::ClrBit(const int n) { // очистить бит

    if ((n >= 0) && (n < BitLen)) {

        int index = GetMemIndex(n);
        TELEM mask = ~GetMemMask(n);
        pMem[index] = pMem[index] & mask;
    }
    else throw "error";
}

int TBitField::GetBit(const int n) const{ // получить значение бита

    if ((n >= 0) && (n < BitLen)) {

        int tmp;
        int index = GetMemIndex(n);
        TELEM mask = GetMemMask(n);
        if (pMem[index] & mask) {

            tmp = 1;
        }
        else {
            tmp = 0;
        }
        return tmp;
    }
    else throw "error";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf){ // присваивание

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    TELEM* t = new TELEM[bf.MemLen];
    for (int i = 0; i < MemLen; i++) {

        t[i] = bf.pMem[i];
    }
    delete[] pMem;
    pMem = t;
    
    return *this;
}

int TBitField::operator==(const TBitField &bf) const{ // сравнение
    
    if (BitLen != bf.BitLen || MemLen != bf.MemLen) {

        return 0;
    }
    for (int i = 0; i < MemLen; i++) {

        if (pMem[i] != bf.pMem[i]) {

            return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const { // сравнение

    if (BitLen != bf.BitLen) {

        return 1;
    }
    for (int i = 0; i < MemLen; i++) {

        if (pMem[i] != bf.pMem[i]) {

            return 1;
        }  
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf){ // операция "или"

    int max = BitLen;
    if (BitLen < bf.BitLen) {

        max = bf.BitLen;
    }
    TBitField tmp(max);
    for (int i = 0; i < MemLen; i++) {

        tmp.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {

        tmp.pMem[i] = tmp.pMem[i] | bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) { // операция "и"

    if (bf.BitLen > BitLen) {

        TBitField tmp(bf.BitLen);
        for (int i = 0; i < MemLen; i++) {

            tmp.pMem[i] = bf.pMem[i] & pMem[i];
        }
        for (int i = MemLen; i < bf.MemLen; i++) {

            tmp.pMem[i] = 0;
        }
        return tmp;
    }
    else {

        TBitField tmp(BitLen);
        for (int i = 0; i < bf.MemLen; i++) {

            tmp.pMem[i] = bf.pMem[i] & pMem[i];
        }
        for (int i = bf.MemLen; i < MemLen; i++) {

            tmp.pMem[i] = 0;
        }
        return tmp;
    }
}

TBitField TBitField::operator~(void){ // отрицание

    TBitField tmp(*this);
    for (int i = 0; i < tmp.BitLen; i++){
    
        if (tmp.GetBit(i)){

           tmp.ClrBit(i);
        }
        else{

            tmp.SetBit(i);
        }
    }
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf){ // ввод

    char ch;
    int i = 0;
    istr >> ch;
    while (ch != ' ') {
        istr >> ch;
        if (ch == '1') {
            bf.SetBit(i++);
        }
        else {
            bf.ClrBit(i++);
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf){ // вывод

     for (int i = 0; i < bf.BitLen; i++) {

        ostr << bf.GetBit(i);
    } 
    return ostr;
}
