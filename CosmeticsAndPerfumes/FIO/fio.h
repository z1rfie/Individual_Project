// Copyright 2025 Udalova Valeria

class FIO {
	char* first_name;
	char* second_name;
	char* last_name;
public:
	//конструкторы
	FIO();
	FIO(const char*, const char*, const char*);
	FIO(const FIO&);

	//деструктор 
	~FIO();

	//сеттеры (задаем значение имени)
	void set_first_name(const char* first_name);
	void set_second_name(const char* second_name);
	void set_last_name(const char* last_name);

	//геттеры (возвращаем значение имени)
	const char* get_first_name();
	const char* get_second_name();
	const char* get_last_name();
private:
	bool check_corrections(const char* name);
	void convert_to_normal_form();
	char* create_copy();
};