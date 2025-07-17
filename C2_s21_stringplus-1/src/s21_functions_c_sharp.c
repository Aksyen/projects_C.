#include "s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  // Определяем длину строки
  s21_size_t length = s21_strlen(str);

  // Выделяем память для новой строки
  char *upper_str = (char *)malloc((length + 1) * sizeof(char));
  if (upper_str == s21_NULL) {
    return s21_NULL;  // Ошибка выделения памяти
  }

  // Преобразуем символы в верхний регистр
  for (s21_size_t i = 0; i < length; i++) {
    // Проверяем, является ли символ английской маленькой буквой
    if (str[i] >= 'a' && str[i] <= 'z') {
      upper_str[i] = str[i] - ('a' - 'A');
    }
    // Проверяем, является ли символ русской маленькой буквой в UTF-8
    else if ((unsigned char)str[i] == 0xD0 &&
             (unsigned char)str[i + 1] >= 0xB0 &&
             (unsigned char)str[i + 1] <= 0xBF) {
      upper_str[i] = str[i];  // Первый байт остается без изменений
      upper_str[i + 1] = str[i + 1] - 0x20;  // Второй байт изменяется
      i++;  // Пропускаем следующий байт
    }
    // Проверяем, является ли символ русской маленькой буквой в UTF-8 (вторая
    // часть диапазона)
    else if ((unsigned char)str[i] == 0xD1 &&
             (unsigned char)str[i + 1] >= 0x80 &&
             (unsigned char)str[i + 1] <= 0x8F) {
      upper_str[i] = str[i] - 1;  // Первый байт изменяется
      upper_str[i + 1] = str[i + 1] + 0x20;  // Второй байт изменяется
      i++;  // Пропускаем следующий байт
    }
    // Остальные символы остаются без изменений
    else {
      upper_str[i] = str[i];
    }
  }
  upper_str[length] = '\0';  // Добавляем завершающий нулевой символ

  return upper_str;
}

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  // Определяем длину строки
  s21_size_t length = s21_strlen(str);

  // Выделяем память для новой строки
  char *lower_str = (char *)malloc((length + 1) * sizeof(char));
  if (lower_str == s21_NULL) {
    return s21_NULL;  // Ошибка выделения памяти
  }

  s21_size_t j = 0;  // Индекс для lower_str
  for (s21_size_t i = 0; i < length; i++, j++) {
    // Проверяем, является ли символ английской большой буквой
    if (str[i] >= 'A' && str[i] <= 'Z') {
      lower_str[j] = str[i] + ('a' - 'A');
    }
    // Остальные символы остаются без изменений
    else {
      lower_str[j] = str[i];
    }
  }
  lower_str[j] = '\0';  // Добавляем завершающий нулевой символ

  return lower_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == s21_NULL || str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index > src_len) {
    return s21_NULL;  // Если начальный индекс больше длины исходной строки
  }

  // Выделяем память для новой строки
  char *new_str = (char *)malloc((src_len + str_len + 1) * sizeof(char));
  if (new_str == s21_NULL) {
    return s21_NULL;  // Ошибка выделения памяти
  }

  // Копируем часть строки src до start_index
  s21_memcpy(new_str, src, start_index);

  // Копируем строку str
  s21_memcpy(new_str + start_index, str, str_len);

  // Копируем оставшуюся часть строки src после start_index
  s21_memcpy(new_str + start_index + str_len, src + start_index,
             src_len - start_index + 1);

  return new_str;
}

int s21_is_trim_char(char c, const char *trim_chars) {
  int result = 0;
  while (*trim_chars != '\0' && !result) {
    if (c == *trim_chars) {
      result = 1;
    }
    trim_chars++;
  }
  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL) {
    return s21_NULL;
  }
  if (trim_chars == s21_NULL || *trim_chars == '\0') {
    trim_chars = " ";
  }

  s21_size_t start = 0;
  s21_size_t end = s21_strlen(src);

  // Находим индекс первого символа, который не следует удалять
  while (start < end && s21_is_trim_char(src[start], trim_chars)) {
    start++;
  }

  // Находим индекс последнего символа, который не следует удалять
  while (end > start && s21_is_trim_char(src[end - 1], trim_chars)) {
    end--;
  }

  // Вычисляем новую длину строки после обрезки
  s21_size_t new_len = end - start;

  // Выделяем память для новой строки
  char *trimmed_str = (char *)malloc((new_len + 1) * sizeof(char));
  if (trimmed_str == s21_NULL) {
    return s21_NULL;  // Ошибка выделения памяти
  }

  // Копируем обрезанную часть строки
  s21_strncpy(trimmed_str, src + start, new_len);
  trimmed_str[new_len] = '\0';  // Добавляем завершающий нулевой символ

  return trimmed_str;
}