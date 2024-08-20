-- Создание функции для перевода Цельсия в Фаренгейты
CREATE FUNCTION cels_to_fahr(double precision)
RETURNS double precision
AS 'MODULE_PATHNAME', 'CelsToFahr'
LANGUAGE C STRICT;

-- Создание функции для перевода Фаренгейта в Цельсий
CREATE FUNCTION fahr_to_cels(double precision)
RETURNS double precision
AS 'MODULE_PATHNAME', 'FahrToCels'
LANGUAGE C STRICT;

-- Создание функции для округления числа с учетом GUC-переменной
CREATE FUNCTION round_with_threshold(double precision)
RETURNS double precision
AS 'MODULE_PATHNAME', 'RoundWithThreshold'
LANGUAGE C STRICT;