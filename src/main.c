#include <stdio.h>	// Для printf / sprintf
#include <math.h>	// Для ceil

typedef struct {
	char* name; // имя атрибута
	double value; // значение атрибута
} Attribute;

// Округляет значение характеристики персонажа вверх
// Например, не хочу видеть игроков со здоровьем 80.356, пусть будет 81
int normalizeAttribute(double value) {
	return (int)ceil(value);
}

// выводим информацию об характеристики персонажа на экран
void testPrintAttribute(Attribute* attribute) {
	int value = normalizeAttribute(attribute->value);
	printf("%s: %d\n", attribute->name, value);
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
