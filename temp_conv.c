#include "postgres.h"
#include "fmgr.h"
#include "utils/guc.h"
#include "utils/builtins.h"

PG_MODULE_MAGIC;

// Перевод Цельсия в Фаренгейты
PG_FUNCTION_INFO_V1(CelsToFahr);

Datum
CelsToFahr(PG_FUNCTION_ARGS)
{
    float8 cels = PG_GETARG_FLOAT8(0);
    float8 fahr = (cels * 9.0 / 5.0) + 32;

    PG_RETURN_FLOAT8(fahr);
}

// Перевод Фаренгейты в Цельсия
PG_FUNCTION_INFO_V1(FahrToCels);

Datum
FahrToCels(PG_FUNCTION_ARGS)
{
    float8 fahr = PG_GETARG_FLOAT8(0);
    float8 cels = (fahr - 32) * 5.0 / 9.0;

    PG_RETURN_FLOAT8(cels);
}

// Определение GUC-переменной
static double rounding_threshold = 0.5;

void
_PG_init(void)
{
    // Определяем GUC-переменную
    DefineCustomRealVariable(
        "rounding.threshold",
        "Threshold for rounding numbers",
        NULL,                  // длинное описание
        &rounding_threshold,  // указатель на переменную
        0.5,                   // начальное значение
        0.0,                   // минимальное значение
        1.0,                   // максимальное значение
        PGC_USERSET,           // категория
        0,                     // флаги
        NULL,                  // проверка значения
        NULL,                  // хук присвоения
        NULL                   // хук отображения
    );

    // Запрещаем регистрацию параметров с префиксом "rounding"
    MarkGUCPrefixReserved("rounding");
}

// Функция для округления числа с учетом GUC-переменной
PG_FUNCTION_INFO_V1(RoundWithThreshold);

Datum
RoundWithThreshold(PG_FUNCTION_ARGS)
{
    float8 number = PG_GETARG_FLOAT8(0);
    float8 threshold = rounding_threshold;
    float8 rounded;

    // Округление с учетом порога
    if (number - floor(number) >= threshold) {
        rounded = ceil(number);
    } else {
        rounded = floor(number);
    }

    PG_RETURN_FLOAT8(rounded);
}
