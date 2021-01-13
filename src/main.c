#include <stdio.h>	// Для printf / sprintf

typedef struct {
	char* name; // имя атрибута
	double value; // значение атрибута
} Attribute;

// выводим информацию об характеристики персонажа на экран
void testPrintAttribute(Attribute* attribute) {
	printf("%s: %f\n", attribute->name, attribute->value);
}

// тестирует функционал вывода характеристик персонажа на экран
void testAttribute() {
	Attribute health = {"Health", 100};
	testPrintAttribute(&health);
	
	Attribute strength = {"Strength", 20};
	testPrintAttribute(&strength);
}

int main() {
	testAttribute();
	
	return 0;
}
