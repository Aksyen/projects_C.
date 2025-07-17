#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  // Преобразуем указатель s в указатель на тип unsigned char,

  const unsigned char *ptr = (const unsigned char *)str;

  // Преобразуем c в unsigned char, так как будем сравнивать
  // каждый байт в блоке памяти с этим значением.
  unsigned char ch = (unsigned char)c;

  // Временная переменная для хранения результата.
  void *result = s21_NULL;
  int flag_stop = 1;

  // Проходим по блоке памяти длиной n байт.
  for (s21_size_t i = 0; i < n && flag_stop; i++) {
    // Если текущий байт равен заданному символу,
    // сохраняем указатель на этот байт в result и прерываем цикл.
    if (ptr[i] == ch) {
      result = (void *)(ptr + i);
      flag_stop = 0;
    }
  }

  // Возвращаем результат.
  return result;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  const unsigned char *p1 = (const unsigned char *)str1;
  const unsigned char *p2 = (const unsigned char *)str2;
  int result = 0;
  int flag_stop = 1;
  for (s21_size_t i = 0; i < n && flag_stop; i++) {
    if (p1[i] != p2[i]) {
      result = p1[i] - p2[i];
      flag_stop = 0;
    }
  }
  //Если найдены различия, функция возвращает разницу между байтами двух блоков
  //памяти. Если различий нет, возвращает 0.

  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  // Приводим указатели к типу unsigned char *
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  // Копируем n байт из src в dest
  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  // Возвращаем указатель на dest
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  // Приводим указатель к типу unsigned char *
  unsigned char *p = (unsigned char *)str;

  // Преобразуем int c к типу unsigned char
  unsigned char value = (unsigned char)c;

  // Заполняем первые n байт значением value
  for (s21_size_t i = 0; i < n; i++) {
    p[i] = value;
  }

  // Возвращаем указатель на str
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  // Находим конец строки dest
  char *d = dest;
  while (*d != '\0') {
    d++;
  }

  // Копируем до n символов из src в конец dest
  int flag_stop = 1;
  s21_size_t i;
  for (i = 0; i < n && flag_stop; i++) {
    if (src[i] == '\0') {
      flag_stop = 0;
      i--;
    } else
      d[i] = src[i];
  }

  // Добавляем нулевой символ в конец dest
  d[i] = '\0';

  return dest;
}

char *s21_strchr(const char *str, int c) {
  // Преобразуем int к char, так как str состоит из символов char
  char ch = (char)c;
  char *ptr = s21_NULL;
  int flag_stop = 1;

  // Проходим по строке, пока не найдем символ или не дойдем до конца строки
  while (*str != '\0' && flag_stop) {
    if (*str == ch) {
      // Возвращаем указатель на найденный символ
      ptr = (char *)str;
      flag_stop = 0;
    }
    str++;
  }

  // Если символ не найден, проверяем, равен ли он нулевому символу
  if (ptr == s21_NULL && ch == '\0') {
    ptr = (char *)str;
  }

  // Если символ не найден, возвращаем NULL
  return ptr;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      return (unsigned char)str1[i] - (unsigned char)str2[i];
    }
  }
  // Если строки равны до n символов, возвращаем 0
  return 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;

  // Копируем до n символов или пока не достигнем конца src
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  // Если достигли конца src до завершения n, заполняем оставшуюся часть dest
  // нулями
  while (i < n) {
    dest[i] = '\0';
    i++;
  }

  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *p1;
  const char *p2;
  s21_size_t result;
  int flag_stop = 1;
  for (p1 = str1; *p1 != '\0' && flag_stop; p1++) {
    for (p2 = str2; *p2 != '\0' && flag_stop; p2++) {
      if (*p1 == *p2) {
        result =
            p1 - str1;  // Возвращаем количество символов до первого совпадения
        flag_stop = 0;
      }
    }
  }
  if (flag_stop) {
    result = p1 - str1;
  }

  return result;  // Если нет совпадений, возвращаем длину всей строки str1
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; str[len]; len++)
    ;
  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  // Проходим по каждому символу строки str1
  char *ptr = s21_NULL;
  int flag_stop = 1;
  while (*str1 && flag_stop) {
    // Проходим по каждому символу строки str2
    const char *s2 = str2;
    while (*s2 && flag_stop) {
      // Если текущий символ из str1 равен текущему символу из str2
      if (*str1 == *s2) {
        // Возвращаем указатель на первое вхождение
        ptr = (char *)str1;
        flag_stop = 0;
      }
      s2++;
    }
    str1++;
  }
  // Если символы не найдены, возвращаем NULL
  return ptr;
}

char *s21_strrchr(const char *str, int c) {
  const char *last_occurrence =
      s21_NULL;  // Переменная для хранения указателя на последнее вхождение
  char ch = (char)c;  // Преобразуем c в char для сравнения

  while (*str) {
    if (*str == ch) {
      last_occurrence = str;  // Обновляем последний указатель на вхождение
    }
    str++;
  }

  // Проверяем последний символ строки (в случае, если искомый символ равен
  // '\0')
  if (ch == '\0') {
    last_occurrence =
        str;  // Возвращаем указатель на нулевой символ (конец строки)
  }

  return (char *)last_occurrence;  // Приводим указатель к типу char *
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  int flag_stop = 1;
  if (*needle == '\0') {
    // Если needle пустая строка, возвращаем указатель на начало haystack
    result = (char *)haystack;
    flag_stop = 0;
  }

  while (*haystack && flag_stop) {
    const char *h = haystack;
    const char *n = needle;

    // Сравниваем подстроки
    while (*h && *n && *h == *n) {
      h++;
      n++;
    }

    // Если needle полностью совпала с частью haystack
    if (*n == '\0') {
      result = (char *)haystack;
      flag_stop = 0;
    }

    haystack++;
  }

  // needle не найдена в haystack
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *s21_saveptr;  // Глобальная переменная для сохранения позиции
  // Если str не равно NULL, начинаем новую строку
  if (str != s21_NULL) {
    s21_saveptr = str;
  }

  char *token = s21_NULL;

  if (s21_saveptr != s21_NULL) {
    // Пропускаем начальные разделители
    char *start = s21_saveptr;
    while (*start && s21_strchr(delim, *start)) {
      start++;
    }

    if (*start != '\0') {
      token = start;

      // Ищем конец токена
      while (*start && !s21_strchr(delim, *start)) {
        start++;
      }

      // Если достигли конца строки, устанавливаем указатель сохранения в NULL
      if (*start == '\0') {
        s21_saveptr = s21_NULL;
      } else {
        // Заменяем разделитель на нулевой символ
        *start = '\0';
        // Сохраняем указатель на следующий токен
        s21_saveptr = start + 1;
      }
    }
  }

  return token;
}
