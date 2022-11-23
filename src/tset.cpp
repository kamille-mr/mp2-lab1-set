// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp){

    if (mp > 0) {

        MaxPower = mp;
    }
    else throw "error";
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField){

    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf){

    BitField = bf;
    MaxPower = bf.GetLength();
}

TSet::operator TBitField(){

    TBitField tmp = (TBitField)*this;
    return tmp;
}

int TSet::GetMaxPower(void) const{ // получить макс. к-во эл-тов

    return MaxPower;
}

int TSet::IsMember(const int Elem) const{ // элемент множества?

    if ((Elem >= 0) && (Elem < MaxPower)) {

        if (BitField.GetBit(Elem)) {

            return 1;
        }
        else {

            return 0;
        }
    }
   else throw "error";
}

void TSet::InsElem(const int Elem){ // включение элемента множества

    if ((Elem >= 0) && (Elem < MaxPower)){

        BitField.SetBit(Elem);
   }
    else throw "error";
}

void TSet::DelElem(const int Elem){ // исключение элемента множества

    if ((Elem >= 0) && (Elem < MaxPower)) {
        BitField.ClrBit(Elem);
    }
    else throw "error";
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s){ // присваивание

    if (*this == s) {

        return *this;
    }
    BitField = s.BitField;
    MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet &s) const{ // сравнение

    if (MaxPower != s.MaxPower) {

        return 0;
    }
    else if ((MaxPower == s.MaxPower) && (BitField == s.BitField)) {

        return 1;
    }
    else {

        return 0;
    }
}

int TSet::operator!=(const TSet &s) const{ // сравнение

    if (MaxPower != s.MaxPower) {

        return 1;
    }
    if (BitField != s.BitField){

        return 1;
    }
    return 0;
}

TSet TSet::operator+(const TSet &s){ // объединение

    int max = MaxPower;
    if (MaxPower < s.MaxPower) {

        max = s.MaxPower;
    }
    TSet tmp(max);
    tmp.BitField = BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem){ // объединение с элементом

    if ((Elem >= 0) && (Elem < MaxPower)) {
       
    TSet tmp(MaxPower);
    tmp.BitField = BitField;
    tmp.InsElem(Elem);
    return tmp;
    }
    else throw "error";
}

TSet TSet::operator-(const int Elem){ // разность с элементом

    TSet tmp(MaxPower);
    tmp.BitField = BitField;
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s){ // пересечение

    int max = MaxPower;
    if (MaxPower < s.MaxPower) {

        max = s.MaxPower;
    }
    TSet tmp(max);
    tmp = BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void){ // дополнение
    
    TSet tmp(MaxPower);
    tmp.BitField = ~BitField;
    return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s){ // ввод

    char ch, tmp;
    char ;
    istr >> ch;
    while (ch != ' ') {
        istr >> tmp;
        s.InsElem(tmp);
        istr >> ch;
        while (ch != ',') {
            istr >> ch;
        }
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s){ // вывод

    ostr << s.BitField<<' ';
    return ostr;
}
