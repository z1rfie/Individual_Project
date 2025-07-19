#include <iostream>
#include <clocale>
#include "fio.h"

int len(const char* str) {
    if (str == nullptr) {
        throw std::invalid_argument("�������� ������ �� ����� ���� null");
    }

    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void copy_string(char** new_str, const char* copied_str) {
    if (*new_str != nullptr) {
        delete[] * new_str;
    }
    int length = len(copied_str);

    *new_str = new char[length + 1];

    for (int i = 0; i < length; i++) {
        (*new_str)[i] = copied_str[i];
    }
    (*new_str)[length] = '\0';
}

//������������
FIO::FIO() {
    char fn[20] = "����"; //�������� ������ ��� ���������� �� ���������
    char sn[20] = "������";
    char ln[20] = "��������";

    _first_name = nullptr;
    _second_name = nullptr;
    _last_name = nullptr;

    copy_string(&_first_name, fn);
    copy_string(&_second_name, sn);
    copy_string(&_last_name, ln);
}

//����������� � �����������
FIO::FIO(char* first_name, char* second_name, char* last_name) {
    _first_name = nullptr;
    _second_name = nullptr;
    _last_name = nullptr;

    copy_string(&_first_name, first_name);
    copy_string(&_second_name, second_name);
    copy_string(&_last_name, last_name);
}

FIO::FIO(const FIO& other) {
    _first_name = nullptr;
    _second_name = nullptr;
    _last_name = nullptr;

    copy_string(&_first_name, other._first_name);
    copy_string(&_second_name, other._second_name);
    copy_string(&_last_name, other._last_name);
}

//����������
FIO::~FIO() {
    delete[] _first_name;
    delete[] _second_name;
    delete[] _last_name;
}

//�������
void FIO::set_first_name(char* first_name) {
    check_corrections(first_name);
    convert_to_normal_form(first_name);
    copy_string(&_first_name, first_name);
}

void FIO::set_second_name(char* second_name) {
    check_corrections(second_name);
    convert_to_normal_form(second_name);
    copy_string(&_second_name, second_name);
}

void FIO::set_last_name(char* last_name) {
    check_corrections(last_name);
    convert_to_normal_form(last_name);
    copy_string(&_last_name, last_name);
}

//�������
const char* FIO::get_first_name() {
    return _first_name;
}
const char* FIO::get_second_name() {
    return _second_name;
}
const char* FIO::get_last_name() {
    return _last_name;
}

//��������� �������
void FIO::check_corrections(const char* name) {
    if (name[0] == '\0') {
        throw std::logic_error("������ �� ����� ���� ������.");
    }

    for (int i = 1; name[i] != '\0'; i++) {
        if (!(name[i] >= 'a' && name[i] <= 'z') &&
            !(name[i] >= 'A' && name[i] <= 'Z') &&
            !(name[i] >= '�' && name[i] <= '�') &&
            !(name[i] >= '�' && name[i] <= '�')) {
            throw std::logic_error("���� �������� ������������ �������!");
        }
    }
}

void FIO::convert_to_normal_form(char* name) {
    if ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= '�' && name[0] <= '�')) {
        name[0] = name[0] - 32;
    }
    for (int i = 1; i < len(name); i++) {
        if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= '�' && name[i] <= '�')) {
            name[i] = name[i] + 32;
        }
    }
}