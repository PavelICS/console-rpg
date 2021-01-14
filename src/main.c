#include <stdlib.h>	// Для malloc / free
#include <stdio.h>	// Для printf / sprintf
#include <math.h>	// Для ceil
#include <stdbool.h>// Для true / false

#define COLOR_DEFAULT			"\033[0m"
#define COLOR_RED				"\x1B[31m"
#define COLOR_GREEN				"\x1B[32m"
#define COLOR_YELLOW			"\x1B[33m"
#define COLOR_BLUE				"\x1B[34m"
#define COLOR_MAGENTA			"\x1B[35m"
#define COLOR_CYAN				"\x1B[36m"
#define COLOR_WHITE				"\x1B[37m"
#define COLOR_BRIGHT_RED		"\x1B[91m"
#define COLOR_BRIGHT_GREEN		"\x1B[92m"
#define COLOR_BRIGHT_YELLOW		"\x1B[93m"
#define COLOR_BRIGHT_BLUE		"\x1B[94m"
#define COLOR_BRIGHT_MAGENTA	"\x1B[95m"
#define COLOR_BRIGHT_CYAN		"\x1B[96m"
#define COLOR_BRIGHT_WHITE		"\x1B[97m"

/**
 * Структура AttributeType отвечает за описание характеристики персонажа
 * id - уникальный идентификатор
 * name - полное имя
 * shortName - короткое имя
 * hidden - скрыта ли характеристика от игрока
 * color - цвет отображения в консоли
 * description - описание
 * formater - формат (числовой, вероятностный)
 * maxLimit - максимальное значение
*/
typedef struct {
	char* id;
	char* name;
	char* shortName;
	bool hidden;
	char* color;
	char* description;
	char* formater;
	double maxLimit;
} AttributeType;

/**
 * Структура Attribute отвечает за связь характеристик с персонажем
 * type - опеределяет какая это характеристика (здоровье, сила и тд)
 * value - значение характеристики
*/
typedef struct {
	const AttributeType* type;
	double value;
} Attribute;

#define ATTRIBUTE_FORMAT_NUMBER "numerical"
#define ATTRIBUTE_FORMAT_PERCENTAGE "percentage"

const AttributeType STAT_HEALTH = {
	"stat_health",
	"Health",
	"HP",
	false,
	COLOR_GREEN,
	"Number of maximum Hit Points",
	ATTRIBUTE_FORMAT_NUMBER,
	1000
};

const AttributeType STAT_MANA = {
	"stat_mana",
	"Mana",
	"MP",
	false,
	COLOR_BLUE,
	"Resource consumed to use Magic",
	ATTRIBUTE_FORMAT_NUMBER,
	1000
};

const AttributeType STAT_STRENGTH = {
	"stat_strength",
	"Strength",
	"STR",
	false,
	COLOR_RED,
	"Increases the damage of your attacks",
	ATTRIBUTE_FORMAT_NUMBER,
	500
};

const AttributeType STAT_DEFENSE = {
	"stat_defense",
	"Physical Resistance",
	"DEF",
	false,
	COLOR_YELLOW,
	"Reduces damage taken from attacks",
	ATTRIBUTE_FORMAT_NUMBER,
	500
};

const AttributeType STAT_INTELLIGENCE = {
	"stat_intelligence",
	"Intelligence",
	"DEF",
	false,
	COLOR_CYAN,
	"Increases the power of your magic",
	ATTRIBUTE_FORMAT_NUMBER,
	500
};

const AttributeType STAT_RESISTANCE = {
	"stat_resistance",
	"Magical Resistance",
	"DEF",
	false,
	COLOR_BRIGHT_CYAN,
	"Reduces damage taken from magic",
	ATTRIBUTE_FORMAT_NUMBER,
	500
};

const AttributeType STAT_DODGING = {
	"stat_dodging",
	"Dodging",
	"DOG",
	false,
	COLOR_BRIGHT_YELLOW,
	"Chance to evade an attack",
	ATTRIBUTE_FORMAT_PERCENTAGE,
	0.5
};

const AttributeType STAT_CRIT = {
	"stat_crit",
	"Crit chance",
	"CRI",
	false,
	COLOR_MAGENTA,
	"Chance to make a critical hit",
	ATTRIBUTE_FORMAT_PERCENTAGE,
	0.5
};

// Округляет значение характеристики персонажа вверх
// обычные аттрибуты округляются до целого числа
// атрибуты типа "percentage" округляются до второго чила после запятой
// Например, не хочу видеть игроков со здоровьем 80.356, пусть будет 81
double normalizeAttribute(const AttributeType* type, double value) {
	if (type->formater == ATTRIBUTE_FORMAT_PERCENTAGE) {
		return ceil(value * 100) / 100;
	}
	
	return ceil(value);
}

// форматирует нормализованное значение характеристики персонажа для вывода на экран
// !буффер должен быть не меньше 12 байт, результат не должен превышать 12 байт.
// 12 байт должно быть достаточно для любого атрибута
int formatAttribute(char* buf, const AttributeType* type, double value) {
	if (type->formater == ATTRIBUTE_FORMAT_PERCENTAGE) {
		// проценты, например, 10%
		return sprintf(buf, "%d%%", (int)(value*100));
	}
	
	// просто число, например, 199
	return sprintf(buf, "%d", (int)(value));
}

// выводим информацию об характеристики персонажа на экран
void testPrintAttribute(Attribute* attribute) {
	double value = normalizeAttribute(attribute->type, attribute->value);
	
	// dynamically allocate 12 chars string for displaying formated attribute value
	char* strAtrtibuteValue = (char*)malloc(sizeof(char)*12);
	formatAttribute(strAtrtibuteValue, attribute->type, value);
	
	printf("%s%s: %s\n%s%s\n",
		attribute->type->color,
		attribute->type->name,
		strAtrtibuteValue,
		attribute->type->description,
		COLOR_DEFAULT
	);
	
	// free allocated memory (return back to the system).
	// never forget returning memory to the system. You must return it, if you don't need it anymore
	free(strAtrtibuteValue);
}

// тестирует функционал вывода характеристик персонажа на экран
void testAttribute() {
	Attribute health = {&STAT_HEALTH, 99.36};
	testPrintAttribute(&health);
	
	Attribute mana = {&STAT_MANA, 100};
	testPrintAttribute(&mana);
	
	Attribute strength = {&STAT_STRENGTH, 20};
	testPrintAttribute(&strength);
	
	Attribute defense = {&STAT_DEFENSE, 20};
	testPrintAttribute(&defense);
	
	Attribute intel = {&STAT_INTELLIGENCE, 20};
	testPrintAttribute(&intel);
	
	Attribute resistance = {&STAT_RESISTANCE, 20};
	testPrintAttribute(&resistance);
	
	Attribute dodging = {&STAT_DODGING, 0.05};
	testPrintAttribute(&dodging);
	
	Attribute crit = {&STAT_CRIT, 0.1};
	testPrintAttribute(&crit);
}

int main() {
	testAttribute();
	
	return 0;
}